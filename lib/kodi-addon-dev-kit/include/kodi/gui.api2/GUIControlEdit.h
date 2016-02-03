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
#include "internal/libKODI_guilib_ControlEditHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlEdit
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Editable window text control used as an input control for the osd
  /// keyboard and other input fields</b>
  ///
  /// The edit control allows a user to input text in Kodi. You can choose the
  /// font, size, colour, location and header of the text to be displayed.
  ///
  /// It has the header \ref GUIControlFadeLabel.h "#include <kodi/gui.api2/GUIControlFadeLabel.h>" be included
  /// to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref skin_Edit_control "edit control"
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlEdit
  {
  public:
    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CAddonGUIControlEdit(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Destructor
    ///
    virtual ~CAddonGUIControlEdit();

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param[in] enabled              If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled);

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief To set the text string on edit control
    ///
    /// @param[in] label                Text to show
    ///
    void SetLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Returns the text heading for this edit control.
    ///
    /// @return                         Heading text
    ///
    std::string GetLabel() const;

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Set's text heading for this edit control.
    ///
    /// @param[in] text                 string or unicode - text string.
    ///
    void SetText(const std::string& text);

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Returns the text value for this edit control.
    ///
    /// @return                         Text value of control
    ///
    std::string GetText() const;

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief Set the cursor position on text.
    ///
    /// @param[in] iPosition            The position to set
    ///
    void SetCursorPosition(unsigned int iPosition);

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief To get current cursor position on text field
    ///
    /// @return                         The current cursor position
    ///
    unsigned int GetCursorPosition();

    ///
    /// \ingroup CAddonGUIControlEdit
    /// @brief To set field input type which are defined on \ref AddonGUIInputType
    ///
    /// @param[in] type                 The \ref AddonGUIInputType "Add-on input type" to use
    /// @param[in] heading              The heading text for related keyboard dialog
    ///
    void SetInputType(AddonGUIInputType type, const std::string& heading);

    IMPL_GUI_EDIT_CONTROL;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlEditTail.h"
