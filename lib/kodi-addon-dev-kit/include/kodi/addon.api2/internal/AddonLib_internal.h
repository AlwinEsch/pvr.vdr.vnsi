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

#include <stdbool.h>
#include <stdint.h>
#include <semaphore.h>

/*
 * This file includes not for add-on developer used parts, but required for the
 * interface to Kodi over the library.
 */

#ifdef __cplusplus
extern "C"
{
#endif

  extern const int KODI_API_ConnectionTimeout;
  extern const int KODI_API_ConnectionPort;

  typedef void* KODI_HANDLE;
  
  typedef enum KODI_API_Calls
  {
    KODICall_Noop                     = 0,
    KODICall_LoginVerify              = 1,
    KODICall_Logout                   = 2,
    KODICall_Ping                     = 3,
    KODICall_Log                      = 4,
    KODICall_CreateSubThread          = 5,
    KODICall_DeleteSubThread          = 6

  } KODI_API_Calls;

  typedef enum KODI_API_Packets
  {
    KODIPacket_RequestedResponse      = 1,
    KODIPacket_Status                 = 2

  } KODI_API_Packets;

  typedef struct KODI_API_ErrorTranslator
  {
    uint32_t    errorCode;
    const char* errorName;
  } KODI_API_ErrorTranslator;
  
  extern const KODI_API_ErrorTranslator errorTranslator[];

  /// @{
  /// @brief
  typedef enum KODI_API_Datatype
  {
    /// @brief
    API_DATATYPE_NULL           = 0x00000000,

    /// @{
    /// @brief
    API_CHAR                    = 0x00000001,
    /// @brief
    API_SIGNED_CHAR             = 0x00000002,
    /// @brief
    API_UNSIGNED_CHAR           = 0x00000003,
    /// @}

    /// @{
    /// @brief
    API_SHORT                   = 0x00000101,
    /// @brief
    API_SIGNED_SHORT            = 0x00000102,
    /// @brief
    API_UNSIGNED_SHORT          = 0x00000103,
    /// @}

    /// @{
    /// @brief
    API_INT                     = 0x00000201,
    /// @brief
    API_SIGNED_INT              = 0x00000202,
    /// @brief
    API_UNSIGNED_INT            = 0x00000203,
    /// @}

    /// @{
    /// @brief
    API_LONG                    = 0x00000301,
    /// @brief
    API_SIGNED_LONG             = 0x00000302,
    /// @brief
    API_UNSIGNED_LONG           = 0x00000303,
    /// @}

    /// @{
    /// @brief
    API_FLOAT                   = 0x00000501,
    /// @brief
    API_DOUBLE                  = 0x00000511,
    /// @brief
    API_LONG_DOUBLE             = 0x00000521,
    /// @}

    /// @{
    /// @brief
    API_INT8_T                  = 0x00000701,
    /// @brief
    API_INT16_T                 = 0x00000702,
    /// @brief
    API_INT32_T                 = 0x00000703,
    /// @brief
    API_INT64_T                 = 0x00000704,
    /// @}

    /// @{
    /// @brief
    API_UINT8_T                 = 0x00000801,
    /// @brief
    API_UINT16_T                = 0x00000802,
    /// @brief
    API_UINT32_T                = 0x00000803,
    /// @brief
    API_UINT64_T                = 0x00000804,
    /// @}

    API_BOOLEAN                 = 0x00000901,
    API_STRING                  = 0x00000911,

    /// @{
    /// @brief
    API_PACKED                  = 0x00001001,
    /// @brief
    API_LB                      = 0x00001002,
    /// @brief
    API_UB                      = 0x00001003,
    /// @}

    /// @{
    /// @brief The layouts for the types API_DOUBLE_INT etc are simply
    ///
    /// ~~~~~~~~~~~~~
    /// struct
    /// {
    ///   double var;
    ///   int    loc;
    /// }
    ///
    /// This is documented in the man pages on the various datatypes.
    ///

    /// @brief
    API_FLOAT_INT               = 0x00002001,
    /// @brief
    API_DOUBLE_INT              = 0x00002002,
    /// @brief
    API_LONG_INT                = 0x00002003,
    /// @brief
    API_SHORT_INT               = 0x00002004,
    /// @brief
    API_2INT                    = 0x00002005,
    /// @brief
    API_LONG_DOUBLE_INT         = 0x00002006
    /// @}
  } KODI_API_Datatype;
  /// @}

  typedef union valueType
  {
    float   float_par;
    double  double_par;
    int     int_par;
    bool    bool_par;
    const char* string_par;
  } valueType;
  
  typedef struct KodiAPI_Message
  {
    uint32_t              messageId;
    
    valueType             value1;
    valueType             value2;
    valueType             value3;
    valueType             value4;
    valueType             value5;
    valueType             retValue;
  
    uint8_t               data[];
  } KodiAPI_Message;
  
  typedef struct KodiAPI_ShareData
  {
  #if (defined TARGET_WINDOWS)
    HANDLE          shmSegmentToAddon;
    HANDLE          shmSegmentToKodi;
  #elif (defined TARGET_POSIX)
    sem_t           shmSegmentToAddon;
    sem_t           shmSegmentToKodi;
  #endif
    KodiAPI_Message message;
  } KodiAPI_ShareData;
  
  #define MAX_SEM_COUNT 10 // To use for windows CreateSemaphore(...)

#ifdef __cplusplus
}; /* extern "C" */
#endif
