#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#define _SECURE_SCL 0

class CMenuManager;
extern CMenuManager cMenu;

class CMenu;

// Menu Styles (CMenu->style)
#define STYLE_CLOSE			0x00010
#define STYLE_MINIMIZE		0x00100
#define STYLE_RESIZABLE		0x01000

// Control types (CControl->controlType)
#define TYPE_LABEL			0
#define TYPE_GROUPBOX		1
#define TYPE_BUTTON			2
#define TYPE_CHECKBOX		3
#define TYPE_RADIOBUTTON	4
#define TYPE_DROPDOWN		5
#define TYPE_SLIDER			6
#define TYPE_TAB			7

// States for the controls (CMenuManager->controlState)
#define STATE_NORMAL		0
#define STATE_HOVER			1
#define STATE_PRESSED		2

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class CControl
{
public:
	void addTab(CMenu* menu) { tL.push_back(menu); }
	void addChoice(string choice) { cL.push_back(choice); }
	// All Controls
	string label;
	int xOffset;
	int yOffset;
	int width;
	int height;

	void* value;
	void* function;

	int min;
	int max;
	int off;

	int controlType;

	DWORD align; // CLabel
	int group; // CRadioButton

	int activeTab; // CTab
	typedef vector<CMenu*> tabList; // CTab
	tabList tL; // CTab

	typedef vector<string> choiceList; // CDropDown
	choiceList cL;
	bool isDropped; // CDropDown


	bool needsInput;

	CMenu* parent;
};

class CLabel : public CControl
{
public:
	CLabel(string label, int xOffset, int yOffset, DWORD align)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 0;
		this->height = 0;
		this->function = NULL;
		this->value = 0;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_LABEL;
		this->needsInput = false;

		this->align = align;
	}; 
};

class CGroupBox : public CControl 
{
public: 
	CGroupBox(string label, int xOffset, int yOffset, int width, int height)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = width;
		this->height = height;
		this->function = NULL;
		this->value = 0;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_GROUPBOX;
		this->needsInput = false;
	}; 
};

class CButton : public CControl 
{
public: 
	CButton(string label, int xOffset, int yOffset, int width, int height, void* function)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = width;
		this->height = height;
		this->function = function;
		this->value = 0;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_BUTTON;
		this->needsInput = true;
	}; 
};

class CCheckbox : public CControl 
{
public: 
	CCheckbox(string label, int xOffset, int yOffset, void* value)
	{ 
		this->label = label; 
		this->xOffset = xOffset; 
		this->yOffset = yOffset;
		this->width = 12; 
		this->height = 12; 
		this->function = NULL;
		this->value = value;
		this->min = 0;
		this->max = 1;
		this->off = 0;
		this->controlType = TYPE_CHECKBOX;
		this->needsInput = true;
	}; 
};

class CRadioButton : public CControl 
{
public:
	CRadioButton(string label, int xOffset, int yOffset, int group)
	{ 
		this->label = label; 
		this->xOffset = xOffset; 
		this->yOffset = yOffset;
		this->width = 12;
		this->height = 12;
		this->function = NULL;
		this->value = 0;
		this->min = 0;
		this->max = 1;
		this->off = 0;
		this->controlType = TYPE_RADIOBUTTON;
		this->needsInput = true;

		this->group = group;
	}; 
};

class CDropDown : public CControl
{
public:
	CDropDown(string label, int xOffset, int yOffset, void* value)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 130;
		this->height = 20;
		this->function = NULL;
		this->value = value;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_DROPDOWN;
		this->needsInput = true;

		this->isDropped = true;
	};
};

class CSlider : public CControl 
{
public:
	CSlider(string label, int xOffset, int yOffset, int min, int max, void* value)
	{ 
		this->label = label; 
		this->xOffset = xOffset; 
		this->yOffset = yOffset;
		this->width = 200;
		this->height = 10;
		this->function = NULL;
		this->value = value;
		this->min = min;
		this->max = max;
		this->off = 0;
		this->controlType = TYPE_SLIDER;
		this->needsInput = true;
	}; 
};

class CTab : public CControl 
{
public:
	CTab(int xOffset, int yOffset)
	{ 
		this->label = "";
		this->xOffset = xOffset; 
		this->yOffset = yOffset;
		this->width = 10;
		this->height = 10;
		this->function = NULL;
		this->value = value;
		this->min = min;
		this->max = max;
		this->off = 0;
		this->controlType = TYPE_TAB;
		this->needsInput = true;

		this->activeTab = 0;
	}; 
};

class CMenu
{
public:
	CMenu(string title) { CMenu(title, 100, 100, 100, 100, NULL); }
	CMenu(string title, int x, int y) { CMenu(title, x, y, 100, 100, NULL); }
	CMenu(string title, int x, int y, int w, int h) { CMenu(title, x, y, w, h, NULL); }
	CMenu(string title, int x, int y, int w, int h, DWORD style);

	void setPosition(int x, int y);
	void add(CControl* control);

	string title;
	DWORD style;

	bool minimized;
	bool closed;

	int xPosition;
	int yPosition;
	int width;
	int height;

	typedef vector<CControl*> controlList;
	controlList cL;
};

struct VIRTUALKEY
{
	UINT uiKey;
	PCHAR szKey;
};
extern VIRTUALKEY VirtualKeyTable[];

class CMenuManager
{
private:
	typedef vector<CMenu*> menuList;
	menuList mL;

	bool initialized;
	LPDIRECT3DDEVICE9 direct3DDevice9;

	bool menuOpen;
	short menuKey;
	int titlebarHeight;
	int titlebarOffset;

	CMenu* mainMenu;
	CMenu* forcedTopMenu;
	CMenu* foregroundMenu;
	bool fgMenuActive;
	bool movingMenu;
	bool readyForRelease;

	CControl* activeControl;
	int controlState; // normal, mouse over, pressed

	int mouseX;
	int mouseY;

	int distanceToX;
	int distanceToY;

	// DRAW STUFF
	void drawMenus();
	void drawMenu(CMenu* menu);
	void drawControls(CMenu* menu);
	void drawGroupBox(CControl* control);
	void drawLabel(CControl* control);
	void drawButton(CControl* control);
	void drawCheckbox(CControl* control);
	void drawRadioButton(CControl* control);
	void drawSlider(CControl* control);
	void drawDropDown(CControl* control);
	void drawCursor();

	// INPUT STUFF
	void handleInput();
	void resetInput();
	void getMousePosition();

	CMenu* getMenuAtMousePosition();
	CControl* getControlAtMousePosition();
	int getTabAtMousePosition();

	bool menuIsInRange(CMenu* menu);
	bool controlIsInRange(CControl* control);

	void getNewForegroundMenu();
	void getNewActiveControl();

	bool isMovingMenu();
	bool isOverTitlebar();
	void doMovement();
	
public:
	CMenuManager();
	void add(CMenu* menu);
	void rem(CMenu* menu);

	void setMainMenu(CMenu* menu) { mainMenu = menu; }
	CMenu* getMainMenu() { return mainMenu; }

	void setForegroundMenu(CMenu* menu) { foregroundMenu = menu; (!IsBadReadPtr(menu,4)) ? fgMenuActive = true : fgMenuActive = false; }

	void setForcedTopMenu(CMenu* menu) { forcedTopMenu = menu; foregroundMenu = forcedTopMenu;(!IsBadReadPtr(menu,4)) ? fgMenuActive = true : fgMenuActive = false; }

	void closeMenu( CMenu* menu, bool close = true ) { menu->closed = close; }

	void mimimizeMenu( CMenu* menu, bool minimize = true ) { menu->minimized = minimize; }

	void centerMenu(CMenu* menu);

	void MessageBox(string title, string message);

	int getMenuAmount() { return mL.size(); }

	void initialize();
	void perform();

	LPDIRECT3DTEXTURE9 m_MouseTex;
};

#endif