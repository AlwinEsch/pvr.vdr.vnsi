/*
 *  Copyright (C) 2010-2020 Team Kodi
 *  Copyright (C) 2010 Alwin Esch (Team Kodi)
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "Session.h"

#include <map>
#include <string>

#include <kodi/addon-instance/PVRClient.h>

class CPVRAddon;
class cResponsePacket;
class cRequestPacket;
class cVNSIDemux;
class cVNSIRecording;

class ATTRIBUTE_HIDDEN CVNSIClientInstance : public kodi::addon::CInstancePVRClient,
                                             public cVNSISession,
                                             public P8PLATFORM::CThread
{
public:
  CVNSIClientInstance(const CPVRAddon& base, KODI_HANDLE instance, const std::string& kodiVersion);
  ~CVNSIClientInstance() override;

  bool Start(const std::string& hostname,
             int port,
             const char* name = nullptr,
             const std::string& mac = "");

  PVR_ERROR GetCapabilities(kodi::addon::PVRCapabilities& capabilities) override;

  std::string GetBackendName() override;
  std::string GetBackendVersion() override;
  std::string GetBackendHostname() override;
  std::string GetConnectionString() override;
  PVR_ERROR GetDriveSpace(uint64_t& total, uint64_t& used) override;
  PVR_ERROR CallSettingsMenuHook(const kodi::addon::PVRMenuhook& menuhook) override;
  PVR_ERROR OpenDialogChannelScan() override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  void OnSystemSleep() override;
  void OnSystemWake() override;
  void OnPowerSavingActivated() override;
  void OnPowerSavingDeactivated() override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  int GetChannelsAmount() override;
  PVR_ERROR GetChannels(bool radio, std::vector<kodi::addon::PVRChannel>& channels) override;
  PVR_ERROR GetSignalStatus(int channelUid, kodi::addon::PVRSignalStatus& signalStatus) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  int GetChannelGroupsAmount() override;
  PVR_ERROR GetChannelGroups(bool radio,
                             std::vector<kodi::addon::PVRChannelGroup>& groups) override;
  PVR_ERROR GetChannelGroupMembers(
      const kodi::addon::PVRChannelGroup& group,
      std::vector<kodi::addon::PVRChannelGroupMember>& members) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  PVR_ERROR GetEPGForChannel(int channelUid,
                             time_t start,
                             time_t end,
                             std::vector<kodi::addon::PVREPGTag>& epg) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  PVR_ERROR GetTimerTypes(std::vector<kodi::addon::PVRTimerType>& types) override;
  int GetTimersAmount() override;
  PVR_ERROR GetTimers(std::vector<kodi::addon::PVRTimer>& timers) override;
  PVR_ERROR AddTimer(const kodi::addon::PVRTimer& timer) override;
  PVR_ERROR DeleteTimer(const kodi::addon::PVRTimer& timer, bool forceDelete) override;
  PVR_ERROR UpdateTimer(const kodi::addon::PVRTimer& timer) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  int GetRecordingsAmount(bool deleted) override;
  PVR_ERROR GetRecordings(bool deleted,
                          std::vector<kodi::addon::PVRRecording>& recordings) override;
  PVR_ERROR DeleteRecording(const kodi::addon::PVRRecording& recording) override;
  PVR_ERROR UndeleteRecording(const kodi::addon::PVRRecording& recording) override;
  PVR_ERROR DeleteAllRecordingsFromTrash() override;
  PVR_ERROR RenameRecording(const kodi::addon::PVRRecording& recording) override;
  PVR_ERROR GetRecordingEdl(const kodi::addon::PVRRecording& recording,
                            std::vector<kodi::addon::PVREDLEntry>& edl) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  bool OpenLiveStream(const kodi::addon::PVRChannel& channel) override;
  void CloseLiveStream() override;
  PVR_ERROR GetStreamProperties(std::vector<kodi::addon::PVRStreamProperties>& properties) override;
  DemuxPacket* DemuxRead() override;
  void DemuxAbort() override;
  bool SeekTime(double time, bool backwards, double& startpts) override;
  bool CanPauseStream() override;
  bool CanSeekStream() override;
  bool IsRealTimeStream() override;
  PVR_ERROR GetStreamTimes(kodi::addon::PVRStreamTimes& times) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

  bool OpenRecordedStream(const kodi::addon::PVRRecording& recording) override;
  void CloseRecordedStream() override;
  int ReadRecordedStream(unsigned char* buffer, unsigned int size) override;
  int64_t SeekRecordedStream(int64_t position, int whence) override;
  int64_t LengthRecordedStream() override;
  PVR_ERROR GetStreamReadChunkSize(int& chunksize) override;

  //--==----==----==----==----==----==----==----==----==----==----==----==----==

protected:
  void* Process(void) override;
  virtual bool OnResponsePacket(cResponsePacket* pkt);

  void OnDisconnect() override;
  void OnReconnect() override;

private:
  bool SupportChannelScan();
  bool SupportRecordingsUndelete();
  bool EnableStatusInterface(bool onOff, bool wait = true);
  PVR_ERROR GetAvailableRecordings(std::vector<kodi::addon::PVRRecording>& recordings);
  PVR_ERROR GetDeletedRecordings(std::vector<kodi::addon::PVRRecording>& recordings);
  bool GenTimerChildren(const kodi::addon::PVRTimer& timer,
                        std::vector<kodi::addon::PVRTimer>& timers);
  std::string GenTimerFolder(std::string directory, std::string title);
  PVR_ERROR GetTimerInfo(unsigned int timernumber, kodi::addon::PVRTimer& tag);
  PVR_ERROR RenameTimer(const kodi::addon::PVRTimer& timerinfo, const std::string& newname);

  std::unique_ptr<cResponsePacket> ReadResult(cRequestPacket* vrp);

  struct SMessage
  {
    P8PLATFORM::CEvent event;
    std::unique_ptr<cResponsePacket> pkt;
  };

  class Queue
  {
    typedef std::map<int, SMessage> SMessages;
    SMessages m_queue;
    P8PLATFORM::CMutex m_mutex;

  public:
    SMessage& Enqueue(uint32_t serial);
    std::unique_ptr<cResponsePacket> Dequeue(uint32_t serial, SMessage& message);
    void Set(std::unique_ptr<cResponsePacket>&& vresp);
  };

  Queue m_queue;

  std::string m_videodir;
  std::string m_wolMac;

  bool m_isTimeshift = false;
  bool m_isRealtime = false;
  int64_t m_ptsBufferEnd = 0;
  P8PLATFORM::CMutex m_timeshiftMutex;

  cVNSIDemux* m_demuxer = nullptr;
  cVNSIRecording* m_recording = nullptr;

  const CPVRAddon& m_base;
};
