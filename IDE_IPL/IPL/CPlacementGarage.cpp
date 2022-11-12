/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementGarage.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementGarage::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
						
			this->Pos = { 0 };
			this->Line = { 0 };
			this->Cube = { 0 };
			this->Flags = 0;
			this->Type = 0;
			this->Name = "undefined";
		}

		// Imports entry.
		unsigned __int32 CPlacementGarage::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct 
			{
				unsigned int Flags;
				unsigned int Type;
				char Name[256];
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_SA || game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%f %f %f %f %f %f %f %f %d %d %s",
					&this->Pos.x, &this->Pos.y, &this->Pos.z,
					&this->Line.x, &this->Line.y,
					&this->Cube.x, &this->Cube.y, &this->Cube.z,
					&param.Flags,
					&param.Type,
					&param.Name
					);

				this->Flags = param.Flags;
				this->Type = param.Type;
				this->Name = param.Name;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementGarage::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_SA || game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d, %d, %s",
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->Line.x, this->Line.y,
					this->Cube.x, this->Cube.y, this->Cube.z,
					this->Flags,
					this->Type,
					this->Name.c_str()
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementGarage::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
			func(&this->Cube, pUserData);
		}
	}
}