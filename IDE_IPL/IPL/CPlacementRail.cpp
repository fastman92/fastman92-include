/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementRail.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Constructor
		CPlacementRail::CPlacementRail() : CPlacementBaseInfo(SECTION_IPL_RAIL)
		{
			this->InitValues();
		}

		CPlacementRail::CPlacementRail(ePlacementRailEntryType RailEntryType) : CPlacementBaseInfo(SECTION_IPL_RAIL)
		{
			this->RailEntryType = RailEntryType;
			this->InitValues();
		}

		// Sets default values
		void CPlacementRail::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			this->NumberOfEntriesFollowing = 0;
			this->PathName = "undefined";
			this->Pos = { 0 };
		}

		// Imports entry.
		unsigned __int32 CPlacementRail::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			// tInstParams param;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				CVector Pos;

				char PathName[256];
				int UnknownParam2inBullyScholarschip;

				if (sscanf(xLine.c_str(), "%f %f %f",
					&Pos.x, &Pos.y, &Pos.z) == 3)
				{
					this->RailEntryType = PLACEMENT_RAIL_ENTRY_TYPE_POS;
					this->Pos = Pos;
				}
				else if (sscanf(xLine.c_str(), "%s %d",
					&PathName,
					&UnknownParam2inBullyScholarschip) == 2)
				{
					this->RailEntryType = PLACEMENT_RAIL_ENTRY_TYPE_HEADER;
					this->PathName = PathName;
					this->UnknownParam2inBullyScholarschip = UnknownParam2inBullyScholarschip;
				}
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementRail::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				if (this->RailEntryType == PLACEMENT_RAIL_ENTRY_TYPE_HEADER)
				{
					return sprintf(line, "%s, %d",
						this->PathName.c_str(),
						this->UnknownParam2inBullyScholarschip
						);
				}
				else if (this->RailEntryType == PLACEMENT_RAIL_ENTRY_TYPE_POS)
				{
					return sprintf(line, "%.17g, %.17g, %.17g",
						this->Pos.x,
						this->Pos.y,
						this->Pos.z
						);
				}
			}

			*line = NULL;
			return 0;
		}

		// Executes a function for 3D world position vectors
		void CPlacementRail::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);

			if (this->RailEntryType == PLACEMENT_RAIL_ENTRY_TYPE_POS)
				func(&this->Pos, pUserData);
		}

		// Returns rail entry type
		ePlacementRailEntryType CPlacementRail::GetRailEntryType() const
		{
			return this->RailEntryType;
		}

		// Returns element's scope. 0 by default.
		unsigned int CPlacementRail::GetElementScopeNumber() const
		{
			return this->RailEntryType == PLACEMENT_RAIL_ENTRY_TYPE_HEADER ? 0 : 1;
		};

		// Returns element's number of scopes
		unsigned int CPlacementRail::GetElementNumberOfScopes() const
		{
			return 2;
		}
	}
}