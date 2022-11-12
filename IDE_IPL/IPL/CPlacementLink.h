/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementBaseInfo.h"
#include "../../CBox.h"

namespace File
{
	namespace IPL
	{
		class CPlacementLink : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			int UnknownParam1inGTAIV;
			int UnknownParam2inGTAIV;
			float UnknownParam3inGTAIV;
			int UnknownParam4inGTAIV;
			int UnknownParam5inGTAIV;
			unsigned __int32 Flags;

			// FUNCTIONS

			// Constructor
			CPlacementLink() : CPlacementBaseInfo(SECTION_IPL_LINK) { this->InitValues(); }

			// Clone
			virtual CPlacementLink* clone() const { return new CPlacementLink(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CPlacementLink* ToPlacementLink()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementLink* ToPlacementLink() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}