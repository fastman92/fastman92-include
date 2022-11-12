/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementBaseInfo.h"
#include "../../CVector.h"
#include "../../IMG/IMGstructures.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		class CPlacementTrigger : public CPlacementBaseInfo
		{
		public:
			// VARIABLES
			std::string UnknownParam1inBullyScholarschip;
			__int32 UnknownParam2inBullyScholarschip;
			CVector Pos;
			CVector Rot;
			float UnknownParam9inBullyScholarschip;
			float UnknownParam10inBullyScholarschip;
			float UnknownParam11inBullyScholarschip;
			float UnknownParam12inBullyScholarschip;
			CVector UnknownVectorFromParam13inBullyScholarschip;

			// FUNCTIONS

			// Constructor
			CPlacementTrigger() : CPlacementBaseInfo(SECTION_IPL_TRIG)
			{ this->InitValues(); }

			// Clone
			virtual CPlacementTrigger* clone() const { return new CPlacementTrigger(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementTrigger* ToPlacementTrigger()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementTrigger* ToPlacementTrigger() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}