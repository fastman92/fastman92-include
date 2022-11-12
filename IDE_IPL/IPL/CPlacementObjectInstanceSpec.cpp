/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementObjectInstanceSpec.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementObjectInstanceSpec::InitValues()
		{
			this->CPlacementObjectInstance::InitValues();
			this->AreaName.Initialize("undefined");
			this->AreaType = 0;
		}

		// Imports entry.
		unsigned __int32 CPlacementObjectInstanceSpec::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tInstParams param;

			char AreaName[256];
			int AreaType;
			
			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %f %f %f %f %f %f %f %f %f %f %f %f %s %s %d",
					&param.ModelID,
					param.ModelName,
					&param.fInteriorNum,
					&this->Pos.x,
					&this->Pos.y,
					&this->Pos.z,
					&this->Scale.x,
					&this->Scale.y,
					&this->Scale.z,
					&this->Rot.imag.x,
					&this->Rot.imag.y,
					&this->Rot.imag.z,
					&this->Rot.real,
					&param.field_70_inBullyScholarchip,
					param.CollectibleName,
					AreaName,
					&AreaType
					);

				this->ModelID = param.ModelID;
				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->field_70_inBullyScholarchip = param.field_70_inBullyScholarchip;
				this->CollectibleName.SetStringAndHash(game, param.CollectibleName);
				this->AreaName.SetStringAndHash(game, AreaName);
				this->AreaType = AreaType;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementObjectInstanceSpec::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s, %s, %d",
					this->ModelID,
					this->ModelName.GetString().c_str(),
					(float)this->InteriorNum,
					this->Pos.x,
					this->Pos.y,
					this->Pos.z,
					this->Scale.x,
					this->Scale.y,
					this->Scale.z,
					this->Rot.imag.x,
					this->Rot.imag.y,
					this->Rot.imag.z,
					this->Rot.real,
					this->field_70_inBullyScholarchip,
					this->CollectibleName.GetString().c_str(),
					this->AreaName.GetString().c_str(),
					this->AreaType
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for each other string hash pair
		void CPlacementObjectInstanceSpec::ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData)
		{
			this->CPlacementObjectInstance::ForeachOtherStrHashPairs(func, pUserData);
			func(&this->AreaName, pUserData);
		}
	}
}