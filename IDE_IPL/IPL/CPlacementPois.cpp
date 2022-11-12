/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementPois.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Constructor
		CPlacementPois::CPlacementPois() : CPlacementBaseInfo(SECTION_IPL_POIS)
		{
			this->InitValues();
		}

		CPlacementPois::CPlacementPois(ePlacementPoisEntryType PoisEntryType) : CPlacementBaseInfo(SECTION_IPL_POIS)
		{
			this->PoisEntryType = PoisEntryType;
			this->InitValues();
		}

		// Sets default values
		void CPlacementPois::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			
			this->UnknownElementParam1inBullyScholarschip = "default";
			this->UnknownElementParam2inBullyScholarschip = "default";
			this->UnknownElementParam3inBullyScholarschip = "default";
			this->UnknownElementParam4inBullyScholarschip = "default";
			this->UnknownElementParam5inBullyScholarschip = 0;
			this->Pos = { 0 };
			this->Rot = { 0 };
			this->UnknownElementParam12inBullyScholarschip = false;
			this->UnknownElementParam13inBullyScholarschip = false;
			this->UnknownElementParam14inBullyScholarschip = false;
			this->UnknownElementParam15inBullyScholarschip = false;
			this->UnknownElementParam16inBullyScholarschip = false;
			this->UnknownElementParam17inBullyScholarschip = false;
			this->UnknownElementParam18inBullyScholarschip = false;
			this->UnknownElementParam19inBullyScholarschip = false;
			this->UnknownElementParam20inBullyScholarschip = false;
			this->UnknownElementParam21inBullyScholarschip = false;
			this->UnknownElementParam22inBullyScholarschip = false;
			this->UnknownElementParam23inBullyScholarschip = 0.0;
			this->UnknownElementParam24inBullyScholarschip = false;
			this->UnknownElementParam25inBullyScholarschip = 0;
		}

		// Imports entry.
		unsigned __int32 CPlacementPois::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();			

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tPoisParams p;
						
			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				int scanned =
					sscanf(xLine.c_str(), "%s %s %s %s %d %f %f %f %f %f %f %d %d %d %d %d %d %d %d %d %d %d %f %d %d",
						p.UnknownElementParam1inBullyScholarschip,
						p.UnknownElementParam2inBullyScholarschip,
						p.UnknownElementParam3inBullyScholarschip,
						p.UnknownElementParam4inBullyScholarschip,
						&p.UnknownElementParam5inBullyScholarschip,
						&p.Pos.x, &p.Pos.y, &p.Pos.z,
						&p.Rot.x, &p.Rot.y, &p.Rot.z,
						&p.UnknownParamsFrom12inBullyScholarschip[0],
						&p.UnknownParamsFrom12inBullyScholarschip[1],
						&p.UnknownParamsFrom12inBullyScholarschip[2],
						&p.UnknownParamsFrom12inBullyScholarschip[3],
						&p.UnknownParamsFrom12inBullyScholarschip[4],
						&p.UnknownParamsFrom12inBullyScholarschip[5],
						&p.UnknownParamsFrom12inBullyScholarschip[6],
						&p.UnknownParamsFrom12inBullyScholarschip[7],
						&p.UnknownParamsFrom12inBullyScholarschip[8],
						&p.UnknownParamsFrom12inBullyScholarschip[9],
						&p.UnknownParamsFrom12inBullyScholarschip[10],
						&p.UnknownElementParam23inBullyScholarschip,
						&p.UnknownElementParam24inBullyScholarschip,
						&p.UnknownElementParam25inBullyScholarschip
					);				

				if (scanned > 2)
				{
					this->PoisEntryType = PLACEMENT_POIS_ENTRY_TYPE_ELEMENT;
					
					this->UnknownElementParam1inBullyScholarschip = p.UnknownElementParam1inBullyScholarschip;
					this->UnknownElementParam2inBullyScholarschip = p.UnknownElementParam2inBullyScholarschip;
					this->UnknownElementParam3inBullyScholarschip = p.UnknownElementParam3inBullyScholarschip;
					this->UnknownElementParam4inBullyScholarschip = p.UnknownElementParam4inBullyScholarschip;
					this->UnknownElementParam5inBullyScholarschip = p.UnknownElementParam5inBullyScholarschip;
					this->Pos = p.Pos;
					this->Rot = p.Rot;					

					this->UnknownElementParam12inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[0];
					this->UnknownElementParam13inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[1];
					this->UnknownElementParam14inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[2];
					this->UnknownElementParam15inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[3];
					this->UnknownElementParam16inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[4];
					this->UnknownElementParam17inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[5];
					this->UnknownElementParam18inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[6];
					this->UnknownElementParam19inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[7];
					this->UnknownElementParam20inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[8];
					this->UnknownElementParam21inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[9];
					this->UnknownElementParam22inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[10];

					this->UnknownElementParam23inBullyScholarschip = p.UnknownElementParam23inBullyScholarschip;
					this->UnknownElementParam24inBullyScholarschip = p.UnknownElementParam24inBullyScholarschip;
					this->UnknownElementParam25inBullyScholarschip = p.UnknownElementParam25inBullyScholarschip;

				}
				else
					if (sscanf(xLine.c_str(), "%s %d",
					p.UnknownHeaderParam1inBullyScholarschip,
					&p.UnknownHeaderParam2inBullyScholarschip) == 2)
				{
					this->PoisEntryType = PLACEMENT_POIS_ENTRY_TYPE_HEADER;
					this->UnknownHeaderParam1inBullyScholarschip = p.UnknownHeaderParam1inBullyScholarschip;
					this->UnknownHeaderParam2inBullyScholarschip = p.UnknownHeaderParam2inBullyScholarschip;
				}
			}
						
			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementPois::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				if (this->PoisEntryType == PLACEMENT_POIS_ENTRY_TYPE_HEADER)
				{
					return sprintf(line, "%s, %d",
						this->UnknownHeaderParam1inBullyScholarschip.c_str(),
						this->UnknownHeaderParam2inBullyScholarschip
						);
				}
				else if (this->PoisEntryType == PLACEMENT_POIS_ENTRY_TYPE_ELEMENT)
				{
					return sprintf(line, "%s, %s, %s, %s, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %.17g, %d, %d",
						this->UnknownElementParam1inBullyScholarschip.c_str(),
						this->UnknownElementParam2inBullyScholarschip.c_str(),
						this->UnknownElementParam3inBullyScholarschip.c_str(),
						this->UnknownElementParam4inBullyScholarschip.c_str(),
						this->UnknownElementParam5inBullyScholarschip,
						this->Pos.x,
						this->Pos.y,
						this->Pos.z,
						this->Rot.x,
						this->Rot.y,
						this->Rot.z,
						this->UnknownElementParam12inBullyScholarschip,
						this->UnknownElementParam13inBullyScholarschip,
						this->UnknownElementParam14inBullyScholarschip,
						this->UnknownElementParam15inBullyScholarschip,
						this->UnknownElementParam16inBullyScholarschip,
						this->UnknownElementParam17inBullyScholarschip,
						this->UnknownElementParam18inBullyScholarschip,
						this->UnknownElementParam19inBullyScholarschip,
						this->UnknownElementParam20inBullyScholarschip,
						this->UnknownElementParam21inBullyScholarschip,
						this->UnknownElementParam22inBullyScholarschip,

						this->UnknownElementParam23inBullyScholarschip,
						this->UnknownElementParam24inBullyScholarschip,
						this->UnknownElementParam25inBullyScholarschip
						);
				}
			}

			*line = NULL;
			return 0;
		}

		// Executes a function for 3D world position vectors
		void CPlacementPois::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);

			if (this->PoisEntryType == PLACEMENT_POIS_ENTRY_TYPE_ELEMENT)
				func(&this->Pos, pUserData);
		}

		// Returns pois entry type
		ePlacementPoisEntryType CPlacementPois::GetPoisEntryType() const
		{
			return this->PoisEntryType;
		}

		// Returns element's scope. 0 by default.
		unsigned int CPlacementPois::GetElementScopeNumber() const
		{
			return this->PoisEntryType == PLACEMENT_POIS_ENTRY_TYPE_HEADER ? 0 : 1;
		};

		// Returns element's number of scopes
		unsigned int CPlacementPois::GetElementNumberOfScopes() const
		{
			return 2;
		}
	}
}