#include "Menu.h"
#include "Draw.h"
#include "Colours.h"
#include "VarSystem.h"

CMenu cMenu;
SVars sVars;

char* szAimDist[7] =
{
	"10 Meters",
	"30 Meters",
	"50 Meters",
	"80 Meters",
	"120 Meters",
	"Max View distance",
	"Maximal Distance Possible"
};
char* szAimoption[3] =
{
	"Infantry Only",
	"Vehicle Only",
	"Both"
};
char* szAimStyle[2] = 
{ 
	"Closest to Crosshair",
	"Closest Player" 
};
char* szAimBones[3] = 
{ 
	"Head",
	"Stomach",
	"Origin" 
};
char* szExplosiveWarning[3] =
{
	"5 Meters",
	"10 Meters",
	"20 Meters"
};
char* szViewDist[5] =
{
	"Normal ViewDistance",
	"Unlimited ViewDistance",
	"20%%",
	"50%%",
	"80%%"
};
char* szSpamMessages[6] = 
{ 
	"You_Got_OWN3D", 
	"Domo for the best Hacks!", 
	"You got OwN3d by Domo",
	"You_Got_OWN3D",
	"You_Got_OWN3D",
	"You are too bad - get my hack free From Domo! >|:)"
};
char* szEspDistance[7] =
{
	"Maximal Distance Possible",
	"Max View distance",
	"350 Meters",
	"250 Meters",
	"150 Meters",
	"100 Meters",
	"60 Meters"
};
char* szChamsMethod[2] =
{
	"Texture",
	"Shader"
};
char* szChrosshairStyle[2] =
{
	"BlackBordered",
	"Normal"
};
bool CMenu::NeedNotification(  )
{
	if( m_bMenuIsOpen )
		return false;
	return true;
}
void CMenu::DrawNotification( void )
{
	if( m_bDrawNotification )
	{
		cDraw.DrawBorderString( cDraw.Fonts[6], 400, 400, cCol.colRed, cCol.colBlack, D3DFONT_ZENABLE,"Open Menu with the Delete-Key!" );
		m_bDrawNotification = NeedNotification(  );
	}
}
void CMenu::InitializeMenu( void )
{
	m_pMenuPos.x = m_pMenuPos.y = 80;
	m_iCurrentTab = TABS::About;
	m_iMenuKey = VK_DELETE;
	m_bDrawNotification = true;
	m_iMenuWidth = 600;
	m_iMenuHeight = 400;

	AddTab( 10, 35, "Aimbot", TABS::Aimbot );
	AddPenel( 10, 70, TABS::Aimbot, "Aimbot", 250, 330, cCol.colWhite );
	AddButton( 20, 90,230, TABS::Aimbot, "Activate Aimbot", sVars.aimEnable );
	AddCheckBox( 20, 120, TABS::Aimbot, "Bone Scan [ Temporary Disabled ]", sVars.aimBone );
	//AddCheckBox( 20, 140, TABS::Aimbot, "No Spread", &SVars::fNoSpread );
	//AddCheckBox( 20, 160, TABS::Aimbot, "No Shake", &SVars::fNoShake );
	//AddCheckBox( 20, 180, TABS::Aimbot, "Visible check", &SVars::fVisCheck );
	//AddCheckBox( 20, 200, TABS::Aimbot, "Auto aim AFK people", &SVars::fAutoAimAFKPeople );
	//AddCheckBox( 20, 220, TABS::Aimbot, "Auto aim when capturing a Flag", &SVars::fAutoAimWhenCapingFlag );
	//AddCheckBox( 20, 240, TABS::Aimbot, "Predict Target speed", &SVars::fPredictSpeed );
	//AddCheckBox( 20, 260, TABS::Aimbot, "Predict Bullet drop", &SVars::fPredictBulletDrop );
	//AddCheckBox( 20, 280, TABS::Aimbot, "Predict Ping", &SVars::fPredictPing );
	//AddCheckBox( 20, 300, TABS::Aimbot, "Predict local Speed", &SVars::fPredictLocalSpeed );
	//TVGM Aimbot HERE ----
	AddDropdown( 20, 340, 230, "", sVars.aimDistance, szAimDist, 7, TABS::Aimbot, false );

	AddPenel( 270, 70, TABS::Aimbot, "AimStyle", 250, 240, cCol.colWhite );
	//AddDropdown( 280, 90, 220, "", &SVars::fAimStyle, szAimStyle, 2, TABS::Aimbot, false );
	//AddDropdown( 280, 150, 220, "", &SVars::fOptionalAimoption, szAimoption, 3, TABS::Aimbot, false );


	//AddPenel( 270, 320, TABS::Aimbot, "BoneSettings", 250, 80, cCol.colWhite );
	//AddDropdown( 280, 330, 230, "", &SVars::fAimBone, szAimBones, 3, TABS::Aimbot, false );


	AddTab( 91, 35, "Esp", TABS::Esp );
	//AddPenel( 10, 70, TABS::Esp, "Esp options", 250, 240, cCol.colWhite );
	//AddCheckBox( 20, 100, TABS::Esp, "Name", &SVars::fEspName );
	//AddCheckBox( 20, 120, TABS::Esp, "Distance", &SVars::fEspDistance );
	//AddCheckBox( 20, 140, TABS::Esp, "Class", &SVars::fEspClass );
	//AddCheckBox( 20, 160, TABS::Esp, "Box", &SVars::fEspBox );
	//AddCheckBox( 20, 180, TABS::Esp, "Health bar", &SVars::fEspHealthBar );
	//AddCheckBox( 20, 200, TABS::Esp, "Show Commander", &SVars::fEspCommander );
	//AddCheckBox( 20, 220, TABS::Esp, "Show Squad leaders", &SVars::fEspSquadleader );
	//AddCheckBox( 20, 240, TABS::Esp, "Show AFK Players", &SVars::fEspAFK );
	//AddCheckBox( 20, 260, TABS::Esp, "Show Players with Explosive Weapons [ Temporary Disabled ]", &SVars::fEspExplosiveSoldiers );
	//AddCheckBox( 20, 280, TABS::Esp, "Visibility check", &SVars::fEspVisCheck );

	//AddCheckBox( 150, 100, TABS::Esp, "Bone", &SVars::fEspBone );
	//AddCheckBox( 150, 120, TABS::Esp, "Line", &SVars::fEspLine );
	//AddCheckBox( 150, 140, TABS::Esp, "Aim point", &SVars::fEspAimPoint );

	//AddPenel( 10, 320, TABS::Esp, "Esp Distance", 250, 80, cCol.colWhite );
	//AddDropdown( 20, 330, 230, "", &SVars::fMaxEspDistance, szEspDistance, 7, TABS::Esp, false );

	//AddPenel( 270, 70, TABS::Esp, "Colors", 240, 250, cCol.colWhite );

	//AddPenel( 280, 270, TABS::Esp, "Esp vehicle", 105, 40, cCol.colWhite );
	//AddColorBox( 290, 280, 20, 85, &SColors::fEspVehicleR, &SColors::fEspVehicleG, &SColors::fEspVehicleB, TABS::Esp, 100, 0, 255, false );
	//AddPenel( 390, 210, TABS::Esp, "Esp Explosive", 105, 40, cCol.colWhite );
	//AddColorBox( 400, 220, 20, 85, &SColors::fEspExplosiveR, &SColors::fEspExplosiveG, &SColors::fEspExplosiveB, TABS::Esp, 0, 0, 255, false );
	//AddPenel( 280, 210, TABS::Esp, "Esp AFK Soldiers", 105, 40, cCol.colWhite );
	//AddColorBox( 290, 220, 20, 85, &SColors::fEspAFKR, &SColors::fEspAFKG, &SColors::fEspAFKB, TABS::Esp, 255, 0, 255, false );
	//AddPenel( 390, 150, TABS::Esp, "Esp Squad leader", 105, 40, cCol.colWhite );
	//AddColorBox( 400, 160, 20, 85, &SColors::fEspSquadleaderR, &SColors::fEspSquadleaderG, &SColors::fEspSquadleaderB, TABS::Esp, 0, 255, 255, false );
	//AddPenel( 280, 150, TABS::Esp, "Esp Commander", 105, 40, cCol.colWhite );
	//AddColorBox( 290, 160, 20, 85, &SColors::fEspCommanderR, &SColors::fEspCommanderG, &SColors::fEspCommanderB, TABS::Esp, 255, 255, 0, false );
	//AddPenel( 390, 90, TABS::Esp, "Esp Visible", 105, 40, cCol.colWhite );
	//AddColorBox( 400, 100, 20, 85, &SColors::fEspVisR, &SColors::fEspVisG, &SColors::fEspVisB, TABS::Esp, 0, 255, 0, false );
	//AddPenel( 280, 90, TABS::Esp, "Esp normal", 105, 40, cCol.colWhite );
	//AddColorBox( 290, 100, 20, 85, &SColors::fEspR, &SColors::fEspG, &SColors::fEspB, TABS::Esp, 255, 0, 0, false );



	AddTab( 172, 35, "Object Esp", TABS::ObjectEsp );
	//AddPenel( 10, 70, TABS::ObjectEsp, "Objects", 250, 190, cCol.colWhite );
	//AddCheckBox( 20, 100, TABS::ObjectEsp, "Explosive", &SVars::fExplosive );
	//AddCheckBox( 20, 120, TABS::ObjectEsp, "Hubs", &SVars::fHubs );
	//AddCheckBox( 20, 140, TABS::ObjectEsp, "Grenades", &SVars::fGrenades );
	//AddCheckBox( 20, 160, TABS::ObjectEsp, "Missiles", &SVars::fMissles );
	//AddCheckBox( 20, 180, TABS::ObjectEsp, "Projectiles", &SVars::fProjectiles );
	//AddCheckBox( 20, 200, TABS::ObjectEsp, "Others", &SVars::fOthers );

	//AddPenel( 270, 70, TABS::ObjectEsp, "Colors", 240, 190, cCol.colWhite );

	//AddPenel( 270, 270, TABS::ObjectEsp, "Warning Distance", 240, 130, cCol.colWhite );
	//AddDropdown( 280, 280, 170, "", &SVars::fExplosiveWaringDist, szExplosiveWarning, 3, TABS::ObjectEsp, false );

	//AddPenel( 10, 270, TABS::ObjectEsp, "Optional", 250, 130, cCol.colWhite );
	//AddCheckBox( 20, 290, TABS::ObjectEsp, "Explosive Warning", &SVars::fExplosiveWarning );

	//AddPenel( 390, 210, TABS::ObjectEsp, "Others", 105, 40, cCol.colWhite );//done
	//AddColorBox( 400, 220, 20, 85, &SColors::fOthersR, &SColors::fOthersG, &SColors::fOthersB, TABS::ObjectEsp, 0, 0, 255, false );
	//AddPenel( 280, 210, TABS::ObjectEsp, "Projectiles", 105, 40, cCol.colWhite );//done
	//AddColorBox( 290, 220, 20, 85, &SColors::fProjectilesR, &SColors::fProjectilesG, &SColors::fProjectilesB, TABS::ObjectEsp, 255, 0, 255, false );
	//AddPenel( 390, 150, TABS::ObjectEsp, "Missiles", 105, 40, cCol.colWhite );//done
	//AddColorBox( 400, 160, 20, 85, &SColors::fMisslesR, &SColors::fMisslesG, &SColors::fMisslesB, TABS::ObjectEsp, 0, 255, 255, false );
	//AddPenel( 280, 150, TABS::ObjectEsp, "Grenades", 105, 40, cCol.colWhite );//done
	//AddColorBox( 290, 160, 20, 85, &SColors::fGrenadeR, &SColors::fGrenadeG, &SColors::fGrenadeB, TABS::ObjectEsp, 255, 255, 0, false );
	//AddPenel( 390, 90, TABS::ObjectEsp, "Hubs", 105, 40, cCol.colWhite );//done
	//AddColorBox( 400, 100, 20, 85, &SColors::fHubsR, &SColors::fHubsG, &SColors::fHubsB, TABS::ObjectEsp, 0, 255, 0, false );
	//AddPenel( 280, 90, TABS::ObjectEsp, "Explosive", 105, 40, cCol.colWhite );//done
	//AddColorBox( 290, 100, 20, 85, &SColors::fExplosiveR, &SColors::fExplosiveG, &SColors::fExplosiveB, TABS::ObjectEsp, 255, 0, 0, false );


	AddTab( 253, 35, "Misc", TABS::Misc );

	//AddPenel( 10, 70, TABS::Misc, "Chat Spam", m_iMenuWidth-20, 140, cCol.colWhite );
	//AddCheckBox( 20, 100, TABS::Misc, "Activate Chat Spam", &SVars::fChatSpamActivate );
	//AddCheckBox( 20, 120, TABS::Misc, "Big Font", &SVars::fChatSpamFontBig );
	////AddCheckBox( 20, 140, TABS::Misc, "Remove Chat block [ Temporary Disabled ]", &SVars::fRemoveChatBlock );
	//AddDropdown( 20, 160, m_iMenuWidth-40, "", &SVars::fChatSpam, szSpamMessages, 6, TABS::Misc, false );

	//AddPenel( 10, 220, TABS::Misc, "Crosshair", m_iMenuWidth-20, 50, cCol.colWhite );
	//AddCheckBox( 20, 230, TABS::Misc, "Activate Crosshair", &SVars::fCrosshair );
	//AddDropdown( 160, 230, 100, "", &SVars::fCrosshairStyle, szChrosshairStyle, 2, TABS::Misc, false );
	//AddColorBox( 270, 230, 20, 85, &SColors::fCrossR, &SColors::fCrossG, &SColors::fCrossB, TABS::Misc, 255, 0, 0, false );

	//AddPenel( 10, 280, TABS::Misc, "Options", 300, 120, cCol.colWhite );
	//AddCheckBox( 20, 300, TABS::Misc, "Show Time", &SVars::fShowTime );
	//AddCheckBox( 20, 320, TABS::Misc, "Show FPS", &SVars::fShowFPS );
	//AddCheckBox( 20, 340, TABS::Misc, "Show Date", &SVars::fShowDate );
	//AddCheckBox( 20, 360, TABS::Misc, "Show Resolution", &SVars::fShowResolution );

	//AddPenel( 320, 280, TABS::Misc, "Optional Options", m_iMenuWidth - 330, 120, cCol.colWhite );
	//AddCheckBox( 330, 300, TABS::Misc, "Draw Kill counter [ Temporary Disabled ]", &SVars::fKillCounter );
	//AddCheckBox( 330, 320, TABS::Misc, "Draw Stats Box window", &SVars::fStatsBox );

 //	AddTab( 334, 35, "Visuals", TABS::Visuals );

	//AddPenel( 10, 70, TABS::Visuals, "Removals", m_iMenuWidth-20, 200, cCol.colWhite );
	//AddCheckBox( 20, 100, TABS::Visuals, "No Sky", &SVars::fNoSky );
	//AddCheckBox( 20, 120, TABS::Visuals, "No Fog", &SVars::fNoFog );

	//AddCheckBox( 140, 100, TABS::Visuals, "No Post Production", &SVars::fRemovePostProduction );
	//AddCheckBox( 140, 120, TABS::Visuals, "No HUD", &SVars::fRemoveHUD );

	//AddCheckBox( 280, 100, TABS::Visuals, "No Sun Flare", &SVars::fRemoveSunFlare );
	//AddCheckBox( 280, 120, TABS::Visuals, "Tweak near Plane", &SVars::fTweakNearPlane );

	//AddDropdown( 20, 160, m_iMenuWidth-40, "", &SVars::fViewDistance, szViewDist, 5, TABS::Visuals, false );

 //	AddTab( 415, 35, "Chams", TABS::Chams );

	//AddPenel( 10, 70, TABS::Chams, "PlayerChams", 230, 330, cCol.colWhite );
	//AddButton( 20, 90, 180, TABS::Chams, "Activate PlayerChams", &SVars::fChams );
// 	AddDropdown( 20, 120, 100, "", &SVars::fChamsMethod, szChamsMethod, 2, TABS::Chams, false );
// 
// 	AddPenel( 20, 160, TABS::Chams, "Friend", 105, 40, cCol.colWhite );
// 	AddColorBox( 30, 170, 20, 85, &SColors::fChamsFriendR,&SColors::fChamsFriendG, &SColors::fChamsFriendB, TABS::Chams, 0, 255, 255, false );
// 
// 	AddPenel( 130, 160, TABS::Chams, "Friend Vis", 105, 40, cCol.colWhite );
// 	AddColorBox( 140, 170, 20, 85,&SColors::fChamsFriendVisR,&SColors::fChamsFriendVisG, &SColors::fChamsFriendVisB, TABS::Chams, 0, 255, 255, false );
// 
// 	AddPenel( 20, 270, TABS::Chams, "Enemy", 105, 40, cCol.colWhite );
// 	AddColorBox( 30, 280, 20, 85, &SColors::fChamsEnemyR,&SColors::fChamsEnemyG, &SColors::fChamsEnemyB, TABS::Chams, 255, 0, 0, false );
// 
// 	AddPenel( 130, 270, TABS::Chams, "Enemy Vis", 105, 40, cCol.colWhite );
// 	AddColorBox( 140, 280, 20, 85,&SColors::fChamsEnemyVisR,&SColors::fChamsEnemyVisG, &SColors::fChamsEnemyVisB, TABS::Chams, 255, 255, 0, false );

	AddTab( 496, 35, "2DRadar", TABS::Radar2D );
	AddText( 20, 60, 6, "Coming Soon!", TABS::Radar2D );
}

void CMenu::DrawMenu( void )
{
	if( !m_bMenuIsOpen ) return;


	cDraw.DrawFillRectOut( m_pMenuPos.x, m_pMenuPos.y, m_iMenuWidth, 20, cCol.colWhite, cCol.colBlack );

	cDraw.DrawFillRect( m_pMenuPos.x, m_pMenuPos.y + 27, m_iMenuWidth, m_iMenuHeight - 20, D3DCOLOR_ARGB( 100,0,0,0) );

	cDraw.DrawString( cDraw.Fonts[ 1 ], m_pMenuPos.x + 5, m_pMenuPos.y + 6, cCol.colWhite, D3DFONT_ZENABLE, "| Domo's Hack" );

	for ( int i = 0; i < sText.size(); i++ )
	{
		if( m_iCurrentTab == sText[i].tab )
		{
			cDraw.DrawString( cDraw.Fonts[ sText[i].Font], m_pMenuPos.x + sText[i].x, m_pMenuPos.y + sText[i].y, cCol.colWhite, D3DFONT_ZENABLE, sText[i].Text );
		}
	}
	for ( int i = 0; i < sButton.size(); i++ )
	{
		if( m_iCurrentTab == sButton[i].tab )
		{
			if( IsMouseOver( m_pMenuPos.x + sButton[i].x, m_pMenuPos.y + sButton[i].y, sButton[i].w, 20) )
				cDraw.AddButton( m_pMenuPos.x + sButton[i].x, m_pMenuPos.y + sButton[i].y, sButton[i].w, sButton[i].Name );
			else if( *sButton[i].Hack == 1.0f )
				cDraw.AddButtonActivated( m_pMenuPos.x + sButton[i].x, m_pMenuPos.y + sButton[i].y, sButton[i].w, sButton[i].Name );
			else
				cDraw.AddButtonDeactivated( m_pMenuPos.x + sButton[i].x, m_pMenuPos.y + sButton[i].y, sButton[i].w, sButton[i].Name );
		}
	}
	for( int i = 0; i < sCheckBox.size(); i++ )
	{
		if( m_iCurrentTab == sCheckBox[i].Tab )
		{
			if( IsMouseOver( m_pMenuPos.x + sCheckBox[i].x, m_pMenuPos.y + sCheckBox[i].y, 14, 14 ) )
				cDraw.AddCheckBoxNormal( m_pMenuPos.x + sCheckBox[i].x, m_pMenuPos.y + sCheckBox[i].y, sCheckBox[i].name );
			else if( *sCheckBox[i].Hack == 1.0f )
				cDraw.AddCheckBoxActivated( m_pMenuPos.x + sCheckBox[i].x, m_pMenuPos.y + sCheckBox[i].y, sCheckBox[i].name );
			else
				cDraw.AddCheckBoxDeactivated( m_pMenuPos.x + sCheckBox[i].x, m_pMenuPos.y + sCheckBox[i].y, sCheckBox[i].name );
		}
	}
	for( int i = 0; i < sPenel.size(); i++ )
	{
		if( m_iCurrentTab == sPenel[i].tab )
		{
			cDraw.DrawFillRect( m_pMenuPos.x + sPenel[i].x						, m_pMenuPos.y + sPenel[i].y				, 10			, 1					, sPenel[i].Color );
			cDraw.DrawFillRect( m_pMenuPos.x + sPenel[i].x						, m_pMenuPos.y + sPenel[i].y				, 1				, sPenel[i].h		, sPenel[i].Color );
			cDraw.DrawFillRect( m_pMenuPos.x + sPenel[i].x + sPenel[i].w - 10	, m_pMenuPos.y + sPenel[i].y				, 10			, 1					, sPenel[i].Color );
			cDraw.DrawFillRect( m_pMenuPos.x + sPenel[i].x						, m_pMenuPos.y + sPenel[i].y + sPenel[i].h	, sPenel[i].w	, 1					, sPenel[i].Color );
			cDraw.DrawFillRect( m_pMenuPos.x + sPenel[i].x + sPenel[i].w		, m_pMenuPos.y + sPenel[i].y				, 1				, sPenel[i].h + 1	, sPenel[i].Color );

			cDraw.DrawString( cDraw.Fonts[1],  m_pMenuPos.x + sPenel[i].x + sPenel[i].w/2, m_pMenuPos.y + sPenel[i].y - 4, sPenel[i].Color, D3DFONT_CENTERED, sPenel[i].Name );
		}
	}

	for( int i = 0; i < sTab.size(); i++ )
	{
		sRect Rect;
		if( m_iCurrentTab == sTab[i].Tab )
		{
			Rect.y = m_pMenuPos.y + sTab[i].y -5;
			Rect.h = 25;
		}
		else
		{
			Rect.y = m_pMenuPos.y + sTab[i].y;
			Rect.h = 20;
		}
		if( m_iCurrentTab == sTab[i].Tab )
			cDraw.DrawBox( m_pMenuPos.x + sTab[i].x, Rect.y, 80, Rect.h, 2 );
		else
			cDraw.DrawBox( m_pMenuPos.x + sTab[i].x, Rect.y, 80, Rect.h, 1 );

		cDraw.DrawString( cDraw.Fonts[1], m_pMenuPos.x + sTab[i].x + 5, Rect.y + 5, cCol.colWhite, D3DFONT_ZENABLE, sTab[i].Name );
	}
	for ( int i = 0; i < sDropDown.size(); i++ )
	{
		if( m_iCurrentTab == sDropDown[i].Tab )
		{
			sRect sRectBarNormal, sRectTotal;
			sRectBarNormal.x = sRectTotal.x = sDropDown[i].x + m_pMenuPos.x;
			sRectBarNormal.y = sDropDown[i].y + m_pMenuPos.y;
			sRectBarNormal.h = 20;
			sRectBarNormal.w = sRectTotal.w = sDropDown[i].w;
			sRectTotal.y = sRectBarNormal.y + sRectBarNormal.h + 1;


			for( int i2 = 0; i2 < sDropDown[i].Totaloptions; i2++ )
			{
				sRectTotal.h = 20 * i2;
				cDraw.DrawFillRectOut( sRectBarNormal.x, sRectBarNormal.y, sRectBarNormal.w, sRectBarNormal.h, cCol.colWhite, cCol.colBlack );

				if( sDropDown[i].dropped )
				{
					cDraw.DrawFillRectOut( sRectTotal.x, sRectTotal.y + ( 15 * i2 ), sRectTotal.w, 15, cCol.colWhite, cCol.colBlack );
					cDraw.DrawString( cDraw.Fonts[1], sRectTotal.x + SPACE, sRectTotal.y + ( 15 * i2 ), cCol.colWhite, D3DFONT_ZENABLE, sDropDown[i].Options[i2] );
				}
				cDraw.DrawString( cDraw.Fonts[1], sRectTotal.x + SPACE, sRectBarNormal.y + SPACE, cCol.colWhite, D3DFONT_ZENABLE, sDropDown[i].Options[ (int)*sDropDown[i].Hack ] );
			}
		}
	}
	for( int i = 0; i < sColorBox.size(); i++ )
	{

		if( sColorBox[i].iCol == 0 )
		{
			*sColorBox[i].OutR = sColorBox[i].NormalR;
			*sColorBox[i].OutG = sColorBox[i].NormalG;
			*sColorBox[i].OutB = sColorBox[i].NormalB;
		}
		if( m_iCurrentTab == sColorBox[i].tab )
		{

			sRect sRectBarNormal, sRectTotal;
			sRectBarNormal.x = sRectTotal.x = sColorBox[i].x + m_pMenuPos.x;
			sRectBarNormal.y = sColorBox[i].y + m_pMenuPos.y;
			sRectBarNormal.h = sColorBox[i].barH;
			sRectBarNormal.w = sRectTotal.w = sColorBox[i].w;
			sRectTotal.y = sRectBarNormal.y + sRectBarNormal.h + 1;
			sRectTotal.h = TOTALSIZE;

			//BarNormal
			cDraw.DrawFillRectOut( sRectBarNormal.x, sRectBarNormal.y, sRectBarNormal.w, sRectBarNormal.h, cCol.colBlack, cCol.CustomColor( 100, 0, 0, 0 ) );
			
			if( sColorBox[i].iCol == 0 )
				cDraw.DrawFillRect( sRectBarNormal.x + 5, sRectBarNormal.y + 5, sRectBarNormal.w - 10, sRectBarNormal.h -10, cCol.CustomColor( 255, (int)sColorBox[i].NormalR,(int)sColorBox[i].NormalG,(int)sColorBox[i].NormalB  ) );
			else
				cDraw.DrawFillRect( sRectBarNormal.x + 5, sRectBarNormal.y + 5, sRectBarNormal.w - 10, sRectBarNormal.h -10, cCol.CustomColor( 255, (int)*sColorBox[i].OutR,(int)*sColorBox[i].OutG,(int)*sColorBox[i].OutB  ) );

			if( sColorBox[i].Dropped )
			{
				//TotalRect
				cDraw.DrawFillRectOut( sRectTotal.x, sRectTotal.y, sRectTotal.w, sRectTotal.h, cCol.colWhite, cCol.colBlack );
				//Line1
				/*1 - colRed		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE			, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colRed		);
				/*2 - colBlue		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + 20		, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colBlue		);
				/*3 - colGreen		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*2)	, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colGreen		);
				/*4 - colCyan		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*3)	, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colCyan		);
				//Line2
				/*5 - colLightBlue	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE			, sRectTotal.y + 25		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colLightBlue	);
				/*6 - colLightRed	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20)	, sRectTotal.y + 25		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colLightRed	);
				/*7 - colLightGreen	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*2)	, sRectTotal.y + 25		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colLightGreen	);
				/*8 - colDarkBlue	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*3)	, sRectTotal.y + 25		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colDarkBlue	);
				//Line3
				/*9 -  colDarkRed	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE			, sRectTotal.y + 45		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colDarkRed	);
				/*10 - colDarkGreen	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + 20		, sRectTotal.y + 45		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colDarkGreen	);
				/*11 - colOrange	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*2)	, sRectTotal.y + 45		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colOrange		);
				/*12 - colPurple	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*3)	, sRectTotal.y + 45		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colPurple		);
				//Line4
				/*13 - colYellow	*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE			, sRectTotal.y + 65		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colYellow		);
				/*14 - colWhite		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + 20		, sRectTotal.y + 65		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colWhite		);
				/*15 - colBlack		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*2)	, sRectTotal.y + 65		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colBlack		);
				/*16 - colGray		*/ cDraw.DrawFillRectOut( sRectTotal.x + SPACE + (20*3)	, sRectTotal.y + 65		, RECTSIZE, RECTSIZE, cCol.colWhite, cCol.colGray		);
			}
		}
	}
	DrawMouse();
}

void CMenu::UpdateMenu( int MenuKey )
{
	if( GetAsyncKeyState( MenuKey )&1 )
		m_bMenuIsOpen =! m_bMenuIsOpen;

	if( !m_bMenuIsOpen ) return;

	GetCursorPos( &m_pMousePos );
	SetMousePosition( m_pMousePos.x, m_pMousePos.y );

	static bool bLeftDown = false;
	static bool bMoveMenu = false;

	if( bMoveMenu )
	{
		m_pMenuPos.x = m_pMousePos.x - m_iDifferenceX; 
		m_pMenuPos.y = m_pMousePos.y - m_iDifferenceY;

		if( m_pMenuPos.x < 1 ) m_pMenuPos.x = 1;
		if( m_pMenuPos.x > cDraw.ViewPort.Width - m_iMenuWidth - 2 ) m_pMenuPos.x = cDraw.ViewPort.Width - m_iMenuWidth;

		if( m_pMenuPos.y < 1 ) m_pMenuPos.y = 1;
		if( m_pMenuPos.y > cDraw.ViewPort.Height - m_iMenuHeight - 2 ) m_pMenuPos.y = cDraw.ViewPort.Height - m_iMenuHeight;
	}

	if(KEY_DOWN(VK_LBUTTON))
	{
		bLeftDown = true;

		if( IsMouseOver( m_pMenuPos.x, m_pMenuPos.y, m_iMenuWidth, 20 ) )
		{
			m_iDifferenceX = m_pMousePos.x - m_pMenuPos.x;
			m_iDifferenceY = m_pMousePos.y - m_pMenuPos.y;
			bMoveMenu = true;
		}
	}
	else
	{
		if(bLeftDown)
		{
			bLeftDown = false;
			bMoveMenu = false;

			for( int i = 0; i < sCheckBox.size(); i++ )
			{
				if( m_iCurrentTab == sCheckBox[i].Tab )
				{
					if( IsMouseOver( m_pMenuPos.x + sCheckBox[i].x, m_pMenuPos.y + sCheckBox[i].y, 14, 14 ) )
					{
						if( *sCheckBox[i].Hack == 0.0f )
							*sCheckBox[i].Hack = 1.0f;
						else
							*sCheckBox[i].Hack = 0.0f;
					}
				}
			}
			for ( int i = 0; i < sTab.size(); i++ )
			{
				sRect Rect;
				if( m_iCurrentTab == sTab[i].Tab )
				{
					Rect.y = m_pMenuPos.y + sTab[i].y -5;
					Rect.h = 25;
				}
				else
				{
					Rect.y = m_pMenuPos.y + sTab[i].y;
					Rect.h = 20;
				}
				if( IsMouseOver( m_pMenuPos.x + sTab[i].x, m_pMenuPos.y + sTab[i].y, 80, Rect.h ) )
				{
					m_iCurrentTab = sTab[i].Tab;
				}
			}
			for ( int i = 0; i < sButton.size(); i++ )
			{
				if( m_iCurrentTab == sButton[i].tab )
				{
					if( IsMouseOver( m_pMenuPos.x + sButton[i].x, m_pMenuPos.y + sButton[i].y, sButton[i].w, 20) )
					{
						if( *sButton[i].Hack == 0.0f )
							*sButton[i].Hack = 1.0f;
						else
							*sButton[i].Hack = 0.0f;
					}
				}
			}
			for ( int i = 0; i < sDropDown.size(); i++ )
			{
				if( m_iCurrentTab == sDropDown[i].Tab )
				{
					sRect sRectBarNormal, sRectTotal;
					sRectBarNormal.x = sRectTotal.x = sDropDown[i].x + m_pMenuPos.x;
					sRectBarNormal.y = sDropDown[i].y + m_pMenuPos.y;
					sRectBarNormal.h = 20;
					sRectBarNormal.w = sRectTotal.w = sDropDown[i].w;
					sRectTotal.y = sRectBarNormal.y + sRectBarNormal.h + 1;

					int iTotal = sDropDown[i].Totaloptions;
					if( IsMouseOver( sRectBarNormal.x, sRectBarNormal.y, sRectBarNormal.w, sRectBarNormal.h ) )
					{
						sDropDown[i].dropped = true;
					}

					for( int i2 = 0; i2 < iTotal; i2++ )
					{
						if( IsMouseOver( sRectTotal.x, sRectTotal.y + ( 15 * i2 ), sRectTotal.w, 15 ) && sDropDown[i].dropped )
						{
							*sDropDown[i].Hack = i2;
							sDropDown[i].dropped = false;
							break;
						}
					}
				}
			}
			for( int i = 0; i < sColorBox.size(); i++ )
			{
				if( m_iCurrentTab == sColorBox[i].tab )
				{
					sRect sRectBarNormal, sRectTotal;
					sRectBarNormal.x = sRectTotal.x = sColorBox[i].x + m_pMenuPos.x;
					sRectBarNormal.y = sColorBox[i].y + m_pMenuPos.y;
					sRectBarNormal.h = sColorBox[i].barH;
					sRectBarNormal.w = sRectTotal.w = sColorBox[i].w;
					sRectTotal.y = sRectBarNormal.y + sRectBarNormal.h + 1;
					sRectTotal.h = TOTALSIZE;

					if( IsMouseOver( sRectBarNormal.x, sRectBarNormal.y, sRectBarNormal.w, sRectBarNormal.h ) )
					{
						sColorBox[i].Dropped = true;
					}
					if( sColorBox[i].Dropped )
					{
						if( IsMouseOver( sRectTotal.x + SPACE			, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Red; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20		, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol= Blue; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*2		, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Green; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*3		, sRectTotal.y + SPACE	, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Cyan; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE			, sRectTotal.y + 25		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = LightBlue; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20		, sRectTotal.y + 25		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol= LightRed; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*2		, sRectTotal.y + 25		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = LightGreen; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*3		, sRectTotal.y + 25		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = DarkBlue; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE			, sRectTotal.y + 45		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = DarkRed; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20		, sRectTotal.y + 45		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = DarkGreen; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*2		, sRectTotal.y + 45		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Orange; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*3		, sRectTotal.y + 45		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Purble; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE			, sRectTotal.y + 65		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Yellow; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20		, sRectTotal.y + 65		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = White; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*2		, sRectTotal.y + 65		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Black; sColorBox[i].Dropped = false; }
						if( IsMouseOver( sRectTotal.x + SPACE + 20*3		, sRectTotal.y + 65		, RECTSIZE, RECTSIZE ) ) { sColorBox[i].iCol = Gray; sColorBox[i].Dropped = false; }
					}




					if	( sColorBox[i].iCol == Red )	
					{
						*sColorBox[i].OutR = 255.0f;
						*sColorBox[i].OutG = 0.0f;
						*sColorBox[i].OutB = 0.0f;
					}
					else if	( sColorBox[i].iCol == Blue )	
					{
						*sColorBox[i].OutR = 0.0f;
						*sColorBox[i].OutG = 0.0f;
						*sColorBox[i].OutB = 255.0f;
					}		
					else if	( sColorBox[i].iCol == Green )	
					{
						*sColorBox[i].OutR = 0.0f;
						*sColorBox[i].OutG = 255.0f;
						*sColorBox[i].OutB = 0.0f;
					}		
					else if	( sColorBox[i].iCol == Cyan )	
					{
						*sColorBox[i].OutR = 23.0f;
						*sColorBox[i].OutG = 187.0f;
						*sColorBox[i].OutB = 183.0f;
					}		
					else if	( sColorBox[i].iCol == LightBlue )		
					{
						*sColorBox[i].OutR = 36.0f;
						*sColorBox[i].OutG = 239.0f;
						*sColorBox[i].OutB = 255.0f;
					}
					else if	( sColorBox[i].iCol == LightRed )		
					{
						*sColorBox[i].OutR = 236.0f;
						*sColorBox[i].OutG = 83.0f;
						*sColorBox[i].OutB = 87.0f;
					}
					else if ( sColorBox[i].iCol == LightGreen ) 	
					{
						*sColorBox[i].OutR = 150.0f;
						*sColorBox[i].OutG = 255.0f;
						*sColorBox[i].OutB = 100.0f;
					} 
					else if	( sColorBox[i].iCol == DarkBlue )		
					{
						*sColorBox[i].OutR = 9.0f;
						*sColorBox[i].OutG = 0.0f;
						*sColorBox[i].OutB = 119.0f;
					}
					else if	( sColorBox[i].iCol == DarkRed )			
					{
						*sColorBox[i].OutR = 119.0f;
						*sColorBox[i].OutG = 0.0f;
						*sColorBox[i].OutB = 0.0f;
					}
					else if	( sColorBox[i].iCol == DarkGreen )	
					{
						*sColorBox[i].OutR = 27.0f;
						*sColorBox[i].OutG = 119.0f;
						*sColorBox[i].OutB = 0.0f;
					}
					else if	( sColorBox[i].iCol == Orange )	
					{
						*sColorBox[i].OutR = 255.0f;
						*sColorBox[i].OutG = 128.0f;
						*sColorBox[i].OutB = 0.0f;
					}		
					else if	( sColorBox[i].iCol == Purble )	
					{
						*sColorBox[i].OutR = 128.0f;
						*sColorBox[i].OutG = 0.0f;
						*sColorBox[i].OutB = 128.0f;
					}		
					else if	( sColorBox[i].iCol == Yellow )	
					{
						*sColorBox[i].OutR = 255.0f;
						*sColorBox[i].OutG = 255.0f;
						*sColorBox[i].OutB = 0.0f;
					}		
					else if	( sColorBox[i].iCol == White )	
					{
						*sColorBox[i].OutR = 255.0f;
						*sColorBox[i].OutG = 255.0f;
						*sColorBox[i].OutB = 255.0f;
					}		
					else if	( sColorBox[i].iCol == Black )		
					{
						*sColorBox[i].OutR = 0.0f;
						*sColorBox[i].OutG = 0.0f;
						*sColorBox[i].OutB = 0.0f;
					}	
					else if	( sColorBox[i].iCol == Gray )		
					{
						*sColorBox[i].OutR = 192.0f;
						*sColorBox[i].OutG = 192.0f;
						*sColorBox[i].OutB = 192.0f;
					}
				}
			}
		}
	}
}
void CMenu::DrawMouse( void )
{
	cDraw.DrawCrosshair( m_pMousePos.x, m_pMousePos.y, 15, 1, true, cCol.colGreen );
}
void CMenu::SetMousePosition( int PosXNew, int PosYNew )
{
	m_pMousePos.x = PosXNew;
	m_pMousePos.y = PosYNew;
}
bool CMenu::IsMouseOver( float x, float y, float objWidth, float objHeight )
{
	if( m_pMousePos.x >= x && m_pMousePos.x <= ( x + objWidth ) && m_pMousePos.y >= y && m_pMousePos.y <= ( y + objHeight ) )
		return true;
	else
		return false;
}
void CMenu::AddColorBox( int x, int y, int barH, int w, PFLOAT OurR, PFLOAT OurG, PFLOAT OurB, int Tab, float NormalR, float NormalG, float NormalB, bool dropped )
{
	SColorBox sColBox;
	sColBox.x = x;
	sColBox.y = y;
	sColBox.w = w;
	sColBox.tab = Tab;
	sColBox.barH = barH;
	sColBox.Dropped = dropped;
	sColBox.NormalR = NormalR;
	sColBox.NormalG = NormalG;
	sColBox.NormalB = NormalB;
	sColBox.OutR = OurR;
	sColBox.OutG = OurG;
	sColBox.OutB = OurB;
	sColBox.iCol = 0;

	sColorBox.push_back( sColBox );
}
void CMenu::AddDropdown( int x, int y, int w, char* name, PFLOAT Hack, char** Options, int totaloptions, int tab, bool dropped )
{
	SDropDown sDrop;
	sDrop.x = x;
	sDrop.y = y;
	sDrop.w = w;
	sDrop.name = name;
	sDrop.Hack = Hack;
	sDrop.Options = Options;
	sDrop.Totaloptions = totaloptions;
	sDrop.Tab = tab;
	sDrop.dropped = dropped;

	sDropDown.push_back( sDrop );
}
void CMenu::AddTab( int x, int y, char* name, int Tab )
{
	STab sTaby;
	sTaby.x = x;
	sTaby.y = y;
	sTaby.Name = name;
	sTaby.Tab = Tab;

	sTab.push_back( sTaby );
}

void CMenu::AddPenel( int x, int y, int tab, char* name, int w, int h, DWORD col )
{
	SPenel sPen;
	sPen.x = x;
	sPen.y = y;
	sPen.w = w;
	sPen.h = h;
	sPen.Color = col;
	sPen.Name = name;
	sPen.tab = tab;

	sPenel.push_back( sPen );
}
void CMenu::AddCheckBox( int x, int y, int tab, char* name, PFLOAT hack )
{
	SCheckBox sCheck;
	sCheck.x = x;
	sCheck.y = y;
	sCheck.name = name;
	sCheck.Tab = tab;
	sCheck.Hack = hack;

	sCheckBox.push_back( sCheck );
}

void CMenu::AddButton( int x, int y, int w, int tab, char* name, PFLOAT Hack )
{
	SButton sBut;
	sBut.x = x;
	sBut.y = y;
	sBut.w = w;
	sBut.tab = tab;
	sBut.Name = name;
	sBut.Hack = Hack;

	sButton.push_back( sBut );
}
void CMenu::AddText( int x, int y, int Font, char* Text, int Tab )
{	
	SText sTex;
	sTex.x = x;
	sTex.y = y;
	sTex.Font = Font;
	sTex.Text = Text;
	sTex.tab = Tab;

	sText.push_back( sTex );
}
