/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementBaseInfo.h"
#include "../../CVector.h"

namespace File
{
	namespace IPL
	{
		class CPlacementVehicleNode : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			CVector Pos;
			bool UnknownParam4inGTAIV;
			bool UnknownParam5inGTAIV;
			bool UnknownParam6inGTAIV;
			int UnknownParam7inGTAIV;
			int UnknownParam8inGTAIV;
			float UnknownParam9inGTAIV;
			int UnknownParam10inGTAIV;
			bool UnknownParam11inGTAIV;
			bool UnknownParam12inGTAIV;
			bool UnknownParam13inGTAIV;

			// FUNCTIONS

			// Constructor
			CPlacementVehicleNode() : CPlacementBaseInfo(SECTION_IPL_VNOD) { this->InitValues(); }

			// Clone
			virtual CPlacementVehicleNode* clone() const { return new CPlacementVehicleNode(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementVehicleNode* ToPlacementVehicleNode()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementVehicleNode* ToPlacementVehicleNode() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}