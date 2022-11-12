/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementWithModel.h"
#include "../../IMG/IMGstructures.h"
#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementWithModel::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			this->ModelName.Initialize("undefined");
		}

		// Imports entry.
		unsigned __int32 CPlacementWithModel::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();
			this->ImportedLine = line;

			unsigned __int32 modelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];

			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			sscanf(xLine.c_str(), "%d %s", &modelID, ModelName);

			this->ModelID = modelID;
			this->ModelName.SetStringAndHash(game, ModelName);

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementWithModel::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			return sprintf(line, "%d, %s", this->ModelID, this->ModelName.GetString().c_str());
		}
		
		// Executes a function for each model string hash pair
		void CPlacementWithModel::ForeachModelStrHashPairs(tHashStrPairFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::ForeachModelStrHashPairs(func, pUserData);
			func(&this->ModelName, pUserData);
		}
	}
}