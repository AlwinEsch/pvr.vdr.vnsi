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

/*
 * GUILib.h EOF header, passed there (out of normal code style) to reduce
 * not needed parts, to have only add-on programming related stuff there.
 */

namespace GUILIB
{
namespace V2
{

  inline CAddonGUIListItem::CAddonGUIListItem(
    const std::string&      label,
    const std::string&      label2,
    const std::string&      iconImage,
    const std::string&      thumbnailImage,
    const std::string&      path)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    m_ListItemHandle = m_cb->ListItem.Create(m_Handle->addonData, label.c_str(),
                                             label2.c_str(), iconImage.c_str(),
                                             thumbnailImage.c_str(), path.c_str());
  }

  inline CAddonGUIListItem::CAddonGUIListItem(GUIHANDLE listItemHandle)
   : m_Handle((ADDON::AddonCB*)CGUILib::g_libKODI_Internal->m_Handle),
     m_cb(CGUILib::g_libKODI_Internal->m_Callbacks)
  {
    m_ListItemHandle = listItemHandle;
  }

  inline CAddonGUIListItem::~CAddonGUIListItem()
  {
    m_cb->ListItem.Destroy(m_Handle->addonData, m_ListItemHandle);
  }

  inline std::string CAddonGUIListItem::GetLabel()
  {
    std::string label;
    label.resize(1024);
    unsigned int size = (unsigned int)label.capacity();
    m_cb->ListItem.GetLabel(m_Handle->addonData, m_ListItemHandle, label[0], size);
    label.resize(size);
    label.shrink_to_fit();
    return label.c_str();
  }

  inline void CAddonGUIListItem::SetLabel(const std::string &label)
  {
    m_cb->ListItem.SetLabel(m_Handle->addonData, m_ListItemHandle, label.c_str());
  }

  inline std::string CAddonGUIListItem::GetLabel2()
  {
    std::string label;
    label.resize(1024);
    unsigned int size = (unsigned int)label.capacity();
    m_cb->ListItem.GetLabel2(m_Handle->addonData, m_ListItemHandle, label[0], size);
    label.resize(size);
    label.shrink_to_fit();
    return label.c_str();
  }

  inline void CAddonGUIListItem::SetLabel2(const std::string &label)
  {
    m_cb->ListItem.SetLabel2(m_Handle->addonData, m_ListItemHandle, label.c_str());
  }

  inline std::string CAddonGUIListItem::GetIconImage()
  {
    std::string image;
    image.resize(1024);
    unsigned int size = (unsigned int)image.capacity();
    m_cb->ListItem.GetIconImage(m_Handle->addonData, m_ListItemHandle, image[0], size);
    image.resize(size);
    image.shrink_to_fit();
    return image.c_str();
  }

  inline void CAddonGUIListItem::SetIconImage(const std::string &image)
  {
    m_cb->ListItem.SetIconImage(m_Handle->addonData, m_ListItemHandle, image.c_str());
  }

  inline std::string CAddonGUIListItem::GetOverlayImage()
  {
    std::string image;
    image.resize(1024);
    unsigned int size = (unsigned int)image.capacity();
    m_cb->ListItem.GetOverlayImage(m_Handle->addonData, m_ListItemHandle, image[0], size);
    image.resize(size);
    image.shrink_to_fit();
    return image.c_str();
  }

  inline void CAddonGUIListItem::SetOverlayImage(unsigned int image, bool bOnOff /*= false */)
  {
    m_cb->ListItem.SetOverlayImage(m_Handle->addonData, m_ListItemHandle, image, bOnOff);
  }

  inline void CAddonGUIListItem::SetThumbnailImage(const std::string &image)
  {
    m_cb->ListItem.SetThumbnailImage(m_Handle->addonData, m_ListItemHandle, image.c_str());
  }

  inline void CAddonGUIListItem::SetArt(const std::string &type, const std::string &url)
  {
    m_cb->ListItem.SetArt(m_Handle->addonData, m_ListItemHandle, type.c_str(), url.c_str());
  }

  inline void CAddonGUIListItem::SetArtFallback(const std::string &from, const std::string &to)
  {
    m_cb->ListItem.SetArtFallback(m_Handle->addonData, m_ListItemHandle, from.c_str(), to.c_str());
  }

  inline bool CAddonGUIListItem::HasArt(const std::string &type)
  {
    return m_cb->ListItem.HasArt(m_Handle->addonData, m_ListItemHandle, type.c_str());
  }

  inline void CAddonGUIListItem::Select(bool bOnOff)
  {
    m_cb->ListItem.Select(m_Handle->addonData, m_ListItemHandle, bOnOff);
  }

  inline bool CAddonGUIListItem::IsSelected()
  {
    return m_cb->ListItem.IsSelected(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasIcon()
  {
    return m_cb->ListItem.HasIcon(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasOverlay()
  {
    return m_cb->ListItem.HasOverlay(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::IsFileItem()
  {
    return m_cb->ListItem.IsFileItem(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::IsFolder()
  {
    return m_cb->ListItem.IsFolder(m_Handle->addonData, m_ListItemHandle);
  }

  inline void CAddonGUIListItem::SetProperty(const std::string &key, const std::string &value)
  {
    m_cb->ListItem.SetProperty(m_Handle->addonData, m_ListItemHandle, key.c_str(), value.c_str());
  }

  inline std::string CAddonGUIListItem::GetProperty(const std::string &key)
  {
    std::string property;
    property.resize(1024);
    unsigned int size = (unsigned int)property.capacity();
    m_cb->ListItem.GetProperty(m_Handle->addonData, m_ListItemHandle, key.c_str(), property[0], size);
    property.resize(size);
    property.shrink_to_fit();
    return property;
  }

  inline void CAddonGUIListItem::ClearProperty(const std::string &key)
  {
    m_cb->ListItem.ClearProperty(m_Handle->addonData, m_ListItemHandle, key.c_str());
  }

  inline void CAddonGUIListItem::ClearProperties()
  {
    m_cb->ListItem.ClearProperties(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasProperties()
  {
    return m_cb->ListItem.HasProperties(m_Handle->addonData, m_ListItemHandle);
  }

  inline bool CAddonGUIListItem::HasProperty(const std::string &key)
  {
    return m_cb->ListItem.HasProperty(m_Handle->addonData, m_ListItemHandle, key.c_str());
  }

  inline void CAddonGUIListItem::SetPath(const std::string &path)
  {
    m_cb->ListItem.SetPath(m_Handle->addonData, m_ListItemHandle, path.c_str());
  }

  inline std::string CAddonGUIListItem::GetPath()
  {
    std::string strReturn;
    char* strMsg = m_cb->ListItem.GetPath(m_Handle->addonData, m_ListItemHandle);
    if (strMsg != nullptr)
    {
      if (std::strlen(strMsg))
        strReturn = strMsg;
      m_cb->General.free_string(m_Handle, strMsg);
    }
    return strReturn;
  }

  inline int CAddonGUIListItem::GetDuration() const
  {
    return CAddonGUIListItem::m_cb->ListItem.GetDuration(m_Handle->addonData, m_ListItemHandle);
  }

  inline void CAddonGUIListItem::SetSubtitles(const std::vector<std::string>& subtitleFiles)
  {
    unsigned int size = subtitleFiles.size();
    if (size == 0)
      return;

    const char** subtitles = (const char**)malloc(size);
    for (unsigned int i = 0; i < size; ++i)
      subtitles[i] = subtitleFiles[i].c_str();

    CAddonGUIListItem::m_cb->ListItem.SetSubtitles(m_Handle->addonData, m_ListItemHandle, subtitles, size);
    free(subtitles);
  }

  inline void CAddonGUIListItem::SetMimeType(const std::string& mimetype)
  {
    CAddonGUIListItem::m_cb->ListItem.SetMimeType(m_Handle->addonData, m_ListItemHandle, mimetype.c_str());
  }

  inline void CAddonGUIListItem::SetContentLookup(bool enable)
  {
    CAddonGUIListItem::m_cb->ListItem.SetContentLookup(m_Handle->addonData, m_ListItemHandle, enable);
  }

  inline void CAddonGUIListItem::AddContextMenuItems(const std::vector<std::pair<std::string, std::string> >& items, bool replaceItems)
  {
    const char*** entries = nullptr;
    unsigned int size = items.size();
    if (size != 0)
    {
      entries = (const char***)malloc(size*sizeof(const char***));
      for (unsigned int i = 0; i < size; ++i)
      {
        entries[i][0] = items.at(i).first.c_str();
        entries[i][1] = items.at(i).second.c_str();
      }
    }

    CAddonGUIListItem::m_cb->ListItem.AddContextMenuItems(m_Handle->addonData, m_ListItemHandle, entries, size, replaceItems);
    if (entries)
      free(entries);
  }

  inline void CAddonGUIListItem::AddStreamInfo(const std::string& cType, const std::vector<std::pair<std::string, std::string> >& dictionary)
  {
    const char*** entries = nullptr;
    unsigned int size = dictionary.size();
    if (size == 0)
      return;

    entries = (const char***)malloc(size*sizeof(const char***));
    for (unsigned int i = 0; i < size; ++i)
    {
      entries[i][0] = dictionary.at(i).first.c_str();
      entries[i][1] = dictionary.at(i).second.c_str();
    }

    CAddonGUIListItem::m_cb->ListItem.AddStreamInfo(m_Handle->addonData, m_ListItemHandle, cType.c_str(), entries, size);
    free(entries);
  }

  inline void CAddonGUIListItem::SetMusicInfo_BOOL(ADDON_MusicInfoTag type, bool value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetMusicInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(bool));
  }

  inline void CAddonGUIListItem::SetMusicInfo_INT(ADDON_MusicInfoTag type, int value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetMusicInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(int));
  }

  inline void CAddonGUIListItem::SetMusicInfo_UINT(ADDON_MusicInfoTag type, unsigned int value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetMusicInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(unsigned int));
  }

  inline void CAddonGUIListItem::SetMusicInfo_FLOAT(ADDON_MusicInfoTag type, float value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetMusicInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(float));
  }

  inline void CAddonGUIListItem::SetMusicInfo_STRING(ADDON_MusicInfoTag type, std::string value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetMusicInfo(m_Handle->addonData, m_ListItemHandle, type, (void*)value.c_str(), sizeof(const char*));
  }

  inline void CAddonGUIListItem::SetMusicInfo_STRING_LIST(ADDON_MusicInfoTag type, std::vector<std::string> values)
  {
    unsigned int size = values.size();
    if (type == 0 || size == 0)
      return;

    const char** entries = (const char**)malloc(size*sizeof(const char**));
    for (unsigned int i = 0; i < size; ++i)
      entries[i] = values[i].c_str();

    CAddonGUIListItem::m_cb->ListItem.SetMusicInfo(m_Handle->addonData, m_ListItemHandle, type, &entries, size);
    free(entries);
  }


  inline void CAddonGUIListItem::SetVideoInfo_BOOL(ADDON_VideoInfoTag type, bool value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(bool));
  }

  inline void CAddonGUIListItem::SetVideoInfo_INT(ADDON_VideoInfoTag type, int value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(int));
  }

  inline void CAddonGUIListItem::SetVideoInfo_UINT(ADDON_VideoInfoTag type, unsigned int value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(unsigned int));
  }

  inline void CAddonGUIListItem::SetVideoInfo_FLOAT(ADDON_VideoInfoTag type, float value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(float));
  }

  inline void CAddonGUIListItem::SetVideoInfo_STRING(ADDON_VideoInfoTag type, std::string value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, type, (void*)value.c_str(), sizeof(const char*));
  }

  inline void CAddonGUIListItem::SetVideoInfo_STRING_LIST(ADDON_VideoInfoTag type, std::vector<std::string> values)
  {
    unsigned int size = values.size();
    if (type == 0 || size == 0)
      return;

    const char** entries = (const char**)malloc(size*sizeof(const char**));
    for (unsigned int i = 0; i < size; ++i)
      entries[i] = values[i].c_str();

    CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, type, (void*)entries, size);
    free(entries);
  }

  inline void CAddonGUIListItem::SetVideoInfo_Resume(ADDON_VideoInfoTag_Resume &resume)
  {
    CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, ADDON_VideoInfoTag____resume____________________DATA, &resume, sizeof(ADDON_VideoInfoTag____resume____________________DATA));
  }

  inline void CAddonGUIListItem::SetVideoInfo_Cast(std::vector<ADDON_VideoInfoTag_Cast> &cast)
  {
    unsigned int size = cast.size();
    if (size == 0)
      return;

    ADDON_VideoInfoTag__cast__DATA_STRUCT** entries = (ADDON_VideoInfoTag__cast__DATA_STRUCT**)malloc(size*sizeof(ADDON_VideoInfoTag__cast__DATA_STRUCT**));
    for (unsigned int i = 0; i < size; ++i)
    {
      entries[i] = (ADDON_VideoInfoTag__cast__DATA_STRUCT*)malloc(sizeof(ADDON_VideoInfoTag__cast__DATA_STRUCT*));
      entries[i]->name       = cast[i].name.c_str();
      entries[i]->role       = cast[i].role.c_str();
      entries[i]->order      = cast[i].order;
      entries[i]->thumbnail  = cast[i].thumbnail.c_str();
    }

    CAddonGUIListItem::m_cb->ListItem.SetVideoInfo(m_Handle->addonData, m_ListItemHandle, ADDON_VideoInfoTag____cast______________________DATA_LIST, (void*)entries, size);
    free(entries);
  }

  inline void CAddonGUIListItem::SetPictureInfo_BOOL(ADDON_PictureInfoTag type, bool value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetPictureInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(bool));
  }

  inline void CAddonGUIListItem::SetPictureInfo_INT(ADDON_PictureInfoTag type, int value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetPictureInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(int));
  }

  inline void CAddonGUIListItem::SetPictureInfo_UINT(ADDON_PictureInfoTag type, unsigned int value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetPictureInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(unsigned int));
  }

  inline void CAddonGUIListItem::SetPictureInfo_FLOAT(ADDON_PictureInfoTag type, float value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetPictureInfo(m_Handle->addonData, m_ListItemHandle, type, &value, sizeof(float));
  }

  inline void CAddonGUIListItem::SetPictureInfo_STRING(ADDON_PictureInfoTag type, std::string value)
  {
    if (type != 0)
      CAddonGUIListItem::m_cb->ListItem.SetPictureInfo(m_Handle->addonData, m_ListItemHandle, type, (void*)value.c_str(), sizeof(const char*));
  }

  inline void CAddonGUIListItem::SetPictureInfo_STRING_LIST(ADDON_PictureInfoTag type, std::vector<std::string> values)
  {
    unsigned int size = values.size();
    if (type == 0 || size == 0)
      return;

    const char** entries = (const char**)malloc(size*sizeof(const char**));
    for (unsigned int i = 0; i < size; ++i)
      entries[i] = values[i].c_str();

    CAddonGUIListItem::m_cb->ListItem.SetPictureInfo(m_Handle->addonData, m_ListItemHandle, type, (void*)entries, size);
    free(entries);
  }


}; /* namespace V2 */
}; /* namespace GUILIB */
