/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CVector2D.h"

template <template<class> class Wrapper> class CBox2D_template
{
public:
	CVector2D_template<Wrapper> m_vInf;
	CVector2D_template<Wrapper> m_vSup;
};

DEFINE_ENDIAN_STRUCTURE_DEFAULT(CBox2D);