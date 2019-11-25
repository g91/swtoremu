// ==========================================================
// Nexus - ToR Project
// 
// Author: NoFaTe
// ==========================================================
#pragma once

#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
	static DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] );
	static unsigned int oneAtATimeHash( const char* inpStr );
	static DWORD OffsetToCode( HANDLE hHandle );
	static DWORD GetSizeOfCode( HANDLE hHandle );
	static void AllocateConsole(const char* pTitle);
	static void add_log( const char *fmt, ... );
	static void http(char* post_to, static TCHAR frmdata[]);
};

#endif