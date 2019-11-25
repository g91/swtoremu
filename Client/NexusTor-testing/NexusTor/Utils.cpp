// ==========================================================
// Nexus - ToR Project
// 
// Author: NoFaTe
// ==========================================================

#include "StdAfx.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <winbase.h>
#include "wininet.h"

using namespace std;
ofstream ofile;

#define LOG_FILE "SWTOR_LOG.txt"

void Utils::AllocateConsole(const char* pTitle)
{
	// Allocate Console Window
	AllocConsole() ;
	AttachConsole( GetCurrentProcessId() );
	freopen( "CON", "w", stdout ) ;
	SetConsoleTitle( pTitle );

	// Resize console (max length)
	COORD cordinates = {80, 32766};
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, cordinates);
}

void Utils::http(char* post_to, static TCHAR frmdata[])
{
	static TCHAR hdrs[] = "Content-Type: application/x-www-form-urlencoded";

	HINTERNET hSession = InternetOpen("MyAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnect(hSession, "emulatornexus.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL,INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", post_to, NULL, NULL, (LPCSTR*)"*/*", 0, 1);
	HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(frmdata));
}

unsigned int Utils::oneAtATimeHash(const char *inpStr)
{
	unsigned int value = 0, temp = 0;
	for(size_t i = 0; inpStr[i] != 0; ++i)
	{
		char ctext = tolower(inpStr[i]);
		temp = ctext + value;
		value = temp << 10;
		temp = temp + value;
		value = temp >> 6;
		value = value ^ temp;
	}
	temp = value << 3;
	temp = temp + value;
	unsigned int temp2 = temp >> 11;
	temp = temp2 ^ temp;
	temp2 = temp << 15;
	value = temp2 + temp;
	if(value < 2)
		return value + 2;
	return value;
}

DWORD Utils::FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] )
{
	unsigned int i = NULL;
	int iLen = strlen( pszMask ) - 1;

	for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ )
	{
		if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' )
		{
			if( pszMask[i+1] == '\0' )
				return( dwRet - iLen );
			i++;
		} 
		else 
			i = NULL;
	}
	return NULL;
}

DWORD Utils::GetSizeOfCode( HANDLE hHandle )
{
	HMODULE hModule = (HMODULE)hHandle;

	if ( !hModule )
		return NULL;

	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule );

	if( !pDosHeader )
		return NULL;

	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew );

	if( !pNTHeader )
		return NULL;

	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader;

	if( !pOptionalHeader )
		return NULL;

	return pOptionalHeader->SizeOfCode;
}

DWORD Utils::OffsetToCode( HANDLE hHandle )
{
	HMODULE hModule = (HMODULE)hHandle;

	if ( !hModule )
		return NULL;

	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule );

	if( !pDosHeader )
		return NULL;

	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew );

	if( !pNTHeader )
		return NULL;

	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader;

	if( !pOptionalHeader )
		return NULL;

	return pOptionalHeader->BaseOfCode;
}

void Utils::add_log( const char *fmt, ... )
{
	ofile.open( LOG_FILE, ios::app );

	va_list va_alist;
	char logbuf[256] = {0};

	va_start( va_alist, fmt );
	vsnprintf( logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist );
	va_end( va_alist );

	ofile << logbuf << endl;

	ofile.close();
}