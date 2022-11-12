/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementBaseInfo.h"
#include "../../CVector.h"
#include "../../CVector2D.h"

namespace File
{
	namespace IPL
	{
		class CPlacementGarage : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			CVector Pos;
			CVector2D Line;
			CVector Cube;
			unsigned int Flags;
			unsigned int Type;
			std::string Name;

			// FUNCTIONS

			// Constructor
			CPlacementGarage() : CPlacementBaseInfo(SECTION_IPL_GRGE) { this->InitValues(); }

			// Clone
			virtual CPlacementGarage* clone() const { return new CPlacementGarage(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementGarage* ToPlacementGarage()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementGarage* ToPlacementGarage() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}