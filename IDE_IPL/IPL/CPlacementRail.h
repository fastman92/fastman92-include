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
		enum ePlacementRailEntryType
		{
			PLACEMENT_RAIL_ENTRY_TYPE_HEADER,
			PLACEMENT_RAIL_ENTRY_TYPE_POS
		};

		class CPlacementRail : public CPlacementBaseInfo
		{
			ePlacementRailEntryType RailEntryType;

		public:
			// VARIABLES

			// if header
			unsigned int NumberOfEntriesFollowing;
			std::string PathName;
			int UnknownParam2inBullyScholarschip;

			// if position
			CVector Pos;

			// FUNCTIONS

			// Constructor
			CPlacementRail();

			// Constructor
			CPlacementRail(ePlacementRailEntryType RailEntryType);

			// Clone
			virtual CPlacementRail* clone() const { return new CPlacementRail(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Returns rail entry type
			ePlacementRailEntryType GetRailEntryType() const;

			// Returns element's scope. 0 by default.
			virtual unsigned int GetElementScopeNumber() const;

			// Returns element's number of scopes
			virtual unsigned int GetElementNumberOfScopes() const;

			// Types
			virtual const CPlacementRail* ToPlacementRail()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementRail* ToPlacementRail() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}