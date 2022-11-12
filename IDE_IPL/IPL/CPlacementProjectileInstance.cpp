/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementProjectileInstance.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementProjectileInstance::InitValues()
		{
			this->CPlacementWithModel::InitValues();
			this->UnknownParam3inBullyScholarschip = 0.0;
			this->Pos = { 0 };
			this->Scale = { 0 };
			this->Rot = { 0 };
		}

		// Imports entry.
		unsigned __int32 CPlacementProjectileInstance::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tProjParams param;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{				
				sscanf(xLine.c_str(), "%d %s %f %f %f %f %f %f %f %f %f %f",
					&param.ModelID,
					param.ModelName,
					&param.UnknownParam3inGTAIV,
					&this->Pos.x,
					&this->Pos.y,
					&this->Pos.z,
					&this->Scale.x,
					&this->Scale.y,
					&this->Scale.z,
					&this->Rot.x,
					&this->Rot.y,
					&this->Rot.z
					);

				this->ModelID = param.ModelID;
				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->UnknownParam3inBullyScholarschip = this->UnknownParam3inBullyScholarschip;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementProjectileInstance::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
					this->ModelID,
					this->ModelName.GetString().c_str(),
					this->UnknownParam3inBullyScholarschip,
					this->Pos.x,
					this->Pos.y,
					this->Pos.z,
					this->Scale.x,
					this->Scale.y,
					this->Scale.z,
					this->Rot.x,
					this->Rot.y,
					this->Rot.z
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementProjectileInstance::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}