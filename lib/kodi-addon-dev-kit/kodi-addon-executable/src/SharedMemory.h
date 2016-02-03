#pragma once
/*
 *      Copyright (C) 2010-2015 Team KODI
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

#include <string>

#define DEFAULT_SHARED_MEM_SIZE 2*1024*1024

class CBinaryAddonSharedMemoryPosix;
class CBinaryAddonSharedMemoryWindows;

class CBinaryAddonSharedMemory
{
public:
  CBinaryAddonSharedMemory(size_t size = DEFAULT_SHARED_MEM_SIZE);
  virtual ~CBinaryAddonSharedMemory();

  virtual bool CreateSharedMemory() = 0;
  virtual void DestroySharedMemory() = 0;

  virtual bool Lock_AddonToKodi_Addon() = 0;
  virtual void Unlock_AddonToKodi_Kodi() = 0;

  virtual bool Lock_KodiToAddon_Addon() = 0;
  virtual void Unlock_KodiToAddon_Kodi() = 0;
  virtual void Unlock_KodiToAddon_Addon() = 0;

private:
  friend class CBinaryAddonSharedMemoryPosix;
  friend class CBinaryAddonSharedMemoryWindows;
  friend class CKODIAddon_InterProcess;

  int                 m_randomConnectionNumber;
  size_t              m_sharedMem_Size;
  KodiAPI_ShareData*  m_sharedMem_AddonToKodi;
  KodiAPI_ShareData*  m_sharedMem_KodiToAddon;
};
