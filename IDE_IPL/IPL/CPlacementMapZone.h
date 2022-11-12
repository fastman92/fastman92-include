/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementZone.h"
#include "../../CVector.h"

namespace File
{
	namespace IPL
	{
		class CPlacementMapZone : public CPlacementZone
		{			
		public:
			// FUNCTIONS

			// Constructor
			CPlacementMapZone() : CPlacementZone(SECTION_IPL_MZON) { this->InitValues(); }

			// Clone
			virtual CPlacementMapZone* clone() const { return new CPlacementMapZone(*this); };

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);
			
			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CPlacementMapZone* ToPlacementMapZone()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementMapZone* ToPlacementMapZone() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}