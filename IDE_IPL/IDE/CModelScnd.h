/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModel3commonElements.h"
#include <string>

namespace File
{
	namespace IDE
	{
		class CModelScnd : public CModel3commonElements 
		{
		public:
			// Constructor
			CModelScnd() : CModel3commonElements(SECTION_IDE_SCND) { this->InitValues(); }

			// Clone
			virtual CModelScnd* clone() const { return new CModelScnd(*this); };
		};
	}
}