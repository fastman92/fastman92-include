/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementPont.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementPont::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();

			this->UnknownParam1inBullyScholarschip = "undefined";
			this->UnknownParam2inBullyScholarschip = 0;
			this->Pos = { 0 };
			this->Rot = { 0 };
			this->UnknownParam9inBullyScholarschip;
			this->UnknownParam10inBullyScholarschip = "default";
			this->UnknownParam11inBullyScholarschip = "default";
			this->UnknownParam12inBullyScholarschip = "default";
			this->UnknownParam13inBullyScholarschip = 0;
			this->UnknownParam14inBullyScholarschip = 0;
			this->UnknownParam15inBullyScholarschip = 0;
			this->UnknownParam16inBullyScholarschip = 0;
			this->UnknownParam17inBullyScholarschip = 0;
			this->UnknownParam18inBullyScholarschip = 0;
			this->UnknownParam19inBullyScholarschip = "default";
			this->UnknownParam20inBullyScholarschip = "default";
		}

		// Imports entry.
		unsigned __int32 CPlacementPont::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tPontParams p;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%s %d %f %f %f %f %f %f %f %s %s %s %d %d %d %d %d %d %s %s",
					p.UnknownParam1inBullyScholarschip,
					&p.UnknownParam2inBullyScholarschip,
					&p.Pos.x, &p.Pos.y, &p.Pos.z,
					&p.Rot.x, &p.Rot.y, &p.Rot.z,
					&p.UnknownParam9inBullyScholarschip,
					p.UnknownParam10inBullyScholarschip,
					p.UnknownParam11inBullyScholarschip,
					p.UnknownParam12inBullyScholarschip,

					&p.UnknownParamsFrom13inBullyScholarschip[0],
					&p.UnknownParamsFrom13inBullyScholarschip[1],
					&p.UnknownParamsFrom13inBullyScholarschip[2],
					&p.UnknownParamsFrom13inBullyScholarschip[3],
					&p.UnknownParamsFrom13inBullyScholarschip[4],
					&p.UnknownParamsFrom13inBullyScholarschip[5],

					p.UnknownParam19inBullyScholarschip,
					p.UnknownParam20inBullyScholarschip
					);

				this->UnknownParam1inBullyScholarschip = p.UnknownParam1inBullyScholarschip;
				this->UnknownParam2inBullyScholarschip = p.UnknownParam2inBullyScholarschip;
				this->Pos = p.Pos;
				this->Rot = p.Rot;
				this->UnknownParam9inBullyScholarschip = p.UnknownParam9inBullyScholarschip;
				this->UnknownParam10inBullyScholarschip = p.UnknownParam10inBullyScholarschip;
				this->UnknownParam11inBullyScholarschip = p.UnknownParam11inBullyScholarschip;
				this->UnknownParam12inBullyScholarschip = p.UnknownParam12inBullyScholarschip;
				this->UnknownParam13inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[0];
				this->UnknownParam14inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[1];
				this->UnknownParam15inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[2];
				this->UnknownParam16inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[3];
				this->UnknownParam17inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[4];
				this->UnknownParam18inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[5];
				this->UnknownParam19inBullyScholarschip = p.UnknownParam19inBullyScholarschip;
				this->UnknownParam20inBullyScholarschip = p.UnknownParam20inBullyScholarschip;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementPont::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%s, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s, %s, %s, %d, %d, %d, %d, %d, %d, %s, %s",
					this->UnknownParam1inBullyScholarschip.c_str(),
					this->UnknownParam2inBullyScholarschip,
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->Rot.x, this->Rot.y, this->Rot.z,
					this->UnknownParam9inBullyScholarschip,
					this->UnknownParam10inBullyScholarschip.c_str(),
					this->UnknownParam11inBullyScholarschip.c_str(),
					this->UnknownParam12inBullyScholarschip.c_str(),

					this->UnknownParam13inBullyScholarschip,
					this->UnknownParam14inBullyScholarschip,
					this->UnknownParam15inBullyScholarschip,
					this->UnknownParam16inBullyScholarschip,
					this->UnknownParam17inBullyScholarschip,
					this->UnknownParam18inBullyScholarschip,

					this->UnknownParam19inBullyScholarschip.c_str(),
					this->UnknownParam20inBullyScholarschip.c_str()
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementPont::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}