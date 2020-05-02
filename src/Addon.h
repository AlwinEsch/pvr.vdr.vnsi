/*
 *  Copyright (C) 2010-2020 Team Kodi
 *  Copyright (C) 2010 Alwin Esch (Team Kodi)
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <kodi/AddonBase.h>
#include <unordered_map>

class CVNSIClientInstance;

class ATTRIBUTE_HIDDEN CPVRAddon : public kodi::addon::CAddonBase
{
public:
  CPVRAddon() = default;

  ADDON_STATUS Create() override;
  ADDON_STATUS SetSetting(const std::string& settingName,
                          const kodi::CSettingValue& settingValue) override;
  ADDON_STATUS CreateInstanceEx(int instanceType,
                                std::string instanceID,
                                KODI_HANDLE instance,
                                KODI_HANDLE& addonInstance,
                                const std::string& version) override;
  void DestroyInstance(int instanceType,
                       std::string instanceID,
                       KODI_HANDLE addonInstance) override;

private:
  std::unordered_map<std::string, CVNSIClientInstance*> m_usedInstances;
};
