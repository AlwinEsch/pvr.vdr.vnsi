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

#include "internal/libKODI_guilib_internal.h"
#include "internal/libKODI_guilib_ListItemHead.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup CAddonGUIListItem
  /// \defgroup CAddonGUIListItem_MusicInfoTag Functions - Music info tag
  ///

  ///
  /// \ingroup CAddonGUIListItem
  /// \defgroup CAddonGUIListItem_VideoInfoTag Functions - Video info tag
  ///

  ///
  /// \ingroup CAddonGUIListItem
  /// \defgroup CAddonGUIListItem_PictureInfoTag Functions - Picture info tag
  ///

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIListItem
  /// @{
  /// @brief <b>Selectable window list item</b>
  ///
  /// The list item control is used for creating item lists in Kodi
  ///
  /// The with \ref GUIListItem.h "#include <kodi/addon.api2/GUIListItem.h>" given
  /// class is used to create a item entry for a list on window and to support it's
  /// control.
  ///
  class CAddonGUIListItem
  {
  public:
    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Class constructor with parameters
    ///
    /// @param[in] label                Item label
    /// @param[in] label2               Second Item label (if needed)
    /// @param[in] iconImage            Item icon image (if needed)
    /// @param[in] thunbnailImage       Thumbnail Image of item (if needed)
    /// @param[in] path                 Path to where item is defined
    ///
    CAddonGUIListItem(
      const std::string&      label,
      const std::string&      label2,
      const std::string&      iconImage,
      const std::string&      thumbnailImage,
      const std::string&      path);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Class destructor
    ///
    ///
    ///
    ~CAddonGUIListItem();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Returns the listitem label.
    ///
    /// @return                       Label of item
    ///
    std::string GetLabel();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets the listitem's label.
    ///
    /// @param[in] label              string or unicode - text string.
    ///
    void SetLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Returns the second listitem label.
    ///
    /// @return                       Second label of item
    ///
    std::string GetLabel2();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets the listitem's label2.
    ///
    /// @param[in] label              string or unicode - text string.
    ///
    void SetLabel2(const std::string& label);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To get current icon image of entry
    ///
    /// @return The current icon image path (if present)
    ///
    std::string GetIconImage();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To set icon image of entry
    ///
    /// @param image                    The image to use for.
    ///
    /// @note Alternative can be \ref SetArt used
    ///
    ///
    void SetIconImage(const std::string& image);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To get current overlay image of entry
    ///
    /// @return The current overlay image path (if present)
    ///
    std::string GetOverlayImage();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To set overlay image of entry
    ///
    /// @param image                    The image to use for.
    /// @param bOnOff                   To switch image view on (true) or off (false)
    ///
    void SetOverlayImage(unsigned int image, bool bOnOff = false);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To set thumbnail image of entry
    ///
    /// @warning Deprecated. Use setArt
    ///
    ///
    void SetThumbnailImage(const std::string& image);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets the listitem's art
    ///
    /// @param[in] type                 Type of Art to set
    /// @param[in] url                  The url to use for Art
    ///  - Some default art values (any string possible):
    ///  | value (type)  | Type                                              |
    ///  |:-------------:|:--------------------------------------------------|
    ///  | thumb         | string - image filename
    ///  | poster        | string - image filename
    ///  | banner        | string - image filename
    ///  | fanart        | string - image filename
    ///  | clearart      | string - image filename
    ///  | clearlogo     | string - image filename
    ///  | landscape     | string - image filename
    ///  | icon          | string - image filename
    ///
    void SetArt(const std::string& type, const std::string& url);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets the listitem's fallback art to use if other is not present
    ///
    /// @param[in] type                 Type of Art to set
    /// @param[in] url                  The url to use for Art
    ///  - Some default art values (any string possible):
    ///  | value (type)  | Type                                              |
    ///  |:-------------:|:--------------------------------------------------|
    ///  | thumb         | string - image filename
    ///  | poster        | string - image filename
    ///  | banner        | string - image filename
    ///  | fanart        | string - image filename
    ///  | clearart      | string - image filename
    ///  | clearlogo     | string - image filename
    ///  | landscape     | string - image filename
    ///  | icon          | string - image filename
    ///
    void SetArtFallback(const std::string& from, const std::string& to);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief
    ///
    /// @return                         true if present,, false if not
    ///
    bool HasArt(const std::string& type);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Check item about presence of Icon
    ///
    /// @return                         true if present,, false if not
    ///
    bool HasIcon();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To check item for presence of a Overlay image
    ///
    /// @return                         true if present, false if not
    ///
    bool HasOverlay();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To check item is a File
    ///
    /// @return                         true if is a file, false if not
    ///
    bool IsFileItem();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To check item is a Folder
    ///
    /// @return                         true if yes, false if not
    ///
    bool IsFolder();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To control selection of item in list (also multiple selection,
    /// in list on serveral items possible).
    ///
    /// @param[in] bOnOff               if true becomes set as selected
    ///
    void Select(bool bOnOff);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To check item is selected on list.
    ///
    /// @return                         true if selected, otherwise false
    ///
    bool IsSelected();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets a listitem property, similar to an infolabel.
    ///
    /// @param[in] key            string - property name.
    /// @param[in] value          string or unicode - value of property.
    ///
    /// @note Key is NOT case sensitive.
    ///       You can use the above as keywords for arguments and skip certain\n
    ///       optional arguments.\n
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    /// Some of these are treated internally by Kodi, such as the
    /// <b>'StartOffset'</b> property, which is the offset in seconds at which to
    /// start playback of an item.  Others may be used in the skin to add
    /// extra information, such as <b>'WatchedCount'</b> for tvshow items
    ///
    void SetProperty(const std::string& key, const std::string& value);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Returns a listitem property as a string, similar to an infolabel.
    ///
    /// @param[in] key                string - property name.
    /// @return                       string - List item property
    ///
    /// @note Key is NOT case sensitive.\n
    ///       You can use the above as keywords for arguments and skip certain
    ///       optional arguments.\n
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    std::string GetProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Clears the specific window property.
    ///
    /// @param[in] key                string - property name.
    ///
    /// @note Key is NOT case sensitive. Equivalent to setProperty(key,'')
    ///       You can use the above as keywords for arguments and skip certain
    ///       optional arguments.
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ..
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    void ClearProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Clears all window properties.
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ..
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    void ClearProperties();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To check list item about presence of properties
    ///
    /// @return                         true if properties present
    ///
    bool HasProperties();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief To check list item about presence of searched key by name
    ///
    /// @param[in] key                  Property to check
    /// @return                         true if properties present
    ///
    bool HasProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets the listitem's path.
    ///
    /// @param[in] path               string or unicode - path, activated when
    ///                               item is clicked.
    ///
    /// @note You can use the above as keywords for arguments.
    ///
    void SetPath(const std::string& path);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Returns the path / filename of this listitem.
    ///
    /// @return                       Path string
    ///
    std::string GetPath();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Returns the description of this listitem.
    ///
    /// @return                       Description string
    ///
    std::string GetDescription();

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Returns the duration of this listitem
    ///
    /// @return                       Duration of item as integer
    ///
    int GetDuration() const;

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets subtitles for this listitem.
    ///
    /// @param[in] subtitleFiles      string - List of subtitles to add
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetSubtitles(const std::vector<std::string>& subtitleFiles);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Sets the listitem's mimetype if known.
    ///
    /// @param[in] mimetype           string or unicode - mimetype.
    ///
    /// If known prehand, this can (but does not have to) avoid HEAD requests
    /// being sent to HTTP servers to figure out file type.
    ///
    void SetMimeType(const std::string& mimetype);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Enable or disable content lookup for item.
    ///
    /// If disabled, HEAD requests to e.g. determine mime type will not be
    /// sent.
    ///
    /// @param[in] enable             bool - True = enable, False = disable
    ///
    void SetContentLookup(bool enable);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Adds item(s) to the context menu for media lists.
    ///
    /// @param[in] items              list - <b><c>[(label, action,)*]</c></b> A list of tuples consisting of label and action pairs.
    ///                               - `label`          : string or unicode - item's label.
    ///                               - `action`         : string or unicode - any built-in function to perform.
    /// @param[in] replaceItems       [opt] bool - True=only your items will show/False=your items will be added to context menu(Default).
    ///
    /// [List of built-in functions](http://kodi.wiki/view/List_of_Built_In_Functions)
    ///
    /// @note You can use the above as keywords for arguments and skip certain
    ///       optional arguments.\n
    ///       Once you use a keyword, all following arguments require the
    ///       keyword.
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void AddContextMenuItems(const std::vector<std::pair<std::string, std::string> >& items, bool replaceItems = false);

    ///
    /// \ingroup CAddonGUIListItem
    /// @brief Add a stream with details.
    ///
    /// @param[in] type               string - type of stream(video/audio/subtitle).
    /// @param[in] values             dictionary - pairs of { label: value }.
    /// - Video Values:
    ///  | Label       | Type          | Example value     |
    ///  |:-----------:|:-------------:|:------------------|
    ///  | codec       | string        | h264
    ///  | aspect      | float         | 1.78
    ///  | width       | integer       | 1280
    ///  | height      | integer       | 720
    ///  | duration    | integer       | seconds
    ///
    /// - Audio Values:
    ///  | Label       | Type          | Example value     |
    ///  |:-----------:|:-------------:|:------------------|
    ///  | codec       | string        | dts
    ///  | language    | string        | en
    ///  | channels    | integer       | 2
    ///
    /// - Subtitle Values:
    ///  | Label       | Type          | Example value    |
    ///  |:-----------:|:-------------:|:-----------------|
    ///  | language    | string        | en
    ///
    ///
    ///
    ///-----------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void AddStreamInfo(const std::string& cType, const std::vector<std::pair<std::string, std::string> >& dictionary);

    ///
    /// \ingroup CAddonGUIListItem_MusicInfoTag
    /// @brief Sets the music listitem's infoLabels of type bool.
    ///
    /// @param[in] type               type of \ref ADDON_MusicInfoTag "Music Info Tag"
    /// @param[in] value              boolean value to set
    ///
    void SetMusicInfo_BOOL(ADDON_MusicInfoTag type, bool value);

    ///
    /// \ingroup CAddonGUIListItem_MusicInfoTag
    /// @brief Sets the music listitem's infoLabels of type integer.
    ///
    /// @param[in] type               type of \ref ADDON_MusicInfoTag "Music Info Tag"
    /// @param[in] value              integer value to set
    ///
    void SetMusicInfo_INT(ADDON_MusicInfoTag type, int value);

    ///
    /// \ingroup CAddonGUIListItem_MusicInfoTag
    /// @brief Sets the music listitem's infoLabels of type unsigned integer.
    ///
    /// @param[in] type               type of \ref ADDON_MusicInfoTag "Music Info Tag"
    /// @param[in] value              unsigned integer value to set
    ///
    void SetMusicInfo_UINT(ADDON_MusicInfoTag type, unsigned int value);

    ///
    /// \ingroup CAddonGUIListItem_MusicInfoTag
    /// @brief Sets the music listitem's infoLabels of type float.
    ///
    /// @param[in] type               type of \ref ADDON_MusicInfoTag "Music Info Tag"
    /// @param[in] value              float value to set
    ///
    void SetMusicInfo_FLOAT(ADDON_MusicInfoTag type, float value);

    ///
    /// \ingroup CAddonGUIListItem_MusicInfoTag
    /// @brief Sets the music listitem's infoLabels with a string.
    ///
    /// @param[in] type               type of \ref ADDON_MusicInfoTag "Music Info Tag"
    /// @param[in] value              string value to set
    ///
    void SetMusicInfo_STRING(ADDON_MusicInfoTag type, std::string value);

    ///
    /// \ingroup CAddonGUIListItem_MusicInfoTag
    /// @brief Sets the music listitem's infoLabels with string table.
    ///
    /// @param[in] type               type of \ref ADDON_MusicInfoTag "Music Info Tag"
    /// @param[in] value              string table to set
    ///
    void SetMusicInfo_STRING_LIST(ADDON_MusicInfoTag type, std::vector<std::string> value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels of type bool.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              boolean value to set
    ///
    void SetVideoInfo_BOOL(ADDON_VideoInfoTag type, bool value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels of type integer.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              integer value to set
    ///
    void SetVideoInfo_INT(ADDON_VideoInfoTag type, int value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels of type unsigned integer.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              unsigned integer value to set
    ///
    void SetVideoInfo_UINT(ADDON_VideoInfoTag type, unsigned int value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels of type float.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              float value to set
    ///
    void SetVideoInfo_FLOAT(ADDON_VideoInfoTag type, float value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels with a string.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              string value to set
    ///
    void SetVideoInfo_STRING(ADDON_VideoInfoTag type, std::string value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels with string table.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              string table to set
    ///
    void SetVideoInfo_STRING_LIST(ADDON_VideoInfoTag type, std::vector<std::string> value);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video listitem's infoLabels of type bool.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              boolean value to set
    ///
    void SetVideoInfo_Resume(ADDON_VideoInfoTag_Resume &resume);

    ///
    /// \ingroup CAddonGUIListItem_VideoInfoTag
    /// @brief Sets the video infoLabels for cast.
    ///
    /// @param[in] type               type of \ref ADDON_VideoInfoTag "Video Info Tag"
    /// @param[in] value              boolean value to set
    ///
    void SetVideoInfo_Cast(std::vector<ADDON_VideoInfoTag_Cast> &cast);

    ///
    /// \ingroup CAddonGUIListItem_PictureInfoTag
    /// @brief Sets the video infoLabels with picture info tag
    ///
    /// @param[in] type               type of \ref ADDON_PictureInfoTag "Picture Info Tag"
    /// @param[in] value              boolean value to set
    ///
    void SetPictureInfo_BOOL(ADDON_PictureInfoTag type, bool value);

    ///
    /// \ingroup CAddonGUIListItem_PictureInfoTag
    /// @brief Sets the picture listitem's infoLabels of type integer.
    ///
    /// @param[in] type               type of \ref ADDON_PictureInfoTag "Picture Info Tag"
    /// @param[in] value              integer value to set
    ///
    void SetPictureInfo_INT(ADDON_PictureInfoTag type, int value);

    ///
    /// \ingroup CAddonGUIListItem_PictureInfoTag
    /// @brief Sets the picture listitem's infoLabels of type unsigned integer.
    ///
    /// @param[in] type               type of \ref ADDON_PictureInfoTag "Picture Info Tag"
    /// @param[in] value              unsigned integer value to set
    ///
    void SetPictureInfo_UINT(ADDON_PictureInfoTag type, unsigned int value);

    ///
    /// \ingroup CAddonGUIListItem_PictureInfoTag
    /// @brief Sets the picture listitem's infoLabels of type float.
    ///
    /// @param[in] type               type of \ref ADDON_PictureInfoTag "Picture Info Tag"
    /// @param[in] value              float value to set
    ///
    void SetPictureInfo_FLOAT(ADDON_PictureInfoTag type, float value);

    ///
    /// \ingroup CAddonGUIListItem_PictureInfoTag
    /// @brief Sets the picture listitem's infoLabels with a string.
    ///
    /// @param[in] type               type of \ref ADDON_PictureInfoTag "Picture Info Tag"
    /// @param[in] value              string value to set
    ///
    void SetPictureInfo_STRING(ADDON_PictureInfoTag type, std::string value);

    ///
    /// \ingroup CAddonGUIListItem_PictureInfoTag
    /// @brief Sets the picture listitem's infoLabels with string table.
    ///
    /// @param[in] type               type of \ref ADDON_PictureInfoTag "Picture Info Tag"
    /// @param[in] value              string table to set
    ///
    void SetPictureInfo_STRING_LIST(ADDON_PictureInfoTag type, std::vector<std::string> value);

    IMPL_ADDON_GUI_LIST;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace GUILIB */
#include "internal/libKODI_guilib_ListItemTail.h"
