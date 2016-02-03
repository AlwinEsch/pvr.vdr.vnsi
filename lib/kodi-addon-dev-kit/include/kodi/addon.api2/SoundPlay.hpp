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
#include "internal/libKODI_addon_AudioHead.hpp"
#include "internal/libKODI_addon_Internal.hpp"

namespace AddOnLIB
{
namespace V2
{

  ///
  /// \defgroup CAddonLib_SoundPlay
  /// \ingroup AddOnLIB
  /// @{
  /// @brief <b>Background sound playback</b>
  ///
  /// This class is designed for playback of "wave" audio files to point for the
  /// user with sound steps performed or to draw attention to warnings.
  ///
  /// Further allowed this playback on a single selected channel which can be
  /// used to identify or also to test. For larger and more extensive audio
  /// system testing is recommended but the use of "CAddonAE_Stream" since
  /// this is intended specifically for this purpose.
  ///
  /// @warning class supports only <b>wave files (*.wav)</b> for play back!
  ///
  /// It has the header \ref SoundPlay.h "#include <kodi/addon.api2/SoundPlay.h>" be included
  /// to enjoy it.
  ///
  /// \b Example:
  /// @code
  /// #include <kodi/addon.api2/SoundPlay.h>
  /// #include <kodi/gui.api2/GUIDialogFileBrowser.h>
  ///
  /// ...
  ///
  /// void PlaySelectedWaveFile()
  /// {
  ///   std::string filename;
  ///   if (CAddonGUIDialogFileBrowser::ShowAndGetFile("local", "*.wav",
  ///                                                  "Test File selection and playback of them",
  ///                                                  filename))
  ///   {
  ///     /*
  ///      * The example performs a playback with the value "waitUntilEnd" from
  ///      * "CAddonLib_SoundPlay::Play(...)" is set to true. This waits for the call
  ///      * until the playback is complete, so that it is then also possible to
  ///      * use the class static as in this example.
  ///      */
  ///     CAddonLib_SoundPlay playback(filename);
  ///     playback->Play(true);
  ///   }
  /// }
  /// @endcode
  ///
  class CAddonLib_SoundPlay
  {
  public:
    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Construct class
    ///
    /// Construct the class for background playback of given wave file.
    ///
    /// @param[in] filename The wave file to play
    ///
    CAddonLib_SoundPlay(const std::string& filename);

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Destructor
    ///
    virtual ~CAddonLib_SoundPlay(void);

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Start playback
    ///
    /// Starts the playback of wave file. Normally returns this function.
    ///
    /// This function ordinarily comes after him begin the sound reproduction
    /// immediately again back around other steps to permit. If it itself,
    /// however, only around the reproduction of a file acts no other operation
    /// required is able by placed of the value "waitUntilEnd" on true by the
    /// call are waited to him is ready. This also permits the use of the class
    /// statically in the function.
    ///
    /// @param[in] waitUntilEnd [opt] If set to true returns call after end of
    /// playback, default is false
    ///
    void Play(bool waitUntilEnd = false);

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Stop playback
    ///
    /// Stops the playback of wave file
    ///
    void Stop();

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief To check playing is active
    ///
    /// The check used class during playback of wave file is still playing.
    ///
    /// @return true if playing active, otherwise false
    ///
    bool IsPlaying();

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Set audio channel for playback
    ///
    /// To set channel position the for a single channel playback of wave file.
    /// To reset selection use "AUDIO_CH_INVALID".
    ///
    /// @param[in] channel The channel identifier to play on
    ///
    void SetChannel(audio_channel channel);

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Get the active channel for playback
    ///
    /// To set channel position the for a single channel playback of wave file.
    ///
    /// @return The channel where currently played
    ///
    audio_channel GetChannel();

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Set the volume
    ///
    /// To set the volume of wave file playback.
    ///
    /// @note Volume is independent from Kodi's normal volume control and only
    /// for the wave file. Also is the volume only on this class and not to all
    /// background sounds on Kodi.
    ///
    /// @param[in] volume The playback volume of wave file
    ///
    void SetVolume(float volume);

    ///
    /// @ingroup CAddonLib_SoundPlay
    /// @brief Get the volume
    ///
    /// To get the volume of wave file playback.
    ///
    /// @note Volume is independent from Kodi's normal volume control and only
    /// for the wave file. Also is the volume only on this class and not to all
    /// background sounds on Kodi.
    ///
    /// @return The currently active volume of this wave file
    ///
    float GetVolume();

    IMPL_ADDONSOUNDPLAY;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace AddOnLIB */
#include "internal/libKODI_addon_AudioTail.hpp"
