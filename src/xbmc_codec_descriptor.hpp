/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#ifndef XBMC_CODEC_DESCRIPTOR_HPP
#define XBMC_CODEC_DESCRIPTOR_HPP

#include <kodi/addon-instance/PVRClient.h>

/**
 * Adapter which converts codec names used by tvheadend and VDR into their 
 * FFmpeg equivalents.
 */
class CodecDescriptor
{
public:
  CodecDescriptor() = default;
  CodecDescriptor(kodi::addon::PVRCodec codec, const std::string& name) :
    m_codec(codec),
    m_strName(name) {}
  virtual ~CodecDescriptor(void) = default;

  const std::string& Name(void) const  { return m_strName; }
  kodi::addon::PVRCodec Codec(void) const { return m_codec; }

  static CodecDescriptor GetCodecByName(const char* strCodecName)
  {
    CodecDescriptor retVal;
    // some of Tvheadend's and VDR's codec names don't match ffmpeg's, so translate them to something ffmpeg understands
    if (!strcmp(strCodecName, "MPEG2AUDIO"))
      retVal = CodecDescriptor(PVR->GetCodecByName("MP2"), strCodecName);
    else if (!strcmp(strCodecName, "MPEGTS"))
      retVal = CodecDescriptor(PVR->GetCodecByName("MPEG2VIDEO"), strCodecName);
    else if (!strcmp(strCodecName, "TEXTSUB"))
      retVal = CodecDescriptor(PVR->GetCodecByName("TEXT"), strCodecName);
    else
      retVal = CodecDescriptor(PVR->GetCodecByName(strCodecName), strCodecName);

    return retVal;
  }

private:
  kodi::addon::PVRCodec m_codec;
  std::string m_strName;
};

#endif	/* XBMC_CODEC_DESCRIPTOR_HPP */
