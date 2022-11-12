/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

/*
	Problem: unordered_map can't be compiled with Android NDK.
	map can be compiled.
*/

#pragma once

#if IS_PLATFORM_WIN
#include <unordered_map>
#define prefered_unordered_map std::unordered_map
#else
#include <map>
#define prefered_unordered_map std::map
#endif