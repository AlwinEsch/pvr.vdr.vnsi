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

#include "internal/AddonLib_internal.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

  //============================================================================
  ///
  /// \ingroup KodiAddon_C_Main
  /// \ingroup KodiAddon_CPP_Main
  /// @brief The current add-on interface API level
  /// 
  extern const int   KODI_API_Level;
  ///
  /// \ingroup KodiAddon_C_Main
  /// \ingroup KodiAddon_CPP_Main
  /// @brief The complete Version of this interface architecture.
  /// 
  extern const char* KODI_API_Version;
  //----------------------------------------------------------------------------
  
  
  //============================================================================
  /// @{
  /// \ingroup KodiAddon_C_Main
  /// \ingroup KodiAddon_CPP_Main
  /// @brief KODI API Error Classes
  ///
  /// The error codes are to describe the caused errors on interface.
  ///  
  typedef enum KODI_API_Errortype
  {
    /// @brief Successful return code
    API_SUCCESS                 = 0,

    /// @brief Invalid buffer pointer
    API_ERR_BUFFER              = 1,

    /// @brief Invalid count argument
    API_ERR_COUNT               = 2,

    /// @brief Invalid datatype argument
    API_ERR_TYPE                = 3,

    /// @brief Invalid tag argument
    API_ERR_TAG                 = 4,

    /// @brief Invalid communicator
    API_ERR_COMM                = 5,

    /// @brief Invalid rank
    API_ERR_RANK                = 6,

    /// @brief Invalid root
    API_ERR_ROOT                = 7,

    /// @brief Null group passed to function
    API_ERR_GROUP               = 8,

    /// @brief Invalid operation
    API_ERR_OP                  = 9,

    /// @brief Invalid topology
    API_ERR_TOPOLOGY            = 10,

    /// @brief Illegal dimension argument
    API_ERR_DIMS                = 11,

    /// @brief Invalid argument
    API_ERR_ARG                 = 12,

    /// @brief Unknown error
    API_ERR_UNKNOWN             = 13,

    /// @brief message truncated on receive
    API_ERR_TRUNCATE            = 14,

    /// @brief Other error; use Error_string
    API_ERR_OTHER               = 15,

    /// @brief internal error code
    API_ERR_INTERN              = 16,

    /// @brief Look in status for error value
    API_ERR_IN_STATUS           = 17,

    /// @brief Pending request
    API_ERR_PENDING             = 18,

    /// @brief illegal API_request handle
    API_ERR_REQUEST             = 19,

    /// @brief failed to connect
    API_ERR_CONNECTION          = 20,

    /// @brief Last error code -- always at end
    API_ERR_LASTCODE            = 21
  } KODI_API_Errortype;
  /// @}
  //----------------------------------------------------------------------------
  
  
  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief Last error code generated from lib
  ///
  /// Becomes only be set if on  function on  error the  return of them  is  not
  /// possible, e.g. `KodiAPI_Init`.
  ///
  /// Human readable string can be retrived with `KodiAPI_ErrorCodeToString`.
  ///
  extern uint32_t KODI_API_lasterror;
  //----------------------------------------------------------------------------
  
  
  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief Get string for error code
  ///
  /// To  translate a from several functions used error code in a human readable
  /// format
  ///
  /// @param[in] code         Error value to translate to string
  /// @return                 String about error
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.c}
  /// #include <AddonLib.h>
  ///
  /// KODI_HANDLE handle;
  ///
  /// ...
  /// handle = KodiAPI_Init(argc, argv, &props);
  /// if (handle == nullptr)
  /// {
  ///   fprintf(stderr, "Binary AddOn: %s\n", KodiAPI_ErrorCodeToString(KODI_API_lasterror));
  ///   return 1;
  /// }
  /// ...
  /// ~~~~~~~~~~~~~
  ///
  const char* KodiAPI_ErrorCodeToString(uint32_t code);
  //----------------------------------------------------------------------------
  
  
  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief
  /// 
  ///
  typedef struct addon_properties
  {
    ///
    /// @brief The own name.
    ///
    /// The human readable name of add-on used from Kodi e.g. in Log entries.
    ///
    const char* addon_name;
    ///
    /// @brief To inform add-on is independent from Kodi. 
    ///
    /// To  inform Kodi  that add-on  is independent and is not  stopped by Kodi 
    /// after calling "KodiAPI_Finalize".
    ///
    bool        is_independent;
    ///
    /// @brief Option to create interface only over network.
    ///
    /// @note Should be  ignored and set  to false.  Is passicly  used for  test
    /// purpose only.
    ///
    bool        use_net_only;
  } addon_properties;
  //----------------------------------------------------------------------------

  
  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief Add-on initialization function
  ///
  /// @warning Function only be needed on binary executable add-ons for Kodi!
  ///
  /// To be used for initialization of main interface  from Add-on to Kodi. This
  /// is  the  master  to be used  on  the  executables  <b><c>main(...)</c></b>
  /// function.
  ///
  /// The returned handle  is used on all  related Add-on to Kodi calls as first
  /// function value.
  ///
  /// @warning The  returned handle  is only be  used on his thread,  if another
  /// thread    is   created,   should    be   another  handle   returned   from
  /// <b><c>KodiAPI_InitThread(...)</c></b> to be used!\n\n
  /// Further  is  this  call   only   be   allowed   to   call   one   time  on 
  /// <b><c>main(...)</c></b>.\n\n
  /// Also  should  never  forget  to  call  <b><c>KodiAPI_Finalize(...)</c></b>
  /// before exit  of  addon  to   prevent  problems   about  still  organizated
  /// communication interface between Kodi and Add-on
  ///
  /// @param[in] argc         Amount of command line values present
  /// @param[in] argv[]       String list with given command line values
  /// @param[in] props        From add-on developer requested  properties on his
  ///                         add-on to Kodi.
  /// @return                 The for other calls  on his thread  needed  Handle
  ///                         identifier, which always  passed as  first command
  ///                         there.
  ///
  /// @note If pointer is  returned  NULL is the  related last  error code  with
  /// `uint32_t KODI_API_lasterror` available.
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.c}
  /// #include <AddonLib.h>
  ///
  /// KODI_HANDLE handle;
  ///
  /// int main(int argc, char *argv[])
  /// {
  ///   addon_properties props;
  ///   props.addon_name      = "My Demo binary add-on";
  ///   props.is_independent  = false;
  ///     
  ///   handle = KodiAPI_Init(argc, argv, &props);
  ///   if (handle == nullptr)
  ///   {
  ///     fprintf(stderr, "Binary AddOn: %s\n", KodiAPI_ErrorCodeToString(KODI_API_lasterror));
  ///     return 1;
  ///   }
  ///   ...
  ///   return 0;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  KODI_HANDLE KodiAPI_Init(
    int               argc, 
    char*             argv[], 
    addon_properties* props);
  //----------------------------------------------------------------------------


  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief Add-on's thread to Kodi's API creation
  ///
  /// @warning Function only be needed on binary executable add-ons for Kodi!
  ///
  /// This function creates the interface to Kodi for a new thread created  from
  /// add-on.If on new thread no call to Kodi's API is used can be this ignored.
  /// 
  /// @warning A call of  <b><c>KodiAPI_Finalize(...)</c></b> on thread  end  is
  /// needed if this function is used!\n\n
  /// Also  can  this  function only  be  used on  Threads new  process function
  /// `void* CThread::Process(void)` to have work on right thread id!
  ///
  /// 
  /// @return                 The for other  calls on  his thread needed  Handle
  ///                         identifier, which always passed  as first  command
  ///                         there.
  ///
  /// @note If pointer is returned  NULL is  the related  last error  code  with
  /// `uint32_t KODI_API_lasterror` available.
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.c}
  /// #include <AddonLib.h>
  ///
  /// void* CThreadTest::Process(void)
  /// {
  ///   KODI_HANDLE handle = KodiAPI_InitThread();
  ///
  ///   int cnt = 8;
  ///   while (!IsStopped())
  ///   {
  ///     sleep(1);
  ///     cnt--;
  ///     KodiAPI_Log(handle, LOG_ERROR, "Countdown ---> %i", cnt);
  ///
  ///     if (cnt == 0)
  ///       break;
  ///   }
  ///
  ///   KodiAPI_Finalize(handle);
  ///   return nullptr;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  ///
  KODI_HANDLE KodiAPI_InitThread();
  //----------------------------------------------------------------------------

  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief Resolve all callback methods for shared library type add-on
  ///
  /// @warning This function is only be used on shared library add-on for Kodi!
  ///
  /// This  function  link the all functions from  library to  kodi and  without
  /// this call are them note usable.
  ///
  /// @note The required handle becomes only be send from ADDON_Create call.
  ///
  /// @param[in] handle       Pointer to the shared lib add-on
  /// @return                 The for other  calls on  his thread needed  Handle
  ///                         identifier, which always passed  as first  command
  ///                         there.
  ///
  /// @note If pointer is returned  NULL is  the related  last error  code  with
  /// `uint32_t KODI_API_lasterror` available.
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.c}
  /// #include <AddonLib.h>
  ///
  /// // Insert one macro on your add-on for it
  /// KODI_HANDLE handle;
  /// ...
  /// ADDON_STATUS ADDON_Create(void* hdl, void* props)
  /// {
  ///   ...
  ///   // Enable access to all add-on to Kodi functions
  ///   handle = KodiAPI_InitLibAddon(hdl);
  ///   if (handle == nullptr)
  ///   {
  ///     fprintf(stderr, "Binary AddOn: %s\n", KodiAPI_ErrorCodeToString(KODI_API_lasterror));
  ///     return ADDON_STATUS_PERMANENT_FAILURE;
  ///   }
  ///
  ///   ...
  /// }
  /// ~~~~~~~~~~~~~
  ///
  ///
  KODI_HANDLE KodiAPI_InitLibAddon(void* hdl);
  //----------------------------------------------------------------------------
  
  
  //============================================================================
  /// \ingroup KodiAddon_C_Main
  /// @brief To close Add-on to Kodi control interface
  ///
  /// This function is required after end of processes and on exit of them, e.g.
  /// Add-on itself exits or a thread with handling becomes closed.
  /// 
  /// @param[in] handle       The from KodiAPI_Init(...) or KodiAPI_InitThread(...)
  ///                         generated handle to close
  /// @return                 Add-on error codes from `KODI_API_Errortype` or if
  ///                         OK with `API_SUCCESS`
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example 1:**
  /// ~~~~~~~~~~~~~{.c}
  /// #include <AddonLib.h>
  ///
  /// KODI_HANDLE handle;
  ///
  /// int main(int argc, char *argv[])
  /// {
  ///   addon_properties props;
  ///   ...
  ///     
  ///   handle = KodiAPI_Init(argc, argv, &props);
  ///   ...
  ///   
  ///   KodiAPI_Finalize(handle);
  ///   return 0;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example 2:**
  /// ~~~~~~~~~~~~~{.c}
  /// #include <AddonLib.h>
  ///
  /// void* CThreadTest::Process(void)
  /// {
  ///   KODI_HANDLE handle; = KodiAPI_InitThread();
  ///
  ///   while (!IsStopped())
  ///   {
  ///     ...
  ///   }
  ///
  ///   KodiAPI_Finalize(handle);
  ///   return nullptr;
  /// }
  /// ~~~~~~~~~~~~~
  ///
  int KodiAPI_Finalize(
    KODI_HANDLE      handle);
  //----------------------------------------------------------------------------


  //============================================================================
  /// \ingroup KodiAddon_C_General
  /// \ingroup KodiAddon_CPP_General
  /// @brief
  ///
  typedef enum addon_log
  {
    /// @brief Log level "Debug"
    ///
    /// In  depth  informatio n about  the  status  of  Kodi.  This  information 
    /// can  pretty  much only be  deciphered  by a developer or  long time Kodi 
    /// power user.
    ///
    ADDON_LOG_DEBUG,

    /// @brief Log level "Info"
    /// 
    /// Something  has happened. It's not  a problem, we just  thought you might 
    /// want to know. Fairly excessive output that most people won't care about.
    ///
    ADDON_LOG_INFO,

    /// @brief Log level "Notice"
    /// 
    /// Similar  to  INFO but  the average  Joe might  want to  know about these 
    /// events. This level and above are logged by default.
    ///
    ADDON_LOG_NOTICE,

    /// @brief Log level "Warning"
    /// 
    /// Something potentially bad has happened. If Kodi did something you didn't 
    /// expect, this is probably why. Watch for errors to follow.
    ///
    ADDON_LOG_WARNING,

    /// @brief Log level "Error"
    /// 
    /// This event is bad.  Something has failed.  You  likely noticed  problems 
    /// with the application be it skin artifacts, failure of playback a crash,
    /// etc.
    ///
    ADDON_LOG_ERROR,

    /// @brief Log level "Severe"
    ///
    ADDON_LOG_SEVERE,

    /// @brief Log level "Fatal"
    /// 
    /// We're screwed. Kodi's add-on is about to crash.
    ///
    ADDON_LOG_FATAL
  } addon_log;
  //----------------------------------------------------------------------------
  
  
  //============================================================================
  /// \ingroup KodiAddon_C_General
  /// @brief Add a message to [KODI's log](http://kodi.wiki/view/Log_file/Advanced#Log_levels).
  ///
  /// @param[in] handle       With KodiAPI_Init or KodiAPI_InitThread retrieved
  ///                         handle for processes on add-on
  /// @param[in] loglevel     The log level of the message
  ///  |  enum code:  | Description:          |
  ///  |-------------:|-----------------------|
  ///  |  LOG_DEBUG   | In depth information about the status of Kodi. This information can pretty much only be deciphered by a developer or long time Kodi power user.
  ///  |  LOG_INFO    | Something has happened. It's not a problem, we just thought you might want to know. Fairly excessive output that most people won't care about.
  ///  |  LOG_NOTICE  | Similar to INFO but the average Joe might want to know about these events. This level and above are logged by default.
  ///  |  LOG_WARNING | Something potentially bad has happened. If Kodi did something you didn't expect, this is probably why. Watch for errors to follow.
  ///  |  LOG_ERROR   | This event is bad. Something has failed. You likely noticed problems with the application be it skin artifacts, failure of playback a crash, etc.
  ///  |  LOG_FATAL   | We're screwed. Kodi is about to crash.
  /// @param[in] format       The format of the message to pass to KODI.
  /// @param[in] ...          Added string values
  ///
  ///
  /// --------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.c}
  /// KODI_HANDLE handle;
  ///
  /// int main(int argc, char *argv[])
  /// {
  ///   addon_properties props;
  ///   props.addon_name      = "My Demo binary add-on";
  ///   props.is_independent  = false;
  ///   ...
  ///     
  ///   handle = KodiAPI_Init(argc, argv, &props);
  ///   if (!handle)
  ///     exit(1);
  ///   ...
  ///   KodiAPI_Log(handle, LOG_FATAL, "Oh my goddess, I'm so fatal ;)");
  ///   ...
  /// }
  /// ~~~~~~~~~~~~~
  ///
  void KodiAPI_Log(
    KODI_HANDLE       handle,
    const addon_log   loglevel, 
    const char*       format, 
    ... );
  //----------------------------------------------------------------------------


#ifdef __cplusplus
}; /* extern "C" */
#endif
