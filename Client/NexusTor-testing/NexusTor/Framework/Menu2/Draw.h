#ifndef CRENDER_H
#define CRENDER_H
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <stdio.h>
#include "RenderFont.h"

#pragma comment(lib,"d3d9")
#pragma comment(lib,"d3dx9")
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#define PI 3.14159265
#define TWO_PI (PI*2)

struct CVERTEX
{
	float x,y,z,rhw;
	DWORD dwColour;
};

struct S_Shaders
{
	LPDIRECT3DPIXELSHADER9 sFriend, sFriendVis, sEnemy, sEnemyVis, sVehicle, sVehicleVis, sMisc, sMiscVis;
};
struct S_Textures
{
	LPDIRECT3DTEXTURE9 tFriend, tFriendVis, tEnemy, tEnemyVis, tVehicle, tVehicleVis, tMisc, tMiscVis;
};
class CDraw
{
public:
	bool		InitializeD3D			( LPDIRECT3DDEVICE9 pD3Ddevice );
	HRESULT		DrawOutline				( float x, float y, float width, float height, DWORD dwColour );
	HRESULT		DrawLine				( float startX, float startY, float endX, float endY, DWORD dwColour );
	HRESULT		DrawFillRect			( float x, float y, float width, float height, DWORD dwColour );
	HRESULT		GenerateShader			( IDirect3DPixelShader9 **pShader, float r, float g, float b );
	HRESULT		GenerateTexture			( IDirect3DTexture9 **ppD3Dtex, DWORD colour32 );
	void		DrawShape				( long x, long y, float fDegrees, DWORD dwSides, DWORD dwSize, D3DCOLOR Color );
	void		Box						( float PosX, float PosY, float h, float w, float Space,float CornerLineLength, DWORD CornerLineW, DWORD LineW, DWORD ColCorners, DWORD ColLines );
	void		DrawHealthbar			( int Choose, int x, int y, float health, int w, int h, D3DCOLOR ColOut, D3DCOLOR ColHealth );
	void		DrawCross				( float PositionX, float PositionY, float Size, D3DCOLOR col );
	void		DrawString				( CD3DFont* pFont, int x, int y, DWORD dwColor, DWORD dwAlign, const char* szText, ... );
	void		DrawBorderString		( CD3DFont* pFont,int x, int y, DWORD dwColor,DWORD dwBorderColor, DWORD dwAlign,const char* szText, ...) ;
	void		DrawFillRectOut			( float x, float y, float width, float height, DWORD dwOutCol, DWORD dwFillCol );
	void		DrawSprite				( LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 vPosition );
	void		DrawBox					( int x, int y, int w, int h, int choose );
	void		AddCheckBoxDeactivated	( float X, float Y, char* Name );
	void		AddCheckBoxActivated	( float X, float Y, char* Name );
	void		AddCheckBoxNormal		( float X, float Y, char* Name );
	void		AddRadioButtonDeactivated( float X, float Y, char* Name );
	void		AddRadioButtonActivated	( float X, float Y, char* Name );
	void		AddButtonDeactivated	( float X, float Y, float W, char* Name );
	void		AddButtonActivated		( float X, float Y, float W, char* Name );
	void		AddButton				( float X, float Y, float W, char* Name );
	void		AddRadioButton			( float X, float Y, char* Name );
	void		DrawCrosshair			( int x, int y, int Size, int linethick, bool Bordered, DWORD Color );
	void		InitChamsCol			(  );

	D3DVIEWPORT9			ViewPort;
	CD3DFont*				Fonts[7];
	LPDIRECT3DDEVICE9		pDevice;
	LPDIRECT3DBASETEXTURE9	pTex;
	LPD3DXSPRITE			m_pSprite; 

	S_Shaders Shaders;
	S_Textures Textures;
};
extern CDraw cDraw;
#endif