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
		class CModelAccessory : public CModel3commonElements 
		{
		public:
			// Constructor
			CModelAccessory() : CModel3commonElements(SECTION_IDE_ACCS) { this->InitValues(); }

			// Clone
			virtual CModelAccessory* clone() const { return new CModelAccessory(*this); };
		};
	}
}