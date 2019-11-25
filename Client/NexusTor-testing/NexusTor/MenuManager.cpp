#include "StdAfx.h"

CMenuManager cMenu;

CMenuManager::CMenuManager()
{
	this->mL.clear();

	this->initialized = false;
	this->direct3DDevice9 = NULL;

	this->menuOpen = false;
	this->menuKey = VK_INSERT;
	this->titlebarHeight = 20;
	this->titlebarOffset = 0;

	this->mainMenu = NULL;
	this->forcedTopMenu = NULL;
	this->foregroundMenu = NULL;
	this->fgMenuActive = false;
	this->movingMenu = false;
	this->readyForRelease = false;

	this->activeControl = NULL;
	this->controlState = -1;

	this->mouseX = 0;
	this->mouseY = 0;

	this->distanceToX = 0;
	this->distanceToY = 0;
}

void SelectAimKey()
{	

}

bool testBool = false;
int testInteger = 20;
void CMenuManager::initialize()
{
	if(this->initialized) return;

	CMenu* mainMenu = new CMenu("Domo's Hacks v2.0", 100, 100, 450, 350, STYLE_CLOSE|STYLE_MINIMIZE); // Create a new menu

	CControl* mainTabControl = new CTab(10,10);

	CMenu* espTab = new CMenu("ESP", -1, -1, 450, 310, NULL);
	espTab->add(new CGroupBox("ESP", 10, 40, 430, 300)); // Add a groupbox

	espTab->add(new CCheckbox("Name ESP", 30, 60, &sVars::espName));
	espTab->add(new CCheckbox("Distance ESP", 30, 80, &sVars::espDistance));
	espTab->add(new CCheckbox("Box ESP", 30, 100, &sVars::espBox));
	espTab->add(new CCheckbox("Health ESP", 30, 120, &sVars::espHealth));
	espTab->add(new CCheckbox("Bone ESP", 30, 140, &sVars::espBones));
	espTab->add(new CCheckbox("Weapon ESP", 30, 160, &sVars::espKits));
	espTab->add(new CCheckbox("Tracer ESP", 30, 180, &sVars::espTracer));
	espTab->add(new CCheckbox("Visibility ESP", 30, 200, &sVars::espVis));
	espTab->add(new CCheckbox("Friendly ESP", 30, 220, &sVars::espFriendly));

	espTab->add(new CSlider("ESP Distance",30,280,0,100,&sVars::espViewDist));
	
	//         //

	CMenu* radarTab = new CMenu("Radar", -1, -1, 450, 310, NULL);
	radarTab->add(new CGroupBox("Radar", 10, 40, 430, 300)); // Add a groupbox


	//         //

	CMenu* aimbotTab = new CMenu("Aimbot", -1, -1, 450, 310, NULL);
	aimbotTab->add(new CGroupBox("Aimbot", 10, 40, 430, 300)); // Add a groupbox

	// Drop Down Tabs
	CControl* botTargetStyles = new CDropDown("Target Style", 160, 60, &sVars::aimStyle);
	botTargetStyles->addChoice("Closest To Crosshair");
	botTargetStyles->addChoice("Closest To Distance");
	botTargetStyles->addChoice("Lowest Health");
	aimbotTab->add(botTargetStyles);

	CControl* aimBones = new CDropDown("Aim Bone", 300, 60, &sVars::aimBone);
	aimBones->addChoice("Head");
	aimBones->addChoice("Neck");
	aimBones->addChoice("Chest");
	aimBones->addChoice("Stomach");
	aimbotTab->add(aimBones);

	// Aim Key Selector
	//aimbotTab->add(new CButton("Select Aim Key", 300, 300, 100, 25, SelectAimKey));

	aimbotTab->add(new CCheckbox("Enable Aimbot", 30, 60, &sVars::aimEnable));
	aimbotTab->add(new CCheckbox("Visibility Checks", 30, 80, &sVars::aimVis));
	aimbotTab->add(new CCheckbox("No Recoil", 30, 100, &sVars::aimRecoil));
	aimbotTab->add(new CCheckbox("No Spread", 30, 120, &sVars::aimSpread));
	aimbotTab->add(new CCheckbox("Bullet Drop Correction", 30, 140, &sVars::aimBulletDrop));
	aimbotTab->add(new CCheckbox("Knife Bot", 30, 160, &sVars::aimKnife));
	aimbotTab->add(new CCheckbox("AutoShoot", 30, 180, &sVars::aimAuto));
	aimbotTab->add(new CCheckbox("Auto Predict", 30, 200, &sVars::aimAutoPred));
	aimbotTab->add(new CCheckbox("Speed Correction", 30, 220, &sVars::aimPredSpeed));
	aimbotTab->add(new CCheckbox("Ping Correction", 30, 240, &sVars::aimPredPing));

	// Sliders
	aimbotTab->add(new CSlider("Scale", 30, 280, 0, 100, &sVars::aimPredScale));
	aimbotTab->add(new CSlider("FOV", 30, 320, 0, 360, &sVars::aimFov));


	//            //

	CMenu* miscTab = new CMenu("Misc", -1, -1, 450, 310, NULL);
	miscTab->add(new CGroupBox("Misc", 10, 40, 430, 300)); // Add a groupbox


	//          //

	CMenu* VisualTab = new CMenu("Visuals", -1, -1, 450, 310, NULL);
	VisualTab->add(new CGroupBox("Visuals", 10, 40, 430, 300)); // Add a groupbox


	//            //

	mainTabControl->addTab(aimbotTab);
	mainTabControl->addTab(espTab);
	mainTabControl->addTab(radarTab);
	mainTabControl->addTab(miscTab);
	mainTabControl->addTab(VisualTab);
	mainMenu->add(mainTabControl);
	
	this->add(mainMenu); // Add the menu to the vector

	this->setMainMenu(mainMenu); // set the menu as main window to close the whole menu instead of just this single window on close button click
	this->setForegroundMenu(mainMenu); // set the menu to the foreground (focus)
	this->centerMenu(mainMenu);

	this->initialized = true;
}

void CMenuManager::perform()
{
	this->drawMenus();
	this->handleInput();
}

void CMenuManager::add(CMenu* menu)
{
	this->mL.push_back(menu);
}

void CMenuManager::rem(CMenu* menu)
{
	vector<CMenu*>::iterator it;
	vector<CControl*>::iterator it2;
	for ( it = this->mL.begin(); it != this->mL.end(); )
	{
		if(*it == menu)
		{
			CMenu* menu = *it;

			for ( it2 = menu->cL.begin(); it2 != menu->cL.end(); ++it2)
				delete * it2;

			menu->cL.clear();
			delete * it; // prevent memory leak!
			it = this->mL.erase(it);
		}
		else ++it;
	}
}

void CMenu::add(CControl* control)
{
	control->parent = this;
	this->cL.push_back(control);
}

CMenu::CMenu(string title, int x, int y, int w, int h, DWORD style)
{
	this->title = title;
	this->style = style;

	this->minimized = false;
	this->closed = false;

	this->xPosition = x;
	this->yPosition = y;
	this->width = w;
	this->height = h;

	this->cL.clear();
}

void CMenu::setPosition(int x, int y)
{
	this->xPosition = x;
	this->yPosition = y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///					THE DRAW SECTION.		All functions regarding drawing will follow below			  ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMenuManager::drawMenus()
{
	if( !this->initialized || !this->menuOpen ) return;

	// Draw the menus. Skip the foreground menu because it needs to be on top.
	for(int i=0;i<mL.size();i++)
	{
		CMenu* menu = mL[i];
		if(menu==foregroundMenu || menu->closed) continue;
		drawMenu(menu);
	}

	if(this->forcedTopMenu != NULL)
	{
		int width = cRender.m_ViewPort.Width;
		int height = cRender.m_ViewPort.Height;
		cRender.DrawOutline(0, 0, width, height, D3DCOLOR_ARGB(100, 0, 0, 0));
	}

	if(foregroundMenu) drawMenu(foregroundMenu);

	// Draw cursor at last.
	drawCursor();
}

void CMenuManager::drawMenu(CMenu* menu)
{
	// Last thing to draw is the title bar.

	DWORD titleBarColour = 0xFF8A8A8A;
	DWORD titleBarColourTo = 0xFF717171; // Gradient to this colour
	if(menu == foregroundMenu && fgMenuActive)
	{
		titleBarColour = 0xFF262626;
		titleBarColourTo = 0xFF010101; // Gradient to this colour
	}

	if(titlebarOffset <= 2 || menu->minimized)
	{
		(menu->minimized) ? cRender.DrawFillRect(menu->xPosition-1, menu->yPosition-1, menu->width+1, titlebarHeight+1, 0xFF000000) :
			cRender.DrawFillRect(menu->xPosition-1, menu->yPosition-1, menu->width+1, menu->height+titlebarHeight+1, 0xFF000000);
	}
	else
	{
		cRender.DrawFillRect(menu->xPosition-1, menu->yPosition-1, menu->width+1, titlebarHeight+1, 0xFF000000);
		cRender.DrawFillRect(menu->xPosition-1, menu->yPosition+titlebarHeight+titlebarOffset-1, menu->width+1, menu->height+1, 0xFF000000);
	}

	if(!menu->minimized)
	{
		cRender.DrawFillRect(menu->xPosition, menu->yPosition + titlebarHeight + titlebarOffset, menu->width, menu->height, 0xFF343434); // the actual window
		cRender.DrawBox(menu->xPosition, menu->yPosition + titlebarHeight + titlebarOffset, menu->width, menu->height, 0xFF000000);
		cRender.DrawGradientBox(menu->xPosition - 1, menu->yPosition + titlebarHeight + titlebarOffset + menu->height, menu->width + 2, titlebarHeight/2, titleBarColour, titleBarColourTo, vertical);
		drawControls(menu);
	}

	cRender.DrawGradientBox(menu->xPosition, menu->yPosition, menu->width + 1, titlebarHeight, titleBarColour, titleBarColourTo, vertical); // the title bar
	

	int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
	cRender.DrawString(menu->xPosition+5, menu->yPosition+(titlebarHeight/2)-(charHeight/2), 0xFFFFFFFF, DT_LEFT, MenuFont, menu->title.c_str());

	if(menu->style & STYLE_CLOSE)
	{
		int xOffset = 17;
		cRender.DrawFillRect((menu->xPosition+menu->width)-xOffset, menu->yPosition+3, 11, 11, 0xFFFFFFFF);
		cRender.DrawGradientBox((menu->xPosition+menu->width)-xOffset-1, menu->yPosition+4, 11, 11, 0xFFFFFFFF, 0xFF9F9B9B, vertical);
		cRender.DrawString((menu->xPosition+menu->width)-xOffset-1+6, menu->yPosition+4, 0xFF000000, DT_CENTER, MenuFont, "x");
	}

	if(menu->style & STYLE_MINIMIZE)
	{
		int xOffset = 32;
		cRender.DrawFillRect((menu->xPosition+menu->width)-xOffset, menu->yPosition+3, 11, 11, 0xFFFFFFFF);
		cRender.DrawGradientBox((menu->xPosition+menu->width)-xOffset, menu->yPosition+4, 11, 11, 0xFFFFFFFF, 0xFF9F9B9B, vertical);
		cRender.DrawString((menu->xPosition+menu->width)-xOffset-1+6, menu->yPosition+4, 0xFF000000, DT_CENTER, MenuFont, "--");
	}

}

void CMenuManager::drawControls(CMenu* menu)
{
	for(int i=0;i<menu->cL.size();i++)
	{
		CControl* control = menu->cL[i];
		switch(control->controlType)
		{
		case TYPE_LABEL:
			drawLabel(control);
			break;
		case TYPE_GROUPBOX:
			drawGroupBox(control);
			break;
		case TYPE_BUTTON:
			drawButton(control);
			break;
		case TYPE_CHECKBOX:
			drawCheckbox(control);
			break;
		case TYPE_RADIOBUTTON:
			drawRadioButton(control);
			break;
		case TYPE_DROPDOWN:
			drawDropDown(control);
			break;
		case TYPE_SLIDER:
			drawSlider(control);
			break;
		case TYPE_TAB:
			for(int i=0;i<control->tL.size();i++)
			{
				CMenu* tab = control->tL[i];
				int w = 60;
				int h = 20;

				int xMultiplier = (w+3) * i;
				int x = menu->xPosition+control->xOffset + xMultiplier;
				int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;
			
				cRender.DrawGradientBox(x+1, y+1, w-1, h-1, 0xFFFFFFFF, 0xFF9F9B9B, vertical);
				cRender.DrawBox(x, y, w, h, 0xFF000000);

				int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
				cRender.DrawString(x+(w/2), y+(h/2)-(charHeight/2), 0xFF424242, DT_CENTER, MenuFont, tab->title.c_str());
			}
			CMenu* tab = control->tL[control->activeTab];
			tab->xPosition = menu->xPosition;
			tab->yPosition = menu->yPosition;

			control->width = (60 + 3) * control->tL.size();
			control->height = 20;

			//pDM.drawBox(menu->xPosition+control->xOffset, menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset, control->width, control->height, 0xFF00FF00);
			drawControls(tab);
			break;
		}
	}
}

void CMenuManager::drawLabel(CControl* control)
{
	CMenu* menu = control->parent;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;

	cRender.DrawString(x, y, 0xFFFFFFFF, control->align, MenuFont, control->label.c_str());
}

void CMenuManager::drawGroupBox(CControl* control)
{
	CMenu* menu = control->parent;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;

	cRender.DrawBox(x, y, control->width, control->height, 0xFFFFFFFF);

	int stringLength = cRender.getLength(control->label.c_str(), cRender.m_pFonts[MenuFont]);
	cRender.DrawLine(x+18, y, x+20+stringLength, y, 0xFF343434);

	int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
	cRender.DrawString(x+20+(stringLength/2), y-(charHeight/2), 0xFFFFFFFF, DT_CENTER, MenuFont, control->label.c_str()); 
}

void CMenuManager::drawButton(CControl* control)
{
	CMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if(control == activeControl) state = controlState;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;

	DWORD boxBackground1 = 0xFFFBFBFB;
	DWORD boxBackground2 = 0xFFE3E3E3;
	DWORD textColour = 0xFF424242;

	if(state == STATE_HOVER || state == STATE_PRESSED)
	{
		boxBackground1 = 0xFFFDFDFD;
		boxBackground2 = 0xFFEFEFEF;
		textColour = 0xFF417394;
	}

	cRender.DrawFillRect(x, y, control->width, control->height, 0xFFA8A8A8);
	cRender.DrawGradientBox(x+1, y+1, control->width-1, control->height-1, boxBackground1, boxBackground2, vertical);
	cRender.DrawBox(x, y, control->width, control->height, 0xFF000000);

	int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
	cRender.DrawString(x+(control->width/2), y+(control->height/2)-(charHeight/2), textColour, DT_CENTER, MenuFont, control->label.c_str());
}

void CMenuManager::drawCheckbox(CControl* control)
{
	CMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if(control == activeControl) state = controlState;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;

	if(state == STATE_NORMAL)
	{
		cRender.DrawFillRect(x, y, control->width, control->height, 0xFFA8A8A8);
		cRender.DrawGradientBox(x+1, y+1, control->width-1, control->height-1, 0xFFFBFBFB, 0xFFE3E3E3, vertical);
		cRender.DrawBox(x, y, control->width, control->height, 0xFF000000);
	}
	else if(state == STATE_HOVER || state == STATE_PRESSED)
	{
		cRender.DrawFillRect(x, y, control->width, control->height, 0xFFA8A8A8);
		cRender.DrawGradientBox(x+1, y+1, control->width-1, control->height-1, 0xFFFBFBFB, 0xFFEFEFEF, vertical);
		cRender.DrawBox(x, y, control->width, control->height, 0xFF000000);
	}

	int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
	cRender.DrawString(x+control->width+5, y+(control->height/2)-(charHeight/2), 0xFFFFFFFF, DT_LEFT, MenuFont, control->label.c_str());

	if( control->value && *(float*)control->value == 1.0f )
	{
		cRender.DrawString(x+1+(control->width/2), y+(control->height/2)-(charHeight/2), 0xFF424242, DT_CENTER, MenuFont, "x");
	}
}

void CMenuManager::drawRadioButton(CControl* control)
{
	CMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if(control == activeControl) state = controlState;

	int x = menu->xPosition+control->xOffset + (control->width/2);
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset + (control->height/2);

	if(state == STATE_NORMAL)
	{
		cRender.DrawCircle(x+1, y+1, (control->width/2), 0xFFA8A8A8);
		cRender.DrawCircle(x, y, (control->width)/2, 0xFFA8A8A8);
	}
	else if(state == STATE_HOVER || state == STATE_PRESSED)
	{
		cRender.DrawCircle(x+1, y+1, (control->width/2), 0xFFA8A8A8);
		cRender.DrawCircle(x, y, (control->width/2), 0xFFA8A8A8);
	}

	int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
	cRender.DrawString(x+control->width+5, y+(control->height/2)-(charHeight/2), 0xFFFFFFFF, DT_LEFT, MenuFont, control->label.c_str());
}

void CMenuManager::drawDropDown(CControl* control)
{
	CMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if(control == activeControl) state = controlState;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;

	cRender.DrawFillRect(x, y, control->width, control->height, 0xFFA8A8A8);
	cRender.DrawGradientBox(x+1, y+1, control->width-1, control->height-1, 0xFFFBFBFB, 0xFFE3E3E3, vertical);
	cRender.DrawBox(x, y, control->width, control->height, 0xFF000000);

	if( control->value )
	{
		int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
		cRender.DrawString(x+3, y+(control->height/2)-(charHeight/2), 0xFF424242, DT_LEFT, MenuFont, control->cL[*(int*)control->value].c_str());
		cRender.DrawString(x,y+(control->height/2)-(charHeight/2)-20, 0xFFFFFFFF, DT_LEFT, MenuFont, control->label.c_str());

		if(control->isDropped)
		{
			short choiceListSize = control->cL.size();
			for(int i=0;i<choiceListSize;++i)
			{
				int yOffset = (i+1)*control->height;
				cRender.DrawFillRect(x+1, y+1+yOffset, control->width, control->height, 0xFFFBFBFB);
				cRender.DrawString(x+3, y+(control->height/2)-(charHeight/2)+yOffset, 0xFF424242, DT_LEFT, MenuFont, control->cL[i].c_str());
			}
		}
	}
}

void CMenuManager::drawSlider(CControl* control)
{
	CMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if(control == activeControl) state = controlState;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;

	cRender.DrawLine(x, y+(control->height/2), x+control->width, y+(control->height/2), 0xFFCECECE);

	int pix2value = control->width / (control->max-control->min);
	int valueX = x + (*(int*)control->value * pix2value);

	cRender.DrawFillRect(valueX-2, y, 4, control->height, 0xFFA8A8A8);
	cRender.DrawGradientBox(valueX-2+1, y+1, 4-1, control->height-1, 0xFFFBFBFB, 0xFFE3E3E3, vertical);

	int charHeight = cRender.m_pFonts[MenuFont]->m_fChrHeight;
	cRender.DrawString(x, y+(control->height/2)-(charHeight/2)-10, 0xFFFFFFFF, DT_LEFT, MenuFont, control->label.c_str());

	if(state == STATE_PRESSED)
		cRender.DrawString(valueX, y+control->height+2, 0xFFFFFFFF, DT_CENTER, MenuFont, "%i", *(int*)control->value);  
}

void CMenuManager::drawCursor()
{
	//D3DXCreateTextureFromFileInMemory(this->direct3DDevice9, Mouse, sizeof(Mouse), &m_MouseTex);
	//D3DXCreateTextureFromFileInMemoryEx(cRender.m_pDevice, (LPCVOID)Mouse, sizeof(Mouse), 13, 20,D3DX_DEFAULT,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0,0,0,&m_MouseTex );
	cRender.DrawFillRect(mouseX,mouseY,5,5,0xFF0000FF);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///					THE INPUT SECTION.		All functions regarding input will follow below				  ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int testX = 0;
int testY = 0;
void CMenuManager::handleInput()
{
	if(!this->initialized) return;

	// Hotkey toggle menu
	if(GetAsyncKeyState(menuKey)&1)
		menuOpen = !menuOpen;

	if(!menuOpen) { resetInput(); return; }

	// Get the cursor position. The whole input depends on this.
	getMousePosition();

	getNewActiveControl();

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if(!movingMenu) getNewForegroundMenu();

		if(foregroundMenu == NULL) return;

		CMenu* menu = foregroundMenu;

		if(!fgMenuActive) return;

		doMovement();
		if( ( movingMenu = isMovingMenu() ) == true ) return;

		if(activeControl == NULL) return;

		CControl* control = activeControl;
		if(controlState == STATE_HOVER)
		{
			controlState = STATE_PRESSED;

			if(control->controlType == TYPE_SLIDER)
			{
				int x = foregroundMenu->xPosition+control->xOffset;
				int pix2value = control->width / (control->max-control->min);
				*(int*)control->value = (mouseX - x) / pix2value;

				if(*(int*)control->value > control->max) *(int*)control->value = control->max;
				else if(*(int*)control->value < control->min) *(int*)control->value = control->min;

			}

			readyForRelease = true;
			return;
		}

		keybd_event( VK_LBUTTON, 0, KEYEVENTF_KEYUP, 0 );
	}
	else if(GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if(!movingMenu) getNewForegroundMenu();

		if(foregroundMenu == NULL) return;

		CMenu* menu = foregroundMenu;

		if(!fgMenuActive) return;

		keybd_event( VK_RBUTTON, 0, KEYEVENTF_KEYUP, 0 );
	}
	else if(GetAsyncKeyState(VK_MBUTTON) & 0x8000)
	{
		if(!movingMenu) getNewForegroundMenu();

		if(foregroundMenu == NULL) return;

		CMenu* menu = foregroundMenu;

		if(!fgMenuActive) return;

		if(isOverTitlebar()) menu->minimized = !menu->minimized;

		keybd_event( VK_MBUTTON, 0, KEYEVENTF_KEYUP, 0 );
	}
	else
	{
		if(readyForRelease && controlIsInRange(activeControl))
		{
			CMenu* menu = foregroundMenu;
			CControl* control = activeControl;
			switch(control->controlType)
			{
			case TYPE_CHECKBOX:
				if(*(float*)control->value == 1.0f) 
					*(float*)control->value = 0.0f; 
				else 
					*(float*)control->value = 1.0f;
				break;
			case TYPE_RADIOBUTTON:
				*(bool*)control->value = true;
				break;
			case TYPE_TAB:
				control->activeTab = getTabAtMousePosition();
				break;
			case TYPE_DROPDOWN:
				control->isDropped = !control->isDropped;

				short choiceListSize = control->cL.size();
				for(int i=0;i<choiceListSize;++i)
				{
					int yOffset = (i+1)*control->height;
					int x = menu->xPosition+control->xOffset;
					int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset+yOffset;
					if( mouseX >= x && mouseX <= x+control->width &&
						mouseY >= y && mouseY <= y+control->height )
					{
						*(int*)control->value = i;
						control->isDropped = false;
						break;
					}
				}

				break;
				
			}

			if(!IsBadReadPtr(control->function,4))
			{
				DWORD address = (DWORD)control->function;

				_asm 
				{
					mov eax, control;
					push eax;
					call address;
					pop ebx;
				}
			}

		}

		resetInput();
	}
}

void CMenuManager::resetInput()
{
	movingMenu = false;
	readyForRelease = false;

	//keybd_event( VK_LBUTTON, 0, KEYEVENTF_KEYUP, 0 );
	//keybd_event( VK_RBUTTON, 0, KEYEVENTF_KEYUP, 0 );
	//keybd_event( VK_MBUTTON, 0, KEYEVENTF_KEYUP, 0 );
}

void CMenuManager::getMousePosition()
{
	
	POINT CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(GetForegroundWindow(),&CursorPos);

	mouseX = CursorPos.x;
	mouseY = CursorPos.y;
}

CMenu* CMenuManager::getMenuAtMousePosition()
{
	if(menuIsInRange(foregroundMenu))
		return foregroundMenu;

	for(int i=0;i<mL.size();i++)
	{
		CMenu* menu = mL[i];
		if(menu==foregroundMenu) continue;

		if(menuIsInRange(menu)) return menu;
	}

	return NULL;
}

CControl* CMenuManager::getControlAtMousePosition()
{
	if(controlState == STATE_PRESSED) return activeControl;

	for(int i=0;i<mL.size();i++)
	{
		CMenu* menu = mL[i];

		if(menu->closed || menu->minimized) continue;

		for(int j=0;j<menu->cL.size();j++)
		{
			CControl* control = menu->cL[j];

			if(!control->needsInput) continue;

			if(controlIsInRange(control)) return control;

			if(control->tL.size() > 0)
			{
				CMenu* activeTab = control->tL[control->activeTab];
				for(int k=0;k<activeTab->cL.size();k++)
				{
					CControl* control = activeTab->cL[k];
					if(!control->needsInput) continue;
					if(controlIsInRange(control)) return control;
				}
			}
		}
	}

	return NULL;
}

int CMenuManager::getTabAtMousePosition()
{
	for(int i=0;i<activeControl->tL.size();i++)
	{
		int w = 60;
		int h = 20;

		int xMultiplier = (w+3) * i;
		int x = foregroundMenu->xPosition+activeControl->xOffset + xMultiplier;
		int y = foregroundMenu->yPosition+activeControl->yOffset+titlebarHeight+titlebarOffset;

		if(	mouseX >= x && mouseX <= (x + w) &&
			mouseY >= y && mouseY <= (y + h) )
			return i;
	}
	
	return activeControl->activeTab;
}

bool CMenuManager::menuIsInRange(CMenu* menu)
{
	if(!menu) return false;

	if(	mouseX >= menu->xPosition && mouseX <= (menu->xPosition + menu->width) &&
		mouseY >= menu->yPosition && mouseY <= (menu->yPosition + menu->height+titlebarHeight+titlebarOffset) )
		return true;

	return false;
}

bool CMenuManager::controlIsInRange(CControl* control)
{
	if(!control) return false;

	CMenu* menu = control->parent;
	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition+control->yOffset+titlebarHeight+titlebarOffset;
	int width = control->width;
	int height = control->height;

	if(control->controlType == TYPE_DROPDOWN && control->isDropped)
		height = control->height*(control->cL.size() + 1);

	if(	mouseX >= x && mouseX <= (x + width) &&
		mouseY >= y && mouseY <= (y + height) )
		return true;

	return false;
}

void CMenuManager::getNewForegroundMenu()
{
	if(forcedTopMenu != NULL) return;
	CMenu* newMenu = getMenuAtMousePosition();

	if(newMenu == NULL) 
	{
		fgMenuActive = false;
		return;
	}

	foregroundMenu = newMenu;
	fgMenuActive = true;
}

void CMenuManager::getNewActiveControl()
{
	CControl* newControl = getControlAtMousePosition();

	if(newControl == NULL )
	{
		controlState = STATE_NORMAL;
		return;
	}

	activeControl = newControl;
	controlState = STATE_HOVER;
}

bool CMenuManager::isMovingMenu()
{
	if(movingMenu) return true;

	return isOverTitlebar();
}

bool CMenuManager::isOverTitlebar()
{
	CMenu* menu = foregroundMenu;

	if( mouseX >= menu->xPosition && mouseX <= menu->xPosition + menu->width &&
		mouseY >= menu->yPosition && mouseY <= (menu->yPosition + titlebarHeight) )
		return true;

	return false;
}

void CMenuManager::doMovement()
{
	CMenu* menu = foregroundMenu;

	if(movingMenu)
	{
		menu->xPosition = mouseX - distanceToX;
		menu->yPosition = mouseY - distanceToY;
	}
	else
	{
		distanceToX = mouseX - menu->xPosition;
		distanceToY = mouseY - menu->yPosition;
	}

}

void CMenuManager::centerMenu(CMenu* menu)
{
	int w = menu->width;
	int h = menu->height;
	int centerX = (cRender.m_ViewPort.Width/2) - (w/2);
	int centerY = (cRender.m_ViewPort.Height/2) - (h/2);

	menu->xPosition = centerX;
	menu->yPosition = centerY;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///					THE ADDITIONAL SECTION.		All additional functions will follow below				  ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void closeMB(CControl* control)
{
	CMenu* menu = control->parent;
	cMenu.setForcedTopMenu(NULL);

	cMenu.rem(menu);
}

void CMenuManager::MessageBox(string title, string message)
{
	CMenu* messageBox = new CMenu(title, 100, 100, 400, 150, NULL);
	messageBox->add(new CLabel(message, 200, 75-cRender.m_pFonts[MenuFont]->m_fChrHeight, DT_CENTER));
	messageBox->add(new CButton("OK", 150, 115, 100, 20, closeMB));
	this->add(messageBox);

	setForcedTopMenu(messageBox);
	centerMenu(messageBox);
}

VIRTUALKEY VirtualKeyTable[] =
{
	{ VK_LBUTTON, "LClick" },
	{ VK_RBUTTON, "RClick" },
	{ VK_CANCEL, "Cancel" },
	{ VK_MBUTTON, "MiddleMouse" },
	{ VK_BACK, "Backspace" },
	{ VK_TAB, "TAB" },
	{ VK_CLEAR, "Clear" },
	{ VK_RETURN, "Enter" },
	{ VK_SHIFT, "Shift" },
	{ VK_CONTROL, "Control" },
	{ VK_MENU, "Alt" },
	{ VK_PAUSE, "Pause" },
	{ VK_CAPITAL, "CAPS" },
	{ VK_ESCAPE, "Escape" },
	{ VK_SPACE, "Spacebar" },
	{ VK_PRIOR, "PageUp" },
	{ VK_NEXT, "PageDown" },
	{ VK_END, "End" },
	{ VK_HOME, "Home" },
	{ VK_LEFT, "LArrow" },
	{ VK_UP, "UpArrow" },
	{ VK_RIGHT, "RArrow" },
	{ VK_DOWN, "DownArrow" },
	{ VK_SELECT, "Select" },
	{ VK_PRINT, "Print" },
	{ VK_EXECUTE, "Execute" },
	{ VK_SNAPSHOT, "PrintScreen"},
	{ VK_INSERT, "Insert" },
	{ VK_DELETE, "Delete" },
	{ VK_HELP, "Help" },
	{ 0x30, "0" },
	{ 0x31, "1" },
	{ 0x32, "2" },
	{ 0x33, "3" },
	{ 0x34, "4" },
	{ 0x35, "5" },
	{ 0x36, "6" },
	{ 0x37, "7" },
	{ 0x38, "8" },
	{ 0x39, "9" },
	{ 0x41, "A" },
	{ 0x42, "B" },
	{ 0x43, "C" },
	{ 0x44, "D" },
	{ 0x45, "E" },
	{ 0x46, "F" },
	{ 0x47, "G" },
	{ 0x48, "H" },
	{ 0x49, "I" },
	{ 0x4A, "J" },
	{ 0x4B, "K" },
	{ 0x4C, "L" },
	{ 0x4D, "M" },
	{ 0x4E, "N" },
	{ 0x4F, "O" },
	{ 0x50, "P" },
	{ 0x51, "Q" },
	{ 0x52, "R" },
	{ 0x53, "S" },
	{ 0x54, "T" },
	{ 0x55, "U" },
	{ 0x56, "V" },
	{ 0x57, "W" },
	{ 0x58, "X" },
	{ 0x59, "Y" },
	{ 0x5A, "Z" },
	{ VK_NUMPAD0, "Numpad0" },
	{ VK_NUMPAD1, "Numpad1" },
	{ VK_NUMPAD2, "Numpad2" },
	{ VK_NUMPAD3, "Numpad3" },
	{ VK_NUMPAD4, "Numpad4" }, // 72
	{ VK_NUMPAD5, "Numpad5" },
	{ VK_NUMPAD6, "Numpad6" },
	{ VK_NUMPAD7, "Numpad7" },
	{ VK_NUMPAD8, "Numpad8" },
	{ VK_NUMPAD9, "Numpad9" },
	{ VK_SEPARATOR, "NumpadSeperator" },
	{ VK_SUBTRACT, "NumpadMinus" },
	{ VK_DECIMAL, "NumpadDecimal" },
	{ VK_DIVIDE, "NumpadDivide" },
	{ VK_F1, "F1" },
	{ VK_F2, "F2" },
	{ VK_F3, "F3" },
	{ VK_F4, "F4" },
	{ VK_F5, "F5" },
	{ VK_F6, "F6" },
	{ VK_F7, "F7" },
	{ VK_F8, "F8" },
	{ VK_F9, "F9" },
	{ VK_F10, "F10" },
	{ VK_F11, "F11" },
	{ VK_F12, "F12" },
	{ VK_F13, "F13" },
	{ VK_F14, "F14" },
	{ VK_F15, "F15" },
	{ VK_F16, "F16" },
	{ VK_F17, "F17" },
	{ VK_F18, "F18" },
	{ VK_F19, "F19" },
	{ VK_F20, "F20" },
	{ VK_F21, "F21" },
	{ VK_F22, "F22" },
	{ VK_F23, "F23" },
	{ VK_F24, "F24" },
	{ VK_NUMLOCK, "Numlock" },
	{ VK_SCROLL, "Scroll" },
	{ VK_LSHIFT, "LeftShift" },
	{ VK_RSHIFT, "RightShift" },
	{ VK_LCONTROL, "LeftCtrl" },
	{ VK_RCONTROL, "RightCtrl" },
	{ VK_LMENU, "LeftMenu" },
	{ VK_RMENU, "RightMenu" },
	{ VK_PLAY, "Play" },
	{ VK_ZOOM, "Zoom" },
	{ VK_XBUTTON1, "XBtn1"},
	{ VK_XBUTTON2, "XBtn2"},
}; 
