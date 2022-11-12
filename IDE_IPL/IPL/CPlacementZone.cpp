/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementZone.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementZone::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
						
			this->ZoneName = "UNDEFIN";
			this->Type = 0;
			this->BoxCornerFirst = { 0 };
			this->BoxCornerSecond = { 0 };
			this->LevelID = 0;
			this->GXTlabel = "UNDEFINED";
			this->Flags = 0;
		}

		// Imports entry.
		unsigned __int32 CPlacementZone::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct 
			{
				char ZoneName[64];
				int Type;
				int LevelID;
				char GXTlabel[64];
				unsigned __int32 Flags;
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_III || game == GAME_SIMPLE_NAME_GTA_VC)
			{
				sscanf(xLine.c_str(), "%s %d %f %f %f %f %f %f %d",
					param.ZoneName,
					&param.Type,
					&this->BoxCornerFirst.x, &this->BoxCornerFirst.y, &this->BoxCornerFirst.z,
					&this->BoxCornerSecond.x, &this->BoxCornerSecond.y, &this->BoxCornerSecond.z,
					&param.LevelID
					);

				this->ZoneName = param.ZoneName;
				this->Type = param.Type;
				this->LevelID = param.LevelID;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_SA || game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%s %d %f %f %f %f %f %f %d %s",
					param.ZoneName,
					&param.Type,
					&this->BoxCornerFirst.x, &this->BoxCornerFirst.y, &this->BoxCornerFirst.z,
					&this->BoxCornerSecond.x, &this->BoxCornerSecond.y, &this->BoxCornerSecond.z,
					&param.LevelID,
					&param.GXTlabel
					);

				this->ZoneName = param.ZoneName;
				this->Type = param.Type;
				this->LevelID = param.LevelID;
				this->GXTlabel = param.GXTlabel;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_V)
			{
				sscanf(xLine.c_str(), "%s %f %f %f %f %f %f %s %d",
					param.ZoneName,
					&this->BoxCornerFirst.x, &this->BoxCornerFirst.y, &this->BoxCornerFirst.z,
					&this->BoxCornerSecond.x, &this->BoxCornerSecond.y, &this->BoxCornerSecond.z,
					&param.GXTlabel,
					&param.Flags
					);

				this->ZoneName = param.ZoneName;
				this->GXTlabel = param.GXTlabel;
				this->Flags = param.Flags;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementZone::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_III || game == GAME_SIMPLE_NAME_GTA_VC
				|| game == GAME_SIMPLE_NAME_GTA_SA || game == GAME_SIMPLE_NAME_GTA_IV)
			{

				int l = sprintf(line, "%s, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d",
					this->ZoneName.c_str(),
					this->Type,
					this->BoxCornerFirst.x, this->BoxCornerFirst.y, this->BoxCornerFirst.z,
					this->BoxCornerSecond.x, this->BoxCornerSecond.y, this->BoxCornerSecond.z,
					this->LevelID
					);

				if (game == GAME_SIMPLE_NAME_GTA_SA || game == GAME_SIMPLE_NAME_GTA_IV)
					l += sprintf(line + l, ", %s", this->GXTlabel.c_str());

				return l;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_V)
			{
				return sprintf(line, "%s, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s, %d",
					this->ZoneName.c_str(),
					this->BoxCornerFirst.x, this->BoxCornerFirst.y, this->BoxCornerFirst.z,
					this->BoxCornerSecond.x, this->BoxCornerSecond.y, this->BoxCornerSecond.z,
					this->GXTlabel.c_str(),
					this->Flags
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementZone::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->BoxCornerFirst, pUserData);
			func(&this->BoxCornerSecond, pUserData);
		}
	}
}