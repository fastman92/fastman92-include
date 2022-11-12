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
		class CModelItem : public CModel3commonElements 
		{
		public:
			// Constructor
			CModelItem() : CModel3commonElements(SECTION_ITEM) {}

			// Clone
			virtual CModelItem* clone() const { return new CModelItem(*this); };
		};
	}
}