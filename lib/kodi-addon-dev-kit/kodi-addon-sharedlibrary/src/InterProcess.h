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
#include "FunctionTables.h"
#include "kodi/addon.api2/internal/libKODI_addon_Internal.hpp"

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

// namespace AddOnLIB
// {
// namespace V2
// {
// extern "C"
// {

  class CKODIAddon_InterProcess
  {
  public:
    CKODIAddon_InterProcess();
    virtual ~CKODIAddon_InterProcess();

    KODI_HANDLE Init(int argc, char *argv[], addon_properties* props);
    KODI_HANDLE InitThread();
    KODI_HANDLE InitLibAddon(void* hdl);
    int         Finalize(KODI_HANDLE handle);
    void        Log(KODI_HANDLE handle, const addon_log loglevel, const char* string);

    void*         m_Handle;
    CB_AddOnLib*  m_Callbacks;

  protected:
    _register_level*  KODI_register;
    _unregister_me*   KODI_unregister;

  private:
    void*         m_libKODI_addon;
    struct cb_array
    {
      const char* libPath;
    };
  };

// }; /* extern "C" */
// }; /* namespace V2 */
// }; /* namespace AddOnLIB */
