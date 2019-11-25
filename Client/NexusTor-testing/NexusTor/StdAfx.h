// ==========================================================
// Nexus - ToR Project
// 
// Author: NoFaTe
// ==========================================================

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _WIN32_WINNT_MAXVER

#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment (lib, "detours.lib")

#pragma warning (disable: 4996 4312 4244)

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <winuser.h>
#include <fstream>
#include <tlhelp32.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <ddraw.h>
#include <vector>
#include <Shlwapi.h>
#include <math.h>

#include "detours.h"
#include "Utils.h"
#include "eastl.h"
#include "DebugTextRenderer.h"

using namespace std;

#include "Framework\Renders\CRender.h"
#include "Framework\Renders\CRenderFont.h"
#include "Framework\Renders\CRenderPrim.h"

#include "Framework\Menu\MenuManager.h"
#include "Framework\Menu\SVars.h"
#include "Framework\Menu\Textures.h"

#include "Framework\tools\ADE32.h"
#include "Framework\tools\CDetour.h"
#include "Framework\tools\crap.h"
#include "Framework\tools\xorgen.h"

#define ES	0
#define RST 1
#define DIP	2

#define HOOK(func,addy)	o##func = (t##func)DetourFunction((PBYTE)addy,(PBYTE)hk##func)

#define M_PI       3.14159265358979323846
