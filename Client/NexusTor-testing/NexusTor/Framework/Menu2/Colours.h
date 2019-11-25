#ifndef COLOURS_H
#define COLOURS_H

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#include <d3d9.h>
#include <Windows.h>
class Colour
{
public:
	static DWORD colRed;
	static DWORD colBlue;
	static DWORD colGreen;
	static DWORD colCyan;
	static DWORD colLightBlue;
	static DWORD colLightRed;
	static DWORD colLightGreen;
	static DWORD colDarkBlue;
	static DWORD colDarkRed;
	static DWORD colDarkGreen;
	static DWORD colOrange;
	static DWORD colPurple;
	static DWORD colYellow;
	static DWORD colWhite;
	static DWORD colBlack;
	static DWORD colGray;
	DWORD CustomColor ( int Alpha, int Red, int Green, int Blue );
	DWORD RandomColor ( bool bChangingAlpha );
};
extern Colour cCol;

#endif
