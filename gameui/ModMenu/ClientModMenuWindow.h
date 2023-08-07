//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef CLIENTMODMENUWINDOW_H
#define CLIENTMODMENUWINDOW_H
#ifdef _WIN32
#pragma once
#endif

#include "vgui_controls/PropertyDialog.h"
#include "vgui_controls/KeyRepeat.h"

//-----------------------------------------------------------------------------
// Purpose: Holds all the game option pages
//-----------------------------------------------------------------------------
class ClientModMenuWindow : public vgui::PropertyDialog
{
	DECLARE_CLASS_SIMPLE( ClientModMenuWindow, vgui::PropertyDialog );

public:
	ClientModMenuWindow(vgui::Panel *parent);
	~ClientModMenuWindow();

	void Run();
	virtual void Activate();

	void OnKeyCodePressed( vgui::KeyCode code );

	MESSAGE_FUNC( OnGameUIHidden, "GameUIHidden" );	// called when the GameUI is hidden
};

#endif // CLIENTMODMENUWINDOW_H
