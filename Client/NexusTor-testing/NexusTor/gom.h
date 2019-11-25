#ifndef _gom_h_
#define _gom_h_

//Forward Declare
class GOM;
class Prototype;
class HeroNode;
class HeroClass;
//Prototypes
typedef GOM* (*getGom)(GOM* pGom);
typedef int (__stdcall * tlookupPrototypeName)(void *This, eastl::wstring *protoType, LARGE_INTEGER Val);
typedef int (__stdcall * twhatIs)(void *This,LARGE_INTEGER  Val, eastl::string*ret, eastl::string* str1, eastl::string*  str2);
typedef HeroNode* ( __stdcall * tGetNodeById)(int idLowPart, int idHighPart,int trace );
typedef signed int (__stdcall * tgetPropertyFromNode )(void *This, LARGE_INTEGER Val, wchar_t **a3, eastl::wstring *Out );
typedef int *( __stdcall * tGetClassTotalFields)( int *a3 ,int *ret);

enum HeroTypes
{
	None = 0,
	Id = 1,
	Integer = 2,
	Boolean = 3,
	Enum = 5,
	Float = 4,
	String = 6,
	List = 7,
	LookupList = 8,
	Class = 9,
	Association = 10,
	ScriptRef = 14,
	NodeRef = 15,
	GuiControl = 16,
	Timer = 17,
	Vector3 = 18,
	Guid = 19,
	Timeinterval = 20,
	Date = 21,
	Rawdata = 22
};

class DefinitionId
{
public:
	LARGE_INTEGER ID;
protected:
private:
};
class HeroType
{
public:
	DefinitionId Id;
	HeroType *indexer;
	HeroTypes Type;
	HeroType *values;
protected:
private:
};

class HeroAnyValue
{
public:
	bool hasValue;
	LARGE_INTEGER ID;
protected:
private:
};
class HeroFloat : public HeroAnyValue
{
public:
protected:
private:
};


class HeroClass
{
public:
	virtual void function0();
protected:
private:
};


class HeroNode
{
public:
	virtual void funct0();
	char pading_0[0x0C-0x4];
	WORD m_nodeType;
	char pading_1[0x48-0xE];
	HeroClass * m_heroClass;
	int GetNodeType()
	{
		return (m_nodeType >> 3) &  15;
	}
protected:
private:
};//allocated size 0x58

class Prototype
{
public:
	GOM *m_gom;
	HeroNode * m_node;
	//LARGE_INTEGER m_nodeId;
	//eastl::wstring m_prototypeName;
protected:
private:
};

struct HashTable 
{
	int curentSize;
	void** table;
	int maxSixe;
};

class GOM 
{
public:
	static GOM* GetGOM(GOM* pGom = NULL);
	virtual Prototype* GetPrototypeById(unsigned int Id1, unsigned int id2 ,int trace);
	virtual int	lookupPrototypeId( DWORD* ReturnId, eastl::wstring *protoType, int trace);
	int lookupPrototypeName(eastl::wstring *protoType, LARGE_INTEGER Val);
	HeroNode*  GetNodeById(LARGE_INTEGER val, int trace = 0);
	signed int  getPropertyFromNode(LARGE_INTEGER Val, eastl::wstring *, eastl::wstring *Out); //0x000AB170
	int whatIs(void *This,LARGE_INTEGER Val, eastl::string* ret, eastl::string* str1, eastl::string* str2);
	int  GetEnumDefs( void* defs );
	int  *GetClassTotalFields(LARGE_INTEGER * Val, int *ret);//4A7B10
	char _0x0000[1484];
	__int32 tableSize; //0x05D0 
	char _0x05D4[4];
	void** defTable; //0x05D8 
	char _0x05DC[76];
	HashTable hashTable;
protected:
private:
};

#endif