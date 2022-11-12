#pragma once

#if defined _M_X64 || defined _M_ARM || defined _M_ARM64
#define _UNALIGNED __unaligned
#else
#define _UNALIGNED
#endif

#ifdef __cplusplus
extern "C++"
{
	template <typename _CountofType, size_t _SizeOfArray>
	char(*__countof_helper(_UNALIGNED _CountofType(&_Array)[_SizeOfArray]))[_SizeOfArray]
	{
		return _Array;
	}

#define __crt_countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
}
#else
#define __crt_countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifndef _countof
#define _countof __crt_countof
#endif