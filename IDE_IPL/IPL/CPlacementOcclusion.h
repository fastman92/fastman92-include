/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"

namespace File
{
	namespace IPL
	{
		class CPlacementOcclusion : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			float MidX;
			float MidY;
			float BottomZ;
			float WidthX;
			float WidthY;
			float Height;
			CVector Rot;
			bool UnknownParam10inBullyScholarschip;

			// FUNCTIONS

			// Constructor
			CPlacementOcclusion() : CPlacementBaseInfo(SECTION_IPL_OCCL) { this->InitValues(); }

			// Clone
			virtual CPlacementOcclusion* clone() const { return new CPlacementOcclusion(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CPlacementOcclusion* ToPlacementOcclusion()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementOcclusion* ToPlacementOcclusion() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}