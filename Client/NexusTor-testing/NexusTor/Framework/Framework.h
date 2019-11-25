#pragma once

#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment (lib, "detours.lib")
#pragma comment (lib, "Toolkit.lib")

#pragma warning (disable: 4996 4312 4244)

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <winuser.h>
#include <fstream>
#include <tlhelp32.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <ddraw.h>
#include <vector>
#include <Shlwapi.h>
#include <math.h>
#include <detours.h>
#include <Toolkit.h>

using namespace std;

#include "Renders\CRender.h"
#include "Renders\CRenderFont.h"
#include "Renders\CRenderPrim.h"

#include "Menu\MenuManager.h"
#include "Menu\SVars.h"
#include "Menu\Textures.h"

#include "tools\ADE32.h"
#include "tools\CDetour.h"
#include "tools\crap.h"
#include "tools\xorgen.h"

#define ES	0
#define RST 1
#define DIP	2

#define HOOK(func,addy)	o##func = (t##func)DetourFunction((PBYTE)addy,(PBYTE)hk##func)


using namespace std;

extern "C" void *_ReturnAddress( void );


#define M_PI       3.14159265358979323846
class CDirectX {
public:
	static void RenderFrames();
	static int WINAPI mReset(LPDIRECT3DDEVICE9 pDevice,D3DPRESENT_PARAMETERS* pPresentParams);
	static HRESULT WINAPI mEndScene(LPDIRECT3DDEVICE9 pDevice);
	static void StartPBMonitorThread();

	static DWORD dwD3DBase;
	static DWORD dwEXEBase;
	static DWORD dwModSize;
	static bool  bObjLoaded;
	static bool  bClassesInit;
	static bool  bSwapHooked;
	static bool  bInit;
	static bool  bInitFunc;

	static char cGatewayLoc[256];

	static LPDIRECT3DDEVICE9 pDevice;
	static DWORD WINAPI dwThread(LPVOID);
};
