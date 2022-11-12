/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementMapZone.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IPL
	{

		// Imports entry.
		unsigned __int32 CPlacementMapZone::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			if (game == GAME_SIMPLE_NAME_GTA_V)
			{

				this->InitValues();

				this->ImportedLine = line;
				std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

				struct
				{
					char GXTlabel[64];
					unsigned __int32 Flags;
				} param;


				sscanf(xLine.c_str(), "%f %f %f %f %f %f %s %u",
					&this->BoxCornerFirst.x, &this->BoxCornerFirst.y, &this->BoxCornerFirst.z,
					&this->BoxCornerSecond.x, &this->BoxCornerSecond.y, &this->BoxCornerSecond.z,
					param.GXTlabel,
					&param.Flags
					);

				this->GXTlabel = param.GXTlabel;
				this->Flags = param.Flags;
				
				return -1;
			}
			else
				return this->CPlacementZone::ImportEntry(game, line);			
		}

		// Exports entry. Returns length of output string.
		int CPlacementMapZone::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			if (game == GAME_SIMPLE_NAME_GTA_V)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s, %u",
					this->BoxCornerFirst.x, this->BoxCornerFirst.y, this->BoxCornerFirst.z,
					this->BoxCornerSecond.x, this->BoxCornerSecond.y, this->BoxCornerSecond.z,
					this->GXTlabel.c_str(),
					this->Flags
					);
			}
			else
				return this->CPlacementZone::ExportEntry(game, line);
		}
	}
}