//#include "stdafx.h"
//#include "ToR.h"
//#include "gom.h"
//
//tlookupPrototypeName plookupPrototypeName			= NULL;
//tlookupPrototypeName plookupPrototypeName_detour	= NULL;
//twhatIs pwhatIs										= NULL;
//tGetNodeById pGetNodeById							= NULL;
//getGom pGetgom										= NULL;
//tgetPropertyFromNode  pgetPropertyFromNode			= NULL;  
//tGetClassTotalFields pGetClassTotalFields			= NULL;
//
//int __stdcall GetNodeById_Detour(DWORD a1, DWORD a2,bool a3);
//typedef int (__stdcall *tGetNodeById_Detour)(DWORD a1, DWORD a2,bool a3);
//tGetNodeById_Detour pGetNodeById_Detour;
//
//ToR* tor;
//
//GOM* GOM::GetGOM(GOM* pGom/* = NULL*/)
//{
//	if (pGetgom == NULL)
//	{
//		pGetgom = (getGom)((DWORD)Utils::FindPattern(tor->dwEntryPoint, tor->dwCodeSize, (BYTE*)"\x83\xEC\x58\x56\x33\xF6\x3B\xC6\x75\x41", "xxxxxxxxxx")- 0x20);
//	}
//	return pGetgom(pGom);
//
//}
//
//#pragma region Detours 
//
//int __stdcall GetNodeById_Detour(DWORD a1, DWORD a2,bool a3)
//{
//
//	_asm pushad
//	//CUseFull::add_log("---------------------\na1: 0x%08X\na2: 0x%08X\na3: 0x%08X" , a1,a2,a3);
//	_asm popad
//	return pGetNodeById_Detour(a1,a2,a3);
//}
//
//
//
//#pragma endregion Detours
//
//
//int GOM::lookupPrototypeName( eastl::wstring *protoType, LARGE_INTEGER Val )
//{
//	
//	
//	if (plookupPrototypeName == NULL)
//	{
//		//static DWORD dw = ((DWORD)CUseFull::g_hMainModule)+0x000A5630;
//		//DWORD moduleBase = CUseFull::GetTextBase(CUseFull::g_hMainModule);
//		//DWORD moduleSize = CUseFull::GetTextSize(CUseFull::g_hMainModule);
//		//plookupPrototypeName = (tlookupPrototypeName)((DWORD)CUseFull::FindPattern(moduleBase,moduleSize,(CHAR*)"\x83\xEC\x28\x53\x56\x57\x89\x65\xF0\x8B\x75\x08\x8D\x8E\xC0\x04\x00\x00\x8B\x01\x3B\x41\x04",(CHAR*)"xxxxxxxxxxxxxxxxxxxxxxx") - 0x20);
//		//CUseFull::add_log("0x%08X",plookupPrototypeName);
//		//plookupPrototypeName = (tlookupPrototypeName)dw;
//	}
//	return plookupPrototypeName(this,protoType,Val);
//}
//
//
//
//
//int GOM::whatIs(void *This,LARGE_INTEGER Val, eastl::string*ret, eastl::string* str1, eastl::string* str2)
//{
//	//static DWORD dw = ((DWORD)CUseFull::g_hMainModule)+0x001B35A0;
//	//pwhatIs = (twhatIs)dw;
//
//	//__asm int 3
//	//int i = 
//	return pwhatIs(This,Val,ret,str1,str2);
//}
//
//HeroNode*  GOM::GetNodeById( LARGE_INTEGER val, int trace /*= 0*/ )
//{
//
//	if (pGetNodeById == NULL)
//	{
//		pGetNodeById = (tGetNodeById)((DWORD)Utils::FindPattern(tor->dwEntryPoint, tor->dwCodeSize, (BYTE*)"\x55\x8B\xEC\x83\xE4\xF8\x8B\x45\x10\x8B\x55\x0C\x50\x8B\x45\x08\x52\x50", "xxxxxxxxxxxxxxxxxx"));
//		//CUseFull::add_log("pGetNodeById: 0x%08X",pGetNodeById);
//	}
//	int id1 = val.LowPart;
//	int id2 = val.HighPart;
//	__asm mov ecx, this
//	return pGetNodeById(id1,id2,trace);
//}
//
////signed int  GOM::getPropertyFromNode( LARGE_INTEGER Val, eastl::wstring * In, eastl::wstring *Out )
////{
////	//static DWORD dw = ((DWORD)CUseFull::g_hMainModule)+0x000AB300;
////	//pgetPropertyFromNode = (tgetPropertyFromNode)dw;
////	//wchar_t * Property = new wchar_t[wcslen(In->c_str())+1];
////	//wcscpy(Property,In->c_str());
////	signed int ret = pgetPropertyFromNode(this,Val,&Property,Out);
////	delete []Property;
////	
////	return ret;
////}
//
//
//
//int *GOM::GetClassTotalFields( LARGE_INTEGER * Val,  int *ret )
//{
//	//static DWORD dw = ((DWORD)CUseFull::g_hMainModule)+0x000A7B10;
//
//	//pGetClassTotalFields = (tGetClassTotalFields)dw;
//	//__asm int 3;
//	__asm mov ecx,Val
//	return pGetClassTotalFields((int*)this,ret);
//}
