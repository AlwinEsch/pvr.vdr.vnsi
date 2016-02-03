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

#include "definitions.h"
#include "PlayList.h"
#include "internal/libKODI_player_AddonPlayerHead.h"
#include "internal/libKODI_player_Internal.h"

using namespace GUILIB::V2;

namespace PlayerLIB
{
namespace V2
{

  ///
  /// \defgroup CPlayerLib_Player
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Creates a new Player</b>
  ///
  /// This player use callbacks from Kodi to add-on who are normally used
  /// defined with this class as parent and the all from add-on needed
  /// virtual function must be present on child.
  ///
  /// Also is it possible to use this class complete independent in two
  /// cases, one is when no callbacks are needed and the other is with
  /// own defined functions for them and reported to Kodi with a call of
  /// \ref CPlayerLib_Player::SetIndependentCallbacks where the needed callback functions
  /// are given with address to Kodi.
  ///
  /// It has the header \ref AddonPlayer.h "#include <kodi/player.api2/AddonPlayer.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib_Player
  {
  public:
    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Class constructor
    ///
    CPlayerLib_Player();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Class Destructor
    ///
    virtual ~CPlayerLib_Player();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief To retrieve the supported media type formats on Kodi
    /// by selected media type (File ends e.g. .mp3 or .mpg).
    ///
    /// @return                         Supported Media types as fileendings
    ///
    static std::string GetSupportedMedia(AddonPlayListType mediaType);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Play a item from filename.
    ///
    /// @param[in] item                string - filename, url or
    ///                                playlist.
    /// @param[in] windowed            [opt] bool - true=play video windowed,
    ///                                false=play users preference.(default)
    ///
    bool Play(const std::string& item, bool windowed = false);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Play a item from a GUI list entry.
    ///
    /// @param[in] listitem            listitem - used with setInfo() to
    ///                                set different infolabels.
    /// @param[in] windowed            [opt] bool - true=play video windowed,
    ///                                false=play users preference.(default)
    ///
    bool Play(const CAddonGUIListItem* listitem, bool windowed = false);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Play a items from playlist.
    ///
    /// @param[in] list                list source to play
    /// @param[in] windowed            [opt] bool - true=play video windowed,
    ///                                false=play users preference.(default)
    /// @param[in] startpos            [opt] int - starting position when
    ///                                playing a playlist. Default = -1
    ///
    bool Play(const CAddonPlayList* list, bool windowed = false, int startpos = -1);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Stop playing.
    ///
    void Stop();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Pause or resume playing if already paused.
    ///
    void Pause();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Play next item in playlist.
    ///
    void PlayNext();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Play previous item in playlist.
    ///
    void PlayPrevious();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Play a certain item from the current playlist.
    ///
    /// @param[in] selected             Position in current playlist
    ///
    void PlaySelected(int selected);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Check Kodi is playing something.
    ///
    /// @return                        True if Kodi is playing a file.
    ///
    bool IsPlaying();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Check for playing audio.
    ///
    /// @return                        True if Kodi is playing an audio file.
    ///
    bool IsPlayingAudio();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Check for playing video.
    ///
    /// @return                        True if Kodi is playing a video.
    ///
    bool IsPlayingVideo();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Check for playing radio data system (RDS).
    ///
    /// @return                        True if kodi is playing a radio data
    ///                                system (RDS).
    ///
    bool IsPlayingRDS();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Returns the current playing file as a string.
    ///
    /// @note For LiveTV, returns a __pvr://__ url which is not translatable
    /// to an OS specific file or external url.
    ///
    /// @return                        Playing filename
    ///
    bool GetPlayingFile(std::string& file);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief To get total playing time.
    ///
    /// Returns the total time of the current playing media in seconds.
    /// This is only accurate to the full second.
    ///
    /// @return                        Total time of the current playing media
    ///
    double GetTotalTime();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Get playing time.
    ///
    /// Returns the current time of the current playing media as fractional seconds.
    ///
    /// @return                        Current time as fractional seconds
    ///
    double GetTime();

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Seek time.
    ///
    /// Seeks the specified amount of time as fractional seconds.
    /// The time specified is relative to the beginning of the currently.
    /// playing media file.
    ///
    /// @param[in] seekTime            Time to seek as fractional seconds
    ///
    void SeekTime(double seekTime);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Get Audio stream names
    ///
    /// @param[out] streams            List of audio streams as name
    /// @return                        true if successed, otherwise false
    ///
    bool GetAvailableAudioStreams(std::vector<std::string> &streams);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Set Audio Stream.
    ///
    /// @param[in] iStream             [int] Audio stream to select for play
    ///
    void SetAudioStream(int iStream);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Get Subtitle stream names.
    ///
    /// @param[out] streams            List of subtitle streams as name
    /// @return                        true if successed, otherwise false
    ///
    bool GetAvailableSubtitleStreams(std::vector<std::string> &streams);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Set Subtitle Stream.
    ///
    /// @param[in] iStream             [int] Subtitle stream to select for play
    ///
    void SetSubtitleStream(int iStream);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Enable / disable subtitles.
    ///
    /// @param[in] visible             [boolean] True for visible subtitles.
    ///
    void ShowSubtitles(bool bVisible);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Get subtitle stream name.
    ///
    /// @param[out] name               The name of currently used subtitle
    /// @return                        true if successed and subtitle present
    ///
    bool GetCurrentSubtitleName(std::string& name);

    ///
    /// @ingroup CPlayerLib_Player
    /// @brief Set subtitle file and enable subtitles.
    ///
    /// @param[in] subPath              File to use as source ofsubtitles
    ///
    void AddSubtitle(std::string& subPath);

    ///
    /// @defgroup CPlayerLib_Player_callbacks Callback functions from Kodi to add-on
    /// \ingroup CPlayerLib_Player
    /// @brief Functions to handle control callbacks from Kodi
    ///
    /// @link CPlayerLib_Player Go back to normal functions from CPlayerLib_Player@endlink
    ///

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief OnPlayBackStarted method.
    ///
    /// Will be called when Kodi starts playing a file.
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackStarted() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackEnded method.
    ///
    /// Will be called when Kodi stops playing a file.
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackEnded() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackStopped method.
    ///
    /// Will be called when user stops Kodi playing a file.
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackStopped() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackPaused method.
    ///
    /// Will be called when user pauses a playing file.
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackPaused() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackResumed method.
    ///
    /// Will be called when user resumes a paused file.
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackResumed() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onQueueNextItem method.
    ///
    /// Will be called when user queues the next item.
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnQueueNextItem() { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackSpeedChanged method.
    ///
    /// Will be called when players speed changes (eg. user FF/RW).
    ///
    /// @param[in] speed               [integer] Current speed of player
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackSpeedChanged(int iSpeed) { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackSeek method.
    ///
    /// Will be called when user seeks to a time.
    ///
    /// @param[in] time                [integer] Time to seek to
    /// @param[in] seekOffset          [integer] ?
    ///
    /// @note Function becomes only called from Kodi itself
    ///
    virtual void OnPlayBackSeek(int iTime, int seekOffset) { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief onPlayBackSeekChapter method.
    ///
    /// Will be called when user performs a chapter seek.
    ///
    /// @param[in] chapter             [integer] Chapter to seek to
    ///
    /// @note Function becomes only called from Kodi itself.
    ///
    virtual void OnPlayBackSeekChapter(int iChapter) { }

    ///
    /// @ingroup CPlayerLib_Player_callbacks
    /// @brief If the class is used independent (with "new CPlayerLib_Player")
    /// and not as parent (with "cCLASS_own : CPlayerLib_Player") from own must
    /// be the callback from Kodi to add-on overdriven with own functions!
    ///
    void SetIndependentCallbacks(
        PLAYERHANDLE     cbhdl,
        void      (*CBOnPlayBackStarted)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackEnded)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackStopped)     (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackPaused)      (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackResumed)     (PLAYERHANDLE cbhdl),
        void      (*CBOnQueueNextItem)       (PLAYERHANDLE cbhdl),
        void      (*CBOnPlayBackSpeedChanged)(PLAYERHANDLE cbhdl, int iSpeed),
        void      (*CBOnPlayBackSeek)        (PLAYERHANDLE cbhdl, int iTime, int seekOffset),
        void      (*CBOnPlayBackSeekChapter) (PLAYERHANDLE cbhdl, int iChapter));

    IMPL_ADDON_PLAYER;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_AddonPlayerTail.h"
