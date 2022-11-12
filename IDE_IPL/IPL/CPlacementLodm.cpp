/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementLodm.h"
#include "IPLstructures.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementLodm::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			this->Box = { 0 };
			this->CountOfModels = 0;
			this->UnknownParamFlagPosition24inGTAIV = 0;

			for (int i = 0; i < _countof(ModelNameArray); i++)
				this->ModelNameArray[i].Initialize("undefined");
		}

		// Imports entry.
		unsigned __int32 CPlacementLodm::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct
			{
				unsigned int Flags;
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				unsigned __int32 ModelNameHashes[NUMBER_OF_HASHES_IN_GTAIV_LODM];
				
				int n = sscanf(xLine.c_str(), "%f %f %f %f %f %f %d %d %d %d %d %d %d %d %d %d %d",
					&this->Box.m_vInf.x, &this->Box.m_vInf.y, &this->Box.m_vInf.z,
					&this->Box.m_vSup.x, &this->Box.m_vSup.y, &this->Box.m_vSup.z,
					&param.Flags,
					ModelNameHashes,
					ModelNameHashes + 1,
					ModelNameHashes + 2,
					ModelNameHashes + 3,
					ModelNameHashes + 4,
					ModelNameHashes + 5,
					ModelNameHashes + 6,
					ModelNameHashes + 7,
					ModelNameHashes + 8,
					ModelNameHashes + 9
					);

				this->CountOfModels = param.Flags & 0xF;

				if (this->CountOfModels > NUMBER_OF_HASHES_IN_GTAIV_LODM)
					this->CountOfModels = NUMBER_OF_HASHES_IN_GTAIV_LODM;

				if (this->CountOfModels > _countof(this->ModelNameArray))
					this->CountOfModels = _countof(this->ModelNameArray);

				this->UnknownParamFlagPosition24inGTAIV = param.Flags >> 24;

				for (unsigned i = 0; i < this->CountOfModels; i++)
					this->ModelNameArray[i].SetHashAndString(game, ModelNameHashes[i]);
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementLodm::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				unsigned int countOfModels = this->CountOfModels;

				if (countOfModels > 10)
					countOfModels = 10;

				unsigned __int32 Flags = countOfModels | (this->UnknownParamFlagPosition24inGTAIV << 24);
				
				int l = sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d",
					this->Box.m_vInf.x, this->Box.m_vInf.y, this->Box.m_vInf.z,
					this->Box.m_vSup.x, this->Box.m_vSup.y, this->Box.m_vSup.z,
					this->CountOfModels & 0xF | this->UnknownParamFlagPosition24inGTAIV << 24
					);

				if (countOfModels)
				{
					for (unsigned i = 0; i < countOfModels; i++)
						l += sprintf(line + l, ", %d", this->ModelNameArray[i].GetHash());

					l += sprintf(line + l, " # ");

					for (unsigned i = 0; i < countOfModels; i++)
						l += sprintf(line + l, i == 0 ? "%s" :", %s", this->ModelNameArray[i].GetString().c_str());

				}

				return l;					
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for each model string hash pair
		void CPlacementLodm::ForeachModelStrHashPairs(tHashStrPairFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::ForeachModelStrHashPairs(func, pUserData);
			
			for (unsigned i = 0; i < this->CountOfModels; i++)
				func(this->ModelNameArray + i, pUserData);
		}
	}
}