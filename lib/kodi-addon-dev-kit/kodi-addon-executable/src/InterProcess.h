#pragma once
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

#include "kodi/addon.api2/AddonLib.h"

#include <memory>
#include <string>
#include <p8-platform/sockets/tcp.h>
#include <p8-platform/threads/threads.h>
#if (defined TARGET_WINDOWS)
#  include "SharedMemoryWindows.h"
#elif (defined TARGET_POSIX)
#  include "SharedMemoryPosix.h"
#endif

#ifdef TARGET_WINDOWS
#include <windows.h>
#else
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __declspec
#define __declspec(X)
#endif
#endif

class CResponsePacket;
class CRequestPacket;

extern "C" {
  
class CKODIAddon_InterProcess
#if (defined TARGET_WINDOWS)
  : private CBinaryAddonSharedMemoryWindows,
#elif (defined TARGET_POSIX)
  : private CBinaryAddonSharedMemoryPosix,
#endif
    public P8PLATFORM::CThread
{
public:
  CKODIAddon_InterProcess();
  CKODIAddon_InterProcess(CKODIAddon_InterProcess *parent);
  ~CKODIAddon_InterProcess();

  static bool IsMainThread();
  static uint64_t GetThreadId();

  bool Connect(const std::string &strHostname);
  void Disconnect();

  bool Init(addon_properties* props, bool initialLogin = false);
  void Finalize();

  /*
   * Function pointers to set with for connection possible types
   */
  bool 
        (__cdecl* Ping)
              (CKODIAddon_InterProcess *session);

  void 
        (__cdecl* Log)
              (CKODIAddon_InterProcess *session, 
               const addon_log loglevel, 
               const char* text);

  CKODIAddon_InterProcess* 
        (__cdecl* InitThread)
              (CKODIAddon_InterProcess *session);

  int 
        (__cdecl* FinalizeThread)
              (CKODIAddon_InterProcess* thread);

protected:
  virtual void *Process(void);

private:
  /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  |
  | Group to handle function calls from add-on over the TCP interface
  |
  ******************************************************************************
  */

  void SetFunctions_LocalNet();

  //============================================================================
  /**
  * @brief Network Stream Function: KODICall_LoginVerify
  * 
  * Used  from  add-on  for  login to Kodi,  all  basic  parts  needed  for work 
  * between  Kodi and Add-on  becomes created, also if possible is  with  better
  * performce a shared memory interface created.
  * 
  * For more documentation see BinaryAddon.h on Kodi itself
  */
  static bool Ping_LocalNet(CKODIAddon_InterProcess *session);
  //----------------------------------------------------------------------------

  //============================================================================
  /**
  * @brief Network Stream Function: KODICall_Log
  * 
  * Used from add-on to send  Log message over TCP  stream connection in Kodi to
  * store there in Log file.
  * 
  * For more documentation see BinaryAddon.h on Kodi itself
  */
  static void Log_LocalNet(CKODIAddon_InterProcess *session, const addon_log loglevel, const char* text);
  //----------------------------------------------------------------------------

  //============================================================================
  /**
  * @brief 
  * 
  */
  static CKODIAddon_InterProcess* InitThread_LocalNet(CKODIAddon_InterProcess *session);
  //----------------------------------------------------------------------------
  
  //============================================================================
  /**
  * @brief 
  * 
  */
  static int FinalizeThread_LocalNet(CKODIAddon_InterProcess* thread);
  //----------------------------------------------------------------------------

  /*
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

  //--- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - ---
  
  /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  |
  | Group to handle function calls from add-on over the shared memory
  |
  ******************************************************************************
  */

  void SetFunctions_SharedMem();

  //============================================================================
  /**
  * @brief 
  * 
  */
  static bool Ping_SharedMem(CKODIAddon_InterProcess *session);
  //----------------------------------------------------------------------------

  //============================================================================
  /**
  * @brief 
  * 
  */
  static void Log_SharedMem(CKODIAddon_InterProcess *session, const addon_log loglevel, const char* text);
  //----------------------------------------------------------------------------
  
  //============================================================================
  /**
  * @brief 
  * 
  */
  static CKODIAddon_InterProcess* InitThread_SharedMem(CKODIAddon_InterProcess *session);
  //----------------------------------------------------------------------------
  
  //============================================================================
  /**
  * @brief 
  * 
  */
  static int FinalizeThread_SharedMem(CKODIAddon_InterProcess* thread);
  //----------------------------------------------------------------------------

  /*
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

  
  static void Log_Console(CKODIAddon_InterProcess *session, const addon_log loglevel, const char* text);

  std::unique_ptr<CResponsePacket> ReadResult(CRequestPacket* vrp);
  std::unique_ptr<CResponsePacket> ReadMessage(int iInitialTimeout = 10000, int iDatapacketTimeout = 10000);
  bool TransmitMessage(CRequestPacket* vrp);
  bool readData(uint8_t* buffer, int totalBytes, int timeout);
  
  bool IsConnected();
  bool TryReconnect();
  bool ReadSuccess(CRequestPacket* vrp);

  std::string                 m_name;
  uint32_t                    m_KodiAPILevel;
  std::string                 m_kodiName;
  std::string                 m_kodiVersion;
  bool                        m_LoggedIn;
  std::string                 m_hostname;
  
  P8PLATFORM::CMutex          m_callMutex;

  P8PLATFORM::CTcpConnection *m_socket;
  P8PLATFORM::CMutex          m_readMutex;
  bool                        m_connectionLost;
  bool                        m_sharedMemAvailable;
  CKODIAddon_InterProcess    *m_parent;
  addon_properties            m_props;
};

extern CKODIAddon_InterProcess interProcess;

} /* extern "C" */
