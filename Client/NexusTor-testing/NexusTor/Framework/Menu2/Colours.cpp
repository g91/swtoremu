#include "Colours.h"

Colour cCol;

DWORD Colour::CustomColor ( int Alpha, int Red, int Green, int Blue )
{
	return D3DCOLOR_ARGB( Alpha, Red, Green, Blue );
}
DWORD Colour::RandomColor ( bool bChangingAlpha = false )
{
	DWORD dwReturningColor = NULL;
	int Red = rand() % 255;
	int Green = rand() % 255;
	int Blue = rand() % 255;
	int Alpha = rand() % 255;
	if( !bChangingAlpha )
		dwReturningColor = D3DCOLOR_XRGB( Red, Green, Blue );
	else 
		dwReturningColor = D3DCOLOR_ARGB( Alpha, Red, Green, Blue );

	return dwReturningColor;
}
DWORD Colour::colBlack		= D3DCOLOR_XRGB( 0,0,0		);
DWORD Colour::colBlue		= D3DCOLOR_XRGB(0,0,255		);
DWORD Colour::colCyan		= D3DCOLOR_XRGB(23,187,183	);
DWORD Colour::colGray		= D3DCOLOR_XRGB(192,192,192	);
DWORD Colour::colGreen		= D3DCOLOR_XRGB(0,255,0		);
DWORD Colour::colLightBlue  = D3DCOLOR_XRGB(36,239,255	);
DWORD Colour::colLightGreen = D3DCOLOR_XRGB(150,255,100	);
DWORD Colour::colLightRed	= D3DCOLOR_XRGB(236,83,87	);
DWORD Colour::colOrange		= D3DCOLOR_XRGB(255,128,0	);
DWORD Colour::colPurple		= D3DCOLOR_XRGB(128,0,128	);
DWORD Colour::colRed		= D3DCOLOR_XRGB(255,0,0		);
DWORD Colour::colWhite		= D3DCOLOR_XRGB(255,255,255	);
DWORD Colour::colYellow		= D3DCOLOR_XRGB(255,255,0	);
DWORD Colour::colDarkBlue	= D3DCOLOR_XRGB(9,0,119		);
DWORD Colour::colDarkGreen  = D3DCOLOR_XRGB(27,119,0	);
DWORD Colour::colDarkRed	= D3DCOLOR_XRGB(119,0,0		);