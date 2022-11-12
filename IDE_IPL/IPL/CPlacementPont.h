/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"
#include "../../IMG/IMGstructures.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		struct tPontParams
		{
			char UnknownParam1inBullyScholarschip[256];
			int32_t UnknownParam2inBullyScholarschip;
			CVector Pos;
			CVector Rot;
			float UnknownParam9inBullyScholarschip;
			char UnknownParam10inBullyScholarschip[256];
			char UnknownParam11inBullyScholarschip[256];
			char UnknownParam12inBullyScholarschip[256];
			int32_t UnknownParamsFrom13inBullyScholarschip[6];
			char UnknownParam19inBullyScholarschip[256];
			char UnknownParam20inBullyScholarschip[256];
		};

		class CPlacementPont : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			std::string UnknownParam1inBullyScholarschip;
			char UnknownParam2inBullyScholarschip;
			CVector Pos;
			CVector Rot;
			float UnknownParam9inBullyScholarschip;	// ignored by game
			std::string UnknownParam10inBullyScholarschip;	// ignored by game
			std::string UnknownParam11inBullyScholarschip;	// model name
			std::string UnknownParam12inBullyScholarschip;	// audio name
			char UnknownParam13inBullyScholarschip;
			char UnknownParam14inBullyScholarschip;
			char UnknownParam15inBullyScholarschip;
			char UnknownParam16inBullyScholarschip;		// ignored by game
			char UnknownParam17inBullyScholarschip;		// ignored by game
			char UnknownParam18inBullyScholarschip;		// ignored by game
			std::string UnknownParam19inBullyScholarschip;	// some pickup data
			std::string UnknownParam20inBullyScholarschip;	// ignored by game

			// FUNCTIONS

			// Constructor
			CPlacementPont() : CPlacementBaseInfo(SECTION_IPL_PONT) { this->InitValues(); }

			// Clone
			virtual CPlacementPont* clone() const { return new CPlacementPont(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementPont* ToPlacementPont()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementPont* ToPlacementPont() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}