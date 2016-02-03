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

#include <stdio.h>

#ifdef _WIN32                   // windows
  #ifndef _SSIZE_T_DEFINED
    typedef intptr_t      ssize_t;
    #define _SSIZE_T_DEFINED
  #endif // !_SSIZE_T_DEFINED

  #if defined(BUILD_KODI_ADDON)
      #include "platform/windows/dlfcn-win32.h"
  #else
      #include "dlfcn-win32.h"
  #endif
#else
  #include <dlfcn.h>              // linux+osx
#endif

// namespace AddOnLIB
// {
// namespace V2
// {
extern "C"
{
  
CKODIAddon_InterProcess interProcess;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Class constructors / destructors
|
********************************************************************************
*/

CKODIAddon_InterProcess::CKODIAddon_InterProcess()
  : m_libKODI_addon(NULL),
    m_Handle(NULL)
{

}
    
CKODIAddon_InterProcess::~CKODIAddon_InterProcess()
{
  Finalize();
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

//-- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - --

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
|
| Basic library connection to kodi
|
********************************************************************************
*/

KODI_HANDLE Init(int argc, char *argv[], addon_properties* props)
{
  
}

KODI_HANDLE InitThread()
{
  
}

KODI_HANDLE InitLibAddon(void* hdl)
{
  
}

int Finalize(KODI_HANDLE handle)
{
  
}

void Log(KODI_HANDLE handle, const addon_log loglevel, const char* string)
{
  
}

    

bool CKODIAddon_InterProcess::InitLibAddon(void *Handle)
{
  m_Handle = Handle;

  m_libKODI_addon = dlopen(NULL, RTLD_LAZY);
  if (m_libKODI_addon == NULL)
  {
    fprintf(stderr, "Unable to load %s\n", dlerror());
    return false;
  }

  KODI_register = (_register_level*)
    dlsym(m_libKODI_addon, "ADDONLIB_V2_register_level");
  if (KODI_register == NULL)
  {
    fprintf(stderr, "Unable to assign function %s\n", dlerror());
    return false;
  }

  KODI_unregister = (_unregister_me*)
    dlsym(m_libKODI_addon, "AddOnLib_UnRegister");
  if (KODI_unregister == NULL)
  {
    fprintf(stderr, "Unable to assign function %s\n", dlerror());
    return false;
  }
    
  m_Callbacks = KODI_register(m_Handle, 2);
  return m_Callbacks != NULL;
}   
  
void CKODIAddon_InterProcess::Finalize()
{   
  if (m_libKODI_addon)
  {
    KODI_unregister(m_Handle, m_Callbacks);
    dlclose(m_libKODI_addon);
    m_libKODI_addon = NULL;
  }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

}; /* extern "C" */
// }; /* namespace V2 */
// }; /* namespace AddOnLIB */
