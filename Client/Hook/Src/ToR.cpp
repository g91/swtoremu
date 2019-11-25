// ==========================================================
// Nexus - ToR Project
// 
// Usage: Rename 'MemoryMan.dll' (located in the SWToR
//   directory) to 'Nexus.dll', build this project and place
//   the built 'MemoryMan.dll' in your SWToR directory
//
// Notes: Should work with any version of the game
//   No need for manual patching
//
// Author: NoFaTe
// ==========================================================

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdint.h>
#include "StdAfx.h"
#include "acpdump2.h"
#include "ToR.h"

#pragma comment(lib, "ws2_32.lib")

typedef wchar_t* (__stdcall * getValByName_t)(char* name);
getValByName_t getValByName = (getValByName_t)0x00;

//--------------------------------------------------------------------------------
int (__stdcall* RSAFunc_r)(int a2, int pRSAKey, int a4);

int __stdcall RSAFunc(int a2, int pRSAKey, int a4)
{
	__asm pushad

	Log::Write("RSAHook", "Called");

	unsigned char rawData[292] = {
		0x30, 0x82, 0x01, 0x20, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86,
		0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0D, 0x00,
		0x30, 0x82, 0x01, 0x08, 0x02, 0x82, 0x01, 0x01, 0x00, 0xB2, 0x3B, 0x14,
		0xD0, 0x60, 0xC3, 0x0D, 0xDB, 0x90, 0x53, 0x29, 0x94, 0xFD, 0x63, 0xF3,
		0x57, 0x0D, 0x02, 0x55, 0x41, 0xCD, 0x08, 0x6A, 0x6F, 0xFF, 0x0D, 0x44,
		0xE5, 0x19, 0xA8, 0x04, 0xE6, 0x3C, 0x31, 0x28, 0x1C, 0x71, 0x74, 0x40,
		0xAD, 0x7B, 0xAB, 0x8F, 0xE3, 0x3E, 0x06, 0xF7, 0xBD, 0x10, 0xF5, 0x3D,
		0x8E, 0x0F, 0xA9, 0x00, 0xB8, 0xB6, 0xA0, 0x8F, 0xE4, 0xCB, 0xE4, 0x13,
		0x3D, 0x84, 0xBC, 0xE9, 0x19, 0x91, 0x6E, 0xCE, 0x58, 0x84, 0x50, 0xDC,
		0x79, 0x15, 0xD3, 0x16, 0xEE, 0x6B, 0x36, 0xEC, 0xDF, 0x81, 0x1E, 0x8F,
		0x03, 0x9B, 0x20, 0xB1, 0x8E, 0x56, 0x4E, 0x51, 0x66, 0xED, 0xC7, 0xFC,
		0x7E, 0x03, 0xC4, 0xCC, 0xD2, 0xCD, 0x31, 0x1C, 0xAC, 0x1C, 0x17, 0x3E,
		0xB3, 0xF6, 0x5F, 0xB8, 0xAA, 0x05, 0x5A, 0xAE, 0xB5, 0xB1, 0x50, 0x3E,
		0xE8, 0x90, 0x69, 0x1F, 0xBA, 0x84, 0x0E, 0xDB, 0x62, 0x58, 0x64, 0x4A,
		0x4B, 0x64, 0xE7, 0xB6, 0x5A, 0x2D, 0xA3, 0x6C, 0x8E, 0x6C, 0x26, 0x02,
		0xF6, 0x08, 0xF6, 0x7A, 0x03, 0x20, 0xC0, 0x68, 0x63, 0xB1, 0x19, 0xEF,
		0x18, 0x9A, 0x60, 0xB3, 0xDD, 0x89, 0x21, 0xF6, 0x9A, 0x01, 0x1E, 0x3D,
		0x51, 0x8F, 0x03, 0x0E, 0x5D, 0xD8, 0x96, 0x22, 0x06, 0x7C, 0x47, 0x21,
		0x66, 0xF1, 0x29, 0xBC, 0x28, 0x3E, 0x8D, 0xBE, 0xEE, 0x4B, 0x6B, 0x7D,
		0x57, 0xE1, 0x35, 0x18, 0x6A, 0x87, 0xB5, 0x1F, 0xCC, 0x17, 0xAE, 0xC7,
		0x46, 0x73, 0x79, 0x6E, 0xF8, 0xA6, 0xD9, 0xE5, 0x98, 0x52, 0xE9, 0xE6,
		0x1D, 0x8A, 0x6D, 0x0E, 0xEE, 0xBC, 0x6B, 0x93, 0xF5, 0xF8, 0x7F, 0x7D,
		0x30, 0x69, 0xB6, 0x21, 0x50, 0x3D, 0xA1, 0x27, 0x72, 0x99, 0xC8, 0x22,
		0x00, 0x51, 0xB5, 0x95, 0xB9, 0x41, 0x20, 0x7E, 0xFA, 0x93, 0x55, 0x3A,
		0x31, 0x02, 0x01, 0x11
	};

	memcpy((unsigned char *)pRSAKey, rawData, 0x124);

	__asm popad

	return RSAFunc_r(a2, pRSAKey, a4);
}
//--------------------------------------------------------------------------------
int (__cdecl* SSL_CTX_set_verify_r)(int ctx, int mode, int cb);

int __cdecl SSL_CTX_set_verify(int ctx, int mode, int cb)
{
	// Accept any SSL Certificate
	if (mode == 1)
		mode = 0;

	return SSL_CTX_set_verify_r(ctx, mode, cb);
}
//--------------------------------------------------------------------------------

char (__stdcall* GenRSAHandshake_r)(int a1, int a2, char *uUsername, char *uPassword);

char __stdcall GenRSAHandshake_stub(int a1, int a2, char *uUsername, char *uPassword)
{
	
	return GenRSAHandshake_r(a1, a2, uUsername, uPassword);
}

char __stdcall GenRSAHandshake(int a1, int a2, char *uUsername, char *uPassword)
{
	__asm pushad

	Log::Write("PassHook", "Called; Username: %s | Password: %s", (const char*)uUsername, (const char*)uPassword);

	__asm popad
	/*__asm
	{
		push ebp
		mov ebp, esp
		push dword ptr[ebp + 0x0C] // uPassword
		push dword ptr[ebp + 0x08] // uUsername
		//push uPassword
		//push uUsername
		push ecx // a2
		push eax // a1
		call GenRSAHandshake_stub
		
		mov esp, ebp
		pop ebp

		retn 8//n 8
	}*/

	return GenRSAHandshake_r(a1, a2, uUsername, uPassword);
}

//--------------------------------------------------------------------------------
typedef int (WSAAPI *getaddrinfo_t)(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, PADDRINFOA *ppResult);
getaddrinfo_t getaddrinfo_r = (getaddrinfo_t)getaddrinfo;

char* serverName = NULL;
char* webName = NULL;

int WSAAPI getaddrinfo_c(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, PADDRINFOA *ppResult) 
{
	Log::Write("WS2_32", "GetAddrInfo (%s)", (char*)pNodeName);

	/*unsigned int RandomHost = Utils::oneAtATimeHash("something.com");

	unsigned int current = Utils::oneAtATimeHash((char*)name);

	if (current == RandomHost) 
	{
		serverName = "localhost";
		hostname = serverName;

		Log::Write("WS2_32", "Redirecting to '%s'", serverName);
	}*/

	return getaddrinfo_r(pNodeName, pServiceName, pHints, ppResult);
}


typedef int (WINAPI *recv_t)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
recv_t recv_r = (recv_t)WSARecv;

int WINAPI recv_c(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	_asm pushad;

	if( lpBuffers && lpBuffers->buf && lpBuffers->len > 0 )
	{
		sockaddr_in addr;
		int len = sizeof(sockaddr_in);
		getpeername(s, (sockaddr*)&addr, &len);

		Log::Write("MainHook", "WSARecv Called [%s:%d]", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	}
	
	_asm popad;

	return recv_r(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
}

//--------------------------------------------------------------------------------

typedef int (WINAPI *send_t)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
send_t send_r = (send_t)WSASend;

int WINAPI send_c(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	sockaddr_in addr;
	int len = sizeof(sockaddr_in);
	getpeername(s, (sockaddr*)&addr, &len);

	Log::Write("MainHook", "WSASend Called [%s:%d]", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	return send_r(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

//--------------------------------------------------------------------------------

typedef int (WINAPI *sendTo_t)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
sendTo_t sendTo_r = (sendTo_t)WSASendTo;

int WINAPI sendTo_c(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	Log::Write("MainHook", "WSASendTo Called [%s:%d]", inet_ntoa(((sockaddr_in*)lpTo)->sin_addr), ntohs(((sockaddr_in*)lpTo)->sin_port));
	return sendTo_r(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine);
}

//--------------------------------------------------------------------------------

typedef int (WINAPI *recvFrom_t)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr *lpFrom, LPINT lpFromlen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
recvFrom_t recvFrom_r = (recvFrom_t)WSARecvFrom;

int WINAPI recvFrom_c(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr *lpFrom, LPINT lpFromlen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	Log::Write("MainHook", "WSARecvFrom Called [%s:%d]", inet_ntoa(((sockaddr_in*)lpFrom)->sin_addr), ntohs(((sockaddr_in*)lpFrom)->sin_port));
	return recvFrom_r(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine);
}

//--------------------------------------------------------------------------------

ToR* ToR::gInstance = NULL;

ToR* ToR::GetInstance()
{
	if(gInstance == NULL)
		gInstance = new ToR;
	return gInstance;
}

void ToR::InitHooks()
{
	// Hook GetHostByName - just in case
	PBYTE offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "getaddrinfo");
	getaddrinfo_r = (getaddrinfo_t)DetourFunction(offset, (PBYTE)&getaddrinfo_c);

	// Send/Recv Hooks
	offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "WSARecv");
	recv_r = (recv_t)DetourFunction(offset, (PBYTE)&recv_c);

	offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "WSASend");
	send_r = (send_t)DetourFunction(offset, (PBYTE)&send_c);
	
	// These two are rarely used but whatever
	offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "WSASendTo");
	sendTo_r = (sendTo_t)DetourFunction(offset, (PBYTE)&sendTo_c);

	offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "WSARecvFrom");
	recvFrom_r = (recvFrom_t)DetourFunction(offset, (PBYTE)&recvFrom_c);
	
	// Password setting hook
	// char __userpurge Generate_RSA_Handshake<al>(int a1<eax>, int a2<ecx>, char *uUsername, char *uPassword)
	//DWORD GenRSAHandshake_addr = Utils::FindPattern(dwEntryPoint, dwCodeSize, (BYTE*)"\x55\x8B\xEC\x64\xA1\x00\x00\x00\x00\x6A\xFF\x00\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x81\xEC\x70\x08\x00\x00\x53\x56", "xxxxxxxxxxx?????xxxxxxxxxxxxxxxx");
	//GenRSAHandshake_r = (char (__stdcall*)(int a1, int a2, char *uUsername, char *uPassword))DetourFunction((PBYTE)GenRSAHandshake_addr, (PBYTE)GenRSAHandshake);

	// RSA/SSL Hooks
	DWORD RSAFuncAddr = Utils::FindPattern(dwEntryPoint, dwCodeSize, (BYTE*)"\x50\x64\x89\x25\x00\x00\x00\x00\x51\x53\x56\x8B\xF1\x8B\x46\x5C", "xxxxxxxxxxxxxxxx");
	RSAFuncAddr -= 16;
	//RSAFunc_r = (int (__stdcall*)(int a2, int pRSAKey, int a4))DetourFunction((PBYTE)RSAFuncAddr, (PBYTE)RSAFunc);

	DWORD SSL_CTX_set_verify_addr = Utils::FindPattern(dwEntryPoint, dwCodeSize, (BYTE*)"\x8B\x44\x24\x04\x8B\x4C\x24\x08\x8B\x54\x24\x0C\x89\x88\xC0\x00", "xxxxxxxxxxxxxxxx");
	SSL_CTX_set_verify_r = (int (__cdecl*)(int ctx, int mode, int cb))DetourFunction((PBYTE)SSL_CTX_set_verify_addr, (PBYTE)SSL_CTX_set_verify);

	Log::Write("NexusToR", "Hooked Send/SendTo and Recv/RecvFrom functions");

	Log::Write("NexusToR", "Hooked RSA Key certification and SSL Validation");
}

ToR::ToR()
{
	// Initialize the Logging module
	Log::Init();

	HANDLE hModule = GetModuleHandle(NULL);

	dwCodeSize = Utils::GetSizeOfCode( hModule );
	dwCodeOffset = Utils::OffsetToCode( hModule );
	dwEntryPoint = (DWORD)hModule + dwCodeOffset;

	// Allocate a console for game output
	Utils::AllocateConsole("Star Wars: The Old Republic");
	Log::Write("NexusToR", "Initializing NexusToR Client");

	// Initialize our Hooks
	InitHooks();
}
