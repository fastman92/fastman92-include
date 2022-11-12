/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementTrigger.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementTrigger::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			this->UnknownParam1inBullyScholarschip = "undefined";
			this->UnknownParam2inBullyScholarschip = 0;
			this->Pos = { 0 };
			this->Rot = { 0 };
			this->UnknownParam9inBullyScholarschip = 0.0;
			this->UnknownParam10inBullyScholarschip = 0.0;
			this->UnknownParam11inBullyScholarschip = 0.0;
			this->UnknownParam12inBullyScholarschip = 0.0;
			this->UnknownParam12inBullyScholarschip = { 0 };
		}

		// Imports entry.
		unsigned __int32 CPlacementTrigger::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			char Name[256];

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f",
					Name,
					&this->UnknownParam2inBullyScholarschip,
					&this->Pos.x, &this->Pos.y, &this->Pos.z,
					&this->Rot.x, &this->Rot.y, &this->Rot.z,
					&this->UnknownParam9inBullyScholarschip,
					&this->UnknownParam10inBullyScholarschip,
					&this->UnknownParam11inBullyScholarschip,
					&this->UnknownParam12inBullyScholarschip,

					&this->UnknownVectorFromParam13inBullyScholarschip.x,
					&this->UnknownVectorFromParam13inBullyScholarschip.y,
					&this->UnknownVectorFromParam13inBullyScholarschip.z
					);

				this->UnknownParam1inBullyScholarschip = Name;					
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementTrigger::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%s, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
					this->UnknownParam1inBullyScholarschip.c_str(),
					this->UnknownParam2inBullyScholarschip,
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->Rot.x, this->Rot.y, this->Rot.z,
					this->UnknownParam9inBullyScholarschip,
					this->UnknownParam10inBullyScholarschip,
					this->UnknownParam11inBullyScholarschip,
					this->UnknownParam12inBullyScholarschip,

					this->UnknownVectorFromParam13inBullyScholarschip.x,
					this->UnknownVectorFromParam13inBullyScholarschip.y,
					this->UnknownVectorFromParam13inBullyScholarschip.z
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementTrigger::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}