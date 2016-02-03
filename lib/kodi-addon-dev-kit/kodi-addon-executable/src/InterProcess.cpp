/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "InterProcess.h"
#include "RequestPacket.h"
#include "ResponsePacket.h"

#include <thread>

#include <stdio.h>
#include <signal.h>
#include <p8-platform/util/StringUtils.h>
#include <p8-platform/util/timeutils.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif

#if (defined TARGET_WINDOWS)
#include <process.h>
#elif (defined TARGET_POSIX)
#include <pthread.h>
#endif

using namespace P8PLATFORM;

std::thread::id main_thread_id = std::this_thread::get_id();

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Class constructors / destructors
|
********************************************************************************
*/

CKODIAddon_InterProcess::CKODIAddon_InterProcess()
 : m_KodiAPILevel(2),
   m_socket(NULL),
   m_LoggedIn(false),
   m_sharedMemAvailable(false),
   m_parent(NULL)
{
  // Set console as default log out if not connected to Kodi
  Log = &Log_Console;
}

CKODIAddon_InterProcess::CKODIAddon_InterProcess(CKODIAddon_InterProcess *parent)
 : m_KodiAPILevel(2),
   m_socket(NULL),
   m_LoggedIn(false),
   m_sharedMemAvailable(false),
   m_parent(parent)
{
}

CKODIAddon_InterProcess::~CKODIAddon_InterProcess()
{
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Group for basic API connection functions called from add-on
|
********************************************************************************
*/

bool CKODIAddon_InterProcess::Connect(const std::string &strHostname)
{
  Disconnect();

  m_hostname        = strHostname;
  uint64_t iNow     = GetTimeMs();
  uint64_t iTarget  = iNow + KODI_API_ConnectionTimeout * 1000;

  if (!m_socket)
    m_socket = new CTcpConnection(m_hostname.c_str(), KODI_API_ConnectionPort);

  while (!m_socket->IsOpen() && iNow < iTarget)
  {
    if (!m_socket->Open(iTarget - iNow))
      CEvent::Sleep(100);
    iNow = GetTimeMs();
  }

  if (!m_socket->IsOpen())
  {
    KODI_API_lasterror = API_ERR_CONNECTION;
    return false;
  }

  return true;
}

void CKODIAddon_InterProcess::Disconnect()
{
  StopThread();

  Log = Log_Console;
  if (m_socket)
  {
    if (m_socket->IsOpen())
      m_socket->Close();

    delete m_socket;
    m_socket = NULL;
  }
}

bool CKODIAddon_InterProcess::Init(addon_properties* props, bool initialLogin)
{
  try
  {
    if (!props)
      throw API_ERR_BUFFER;
    
    CLockObject lock(m_callMutex);
  
    memcpy(&m_props, props, sizeof(addon_properties));

    bool isSubThread = false;
    uint64_t pid = GetThreadId();
    CRequestPacket vrp(KODICall_LoginVerify);
    vrp.push(API_UINT32_T, &KODI_API_Level);
    vrp.push(API_UINT64_T, &pid);
    vrp.push(API_BOOLEAN,  &m_props.is_independent);
    vrp.push(API_STRING,    m_props.addon_name);
    vrp.push(API_STRING,    KODI_API_Version);
    vrp.push(API_BOOLEAN,  &isSubThread);
    vrp.push(API_BOOLEAN,  &m_props.use_net_only);
   
    // read welcome
    std::unique_ptr<CResponsePacket> vresp(ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_COMM;

    char* str;
    uint8_t retErr;
    int sharedMemAvailable;
    vresp->pop(API_UINT32_T, &retErr);
    vresp->pop(API_INT,      &m_randomConnectionNumber);
    vresp->pop(API_UINT32_T, &m_KodiAPILevel);
    m_kodiName    = (char*)vresp->pop(API_STRING, &str);
    m_kodiVersion = (char*)vresp->pop(API_STRING, &str);
    vresp->pop(API_INT,      &sharedMemAvailable);
    vresp->pop(API_INT,      &m_sharedMem_Size);
    m_sharedMemAvailable = (sharedMemAvailable > 0) ? true : false;
  
    if (retErr != API_SUCCESS)
      throw API_ERR_UNKNOWN;

    m_LoggedIn = true;

    if (m_KodiAPILevel < KODI_API_Level)
      throw API_ERR_REQUEST;

    if (m_sharedMemAvailable && CreateSharedMemory())
      SetFunctions_SharedMem();
    else
      SetFunctions_LocalNet();

    if (initialLogin)
      KodiAPI_Log(this, LOG_INFO, "Logged in to '%s' Version: '%s' with protocol version '%d'",
                              m_kodiName.c_str(), m_kodiVersion.c_str(), m_KodiAPILevel);
    CreateThread();
  }
  catch (KODI_API_Errortype error)
  {
    Disconnect();
    KODI_API_lasterror = error;
    return false;
  }

  return true;
}

void CKODIAddon_InterProcess::Finalize()
{
  try
  {
    CLockObject lock(m_callMutex);

    Log = Log_Console;

    m_LoggedIn = false;
    if (m_sharedMemAvailable)
      Unlock_KodiToAddon_Addon();
    StopThread();
  
    CRequestPacket vrp(KODICall_Logout);
    auto vresp(ReadResult(&vrp));
    if (!vresp)
      throw "failed to logout Kodi";

    if (m_sharedMemAvailable)
      DestroySharedMemory();

    uint32_t retCode;
    vresp->pop(API_UINT32_T, &retCode);
    if (retCode != API_SUCCESS)
    {
      throw StringUtils::Format("Addon received error after logout to Kodi: %s", errorTranslator[retCode].errorName).c_str();
    }
  }
  catch (const char * str)
  {
    Log_Console(this, LOG_ERROR, StringUtils::Format("Binary AddOn: %s - %s", __FUNCTION__, str).c_str());
    Disconnect();
  }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Group to handle function calls from Kodi over shared memory or network
|
********************************************************************************
*/

void *CKODIAddon_InterProcess::Process(void)
{
  std::unique_ptr<CResponsePacket> vresp;

  while (!IsStopped() && m_LoggedIn)
  {
    if (m_sharedMem_KodiToAddon)
    {
      if (Lock_KodiToAddon_Addon())
      {
        if (IsStopped() || !m_sharedMem_KodiToAddon || !m_LoggedIn)
          break;

        switch (m_sharedMem_KodiToAddon->message.messageId)
        {
          case KODICall_Ping:
          {
            m_sharedMem_KodiToAddon->message.retValue.bool_par = true;
            break;
          }
          default:
          {
            break;
          }
        }

        Unlock_KodiToAddon_Kodi();
      }
    }
    else
    {
      // try to reconnect
      if (m_connectionLost && !TryReconnect())
      {
        Sleep(1000);
        continue;
      }

      // if there's anything in the buffer, read it
      if ((vresp = ReadMessage(5)) == NULL)
      {
        Sleep(5);
        continue;
      }
      
      if (vresp->getChannelID() == m_randomConnectionNumber)
      {
        int requestID = vresp->getRequestID();
        switch (requestID)
        {
          case KODICall_Ping:
          {
            Ping_LocalNet(this);
            break;
          }
          default:
          {
            KodiAPI_Log(this, LOG_ERROR, "Binary AddOn: Rxd a unknown response packet '%i' on thread %lu !!", 
                          requestID, vresp->getChannelID());
            break;
          }
        }
      }
    }
  }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Group to handle function calls from add-on over the TCP interface
|
********************************************************************************
*/
  
void CKODIAddon_InterProcess::SetFunctions_LocalNet()
{
  Ping            = Ping_LocalNet;
  Log             = Log_LocalNet;
  InitThread      = InitThread_LocalNet;
  FinalizeThread  = FinalizeThread_LocalNet;
}

bool CKODIAddon_InterProcess::Ping_LocalNet(CKODIAddon_InterProcess *session)
{
  try
  {
    CRequestPacket vrp(KODICall_Ping);

    auto vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw API_ERR_COMM;

    uint32_t retCode;
    vresp->pop(API_UINT32_T, &retCode);
    if (retCode == API_SUCCESS)
      return true;
    else
      throw retCode;
  }
  catch (KODI_API_Errortype error)
  {
    session->Disconnect();
    KODI_API_lasterror = error;
  }

  return false;
}

void CKODIAddon_InterProcess::Log_LocalNet(CKODIAddon_InterProcess *session, const addon_log loglevel, const char* text)
{
  try
  {
    uint32_t level = loglevel;
    CRequestPacket vrp(KODICall_Log);
    vrp.push(API_UINT32_T, &level);
    vrp.push(API_STRING, text);
    
    CLockObject lock(session->m_callMutex);

    std::unique_ptr<CResponsePacket> vresp(session->ReadResult(&vrp));
    if (!vresp)
      throw "Failed to send log entry in Kodi";

    uint32_t retCode;
    vresp->pop(API_UINT32_T, &retCode);
    if (retCode != API_SUCCESS)
    {
      throw StringUtils::Format("Addon received error after send of log entry to Kodi: %s", 
                                  errorTranslator[retCode].errorName).c_str();
    }
  }
  catch (const char * str)
  {
    Log_Console(session, LOG_ERROR, StringUtils::Format("Binary AddOn: %s", str).c_str());
    session->Disconnect();
  }
}

CKODIAddon_InterProcess* CKODIAddon_InterProcess::InitThread_LocalNet(CKODIAddon_InterProcess *session)
{
  try
  {
    if (IsMainThread())
      throw "Not possible to call 'KodiAPI_InitThread' from main thread! Add-on becomes closed!";

    int randomConnectionNumber = std::rand();
    
    CLockObject lock(interProcess.m_callMutex);

    CKODIAddon_InterProcess *newProcess = new CKODIAddon_InterProcess(&interProcess);
    newProcess->Connect(interProcess.m_hostname.c_str());
    
    bool isSubThread = true;
    uint64_t pid = GetThreadId();
    CRequestPacket vrp(KODICall_LoginVerify);
    vrp.push(API_UINT32_T, &KODI_API_Level);
    vrp.push(API_UINT64_T, &pid);
    vrp.push(API_BOOLEAN,  &interProcess.m_props.is_independent);
    std::string name = StringUtils::Format("%s - Subthread '%lu'", interProcess.m_props.addon_name, pid);
    vrp.push(API_STRING,    name.c_str());
    vrp.push(API_STRING,    KODI_API_Version);
    vrp.push(API_BOOLEAN,  &isSubThread);
    vrp.push(API_BOOLEAN,  &interProcess.m_props.use_net_only);
   
    // read welcome
    std::unique_ptr<CResponsePacket> vresp(newProcess->ReadResult(&vrp));
    if (!vresp)
      throw "failed to read greeting from Kodi for subthread";

    char* str;
    uint32_t retCode;
    int sharedMemAvailable;
    vresp->pop(API_UINT32_T, &retCode);
    vresp->pop(API_INT,      &newProcess->m_randomConnectionNumber);
    vresp->pop(API_UINT32_T, &newProcess->m_KodiAPILevel);
    newProcess->m_kodiName    = (char*)vresp->pop(API_STRING, &str);
    newProcess->m_kodiVersion = (char*)vresp->pop(API_STRING, &str);
    vresp->pop(API_INT,      &sharedMemAvailable);
    vresp->pop(API_INT,      &newProcess->m_sharedMem_Size);
    newProcess->m_sharedMemAvailable = (sharedMemAvailable > 0) ? true : false;

    if (retCode != API_SUCCESS)
    {
      throw StringUtils::Format("Addon received error after send of log entry to Kodi: %s", 
                                  errorTranslator[retCode].errorName).c_str();
    }
    
    newProcess->SetFunctions_LocalNet();
    newProcess->CreateThread(false);

    return newProcess;
  }
  catch (const char * str)
  {
    KodiAPI_Log(&interProcess, LOG_FATAL, "Binary AddOn: %s", str);
    interProcess.Disconnect();
    exit(1);
  }
  return NULL;
}

int CKODIAddon_InterProcess::FinalizeThread_LocalNet(CKODIAddon_InterProcess* thread)
{
  thread->Ping(static_cast<CKODIAddon_InterProcess*>(thread)); // Ping to make sure last call was with no data
  thread->Finalize();
  thread->Disconnect();
  return API_SUCCESS;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Group to handle function calls from add-on over the shared memory
|
********************************************************************************
*/

void CKODIAddon_InterProcess::SetFunctions_SharedMem()
{
  Ping            = Ping_SharedMem;
  Log             = Log_SharedMem;
  InitThread      = InitThread_SharedMem;
  FinalizeThread  = FinalizeThread_SharedMem;
}

bool CKODIAddon_InterProcess::Ping_SharedMem(CKODIAddon_InterProcess *session)
{
  try
  {
    CLockObject lock(session->m_callMutex);

    session->m_sharedMem_AddonToKodi->message.messageId         = KODICall_Ping;
    session->m_sharedMem_AddonToKodi->message.retValue.bool_par = false;
    session->Unlock_AddonToKodi_Kodi();
    session->Lock_AddonToKodi_Addon();
    return session->m_sharedMem_AddonToKodi->message.retValue.bool_par;
  }
  catch (...)
  {
    KodiAPI_Log(session, LOG_FATAL, "Binary AddOn: %s - Undefined exception", __FUNCTION__); // Show with normal output to prevent possible dead loops
    session->Disconnect();
  }
  return false;
}

void CKODIAddon_InterProcess::Log_SharedMem(CKODIAddon_InterProcess *session, const addon_log loglevel, const char* text)
{
  try
  {
    CLockObject lock(session->m_callMutex);

    session->m_sharedMem_AddonToKodi->message.messageId = KODICall_Log;
    session->m_sharedMem_AddonToKodi->message.value1.int_par = loglevel;
    strncpy((char*)session->m_sharedMem_AddonToKodi->message.data, text, session->m_sharedMem_Size-sizeof(KodiAPI_ShareData));
    session->Unlock_AddonToKodi_Kodi();
    session->Lock_AddonToKodi_Addon();
  }
  catch (...)
  {
    Log_Console(session, LOG_ERROR, StringUtils::Format("Binary AddOn: %s - Undefined exception", __FUNCTION__).c_str());
    session->Disconnect();
  }
}

CKODIAddon_InterProcess* CKODIAddon_InterProcess::InitThread_SharedMem(CKODIAddon_InterProcess *session)
{
  try
  {
    if (IsMainThread())
      throw "Not possible to call 'KodiAPI_InitThread' from main thread! Add-on becomes closed!";

    int randomConnectionNumber = std::rand();
    
    CLockObject lock(interProcess.m_callMutex);
    
    interProcess.m_sharedMem_AddonToKodi->message.messageId          = KODICall_CreateSubThread;
    interProcess.m_sharedMem_AddonToKodi->message.retValue.bool_par  = false;
    interProcess.m_sharedMem_AddonToKodi->message.value1.int_par     = randomConnectionNumber;

    interProcess.Unlock_AddonToKodi_Kodi();
    interProcess.Lock_AddonToKodi_Addon();

    int retCode = interProcess.m_sharedMem_AddonToKodi->message.retValue.int_par;
    if (retCode != API_SUCCESS)
    {
      throw StringUtils::Format("No sub thread from Kodi for Add-on created! Error: %s", 
                                  errorTranslator[retCode].errorName).c_str();
    }

    CKODIAddon_InterProcess *newProcess = new CKODIAddon_InterProcess(&interProcess);
    newProcess->m_LoggedIn = true;
    newProcess->m_randomConnectionNumber = randomConnectionNumber;
    if (newProcess->CreateSharedMemory())
      newProcess->SetFunctions_SharedMem();
    else
      throw "Creation of shared Memory for new thread failed!";

    newProcess->CreateThread(false);
    return newProcess;    
  }
  catch (const char * str)
  {
    KodiAPI_Log(&interProcess, LOG_FATAL, "Binary AddOn: %s", str);
    interProcess.Disconnect();
    exit(1);
  }
  return NULL;
}

int CKODIAddon_InterProcess::FinalizeThread_SharedMem(CKODIAddon_InterProcess* thread)
{
  try
  {
    CLockObject lock(interProcess.m_callMutex);
        
    interProcess.m_sharedMem_AddonToKodi->message.messageId          = KODICall_DeleteSubThread;
    interProcess.m_sharedMem_AddonToKodi->message.retValue.bool_par  = false;
    interProcess.m_sharedMem_AddonToKodi->message.value1.int_par     = thread->m_randomConnectionNumber;
    interProcess.Unlock_AddonToKodi_Kodi();
    interProcess.Lock_AddonToKodi_Addon();

    thread->m_LoggedIn = false;
    thread->Unlock_KodiToAddon_Addon();
    int retCode = interProcess.m_sharedMem_AddonToKodi->message.retValue.int_par;
    if (retCode != API_SUCCESS)
    {
      throw StringUtils::Format("Sub thread from Kodi for Add-on failed to stop! Error: %s", 
                                  errorTranslator[retCode].errorName).c_str();
    }

    return API_SUCCESS;    
  }
  catch (const char * str)
  {
    KodiAPI_Log(&interProcess, LOG_FATAL, "Binary AddOn: %s", str);
  }
  return API_ERR_UNKNOWN;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Fallback API functions
|
********************************************************************************
*/

void CKODIAddon_InterProcess::Log_Console(CKODIAddon_InterProcess *session, const addon_log loglevel, const char* text)
{
  fprintf(stderr, "LOG: Level %02u : %s\n", loglevel, text);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Private class functions
|
********************************************************************************
*/

bool CKODIAddon_InterProcess::IsConnected()
{
  return m_socket && m_socket->IsOpen();
}

bool CKODIAddon_InterProcess::TryReconnect()
{
  // @todo
  return false;
}

std::unique_ptr<CResponsePacket> CKODIAddon_InterProcess::ReadMessage(int iInitialTimeout /*= 10000*/,
                                                                    int iDatapacketTimeout /*= 10000*/)
{
  uint32_t          channelID       = 0;
  uint32_t          userDataLength  = 0;
  uint8_t*          userData        = NULL;
  CResponsePacket*  vresp           = NULL;

  CLockObject lock(m_readMutex);

  if (!readData((uint8_t*)&channelID, sizeof(uint32_t), iInitialTimeout))
    return NULL;

  // Data was read
  channelID = ntohl(channelID);
  switch (channelID)
  {
    case KODIPacket_Status:
    case KODIPacket_RequestedResponse:
    {
      vresp = new CResponsePacket();

      if (!readData(vresp->getHeader(), vresp->getHeaderLength(), iDatapacketTimeout))
      {
        delete vresp;
        KodiAPI_Log(this, LOG_ERROR, "Binary AddOn: %s - lost sync on response packet", __FUNCTION__);
        Disconnect();
        return NULL;
      }
      vresp->popHeader();
      userDataLength = vresp->getUserDataLength();

      userData = NULL;
      if (userDataLength > 0)
      {
        userData = (uint8_t*)malloc(userDataLength);
        if (!userData)
          return NULL;

        if (!readData(userData, userDataLength, iDatapacketTimeout))
        {
          free(userData);
          delete vresp;
          KodiAPI_Log(this, LOG_ERROR, "Binary AddOn: %s - lost sync on additional response packet", __FUNCTION__);
          Disconnect();
          return NULL;
        }
      }

      if (channelID == KODIPacket_Status)
        vresp->setStatus(userData, userDataLength);
      else
        vresp->setResponse(userData, userDataLength);
    }
  }

  return std::unique_ptr<CResponsePacket>(vresp);
}

bool CKODIAddon_InterProcess::readData(uint8_t* buffer, int totalBytes, int timeout)
{
  int bytesRead = m_socket->Read(buffer, totalBytes, timeout);
  if (bytesRead == totalBytes)
  {
    return true;
  }
  else if (m_socket->GetErrorNumber() == ETIMEDOUT && bytesRead > 0)
  {
    // we did read something. try to finish the read
    bytesRead += m_socket->Read(buffer+bytesRead, totalBytes-bytesRead, timeout);
    if (bytesRead == totalBytes)
      return true;
  }
  else if (m_socket->GetErrorNumber() == ETIMEDOUT)
  {
    return false;
  }

  Disconnect();
  return false;
}

std::unique_ptr<CResponsePacket> CKODIAddon_InterProcess::ReadResult(CRequestPacket* vrp)
{
  if (!TransmitMessage(vrp))
  {
    Disconnect();
    return NULL;
  }

  std::unique_ptr<CResponsePacket> pkt;

  while ((pkt = ReadMessage(10000, 10000)))
  {
    /* Discard everything other as response packets until it is received */
    if (pkt->getChannelID() == KODIPacket_RequestedResponse && pkt->getRequestID() == vrp->getSerial())
    {
      return pkt;
    }
  }

  Disconnect();
  return NULL;
}

bool CKODIAddon_InterProcess::ReadSuccess(CRequestPacket* vrp)
{
  std::unique_ptr<CResponsePacket> pkt;
  if ((pkt = ReadResult(vrp)) == NULL)
  {
    return false;
  }

  uint32_t retCode;
  pkt->pop(API_UINT32_T, &retCode);
  if (retCode != API_SUCCESS)
  {
    KodiAPI_Log(this, LOG_ERROR, "Binary AddOn: %s - failed with error code '%i': %s", __FUNCTION__, retCode, errorTranslator[retCode].errorName);
    return false;
  }
  return true;
}

bool CKODIAddon_InterProcess::TransmitMessage(CRequestPacket* vrp)
{
  if (!IsConnected())
    return false;

  ssize_t iWriteResult = m_socket->Write(vrp->getPtr(), vrp->getLen());
  if (iWriteResult != (ssize_t)vrp->getLen())
  {
    KodiAPI_Log(this, LOG_ERROR, "Binary AddOn: %s - Failed to write packet (%s), bytes written: %ld of total: %ld",
              __FUNCTION__, m_socket->GetError().c_str(), iWriteResult, vrp->getLen());
    return false;
  }
  return true;
}

bool CKODIAddon_InterProcess::IsMainThread()
{
  return (main_thread_id == std::this_thread::get_id()) ? true : false;
}

uint64_t CKODIAddon_InterProcess::GetThreadId()
{
#if (defined TARGET_WINDOWS)
  return (unit64_t)_getpid();
#elif (defined TARGET_POSIX)
  return (uint64_t)getpid();
#endif
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

