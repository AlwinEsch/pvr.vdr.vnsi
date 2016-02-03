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

namespace GUILIB
{
namespace V2
{
extern "C"
{

  /*
   * Internal Structures to have "C"-Style data transfer
   */
  typedef struct ADDON_VideoInfoTag__cast__DATA_STRUCT
  {
    const char* name;
    const char* role;
    int         order;
    const char* thumbnail;
  } ADDON_VideoInfoTag__cast__DATA_STRUCT;

  typedef GUIHANDLE   GUIListItem_Create
      (void         *addonData,
       const char   *label,
       const char   *label2,
       const char   *iconImage,
       const char   *thumbnailImage,
       const char   *path);

  typedef void        GUIListItem_Destroy
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void        GUIListItem_GetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       char         &label,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef void        GUIListItem_GetLabel2
      (void         *addonData,
       GUIHANDLE     handle,
       char         &label,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetLabel2
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef void        GUIListItem_GetIconImage
      (void         *addonData,
       GUIHANDLE     handle,
       char         &image,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetIconImage
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *image);

  typedef void        GUIListItem_GetOverlayImage
      (void         *addonData,
       GUIHANDLE     handle,
       char         &image,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_SetOverlayImage
      (void         *addonData,
       GUIHANDLE     handle,
       unsigned int  image,
       bool          bOnOff);

  typedef void        GUIListItem_SetThumbnailImage
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *image);

  typedef void        GUIListItem_SetArt
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *type,
       const char   *url);

  typedef void        GUIListItem_SetArtFallback
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *from,
       const char   *to);

  typedef void        GUIListItem_SetLabel
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *label);

  typedef bool        GUIListItem_HasArt
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *type);

  typedef void        GUIListItem_Select
      (void         *addonData,
       GUIHANDLE     handle,
       bool          bOnOff);

  typedef bool        GUIListItem_IsSelected
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasIcon
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasOverlay
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_IsFileItem
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_IsFolder
      (void         *addonData,
       GUIHANDLE     handle);

  typedef void        GUIListItem_SetProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key,
       const char   *value);

  typedef void        GUIListItem_GetProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key,
       char         &property,
       unsigned int &iMaxStringSize);

  typedef void        GUIListItem_ClearProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key);

  typedef void        GUIListItem_ClearProperties
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasProperties
      (void         *addonData,
       GUIHANDLE     handle);

  typedef bool        GUIListItem_HasProperty
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *key);

  typedef void        GUIListItem_SetPath
      (void         *addonData,
       GUIHANDLE     handle,
       const char   *path);

  typedef char*       GUIListItem_GetPath(
       void*         addonData,
       GUIHANDLE     handle);

  typedef char*       GUIListItem_GetDescription(
       void*         addonData,
       GUIHANDLE     handle);

  typedef int         GUIListItem_GetDuration(
       void*         addonData,
       GUIHANDLE     handle);

  typedef void        GUIListItem_SetSubtitles(
       void*         addonData,
       GUIHANDLE     handle,
       const char**  streams,
       unsigned int  entries);

  typedef void        GUIListItem_SetMimeType(
       void*         addonData,
       GUIHANDLE     handle,
       const char*   mimetype);

  typedef void        GUIListItem_SetContentLookup(
       void*         addonData,
       GUIHANDLE     handle,
       bool          enable);

  typedef void        GUIListItem_AddContextMenuItems(
       void*         addonData,
       GUIHANDLE     handle,
       const char**  streams[2],
       unsigned int  entries,
       bool          replaceItems);

  typedef void        GUIListItem_AddStreamInfo(
       void*         addonData,
       GUIHANDLE     handle,
       const char*   cType,
       const char**  dictionary[2],
       unsigned int  entries);

  typedef void        GUIListItem_SetMusicInfo(
       void*         addonData,
       GUIHANDLE     handle,
       unsigned int  type,
       void*         data,
       unsigned int  entries);

  typedef void        GUIListItem_SetVideoInfo(
       void*         addonData,
       GUIHANDLE     handle,
       unsigned int  type,
       void*         data,
       unsigned int  entries);

  typedef void        GUIListItem_SetPictureInfo(
       void*         addonData,
       GUIHANDLE     handle,
       unsigned int  type,
       void*         data,
       unsigned int  entries);
/*
  typedef char*       GUIListItem_GetDescription(
       void*         addonData,
       GUIHANDLE     handle);

*/
  typedef struct CB_GUILib_ListItem
  {
    GUIListItem_Create*                  Create;
    GUIListItem_Destroy*                 Destroy;
    GUIListItem_GetLabel*                GetLabel;
    GUIListItem_SetLabel*                SetLabel;
    GUIListItem_GetLabel2*               GetLabel2;
    GUIListItem_SetLabel2*               SetLabel2;
    GUIListItem_GetIconImage*            GetIconImage;
    GUIListItem_SetIconImage*            SetIconImage;
    GUIListItem_GetOverlayImage*         GetOverlayImage;
    GUIListItem_SetOverlayImage*         SetOverlayImage;
    GUIListItem_SetThumbnailImage*       SetThumbnailImage;
    GUIListItem_SetArt*                  SetArt;
    GUIListItem_SetArtFallback*          SetArtFallback;
    GUIListItem_HasArt*                  HasArt;
    GUIListItem_Select*                  Select;
    GUIListItem_IsSelected*              IsSelected;
    GUIListItem_HasIcon*                 HasIcon;
    GUIListItem_HasOverlay*              HasOverlay;
    GUIListItem_IsFileItem*              IsFileItem;
    GUIListItem_IsFolder*                IsFolder;
    GUIListItem_SetProperty*             SetProperty;
    GUIListItem_GetProperty*             GetProperty;
    GUIListItem_ClearProperty*           ClearProperty;
    GUIListItem_ClearProperties*         ClearProperties;
    GUIListItem_HasProperties*           HasProperties;
    GUIListItem_HasProperty*             HasProperty;
    GUIListItem_SetPath*                 SetPath;
    GUIListItem_GetPath*                 GetPath;
    GUIListItem_GetDuration*             GetDuration;
    GUIListItem_SetSubtitles*            SetSubtitles;
    GUIListItem_SetMimeType*             SetMimeType;
    GUIListItem_SetContentLookup*        SetContentLookup;
    GUIListItem_AddContextMenuItems*     AddContextMenuItems;
    GUIListItem_AddStreamInfo*           AddStreamInfo;
    GUIListItem_SetMusicInfo*            SetMusicInfo;
    GUIListItem_SetVideoInfo*            SetVideoInfo;
    GUIListItem_SetPictureInfo*          SetPictureInfo;
  } CB_GUILib_ListItem;

  class CAddonGUIListItem;

  #define IMPL_ADDON_GUI_LIST                   \
    public:                                     \
      CAddonGUIListItem(GUIHANDLE listItemHandle); \
      const GUIHANDLE GetListItemHandle() const \
      {                                         \
        return m_ListItemHandle;                \
      }                                         \
    protected:                                  \
      GUIHANDLE         m_ListItemHandle;       \
      ADDON::AddonCB*   m_Handle;               \
      CB_GUILib*        m_cb;                   \
    private:                                    \
      friend class CAddonGUIWindow;

}; /* extern "C" */
}; /* namespace V2 */
}; /* namespace GUILIB */
