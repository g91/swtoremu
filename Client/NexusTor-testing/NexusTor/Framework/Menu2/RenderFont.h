//-----------------------------------------------------------------------------
// File: D3DFont.h
// Desc: Texture-based font class
// Copyright (c)  Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef D3DFONT_H
#define D3DFONT_H

#include <tchar.h>
#include <d3d9.h>

// Font creation flags
#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

// Font rendering flags
#define D3DFONT_CENTERED    0x0001
#define D3DFONT_TWOSIDED    0x0002
#define D3DFONT_FILTERED    0x0004
#define D3DFONT_RIGHT       0x0008			// non standard feature
#define D3DFONT_SHADOW      0x0010			// non standard feature



//-----------------------------------------------------------------------------
// Name: class CD3DFont
// Desc: Texture-based font class for doing text in a 3D scene.
//-----------------------------------------------------------------------------
class CD3DFont
{
	TCHAR   m_strFontName[80];            // Font properties
	DWORD   m_dwFontHeight;
	DWORD   m_dwFontFlags;

	LPDIRECT3DDEVICE9       m_pd3dDevice; // A D3DDevice used for rendering
	LPDIRECT3DTEXTURE9      m_pTexture;   // The d3d texture for this font
	LPDIRECT3DVERTEXBUFFER9 m_pVB;        // VertexBuffer for rendering text
	DWORD   m_dwTexWidth;                 // Texture dimensions
	DWORD   m_dwTexHeight;
	FLOAT   m_fTextScale;
	FLOAT   m_fTexCoords[128-32][4];
	DWORD   m_dwSpacing;                  // Character pixel spacing per side

	// Stateblocks for setting and restoring render states
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockSaved;
	LPDIRECT3DSTATEBLOCK9 m_pStateBlockDrawText;

public:
	DWORD GetTextHeight(  ) { return m_dwTexHeight; }
	// 2D and 3D text drawing functions
	HRESULT DrawText( FLOAT x, FLOAT y, DWORD dwColor, 
		const TCHAR* strText, DWORD dwFlags=0L );
	HRESULT DrawTextScaled( FLOAT x, FLOAT y, FLOAT z, 
		FLOAT fXScale, FLOAT fYScale, DWORD dwColor, 
		const TCHAR* strText, DWORD dwFlags=0L );
	HRESULT Render3DText( const TCHAR* strText, DWORD dwFlags=0L );

	// Function to get extent of text
	HRESULT GetTextExtent( const TCHAR* strText, SIZE* pSize );

	// Initializing and destroying device-dependent objects
	HRESULT InitDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice );
	HRESULT RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();

	// Constructor / destructor
	CD3DFont( const TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags=0L );
	~CD3DFont();
};

#endif


