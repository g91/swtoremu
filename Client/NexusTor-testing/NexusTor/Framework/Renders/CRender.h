#ifndef CRENDER_H
#define CRENDER_H
#include "CRenderFont.h"
#include "CRenderPrim.h"
#include "../../StdAfx.h"

#pragma warning(disable:4996)
#pragma warning(disable:4244)

#define COL_RED       D3DCOLOR_XRGB(255,0,0)
#define COL_REDA(a)   D3DCOLOR_ARGB(a,255,0,0)

#define COL_WHITE     D3DCOLOR_XRGB(255,255,255)
#define COL_WHITEA(a) D3DCOLOR_ARGB(a,255,255,255)

#define COL_YELLOW     D3DCOLOR_XRGB(255,255,0)
#define COL_YELLOWA(a) D3DCOLOR_ARGB(a,255,255,0)

#define COL_BLACK	  D3DCOLOR_XRGB(0,0,0)
#define COL_BLACKA(a) D3DCOLOR_ARGB(a,0,0,0)

#define COL_GREEN     D3DCOLOR_XRGB(124,252,0)
#define COL_GREENA(a) D3DCOLOR_ARGB(a,124,252,0)

#define COL_BLUE      D3DCOLOR_XRGB(30,144,255)
#define COL_BLUEA(a)  D3DCOLOR_ARGB(a,30,144,255)

#define COL_PURPLE      D3DCOLOR_XRGB(139,0,204)
#define COL_PURPLEA(a)  D3DCOLOR_ARGB(a,139,0,204)

#define COL_DARKGREEN   D3DCOLOR_XRGB(0,100,0)
#define COL_DARKGREENA  D3DCOLOR_ARGB(a,0,100,0)

#define TOTAL_FONTS  5
enum eFontSet
{
	MenuFont,
	EspFont,
	HeaderFont,
	FooterFont,
	XHairFont,
};

struct shaders
{
	LPDIRECT3DPIXELSHADER9 sBlue, sRed, sPurple, sOrange,sWhite,sGreen,sYellow;
};

struct textures
{
	LPDIRECT3DTEXTURE9 sBlue,sRed,sPurple,sOrange,sWhite,sGreen,sYellow;
};

struct CVERTEX
{
	float x,y,z,rhw;
	DWORD dwColour;
	float fU;
	float fV;
};

enum gr_orientation {
	horizontal,
	vertical
};

class CRender
{
public:

	~CRender();
	bool    InitD3D(LPDIRECT3DDEVICE9 p_Device); 
	void    onLostDevice();
	void    onResetDevice();
	//====================Draw Functions=====================
	void    DrawString(int x, int y, D3DCOLOR dwColour,DWORD dwFlag, eFontSet Font, const char *sztext,...);
	void    DrawBlackBorderString(int x, int y, DWORD dwColor,DWORD dwAlign, eFontSet Font,const char* szText, ...);
	HRESULT DrawLine(float startX,float startY,float endX,float endY, DWORD dwColour);
	HRESULT DrawOutline(float x,float y,float width,float height,DWORD dwColour);
	HRESULT DrawFillRect(float x,float y,float width,float height,DWORD dwColour);
	HRESULT DrawCircle(int x, int y, float radius, DWORD dwColour);
	void	DrawBox(int x, int y, int w, int h, DWORD dwColour);
	void    DrawFillRectOut(float x,float y,float width,float height,DWORD dwOutCol,DWORD dwFillCol);
	void    DrawGradientBox( float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation );
	void	DrawHealthBar(int x, int y, float health, int w, int h, D3DCOLOR color1, D3DCOLOR color2);
	void    DrawSprite(float x, float y, LPDIRECT3DTEXTURE9 Texture, float Alpha = 255);
	//Generate functions
	HRESULT GenerateShader(IDirect3DPixelShader9 **pShader, float r, float g, float b);
	HRESULT GenerateTexture(IDirect3DTexture9 **ppD3Dtex, DWORD colour32);
	int		getLength( const char *szText, CD3DFont* Font );

	//=======Vars==================
	D3DVIEWPORT9 m_ViewPort;
	CD3DFont*    m_pFonts[TOTAL_FONTS];
	CD3DFont*     m_pFont;
	CD3DRender*  m_pRenderPrim;
	LPD3DXSPRITE m_pSprite;

	LPDIRECT3DDEVICE9 m_pDevice;

	//shaders      m_Shaders;
	//textures tex;
	//==============================
};

extern CRender cRender;
#endif