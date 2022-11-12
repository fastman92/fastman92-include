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
		class CPlacementSlow : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			CBox Box;

			// FUNCTIONS

			// Constructor
			CPlacementSlow() : CPlacementBaseInfo(SECTION_IPL_SLOW) { this->InitValues(); }

			// Clone
			virtual CPlacementSlow* clone() const { return new CPlacementSlow(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementSlow* ToPlacementSlow()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementSlow* ToPlacementSlow() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}