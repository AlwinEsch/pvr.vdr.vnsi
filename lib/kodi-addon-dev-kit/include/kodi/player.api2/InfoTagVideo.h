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
#include "internal/libKODI_player_InfoTagVideoHead.h"
#include "internal/libKODI_player_Internal.h"

namespace PlayerLIB
{
namespace V2
{

  ///
  /// \defgroup CPlayerLib_InfoTagVideo
  /// \ingroup PlayerLIB
  /// @{
  /// @brief <b>Used for present video information</b>
  ///
  /// Class contains after request the on Kodi present information of played
  /// video or as entry from a list item.
  ///
  /// It has the header \ref InfoTagVideo.h "#include <kodi/player.api2/InfoTagVideo.h>" be included
  /// to enjoy it.
  ///
  class CPlayerLib_InfoTagVideo
  {
  public:
    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Class constructer with play as source.
    ///
    /// @param[in] player                Class from where the tag data becomes retrieved.
    ///
    CPlayerLib_InfoTagVideo(CPlayerLib_Player* player);

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Class destructor.
    ///
    virtual ~CPlayerLib_InfoTagVideo();

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get [film director](https://en.wikipedia.org/wiki/Film_director)
    /// who has made the film (if present).
    ///
    /// @return [string] Film director name.
    ///
    const std::string& GetDirector() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the writing credits if present from video info tag.
    ///
    /// @return [string] Writing credits
    ///
    const std::string& GetWritingCredits() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the [Video Genre](https://en.wikipedia.org/wiki/Film_genre)
    /// if available.
    ///
    /// @return [string] Genre name
    ///
    const std::string& GetGenre() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get country from where the video is (if rpresent)
    ///
    /// @return [string] Country from Video
    ///
    const std::string& GetCountry() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get video tag line if available.
    ///
    /// @return [string] Video tag line
    ///
    const std::string& GetTagLine() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the outline plot of the video if present.
    ///
    /// @return [string] Outline plot
    ///
    const std::string& GetPlotOutline() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the plot of the video if present.
    ///
    /// @return [string] Plot
    ///
    const std::string& GetPlot() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the URL of the trailer from Video
    ///
    /// @return [string] Trailer URL (if present)
    ///
    const std::string& GetTrailer() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get a picture URL of the video to show as screenshot.
    ///
    /// @return [string] Picture URL
    ///
    const std::string& GetPictureURL() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the video title.
    ///
    /// @return [string] Video title
    ///
    const std::string& GetTitle() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the video votes if available from video info tag.
    ///
    /// @return [string] Votes
    ///
    const std::string& GetVotes() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the cast of the video when available.
    ///
    /// @return [string] Video casts
    ///
    const std::string& GetCast() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the video file name.
    ///
    /// @return [string] File name
    ///
    const std::string& GetFile() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the path where the video is stored.
    ///
    /// @return [string] Path
    ///
    const std::string& GetPath() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the [IMDb](https://en.wikipedia.org/wiki/Internet_Movie_Database)
    /// number of the video (if present).
    ///
    /// @return [string] IMDb number
    ///
    const std::string& GetIMDBNumber() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// To get the [MPAA Rating](https://en.wikipedia.org/wiki/Motion_Picture_Association_of_America_film_rating_system)
    /// of the video (if present).
    ///
    /// @return [string] MPAA rating
    ///
    const std::string& GetMPAARating() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get production year of video if present.
    ///
    /// @return [integer] Production Year
    ///
    int GetYear() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the video rating if present as float (double where supported).
    ///
    /// @return [float] The rating of the video
    ///
    double GetRating() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the number of plays of the video.
    ///
    /// @return [integer] Play Count
    ///
    int GetPlayCount() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Get the last played date / time as string.
    ///
    /// @return [string] Last played date / time
    ///
    const std::string& GetLastPlayed() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get the original title of the video.
    ///
    /// @return [string] Original title
    ///
    const std::string& GetOriginalTitle() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief To get [premiered](https://en.wikipedia.org/wiki/Premiere) date
    /// of the video, if available.
    ///
    /// @return [string] Get premiered date string (if present)
    ///
    const std::string& GetPremiered() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Returns first aired date as string from info tag.
    ///
    /// @return [string] First aired date
    ///
    const std::string& GetFirstAired() const;

    ///
    /// @ingroup CPlayerLib_InfoTagVideo
    /// @brief Returns the duration of video.
    ///
    /// @return Duration of video in seconds
    ///
    unsigned int GetDuration() const;

    IMPL_ADDON_INFO_TAG_VIDEO;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace PlayerLIB */
#include "internal/libKODI_player_InfoTagVideoTail.h"
