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
		class CModelCloth : public CModel3commonElements 
		{
		public:
			// Constructor
			CModelCloth() : CModel3commonElements(SECTION_IDE_ITEM) { this->InitValues(); }

			// Clone
			virtual CModelCloth* clone() const { return new CModelCloth(*this); };
		};
	}
}