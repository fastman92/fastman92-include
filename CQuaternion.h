/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "CVector.h"

template <template<class> class Wrapper> class CQuaternion_template
{
public:
	CVector_template<Wrapper> imag;
	Wrapper<float> real;
};

DEFINE_ENDIAN_STRUCTURE_DEFAULT(CQuaternion);

VALIDATE_SIZE(CQuaternion, 0x10);