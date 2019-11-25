#ifndef _DEBUG_TEXT_RENDERER_H_
#define _DEBUG_TEXT_RENDERER_H_

#pragma once

#include "StdAfx.h"

enum TextFlags
{
	 TOP			 = 0x00000000,
	 LEFT			 = 0x00000000,
	 CENTER			 = 0x00000001,
	 RIGHT			 = 0x00000002,
	 VCENTER		 = 0x00000004,
	 BOTTOM			 = 0x00000008,
	 WORDBREAK		 = 0x00000010,
	 SINGLELINE		 = 0x00000020,
	 EXPANDTABS		 = 0x00000040,
	 TABSTOP		 = 0x00000080,
	 NOCLIP			 = 0x00000100,
	 EXTERNALLEADING = 0x00000200,
	 CALCRECT        = 0x00000400,
	 NOPREFIX        = 0x00000800,
	 INTERNAL        = 0x00001000,
};

class cDebugTextRenderer
{
	public:
		static cDebugTextRenderer* m_cDebugTextRenderer;

		static cDebugTextRenderer* Instance( void )
		{
			if( m_cDebugTextRenderer == NULL )
				m_cDebugTextRenderer = new cDebugTextRenderer( (HMODULE)GetModuleHandle( "RemoteRenderer.dll" ));

			return m_cDebugTextRenderer;
		}

		~cDebugTextRenderer( void )
		{
			delete m_cDebugTextRenderer;
		}

		cDebugTextRenderer( HMODULE hRemoteRenderer )
		{
			Flush		  = (tFlush)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_Flush@RemoteRenderer@bwa@@QAEXXZ" );
			SetFont       = (tSetFont)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_SetFont@RemoteRenderer@bwa@@QAEXI@Z" );
			SetFlags      = (tSetFlags)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_SetFlags@RemoteRenderer@bwa@@QAEXI@Z" );
			SetColor      = (tSetColor)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_SetColor@RemoteRenderer@bwa@@QAEXK@Z" );
			SetDropShadow = (tSetDropShadow)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_SetDropShadow@RemoteRenderer@bwa@@QAEXM@Z" );
			SetClipRegion = (tSetClipRegion)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_SetClipRegion@RemoteRenderer@bwa@@QAEXHHHH@Z" );
			DrawTextEx    = (tDrawTextEx)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_DrawText@RemoteRenderer@bwa@@QAEXHHABV?$basic_string@DVallocator@eastl@@@eastl@@@Z" );
			DrawText      = (tDrawText)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_DrawTextEx@RemoteRenderer@bwa@@QAEXHHABV?$basic_string@DVallocator@eastl@@@eastl@@IUtagRECT@@KIM@Z" );
			DrawText3D    = (tDrawText3D)(DWORD)GetProcAddress( hRemoteRenderer, "?DebugTextRenderer_DrawText3d@RemoteRenderer@bwa@@QAEXABVVector3@2@MMABV?$basic_string@DVallocator@eastl@@@eastl@@@Z" );
		}

		void MyDrawText( int x, int y, eastl::string & str, DWORD dwColor, int iFont )
		{
			Flush();
			SetFont( iFont );
			SetColor( dwColor );
			DrawText( x, y, str );
		}

		void MyDrawText3D( D3DXVECTOR3& vec, eastl::string & str, DWORD dwColor, int iFont, int iFlag )
		{
			Flush();
			SetFont( iFont );
			SetFlags( iFlag );
			SetColor( dwColor );
			DrawText3D( vec, 1, 1, str );
		}

		void MyDrawTextEx( int x, int y, eastl::string & str, unsigned int iFont, RECT rect, DWORD dwColor, unsigned int iFlags, float fSetDropShadow )
		{
			Flush();
			SetFont( iFont );
			SetColor( dwColor );
			SetFlags( iFlags );
			SetDropShadow( fSetDropShadow );
			SetClipRegion( rect.left, rect.right, rect.top, rect.bottom );
			DrawText( x, y, str );
		}


		typedef void( WINAPI *tFlush )( void );
		tFlush Flush;

		typedef void( WINAPI *tSetColor )( DWORD dwColor );
		tSetColor SetColor;

		typedef void( WINAPI *tSetDropShadow )( float fvalue );
		tSetDropShadow SetDropShadow;

		typedef void( WINAPI *tSetFont )( unsigned int iFont );
		tSetFont SetFont;

		typedef void( WINAPI *tSetFlags )( unsigned int iFlags );
		tSetFlags SetFlags;

		typedef void( WINAPI *tDrawText )( int x, int y, eastl::string & str );
		tDrawText DrawText;

		typedef void( WINAPI *tSetClipRegion )( int left, int right, int top, int bottom );
		tSetClipRegion SetClipRegion;

		typedef void( WINAPI *tDrawText3D )( D3DXVECTOR3& vec, float fDist, float fScaleFactor, eastl::string & str ); //still not entirely sure what the two floats are
		tDrawText3D DrawText3D;

		typedef void( WINAPI *tDrawTextEx )( int x, int y, eastl::string & str, unsigned int unk, RECT rect, DWORD dwColor, unsigned int unk2, float fSetDropShadow );
		tDrawTextEx DrawTextEx;               //unk and unk2 is flags and font pointer unsure which is which
};

extern class cDebugTextRenderer* DebugTextRenderer;

#endif