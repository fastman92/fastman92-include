/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelWeapon.h"
#include "../../SectionFile/CSectionFileReader.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModelWeapon::InitValues()
		{
			this->CModel3commonElements::InitValues();
			this->Anim1.clear();
			this->Anim2.clear();
			this->ObjectCount = 1;
			memset(this->DrawDistance, NULL, sizeof(this->DrawDistance));
			this->UnkBullyScholarschip8 = 0;
			this->UnkBullyScholarschip9 = 0;
			this->Flags = 0;
		}

		// Imports entry.
		unsigned __int32 CModelWeapon::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tWeapParams param;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%s %s %s %d %f %X",

					param.ModelName,
					param.TXDname,
					param.Anim1,
					&param.ObjectCount,
					this->DrawDistance,
					&param.Flags
					);

				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->Anim1 = param.Anim1;
				this->ObjectCount = param.ObjectCount;
				this->Flags = param.Flags;
			}
			if (game == GAME_SIMPLE_NAME_GTA_VC || game == GAME_SIMPLE_NAME_GTA_SA)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %d %f %x",
					&param.ModelID,

					param.ModelName,
					param.TXDname,
					param.Anim1,
					&param.ObjectCount,
					this->DrawDistance,					
					&param.Flags
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->Anim1 = param.Anim1;
				this->ObjectCount = param.ObjectCount;
				this->Flags = param.Flags;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %d %f %d %d",
					&param.ModelID,

					param.ModelName,
					param.TXDname,
					param.Anim1,
					param.Anim2,
					&param.ObjectCount,
					this->DrawDistance,
					&param.UnkBullyScholarschip8,
					&param.UnkBullyScholarschip9
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->Anim1 = param.Anim1;
				this->Anim2 = param.Anim2;
				this->ObjectCount = param.ObjectCount;
				this->UnkBullyScholarschip8 = param.UnkBullyScholarschip8;
				this->UnkBullyScholarschip9 = param.UnkBullyScholarschip9;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModelWeapon::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%s, %s, %s, %d %.17g, %x",
					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->Anim1.c_str(),
					this->ObjectCount,
					this->DrawDistance[0],
					this->Flags
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_VC || game == GAME_SIMPLE_NAME_GTA_SA)
			{
				return sprintf(line, "%d, %s, %s, %s, %d %.17g, %x",
					this->ModelID,
					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->Anim1.c_str(),
					this->ObjectCount,
					this->DrawDistance[0],
					this->Flags
					);
			}
			else if(game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %s, %s, %s, %d, %.17g, %d, %d",
					this->ModelID,
					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->Anim1.c_str(),
					this->Anim2.c_str(),
					this->ObjectCount,
					this->DrawDistance[0],
					this->UnkBullyScholarschip8,
					this->UnkBullyScholarschip9
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