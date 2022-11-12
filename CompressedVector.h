/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <Assertions.h>
#include <Endianness\Endianness.h>

#include <stdint.h>


template<template<class> class Wrapper, typename T> class CompressedVector2D_templateForSingleType
{
public:
	Wrapper<T> x;
	Wrapper<T> y;
};

template<template<class> class Wrapper, typename T> class CompressedVector_templateForSingleType
{
public:
	Wrapper<T> x;
	Wrapper<T> y;
	Wrapper<T> z;
};

template <template<class> class Wrapper>
using CompressedVector2D_template = CompressedVector2D_templateForSingleType<Wrapper, int16_t>;

template <template<class> class Wrapper>
using CompressedVector2D_extended_template = CompressedVector2D_templateForSingleType<Wrapper, int32_t>;

template <template<class> class Wrapper>
using CompressedVector_template = CompressedVector_templateForSingleType<Wrapper, int16_t>;

template <template<class> class Wrapper>
using CompressedVector_extended_template = CompressedVector_templateForSingleType<Wrapper, int32_t>;

DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedVector2D);
DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedVector2D_extended);
DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedVector_extended);
DEFINE_ENDIAN_STRUCTURE_DEFAULT(CompressedVector);