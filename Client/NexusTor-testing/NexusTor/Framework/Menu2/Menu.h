#include <vector>
#include <Windows.h>

using namespace std;

namespace TABS
{
	enum Tabs
	{
		Aimbot = 0,
		Esp,
		Misc,
		Visuals,
		Radar2D,
		Colors,
		About,
		ObjectEsp,
		Chams,
	};
}

#define BAR 25
#define RECTSIZE 15
#define TOTALSIZE 85
#define SPACE 5

enum enumColors
{
	Red = 1,
	Blue,
	Green,
	Cyan,
	LightBlue,
	LightRed,
	LightGreen,
	DarkBlue,
	DarkRed,
	DarkGreen,
	Orange,
	Purble,
	Yellow,
	White,
	Black,
	Gray,
	None = 100,
};
typedef struct S_Rect
{
	float x;
	float y;
	float w;
	float h;
}sRect;

struct SSlider
{
	int x,y,w;
	float MaxValue;
	char* name;
	PFLOAT Out;
};
struct STab
{
	int x,y,Tab;
	char* Name;
};
struct SDropDown
{
	int x, y, w, Tab;
	char* name;
	PFLOAT  Hack;
	char** Options;
	int Totaloptions;
	bool dropped;
};
struct SColorBox
{
	int x,y,tab;
	int barH, w;
	PFLOAT OutR,OutG,OutB;
	float NormalR,NormalG,NormalB;
	bool Dropped;
	int iCol;
};
struct SPenel
{
	int x,y,w,h,tab;
	char* Name;
	DWORD Color;
};
struct SCheckBox
{
	int x,y,Tab;
	char* name;
	PFLOAT Hack;
};
struct SButton
{
	int x,y,w, tab;
	char* Name;
	PFLOAT Hack;
};
struct SText
{
	int x, y, tab;
	int Font;
	char* Text;
};
class CMenu
{
public:
	void InitializeMenu			( void );
	void DrawMenu				( void );
	void DrawMouse				( void );
	void DrawNotification		( void );
	bool NeedNotification		(  );
	void UpdateMenu				( int MenuKey );
	void SetMousePosition		( int PosXNew, int PosYNew );
	bool IsMouseOver			( float x, float y, float objWidth, float objHeight );
	void AddColorBox			( int x, int y, int barH, int w, PFLOAT OurR, PFLOAT OurG, PFLOAT OurB, int Tab, float NormalR, float NormalG, float NormalB, bool dropped );
	void AddDropdown			( int x, int y, int w, char* name, PFLOAT Hack, char** Options, int totaloptions, int tab, bool dropped );
	void AddTab					( int x, int y, char* name, int Tab );
	void AddPenel				( int x, int y, int tab, char* name, int w, int h, DWORD col );
	void AddCheckBox			( int x, int y, int tab, char* name, PFLOAT hack );
	void AddButton				( int x, int y, int w, int tab, char* name, PFLOAT Hack );
	void AddText				( int x, int y, int Font, char* Text, int Tab );
	POINT m_pMousePos;
	bool m_bMenuIsOpen;
private:
	vector<SColorBox> sColorBox;
	vector<SDropDown> sDropDown;
	vector<STab> sTab;
	vector<SPenel> sPenel;
	vector<SCheckBox> sCheckBox;
	vector<SButton> sButton;
	vector<SText> sText;
	vector<SSlider> sSlider;
	int m_iDifferenceX, m_iDifferenceY;
	int m_iMenuWidth, m_iMenuHeight;
	int	m_iCurrentTab;
	int m_iMenuKey;
	bool m_bDrawNotification;
	POINT m_pMenuPos;
};

extern CMenu cMenu;