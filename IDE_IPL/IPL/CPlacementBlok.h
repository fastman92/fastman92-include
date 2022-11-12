/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementBaseInfo.h"
#include "../../CVector2D.h"

namespace File
{
	namespace IPL
	{
		class CPlacementBlok : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			std::string BlockName;
			std::string Author;
			std::string DateTime;
			int UnknownParam4inGTAIV;	// flags? type?
			int UnknownParam5inGTAIV;
			std::string UnknownParam6inGTAIV;	// seems to be always "unknown" in all entries

			CVector2D CornerPoints[4];

			// FUNCTIONS

			// Constructor
			CPlacementBlok() : CPlacementBaseInfo(SECTION_IPL_BLOK) { this->InitValues(); }

			// Clone
			virtual CPlacementBlok* clone() const { return new CPlacementBlok(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 2D world position vectors
			virtual void Foreach2DworldPositions(tHashVector2DFunc func, void* pUserData);

			// Types
			virtual const CPlacementBlok* ToPlacementBlok()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementBlok* ToPlacementBlok() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}