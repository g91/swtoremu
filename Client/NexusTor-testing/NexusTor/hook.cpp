#include "StdAfx.h"
#include "hook.h"

#define _ENDSCENE_ //_BEGINSCENE_ //_PRESENT_ //_ENDSCENE_
#define _D3DX_RENDERING_ //_PRIM_RENDERING_ //_PRIM_RENDERING_ //_D3DX_RENDERING_ //_CLEAR_RENDERING_
#define _D3DX_FONT_ 

#define RESET					16
#define PRESENT					17
#define ENDSCENE				42
#define BEGINSCENE				43
#define DRAWINDEXEDPRIMITIVE	82

typedef HRESULT ( WINAPI* oEndScene )             ( LPDIRECT3DDEVICE9 pDevice );
typedef HRESULT ( WINAPI* oBeginScene )			  ( LPDIRECT3DDEVICE9 pDevice );
typedef HRESULT ( WINAPI* oReset )                ( LPDIRECT3DDEVICE9 pDevice,D3DPRESENT_PARAMETERS* pPresentationParameters );
typedef HRESULT ( WINAPI* oPresent )			  ( LPDIRECT3DDEVICE9 pDevice, CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion );
typedef HRESULT ( WINAPI* oDrawIndexedPrimitive ) ( LPDIRECT3DDEVICE9 pDevice,D3DPRIMITIVETYPE Type,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount );
typedef HRESULT ( WINAPI* oSetRenderState )		  ( LPDIRECT3DDEVICE9 pDevice, D3DRENDERSTATETYPE State, DWORD Value, UINT NumVertices, UINT startIndex, UINT primCount, UINT m_Stride );

oReset pReset;
HRESULT hkReset( LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS * pPresentParams )
{
	_asm pushad;

	cRender.onLostDevice();
	HRESULT hRet = pReset(pDevice, pPresentParams);
	cRender.onResetDevice();

	_asm popad;
	return hRet;
}

bool bInit = false;
void RenderBackend( LPDIRECT3DDEVICE9 pDevice )
{
	if(!bInit)
	{
		cRender.InitD3D(pDevice);
		cMenu.initialize();
		bInit = true;
	}

	if(bInit)
	{
		//cDebugTextRenderer::Instance()->MyDrawText( 10, 10, eastl::string( "test" ), 0xFFFF0000,  0);
		cMenu.perform(); // Call Menu
	}

}

DWORD dwRet = NULL;

#if defined( _ENDSCENE_ )

oEndScene pEndScene;
HRESULT WINAPI EndScene( LPDIRECT3DDEVICE9 pDevice )
{
	_asm
	{
		PUSHAD
			MOV EAX, [EBP+0x4]
		MOV dwRet, EAX
	}

	RenderBackend(pDevice);

	_asm popad;

	return pEndScene( pDevice );
}

#elif defined( _BEGINSCENE_ )

oBeginScene pBeginScene;
HRESULT WINAPI BeginScene( LPDIRECT3DDEVICE9 pDevice )
{
	_asm
	{
		PUSHAD
			MOV EAX, [EBP+0x4]
		MOV dwRet, EAX
	}

	RenderBackend( pDevice );

	_asm popad;

	return pBeginScene( pDevice );
}

#elif defined( _PRESENT_ )

oPresent pPresent;
HRESULT WINAPI Present( LPDIRECT3DDEVICE9 pDevice, CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion )
{
	_asm
	{
		PUSHAD
			MOV EAX, [EBP+0x4]
		MOV dwRet, EAX
	}

	RenderBackend( pDevice );

	_asm popad;

	return pPresent( pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

#endif


bool IsGameReady( void )
{
	if( GetModuleHandle( "swtor.exe" )			== NULL 
		|| GetModuleHandle( "d3d9.dll" )		== NULL 
		|| GetModuleHandle( "RemoteRenderer.dll" ) == NULL )
		return false;

	return true;
}

void Init( void )
{
	//dwMemoryManBase = (DWORD)GetModuleHandle( "MemoryMan.dll" );
	//dwSWTOR = (DWORD)GetModuleHandle("swtor.exe");
	//dwRemoteRendererBase = (DWORD)GetModuleHandle( "RemoteRenderer.dll" );
	//dwRemoteRendererThis = dwRemoteRendererBase + 0x1B7618;

	//cDebugTextRenderer::Instance();
}

DWORD WINAPI CDirectX::dwThread( LPVOID lpArg )
{
	while ( !GetAsyncKeyState( VK_F11 ) )
		Sleep( 100 );

	while( !IsGameReady() )
		Sleep( 100 );

	printf("Game is Ready");

	Init();

	DWORD dwD3D, dwAddr, *vtbl;

	dwD3D = 0;

	do 
	{
		dwD3D = (DWORD)GetModuleHandle( "d3d9.dll" );
		Sleep( 25 );
	}while( !dwD3D );


	dwAddr = Utils::FindPattern(dwD3D, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");

	if( dwAddr ) 
	{
		memcpy( &vtbl,(void *)( dwAddr+2 ), 4 );
#pragma endregion

#pragma region Hooking	

#if defined( _ENDSCENE_ )
		pEndScene = (oEndScene)DetourFunction( (PBYTE)vtbl[ENDSCENE], (PBYTE)EndScene );
		printf("DetourFunction ENDSCENE");
#elif defined( _BEGINSCENE_ )
		pBeginScene = (oBeginScene)DetourFunction( (PBYTE)vtbl[BEGINSCENE], (PBYTE)BeginScene );
#elif defined( _PRESENT_ )
		pPresent  = (oPresent)DetourFunction( (PBYTE)vtbl[PRESENT], (PBYTE)Present );
#endif
		pReset = (oReset)DetourFunction( (PBYTE)vtbl[RESET], (PBYTE)hkReset );
		//pDrawIndexedPrimitive = (oDrawIndexedPrimitive)hook->DetourCreate( (PBYTE)vtbl[DRAWINDEXEDPRIMITIVE], (PBYTE)DrawIndexedPrimitive, 5 );
	}
#pragma endregion

	return FALSE;
}