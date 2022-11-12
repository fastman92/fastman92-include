/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include <stdlib.h>

#ifndef VALIDATE_SIZE
#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#endif

#define VALIDATE_SIZE_ONLY_IF_POINTER_SIZE_EQUAL( \
pointerSize, struc, size \
) static_assert(pointerSize != sizeof(void*) || sizeof(struc) == size, "Invalid structure size of " #struc)

#define VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(struc, size) VALIDATE_SIZE_ONLY_IF_POINTER_SIZE_EQUAL(4, struc, size)
#define VALIDATE_SIZE_ONLY_ON_64_BIT_ARCHITECTURE(struc, size) VALIDATE_SIZE_ONLY_IF_POINTER_SIZE_EQUAL(8, struc, size)

#ifndef VALIDATE_ARRAY_COUNTOF
#define VALIDATE_ARRAY_COUNTOF(arrayVar, count) static_assert(_countof(arrayVar) == count, "Invalid array count of " #arrayVar)
#endif
