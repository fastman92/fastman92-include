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
		class CPlacementProp : public CPlacementBaseInfo
		{
		public:
			// VARIABLES
			std::string PropName;

			// FUNCTIONS

			// Constructor
			CPlacementProp() : CPlacementBaseInfo(SECTION_IPL_PROP) { this->InitValues(); }

			// Clone
			virtual CPlacementProp* clone() const { return new CPlacementProp(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CPlacementProp* ToPlacementProp()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementProp* ToPlacementProp() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}