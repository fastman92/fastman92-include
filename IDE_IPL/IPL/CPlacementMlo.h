/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		class CPlacementMlo : public CPlacementWithModel
		{			
		public:
			// VARIABLES
			unsigned __int32 Flags;
			int InstMloIndex;
			int CountParam5inGTAIV;
			CVector Pos;
			CQuaternion Rot;
			int UnknownParam12inGTAIV;
			int UnknownParam13inGTAIV;
				
			// FUNCTIONS

			// Constructor
			CPlacementMlo() : CPlacementWithModel(SECTION_IPL_MLO_PLUS) { this->InitValues(); }

			// Clone
			virtual CPlacementMlo* clone() const { return new CPlacementMlo(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementMlo* ToPlacementMlo()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementMlo* ToPlacementMlo() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}