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
#include "kodi/addon.api2/AddonLib.h"

#include <string>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

extern "C" {
  
const int   KODI_API_ConnectionTimeout = 3;
const int   KODI_API_ConnectionPort    = 34687;

CKODIAddon_InterProcess interProcess;

KODI_HANDLE KodiAPI_Init(int argc, char *argv[], addon_properties* props)
{
  if (interProcess.Connect("127.0.0.1") && interProcess.Init(props, true))
    return (KODI_HANDLE)&interProcess;
  else
    return NULL;
}

KODI_HANDLE KodiAPI_InitThread()
{
  return (KODI_HANDLE)interProcess.InitThread(&interProcess);
}

KODI_HANDLE KodiAPI_InitLibAddon(void* hdl)
{
  KODI_API_lasterror = API_ERR_TYPE;
  return NULL;
}

int KodiAPI_Finalize(KODI_HANDLE handle)
{
  if (CKODIAddon_InterProcess::IsMainThread())
  {
    static_cast<CKODIAddon_InterProcess*>(handle)->Ping(static_cast<CKODIAddon_InterProcess*>(handle)); // Ping to make sure last call was with no data
    static_cast<CKODIAddon_InterProcess*>(handle)->Finalize();
    static_cast<CKODIAddon_InterProcess*>(handle)->Disconnect();
    return API_SUCCESS;
  }
  else
  {
    int ret = interProcess.FinalizeThread(static_cast<CKODIAddon_InterProcess*>(handle));
    delete static_cast<CKODIAddon_InterProcess*>(handle);
    return ret;
  }
}

void KodiAPI_Log(KODI_HANDLE handle, const addon_log loglevel, const char* format, ... )
{
  char buffer[16384];
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  static_cast<CKODIAddon_InterProcess*>(handle)->Log(static_cast<CKODIAddon_InterProcess*>(handle), loglevel, buffer);
}

} /* extern "C" */
