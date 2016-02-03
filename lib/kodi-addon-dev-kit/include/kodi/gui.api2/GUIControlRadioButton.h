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
#include "internal/libKODI_guilib_ControlRadioButtonHead.h"
#include "internal/libKODI_guilib_internal.h"

namespace GUILIB
{
namespace V2
{

  ///
  /// \defgroup CAddonGUIControlRadioButton
  /// \ingroup GUILIB
  /// @{
  /// @brief <b>Window control for a radio button (as used for on/off settings)</b>
  ///
  /// The radio button control is used for creating push button on/off settings
  /// in Kodi. You can choose the position, size, and look of the button. When the
  /// user clicks on the radio button, the state will change, toggling the extra
  /// textures (textureradioon and textureradiooff). Used for settings controls.
  ///
  /// It has the header \ref GUIControlRadioButton.h "#include <kodi/gui.api2/GUIControlRadioButton.h>" be included
  /// to enjoy it.
  ///
  /// Here you find the needed skin part for a \ref Radio_button_control "radio button control"
  ///
  /// @note The call of the control is only possible from the corresponding
  /// window as its class and identification number is required.
  ///
  class CAddonGUIControlRadioButton
  {
  public:

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief Construct a new control
    ///
    /// @param[in] window               related window control class
    /// @param[in] controlId            Used skin xml control id
    ///
    CAddonGUIControlRadioButton(CAddonGUIWindow* window, int controlId);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief Destructor
    ///
    virtual ~CAddonGUIControlRadioButton();

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief Set the control on window to visible
    ///
    /// @param[in] visible              If true visible, otherwise hidden
    ///
    void SetVisible(bool visible);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief Set's the control's enabled/disabled state
    ///
    /// @param[in] enabled              If true enabled, otherwise disabled
    ///
    void SetEnabled(bool enabled);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief To set the text string on radio button
    ///
    /// @param[in] label                Text to show
    ///
    void SetLabel(const std::string& label);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief Get the used text from control
    ///
    /// @return                         Text shown
    ///
    std::string GetLabel() const;

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief To set radio button condition to on or off
    ///
    /// @param[in] selected             true set radio button to selection on, otherwise off
    ///
    void SetSelected(bool selected);

    ///
    /// \ingroup CAddonGUIControlRadioButton
    /// @brief Get the current selected condition of radio button
    ///
    /// @return                         Selected condition
    ///
    bool IsSelected() const;

    IMPL_GUI_RADIO_BUTTON_CONTROL;
  };
  /// @}

}; /* namespace V2 */
}; /* namespace GUILIB */

#include "internal/libKODI_guilib_ControlRadioButtonTail.h"
