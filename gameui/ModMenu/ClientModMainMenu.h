#ifndef CLIENTMODMAINMENU_H
#define CLIENTMODMAINMENU_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/Label.h>

class CLabeledCommandComboBox;


class CCvarToggleCheckButton;
class CCvarSlider;

class ClientModMainMenu;

//-----------------------------------------------------------------------------
// Main Menu properties
//-----------------------------------------------------------------------------
class ClientModMainMenu: public vgui::PropertyPage
{
	DECLARE_CLASS_SIMPLE( ClientModMainMenu, vgui::PropertyPage );

public:
	ClientModMainMenu( vgui::Panel *parent );
	~ClientModMainMenu();

	MESSAGE_FUNC( OnControlModified, "ControlModified" );
	MESSAGE_FUNC_PTR( OnTextChanged, "TextChanged", panel );

	void UpdateViewmodelSliderLabels();

protected:
	MESSAGE_FUNC_PARAMS( OnSliderMoved, "SliderMoved", data );

	// Called when page is loaded.  Data should be reloaded from document into controls.
	virtual void OnResetData();
	// Called when the OK / Apply button is pressed.  Changed data should be written into document.
	virtual void OnApplyChanges();

private:
	CCvarToggleCheckButton*		m_pNewBobbing;
	CCvarSlider*				m_pViewmodelOffsetX;
	vgui::Label*				m_pViewmodelOffsetXLabel;
	CCvarSlider*				m_pViewmodelOffsetY;
	vgui::Label*				m_pViewmodelOffsetYLabel;
	CCvarSlider*				m_pViewmodelOffsetZ;
	vgui::Label*				m_pViewmodelOffsetZLabel;
	CCvarSlider*				m_pViewmodelRecoil;
	vgui::Label*				m_pViewmodelRecoilLabel;
	CLabeledCommandComboBox*	m_pWeaponPos;
};

#endif // CLIENTMODMAINMENU_H
