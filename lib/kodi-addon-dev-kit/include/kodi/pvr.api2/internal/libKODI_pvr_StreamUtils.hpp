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

namespace PVRLIB
{
namespace V2
{

  inline CPVRStream::CPVRStream()
  {
    Clear();
  }

  inline CPVRStream::CPVRStream(const CPVRStream &other)
  {
    memcpy(this, &other, sizeof(PVR_STREAM_PROPERTIES::PVR_STREAM));
  }

  inline CPVRStream& CPVRStream::operator=(const CPVRStream &other)
  {
    memcpy(this, &other, sizeof(PVR_STREAM_PROPERTIES::PVR_STREAM));
    return *this;
  }

  inline bool CPVRStream::operator==(const CPVRStream &other) const
  {
    return iPhysicalId == other.iPhysicalId && iCodecId == other.iCodecId;
  }

  inline bool CPVRStream::operator<(const CPVRStream &other) const
  {
    if (iCodecType == AddOnLIB::V2::KODI_CODEC_TYPE_VIDEO)
      return true;
    else if (other.iCodecType != AddOnLIB::V2::KODI_CODEC_TYPE_VIDEO)
      return iPhysicalId < other.iPhysicalId;
    else
      return false;
  }

  inline bool CPVRStream::IsCleared() const
  {
    return iCodecId   == KODI_INVALID_CODEC_ID &&
           iCodecType == AddOnLIB::V2::KODI_CODEC_TYPE_UNKNOWN;
  }

  inline void CPVRStream::Clear()
  {
    memset(this, 0, sizeof(PVR_STREAM_PROPERTIES::PVR_STREAM));
    iCodecId = KODI_INVALID_CODEC_ID;
    iCodecType = AddOnLIB::V2::KODI_CODEC_TYPE_UNKNOWN;
  }

  /*\___________________________________________________________________________
  \*/

  inline CStreamProperties::CStreamProperties(void)
  {
    // make sure the vector won't have to resize itself later
    m_streamVector = new stream_vector();
    m_streamVector->reserve(PVR_STREAM_MAX_STREAMS);
  }

  inline CStreamProperties::~CStreamProperties(void)
  {
    delete m_streamVector;
  }

  inline void CStreamProperties::Clear(void)
  {
    m_streamVector->clear();
    m_streamIndex.clear();
  }

  inline int CStreamProperties::GetStreamId(unsigned int iPhysicalId) const
  {
    std::map<unsigned int, int>::const_iterator it = m_streamIndex.find(iPhysicalId);
    if (it != m_streamIndex.end())
      return it->second;

    return -1;
  }

  inline CPVRStream* CStreamProperties::GetStreamById(unsigned int iPhysicalId) const
  {
    int position = GetStreamId(iPhysicalId);
    return position != -1 ? &m_streamVector->at(position) : NULL;
  }

  inline void CStreamProperties::GetStreamData(unsigned int iPhysicalId, CPVRStream* stream)
  {
    CPVRStream *foundStream = GetStreamById(iPhysicalId);
    if (foundStream)
      *stream = *foundStream;
    else
    {
      stream->iIdentifier = -1;
      stream->iPhysicalId = iPhysicalId;
    }
  }

  inline bool CStreamProperties::GetProperties(PVR_STREAM_PROPERTIES* props)
  {
    unsigned int i = 0;
    for (stream_vector::const_iterator it = m_streamVector->begin();
         it != m_streamVector->end(); ++it, ++i)
    {
      memcpy(&props->stream[i], &(*it), sizeof(PVR_STREAM_PROPERTIES::PVR_STREAM));
    }

    props->iStreamCount = m_streamVector->size();
    return (props->iStreamCount > 0);
  }

  inline void CStreamProperties::UpdateStreams(stream_vector &newStreams)
  {
    // sort the new streams
    std::sort(newStreams.begin(), newStreams.end());

    // ensure we never have more than PVR_STREAMS_MAX_STREAMS streams
    if (newStreams.size() > PVR_STREAM_MAX_STREAMS)
    {
      while (newStreams.size() > PVR_STREAM_MAX_STREAMS)
        newStreams.pop_back();

      AddOnLIB::V2::CAddonLib_General::Log(AddOnLIB::V2::LOG_ERROR, "%s - max amount of streams reached", __FUNCTION__);
    }

    stream_vector::iterator newStreamPosition;
    for (stream_vector::iterator it = m_streamVector->begin(); it != m_streamVector->end(); ++it)
    {
      newStreamPosition = std::find(newStreams.begin(), newStreams.end(), *it);

      // if the current stream no longer exists we clear it, otherwise we
      // copy it and remove it from newStreams
      if (newStreamPosition == newStreams.end())
        it->Clear();
      else
      {
        *it = *newStreamPosition;
        newStreams.erase(newStreamPosition);
      }
    }

    // replace cleared streams with new streams
    for (stream_vector::iterator it = m_streamVector->begin();
         it != m_streamVector->end() && !newStreams.empty(); ++it)
    {
      if (it->IsCleared())
      {
        *it = newStreams.front();
        newStreams.erase(newStreams.begin());
      }
    }

    // append any remaining new streams
    m_streamVector->insert(m_streamVector->end(), newStreams.begin(), newStreams.end());

    // remove trailing cleared streams
    while (m_streamVector->back().IsCleared())
      m_streamVector->pop_back();

    // update the index
    UpdateIndex();
  }

  /**
   * Updates the stream index
   */
  inline void CStreamProperties::UpdateIndex()
  {
    m_streamIndex.clear();

    int i = 0;
    for (stream_vector::const_iterator it = m_streamVector->begin(); it != m_streamVector->end(); ++it, ++i)
      m_streamIndex[it->iPhysicalId] = i;
  }

}; /* namespace V2 */
}; /* namespace PVRLIB */
