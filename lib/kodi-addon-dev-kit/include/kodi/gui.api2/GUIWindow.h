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
#include "GUIListItem.h"
#include "internal/libKODI_guilib_WindowHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \ingroup GUILIB
  /// \defgroup CAddonGUIWindow
  /// @{
  /// @brief <b>Main window control class</b>
  ///
  /// The with  \ref GUIWindow.h "#include <kodi/addon.api2/GUIWindow.h>"
  /// included file brings support to create a window or dialog on Kodi.
  ///
  /// --------------------------------------------------------------------------
  ///
  /// On functions defined input variable <b><tt>controlId</tt> (GUI control identifier)</b>
  /// is the on window.xml defined value behind type added with <tt><b>id="..."</b></tt> and
  /// used to identify for changes there and on callbacks.
  ///
  /// ~~~~~~~~~~~~~{.xml}
  ///  <control type="label" id="31">
  ///    <description>Title Label</description>
  ///    ...
  ///  </control>
  ///  <control type="progress" id="32">
  ///    <description>progress control</description>
  ///    ...
  ///  </control>
  /// ~~~~~~~~~~~~~
  ///
  ///
  class CAddonGUIWindow
  {
  public:
    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Class constructor with needed values for window / dialog.
    ///
    /// Creates a new Window class.
    ///
    /// @param[in] xmlFilename          XML file for the skin
    /// @param[in] defaultSkin          default skin to use if needed not available
    /// @param[in] forceFallback        If set becomes always default skin used (todo: check correct descr.)
    /// @param[in] asDialog             Use window as dialog if set
    ///
    ///
    CAddonGUIWindow(
      const std::string&          xmlFilename,
      const std::string&          defaultSkin,
      bool                        forceFallback,
      bool                        asDialog
    );

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Class destructor
    ///
    ///
    ///
    virtual ~CAddonGUIWindow();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Show this window.
    ///
    /// Shows this window by activating it, calling close() after it wil activate the
    /// current window again.
    ///
    /// @note If your Add-On ends this window will be closed to. To show it forever,
    /// make a loop at the end of your Add-On or use doModal() instead.
    ///
    /// @return                         Return true if call and show is successed,
    ///                                 if false was something failed to get needed
    ///                                 skin parts.
    ///
    bool Show();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Closes this window.
    ///
    /// Closes this window by activating the old window.
    /// @note The window is not deleted with this method.
    ///
    void Close();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Display this window until close() is called.
    ///
    void DoModal();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Gives the control with the supplied focus.
    ///
    /// @param[in] iControlId           On skin defined id of control
    /// @return                         Return true if call and focus is successed,
    ///                                 if false was something failed to get needed
    ///                                 skin parts.
    ///
    ///
    bool SetFocusId(int iControlId);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Returns the id of the control which is focused.
    ///
    /// @return                         Focused control id
    ///
    ///
    int GetFocusId();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To set the used label on given control id
    ///
    /// @param[in] controlId            Control id where label need to set
    /// @param[in] label                Label to use
    ///
    ///
    void SetControlLabel(int controlId, const std::string& label);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Sets a window property, similar to an infolabel.
    ///
    /// @param[in] key                  string - property name.
    /// @param[in] value                string or unicode - value of property.
    ///
    /// @note  Key is NOT case sensitive. Setting value to an empty string is
    ///        equivalent to clearProperty(key).\n
    ///        You can use the above as keywords for arguments and skip certain
    ///        optional arguments.\n
    ///        Once you use a keyword, all following arguments require the keyword.
    ///
    ///
    ///--------------------------------------------------------------------------
    ///
    void SetProperty(const std::string& key, const std::string& value);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Returns a window property as a string, similar to an infolabel.
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         The property as strin (if present)
    ///
    /// @note  Key is NOT case sensitive. Setting value to an empty string is
    ///        equivalent to clearProperty(key).\n
    ///        You can use the above as keywords for arguments and skip certain
    ///        optional arguments.\n
    ///        Once you use a keyword, all following arguments require the keyword.
    ///
    ///
    std::string GetProperty(const std::string& key) const;

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Sets a window property with integer value
    ///
    /// @param[in] key 	                string - property name.
    /// @param[in] value                integer value to set
    ///
    ///
    void SetPropertyInt(const std::string& key, int value);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Returns a window property with integer value
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         integer value of property
    ///
    int GetPropertyInt(const std::string& key) const;

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Sets a window property with boolean value
    ///
    /// @param[in] key 	                string - property name.
    /// @param[in] value                boolean value to set
    ///
    ///
    void SetPropertyBool(const std::string& key, bool value);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Returns a window property with boolean value
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         boolean value of property
    ///
    bool GetPropertyBool(const std::string& key) const;

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Sets a window property with double value
    ///
    /// @param[in] key 	                string - property name.
    /// @param[in] value                double value to set
    ///
    ///
    void SetPropertyDouble(const std::string& key, double value);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Returns a window property with double value
    ///
    /// @param[in] key 	                string - property name.
    /// @return                         double value of property
    ///
    ///
    double GetPropertyDouble(const std::string& key) const;

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Remove all present properties from window
    ///
    ///
    ///
    void ClearProperties();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Clears the specific window property.
    ///
    /// @param[in] key                string - property name.
    ///
    /// @note Key is NOT case sensitive. Equivalent to SetProperty(key, "")
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
    /// ClearProperty('Category')
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    void ClearProperty(const std::string& key);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Add a string named item to the integrated list.
    ///
    /// @note On delete of "CAddonGUIListItem" is item not removed from list on window.
    ///
    ///
    /// @warning Class need to be deleted after it is not used anymore
    ///
    /// @param[in] name                 Name of the item to add
    /// @param[in] itemPosition         [opt] The position for item, default is on end
    /// @return
    ///
    ///
    CAddonGUIListItem* AddStringItem(const std::string& name, int itemPosition = -1);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To add a list item in the on window integrated list.
    ///
    /// @param[in] item                 List item to add
    /// @param[in] itemPosition         [opt] The position for item, default is on end
    ///
    ///
    void AddItem(CAddonGUIListItem* item, int itemPosition = -1);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Remove list item on position.
    ///
    /// @param[in] itemPosition         List position to remove
    ///
    ///
    void RemoveItem(int itemPosition);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Remove item with given control class from list.
    ///
    /// @note Related control class is not deleted.
    ///
    /// @param[in] item                 List item control class to remove
    ///
    ///
    void RemoveItem(CAddonGUIListItem* item);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To get list item control class on wanted position.
    ///
    /// @param[in] listPos              Position from where control is needed
    /// @return                         The list item control class or null if not found
    ///
    /// @warning Function returns a new generated **CAddonGUIListItem** class, which
    /// to delete. Every call of this generare a new class!
    ///
    CAddonGUIListItem* GetListItem(int listPos);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To set position of selected part in list.
    ///
    /// @param[in] listPos              Position to use
    ///
    ///
    void SetCurrentListPosition(int listPos);

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To get current selected position in list
    ///
    /// @return                         Current list position
    ///
    ///
    int GetCurrentListPosition();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To get the amount of entries in the list.
    ///
    /// @return                         Size of in window integrated control class
    ///
    ///
    int GetListSize();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief Function delete all entries in integrated list.
    ///
    ///
    ///
    void ClearList();

    ///
    /// \ingroup CAddonGUIWindow
    /// @brief To inform Kodi that it need to render region new.
    ///
    ///
    ///
    void MarkDirtyRegion();

    //
    /// @defgroup CAddonGUIWindow_callbacks Callback functions from Kodi to add-on
    /// \ingroup CAddonGUIWindow
    /// @{
    /// @brief <b>GUI window callback functions.</b>
    ///
    /// Functions to handle control callbacks from Kodi
    ///
    /// ------------------------------------------------------------------------
    ///
    /// @link CAddonGUIWindow Go back to normal functions from CAddonGUIWindow@endlink
    //

    ///
    /// \ingroup CAddonGUIWindow_callbacks
    /// @brief OnInit method.
    ///
    /// @return                         Return true if initialize was done successful
    ///
    ///
    virtual bool OnInit() { }

    ///
    /// \ingroup CAddonGUIWindow_callbacks
    /// @brief OnFocus method.
    ///
    /// @param[in] controlId            GUI control identifier
    /// @return                         Return true if focus condition was handled there or false to handle them by Kodi itself
    ///
    ///
    virtual bool OnFocus(int controlId) { }

    ///
    /// \ingroup CAddonGUIWindow_callbacks
    /// @brief OnClick method.
    ///
    /// @param[in] controlId            GUI control identifier
    /// @return                         Return true if click was handled there
    ///                                 or false to handle them by Kodi itself
    ///
    ///
    virtual bool OnClick(int controlId) { }

    ///
    /// \ingroup CAddonGUIWindow_callbacks
    /// @brief OnAction method.
    ///
    /// @param[in] actionId             The action id to perform, see
    ///                                 \ref kodi_key_action_ids to get list of
    ///                                 them
    /// @return                         Return true if action was handled there
    ///                                 or false to handle them by Kodi itself
    ///
    ///
    /// This method will receive all actions that the main program will send
    /// to this window.
    ///
    /// @note
    /// - By default, only the \c PREVIOUS_MENU and \c NAV_BACK actions are handled.
    /// - Overwrite this method to let your code handle all actions.
    /// - Don't forget to capture \c ADDON_ACTION_PREVIOUS_MENU or \c ADDON_ACTION_NAV_BACK, else the user can't close this window.
    ///
    ///
    ///--------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ..
    /// /* Window used with parent / child way */
    /// bool cYOUR_CLASS::OnAction(int actionId)
    /// {
    ///   switch (action)
    ///   {
    ///     case ADDON_ACTION_PREVIOUS_MENU:
    ///     case ADDON_ACTION_NAV_BACK:
    ///       printf("action recieved: previous");
    ///       Close();
    ///       return true;
    ///     case ADDON_ACTION_SHOW_INFO:
    ///       printf("action recieved: show info");
    ///       break;
    ///     case ADDON_ACTION_STOP:
    ///       printf("action recieved: stop");
    ///       break;
    ///     case ADDON_ACTION_PAUSE:
    ///       printf("action recieved: pause");
    ///       break;
    ///     default:
    ///       break;
    ///   }
    ///   return false;
    /// }
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    virtual bool OnAction(int actionId) { }

    ///
    /// \ingroup CAddonGUIWindow_callbacks
    /// @brief **Set independent callbacks**
    ///
    /// If the class is used independent (with "new CAddonGUIWindow") and
    /// not as parent (with "cCLASS_own : CAddonGUIWindow") from own must be the
    /// callback from Kodi to add-on overdriven with own functions!
    ///
    /// @param[in] cbhdl                The pointer to own handle data
    ///                                 structure / class
    /// @param[in] CBOnInit             Own defined window init function
    /// @param[in] CBOnFocus            Own defined focus function
    /// @param[in] CBOnClick            Own defined click function
    /// @param[in] CBOnAction           Own defined action function
    ///
    ///
    ///--------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.cpp}
    /// ...
    ///
    /// bool OnInit(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// bool OnFocus(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// bool OnClick(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// bool OnAction(GUIHANDLE cbhdl)
    /// {
    ///   ...
    ///   return true;
    /// }
    ///
    /// ...
    /// /* Somewhere where you create the window */
    /// CAddonGUIWindow myWindow = new CAddonGUIWindow;
    /// myWindow->SetIndependentCallbacks(myWindow, OnInit, OnFocus, OnClick, OnAction);
    /// ...
    /// ~~~~~~~~~~~~~
    ///
    void SetIndependentCallbacks(
      GUIHANDLE             cbhdl,
      bool    (*CBOnInit)  (GUIHANDLE cbhdl),
      bool    (*CBOnFocus) (GUIHANDLE cbhdl, int controlId),
      bool    (*CBOnClick) (GUIHANDLE cbhdl, int controlId),
      bool    (*CBOnAction)(GUIHANDLE cbhdl, int actionId)
    );

    IMPLEMENT_ADDON_GUI_WINDOW;
  };
  ///@}

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_WindowTail.h"
