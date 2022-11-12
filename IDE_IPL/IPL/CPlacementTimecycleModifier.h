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
		class CPlacementTimecycleModifier : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			CBox Box;
			float UnknownParam7inGTAIV;
			float UnknownParam8inGTAIV;
			int UnknownParam9inGTAIV;
			int UnknownParam10inGTAIV;
			CHashStrPair ModifierName;

			// FUNCTIONS

			// Constructor
			CPlacementTimecycleModifier() : CPlacementBaseInfo(SECTION_IPL_TCYC) { this->InitValues(); }

			// Clone
			virtual CPlacementTimecycleModifier* clone() const { return new CPlacementTimecycleModifier(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Executes a function for each other string hash pair
			virtual void ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData);

			// Types
			virtual const CPlacementTimecycleModifier* ToPlacementTimecycleModifier()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementTimecycleModifier* ToPlacementTimecycleModifier() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}