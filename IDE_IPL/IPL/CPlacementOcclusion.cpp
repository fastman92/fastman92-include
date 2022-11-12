/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementOcclusion.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementOcclusion::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			
			this->MidX = 0.0;
			this->MidY = 0.0;
			this->BottomZ = 0.0;
			this->WidthX = 0.0;
			this->WidthY = 0.0;
			this->Height = 0.0;
			this->Rot = { 0 };
			this->UnknownParam10inBullyScholarschip = false;
		}

		// Imports entry.
		unsigned __int32 CPlacementOcclusion::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			int UnknownParam10inBullyScholarschip;

			if (game == GAME_SIMPLE_NAME_GTA_III
				|| game == GAME_SIMPLE_NAME_GTA_VC				
				|| game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%f %f %f %f %f %f %f",
					&this->MidX, &this->MidY,
					&this->BottomZ,
					&this->WidthX, &this->WidthY,
					&this->Height,
					&this->Rot.z
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_SA
				|| game == GAME_SIMPLE_NAME_GTA_IV)
			{
				UnknownParam10inBullyScholarschip = false;

				sscanf(xLine.c_str(), "%f %f %f %f %f %f %f %f %f %d",
					&this->MidX, &this->MidY,
					&this->BottomZ,
					&this->WidthX, &this->WidthY,
					&this->Height,
					&this->Rot.z,
					&this->Rot.x,
					&this->Rot.y,
					&UnknownParam10inBullyScholarschip
					);

				this->UnknownParam10inBullyScholarschip = UnknownParam10inBullyScholarschip != 0;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementOcclusion::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
					this->MidX, this->MidY,
					this->BottomZ,
					this->WidthX, this->WidthY,
					this->Height,
					this->Rot.z
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_SA
				|| game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d",
					this->MidX, this->MidY,
					this->BottomZ,
					this->WidthX, this->WidthY,
					this->Height,
					this->Rot.z,
					this->Rot.x,
					this->Rot.y,
					this->UnknownParam10inBullyScholarschip
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}
	}
}