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
		class CPlacementZone : public CPlacementBaseInfo
		{			
		public:
			// VARIABLES
			std::string ZoneName;
			int Type;
			CVector BoxCornerFirst;
			CVector BoxCornerSecond;
			int LevelID;
			std::string GXTlabel;
			unsigned __int32 Flags;

			// FUNCTIONS

			// Constructor
			CPlacementZone() : CPlacementBaseInfo(SECTION_IPL_ZONE) { this->InitValues(); }

			// Constructor
			CPlacementZone(int sectionType) : CPlacementBaseInfo(sectionType) { this->InitValues(); }

			// Clone
			virtual CPlacementZone* clone() const { return new CPlacementZone(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementZone* ToPlacementZone()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementZone* ToPlacementZone() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}