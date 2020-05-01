/*
 *  Copyright (C) 2010-2020 Team Kodi
 *  Copyright (C) 2010 Alwin Esch (Team Kodi)
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "addon.h"
#include "Settings.h"
#include "VNSIData.h"

ADDON_STATUS CPVRAddon::Create()
{
  if (!CVNSISettings::Get().Load())
  {
    kodi::Log(ADDON_LOG_ERROR, "%s: Failed to load addon settings", __func__);
    return ADDON_STATUS_UNKNOWN;
  }

  return ADDON_STATUS_OK;
}

ADDON_STATUS CPVRAddon::SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue)
{
  return CVNSISettings::Get().SetSetting(settingName, settingValue);
}

ADDON_STATUS CPVRAddon::CreateInstanceEx(int instanceType, std::string instanceID, KODI_HANDLE instance, KODI_HANDLE& addonInstance, const std::string &version)
{
  if (instanceType == ADDON_INSTANCE_PVR)
  {
    kodi::Log(ADDON_LOG_DEBUG, "Creating VDR VNSI PVR-Client");

    cVNSIData* client = nullptr;
    try
    {
      cVNSIData* client = new cVNSIData(*this, instance, version);
      if (client->Start(CVNSISettings::Get().GetHostname(), CVNSISettings::Get().GetPort(), nullptr, CVNSISettings::Get().GetWolMac()))
      {
        addonInstance = client;
        return ADDON_STATUS_OK;
      }
    }
    catch (std::exception e)
    {
      kodi::Log(ADDON_LOG_ERROR, "%s - %s", __FUNCTION__, e.what());
      delete client;
      return ADDON_STATUS_UNKNOWN;
    }
  }

  return ADDON_STATUS_UNKNOWN;
}

void CPVRAddon::DestroyInstance(int instanceType, std::string instanceID, KODI_HANDLE addonInstance)
{

}

ADDONCREATOR(CPVRAddon)
