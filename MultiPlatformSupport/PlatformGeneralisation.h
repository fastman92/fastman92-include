/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once

// attribute used
#define USED __attribute__((used))

// target
#ifdef __clang__
#define TARGET_ARM __attribute__((target("no-thumb-mode")))
#define TARGET_THUMB  __attribute__((target("thumb-mode")))
#endif

// naked
#ifdef __GNUC__
#define NAKED __attribute__((naked))
#else
#define NAKED __declspec(naked)
#endif

// inline
#ifdef __GNUC__
	#define INLINE __attribute__((inline))
#else
	#define INLINE __inline
#endif

// force inline
#ifdef __GNUC__
	#define FORCEINLINE __attribute__((forceinline))
#else
	#define FORCEINLINE __forceinline
#endif

// no inline
#ifdef __GNUC__
#define NOINLINE __attribute__((noinline))
#else
	#define NOINLINE __declspec(noinline)
#endif

// dll export and dll local
#if defined _WIN32 || defined __CYGWIN__
	#ifdef __GNUC__
		#define DLL_EXPORT __attribute__ ((dllexport))
	#else
		#define DLL_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
	#endif

	#define DLL_LOCAL
#elif __GNUC__ >= 4
	#define DLL_EXPORT __attribute__ ((visibility ("default")))
	#define DLL_LOCAL __attribute__ ((visibility ("hidden")))
#endif

// dll import
#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
	#define DLL_IMPORT __attribute__ ((dllimport))
#else
	#define DLL_IMPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#elif __GNUC__ >= 4
	#define DLL_IMPORT
#endif

// functions
#ifdef __GNUC__
#define _stricmp strcasecmp
#define strtok_s strtok_r
#endif

// warnings
#ifdef __clang__
#pragma clang diagnostic ignored "-Wignored-attributes"
#endif

// pointer
#if IS_ARCHITECTURE_64_BIT
#define PRINTF_POINTER_HEX_STR_PAD "%016llX"
#define PRINTF_POINTER_HEX_STR "%llX"
#else
#define PRINTF_POINTER_HEX_STR_PAD "%08X"
#define PRINTF_POINTER_HEX_STR "%X"
#endif