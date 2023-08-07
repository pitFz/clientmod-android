//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "BasePanel.h"
#include "ClientModMenuWindow.h"

#include "vgui_controls/Button.h"
#include "vgui_controls/CheckButton.h"
#include "vgui_controls/PropertySheet.h"
#include "vgui_controls/Label.h"
#include "vgui_controls/QueryBox.h"

#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/ISystem.h"
#include "vgui/IVGui.h"

#include "KeyValues.h"

//include modmenu pages
#include "ClientModMenuWindow.h"
#include "ClientModMainMenu.h"
#include "ClientModInfo.h"

using namespace vgui;

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

//-----------------------------------------------------------------------------
// Purpose: Basic help dialog
//-----------------------------------------------------------------------------
ClientModMenuWindow::ClientModMenuWindow(vgui::Panel *parent) : PropertyDialog(parent, "OptionsDialog")
{
	SetDeleteSelfOnClose(true);
	SetBounds(0, 0, 512, 406);
	SetSizeable( false );

	SetTitle("#GameUI_Clientmod_Menu_Window", true);

	AddPage(new ClientModMainMenu(this), "#GameUI_ClientModMain");

	SetApplyButtonVisible(true);
	GetPropertySheet()->SetTabWidth(84);
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
ClientModMenuWindow::~ClientModMenuWindow()
{
}

//-----------------------------------------------------------------------------
// Purpose: Brings the dialog to the fore
//-----------------------------------------------------------------------------
void ClientModMenuWindow::Activate()
{
	BaseClass::Activate();
	EnableApplyButton(false);
}

void ClientModMenuWindow::OnKeyCodePressed( KeyCode code )
{
	switch ( GetBaseButtonCode( code ) )
	{
	case KEY_XBUTTON_B:
		OnCommand( "Cancel" );
		return;
	}

	BaseClass::OnKeyCodePressed( code );
}

//-----------------------------------------------------------------------------
// Purpose: Opens the dialog
//-----------------------------------------------------------------------------
void ClientModMenuWindow::Run()
{
	SetTitle("#GameUI_ClientModMenuTitle", true);
	Activate();
}

//-----------------------------------------------------------------------------
// Purpose: Called when the GameUI is hidden
//-----------------------------------------------------------------------------
void ClientModMenuWindow::OnGameUIHidden()
{
	// tell our children about it
	for ( int i = 0 ; i < GetChildCount() ; i++ )
	{
		Panel *pChild = GetChild( i );
		if ( pChild )
		{
			PostMessage( pChild, new KeyValues( "GameUIHidden" ) );
		}
	}
}
