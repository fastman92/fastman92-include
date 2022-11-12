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
		class CModelCash : public CModel3commonElements 
		{
		public:
			// Constructor
			CModelCash() : CModel3commonElements(SECTION_IDE_CASH) { this->InitValues(); }

			// Clone
			virtual CModelCash* clone() const { return new CModelCash(*this); };
		};
	}
}