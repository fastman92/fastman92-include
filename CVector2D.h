/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "Endianness\Endianness.h"

template <template<class> class Wrapper> class CVector2D_template
{
public:
	Wrapper<float> x;
	Wrapper<float> y;
};

DEFINE_ENDIAN_STRUCTURE_DEFAULT(CVector2D);