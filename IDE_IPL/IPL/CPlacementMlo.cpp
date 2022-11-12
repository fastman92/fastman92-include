/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementMlo.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementMlo::InitValues()
		{
			this->CPlacementWithModel::InitValues();
						
			this->Flags = 0;
			this->InstMloIndex = 0;
			this->CountParam5inGTAIV = 0;
			this->Pos = { 0 };
			this->Rot = { 0 };
			this->UnknownParam12inGTAIV = -1;
			this->UnknownParam13inGTAIV = -1;
		}

		// Imports entry.
		unsigned __int32 CPlacementMlo::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct
			{
				char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
				unsigned __int32 Flags;
				int InstMloIndex;
				int CountParam5inGTAIV;
				int UnknownParam12inGTAIV;
				int UnknownParam13inGTAIV;

			} param;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				param.UnknownParam13inGTAIV = -1;

				sscanf(xLine.c_str(), "%s %d %d %d %f %f %f %f %f %f %f %d %d",
					param.ModelName,
					&param.Flags,
					&param.InstMloIndex,
					&param.CountParam5inGTAIV,
					&this->Pos.x, &this->Pos.y, &this->Pos.z,
					&this->Rot.imag.x, &this->Rot.imag.y, &this->Rot.imag.z, &this->Rot.real,
					&param.UnknownParam12inGTAIV,
					&param.UnknownParam13inGTAIV
					);

				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->Flags = param.Flags;
				this->InstMloIndex = param.InstMloIndex;
				this->CountParam5inGTAIV = param.CountParam5inGTAIV;
				this->UnknownParam12inGTAIV = param.UnknownParam12inGTAIV;
				this->UnknownParam13inGTAIV = param.UnknownParam13inGTAIV;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementMlo::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%s, %d, %d, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d, %d",
					this->ModelName.GetString().c_str(),
					this->Flags,
					this->InstMloIndex,
					this->CountParam5inGTAIV,
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->Rot.imag.x, this->Rot.imag.y, this->Rot.imag.z, this->Rot.real,
					this->UnknownParam12inGTAIV,
					this->UnknownParam13inGTAIV
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementMlo::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementWithModel::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}