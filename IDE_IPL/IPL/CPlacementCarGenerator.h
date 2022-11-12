/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"

namespace File
{
	namespace IPL
	{
		class CPlacementCarGenerator : public CPlacementWithModel
		{			
		public:
			// VARIABLES
			CVector Pos;
			CVector Rot;
			float AngleInRadians;	// in radians
			unsigned int PrimCol;
			unsigned int SecCol;
			unsigned int ThirdColor;
			unsigned int SpecularColor;
			unsigned __int32 Flags;
			unsigned int AlarmProbability;
			unsigned int DoorLockProbability;
			int MinDelay;
			int MaxDelay;

			// FUNCTIONS

			// Constructor
			CPlacementCarGenerator() : CPlacementWithModel(SECTION_IPL_CARS) { this->InitValues(); }

			// Clone
			virtual CPlacementCarGenerator* clone() const { return new CPlacementCarGenerator(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementCarGenerator* ToPlacementCarGenerator()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementCarGenerator* ToPlacementCarGenerator() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}