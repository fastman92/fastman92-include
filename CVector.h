/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "Endianness\Endianness.h"

template <template<class> class Wrapper> class CVector_template
{
public:
	Wrapper<float> x;
	Wrapper<float> y;
	Wrapper<float> z;
};

DEFINE_ENDIAN_STRUCTURE_DEFAULT(CVector);