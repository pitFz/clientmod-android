#if defined( WIN32 ) && !defined( _X360 )
#include <windows.h> // SRC only!!
#endif

#include "ClientModMainMenu.h"
#include <stdio.h>

#include <vgui_controls/Button.h>
#include "tier1/KeyValues.h"
#include <vgui_controls/Label.h>
#include <vgui/ISystem.h>
#include <vgui/ISurface.h>
#include <vgui_controls/ComboBox.h>
#include "vgui_controls/QueryBox.h"

#include "CvarTextEntry.h"
#include "CvarToggleCheckButton.h"
#include "cvarslider.h"
#include "LabeledCommandComboBox.h"
#include "EngineInterface.h"
#include "tier1/convar.h"

#if defined( _X360 )
#include "xbox/xbox_win32stubs.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Basic help dialog
//-----------------------------------------------------------------------------
ClientModMainMenu::ClientModMainMenu( vgui::Panel *parent ): vgui::PropertyPage( parent, "ClientModMainMenu" )
{
	Button *cancel = new Button( this, "Cancel", "#GameUI_Cancel" );
	cancel->SetCommand( "Close" );

	Button *ok = new Button( this, "OK", "#GameUI_OK" );
	ok->SetCommand( "Ok" );

	Button *apply = new Button( this, "Apply", "#GameUI_Apply" );
	apply->SetCommand( "Apply" );

	//add params

	
	
	m_pViewmodelOffsetX = new CCvarSlider( this, "ViewmodelOffsetXSlider", "", -5.0f, 5.0f, "viewmodel_offset_x" );
	m_pViewmodelOffsetXLabel = new Label( this, "ViewmodelOffsetXLabel", "" );
	m_pViewmodelOffsetY = new CCvarSlider( this, "ViewmodelOffsetYSlider", "", -5.0f, 5.0f, "viewmodel_offset_y" );
	m_pViewmodelOffsetYLabel = new Label( this, "ViewmodelOffsetYLabel", "" );
	m_pViewmodelOffsetZ = new CCvarSlider( this, "ViewmodelOffsetZSlider", "", -5.0f, 5.0f, "viewmodel_offset_z" );
	m_pViewmodelOffsetZLabel = new Label( this, "ViewmodelOffsetZLabel", "" );
	m_pViewmodelRecoil = new CCvarSlider( this, "ViewmodelRecoilSlider", "", 0.0f, 2.0f, "viewmodel_recoil" );
	m_pViewmodelRecoilLabel = new Label( this, "ViewmodelRecoilLabel", "" );
	m_pWeaponPos = new CLabeledCommandComboBox( this, "WeaponPositionComboBox" );
    m_pNewBobbing = new CCvarToggleCheckButton( this, "NewBobbing", "#GameUI_NewBobbing", "cmod_new_bobbing" );

	m_pWeaponPos->AddItem( "#GameUI_Viewmodel_HandLeft", "cl_righthand 0" );
	m_pWeaponPos->AddItem( "#GameUI_Viewmodel_HandRight", "cl_righthand 1" );

	m_pNewBobbing->AddActionSignalTarget( this );
	m_pViewmodelOffsetX->AddActionSignalTarget( this );
	m_pViewmodelOffsetY->AddActionSignalTarget( this );
	m_pViewmodelOffsetZ->AddActionSignalTarget( this );
	m_pViewmodelRecoil->AddActionSignalTarget( this );
	m_pWeaponPos->AddActionSignalTarget( this );

	LoadControlSettings( "Resource/ClientModMainMenu.res" );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
ClientModMainMenu::~ClientModMainMenu()
{
}

void ClientModMainMenu::UpdateViewmodelSliderLabels()
{
	char strValue[8];
	Q_snprintf( strValue, sizeof( strValue ), "%2.1f", m_pViewmodelOffsetX->GetSliderValue() );
	m_pViewmodelOffsetXLabel->SetText( strValue );
	Q_snprintf( strValue, sizeof( strValue ), "%2.1f", m_pViewmodelOffsetY->GetSliderValue() );
	m_pViewmodelOffsetYLabel->SetText( strValue );
	Q_snprintf( strValue, sizeof( strValue ), "%2.1f", m_pViewmodelOffsetZ->GetSliderValue() );
	m_pViewmodelOffsetZLabel->SetText( strValue );
	Q_snprintf( strValue, sizeof( strValue ), "%2.1f", m_pViewmodelRecoil->GetSliderValue() );
	m_pViewmodelRecoilLabel->SetText( strValue );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ClientModMainMenu::OnControlModified()
{
	PostMessage( GetParent(), new KeyValues( "ApplyButtonEnable" ) );
	InvalidateLayout();
}

void ClientModMainMenu::OnSliderMoved( KeyValues *data )
{
	vgui::Panel* pPanel = static_cast<vgui::Panel*>(data->GetPtr( "panel" ));

	if ( pPanel == m_pViewmodelOffsetX || pPanel == m_pViewmodelOffsetY || pPanel == m_pViewmodelOffsetZ ||  pPanel == m_pViewmodelRecoil )
	{
		UpdateViewmodelSliderLabels();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ClientModMainMenu::OnResetData()
{
 	m_pNewBobbing->Reset();
 	m_pViewmodelOffsetX->Reset();
 	m_pViewmodelOffsetY->Reset();
 	m_pViewmodelOffsetZ->Reset();
 	m_pViewmodelRecoil->Reset();
	 UpdateViewmodelSliderLabels();
 
 	ConVarRef cl_righthand( "cl_righthand" );
 	if ( cl_righthand.IsValid() )
 	 m_pWeaponPos->SetInitialItem( cl_righthand.GetInt() );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void ClientModMainMenu::OnApplyChanges()
{
	m_pNewBobbing->ApplyChanges();
	m_pViewmodelOffsetX->ApplyChanges();
	m_pViewmodelOffsetY->ApplyChanges();
	m_pViewmodelOffsetZ->ApplyChanges();
	m_pViewmodelRecoil->ApplyChanges();
	m_pWeaponPos->ApplyChanges();
}
