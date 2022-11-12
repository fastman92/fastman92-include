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
		class CPlacementLodm : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			CBox Box;
			unsigned int CountOfModels;
			unsigned int UnknownParamFlagPosition24inGTAIV;
			CHashStrPair ModelNameArray[10];

			// FUNCTIONS

			// Constructor
			CPlacementLodm() : CPlacementBaseInfo(SECTION_IPL_LODM) { this->InitValues(); }

			// Clone
			virtual CPlacementLodm* clone() const { return new CPlacementLodm(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for each model string hash pair
			virtual void ForeachModelStrHashPairs(tHashStrPairFunc func, void* pUserData);

			// Types
			virtual const CPlacementLodm* ToPlacementLodm()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementLodm* ToPlacementLodm() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}