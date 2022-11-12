/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementBaseInfo.h"

#include <string>

namespace File
{
	namespace IPL
	{
		class CPlacementWithModel : public CPlacementBaseInfo
		{
		public:
			// VARIABLES
			CHashStrPair ModelName;	

			// FUNCTIONS

			// Constructor
			CPlacementWithModel(eSectionType type) : CPlacementBaseInfo(type) { this->InitValues(); }

			// Clone
			virtual CPlacementWithModel* clone() const { return new CPlacementWithModel(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for each model string hash pair
			virtual void ForeachModelStrHashPairs(tHashStrPairFunc func, void* pUserData);

			// Types
			virtual const CPlacementWithModel* ToPlacementWithModel()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementWithModel* ToPlacementWithModel() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}