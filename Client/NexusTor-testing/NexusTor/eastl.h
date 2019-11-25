#ifndef __EASTL_HEADER__
#define __EASTL_HEADER__
//#define EA_DLL
#define EASTL_NAME_ENABLED 0
#define EASTL_ASSERT_ENABLED 0
#define EA_PLATFORM_MICROSOFT 1
#define FB_MEMORYARENA_ENABLED 1
//#define CHAR8_T_DEFINED

#include <EASTL/allocator.h>
#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/list.h>
#include <EASTL/fixed_list.h>
#include <EASTL/set.h>
#include <EASTL/fixed_set.h>
#include <EASTL/map.h>
#include <EASTL/hash_map.h>
#include <EASTL/hash_set.h>
#include <EASTL/string.h>

namespace eastl
{

	template< typename T > class vector_map
	{
	public:
		unsigned char                    _padding[0x14];
	protected:
	private:
	};

	class SimpelVectorRoot
	{
	public:
	};

	template< typename T > class SimpelVectorBase : public SimpelVectorRoot
	{
	public:
		T*	mpBegin;
		T*	mpEnd;
	};
	template< typename T > class SimpelVector : public SimpelVectorBase<T>
	{
	public:
		//allocator mAllocator;
	};
	template< typename T > class basic_array 
	{
	public:
		T * mpBegin;
	};
};

#endif