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
#include "internal/libKODI_guilib_internal.h"
#include "internal/libKODI_guilib_ControlTextBoxHead.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlTextBox
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Used to show a multi-page piece of text</b>
  ///
  /// The text box control can be used to display descriptions, help texts or
  /// other larger texts. It corresponds to the representation which is also to
  /// be seen on the CAddonGUIDialogTextViewer.
  ///
  /// It has the header \ref GUIControlTextBox.h "#include <kodi/gui.api2/GUIControlTextBox.h>" be included
  /// to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Text_Box "textbox control"
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlTextBox
  {
  public:

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CAddonGUIControlTextBox(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief Destructor
    ///
    virtual ~CAddonGUIControlTextBox();

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief To reset box an remove all the text
    ///
    void Reset();

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief To set the text on box
    ///
    /// @param[in] text                 Text to show
    ///
    void SetText(const std::string& text);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief Get the used text from control
    ///
    /// @return                         Text shown
    ///
    std::string GetText() const;

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief To scroll text on other position
    ///
    /// @param[in] position             The line position to scroll to
    ///
    void Scroll(unsigned int position);

    ///
    /// \ingroup CAddonGUIControlTextBox
    /// @brief To set automatic scrolling of textbox
    ///
    /// Specifies the timing and conditions of any autoscrolling this textbox
    /// should have. Times are in milliseconds. The content is delayed for the
    /// given delay, then scrolls at a rate of one line per time interval until
    /// the end. If the repeat tag is present, it then delays for the repeat
    /// time, fades out over 1 second, and repeats. It does not wrap or reset
    /// to the top at the end of the scroll.
    ///
    /// @param[in] delay                Content delay
    /// @param[in] time                 One line per time interval
    /// @param[in] repeat               Delays with given time, fades out over 1 second, and repeats
    ///
    void SetAutoScrolling(int delay, int time, int repeat);

    IMPL_GUI_TEXTBOX_CONTROL;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlTextBoxTail.h"
