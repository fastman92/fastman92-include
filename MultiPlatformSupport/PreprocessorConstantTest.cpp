/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#if !defined(IS_PLATFORM_WIN) && !defined(IS_PLATFORM_ANDROID) && !defined(IS_PLATFORM_LINUX)
#error Preprocessor definition for fastman92 stuff missing.
#elif !defined(IS_PLATFORM_WIN_ARM32) && !defined(IS_PLATFORM_WIN_ARM64) && !defined(IS_PLATFORM_WIN_X86) && !defined(IS_PLATFORM_WIN_X64) && !defined(IS_PLATFORM_ANDROID_ARM32) && !defined(IS_PLATFORM_ANDROID_ARM64) && !defined(IS_PLATFORM_ANDROID_X86) && !defined(IS_PLATFORM_ANDROID_X64)
#error Preprocessor definition for fastman92 stuff missing.
#elif !defined(IS_ARCHITECTURE_X86) && !defined(IS_ARCHITECTURE_X64) && !defined(IS_ARCHITECTURE_ARM32) && !defined(IS_ARCHITECTURE_ARM64)
#error Preprocessor definition for fastman92 stuff missing.
#elif !defined(IS_ARCHITECTURE_32_BIT) && !defined(IS_ARCHITECTURE_64_BIT)
#error Preprocessor definition for fastman92 stuff missing.
#endif