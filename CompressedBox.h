/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CompressedVector.h"

template<template<class> class Wrapper, typename T> class CompressedBox2D_templateForSingleType
{
public:
	CompressedVector2D_templateForSingleType<Wrapper, T> m_vInf;
	CompressedVector2D_templateForSingleType<Wrapper, T> m_vSup;
};

template<template<class> class Wrapper, typename T> class CompressedBox_templateForSingleType
{
public:
	CompressedVector_templateForSingleType<Wrapper, T> m_vInf;
	CompressedVector_templateForSingleType<Wrapper, T> m_vSup;
};

template <template<class> class Wrapper>
using CompressedBox2D_template = CompressedBox2D_templateForSingleType<Wrapper, int16_t>;

template <template<class> class Wrapper>
using CompressedBox2D_extended_template = CompressedBox2D_templateForSingleType<Wrapper, int32_t>;

template <template<class> class Wrapper>
using CompressedBox_template = CompressedBox_templateForSingleType<Wrapper, int16_t>;

template <template<class> class Wrapper>
using CompressedBox_extended_template = CompressedBox_templateForSingleType<Wrapper, int32_t>;

DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedBox2D);
DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedBox2D_extended);
DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedBox_extended);
DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedBox);