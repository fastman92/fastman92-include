/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementLink.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementLink::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();

			this->UnknownParam1inGTAIV = 0;
			this->UnknownParam2inGTAIV = 0;
			this->UnknownParam3inGTAIV = 0.0;
			this->UnknownParam4inGTAIV = 0;
			this->UnknownParam5inGTAIV = 0;
		}

		// Imports entry.
		unsigned __int32 CPlacementLink::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct
			{
				int UnknownParam1inGTAIV;
				int UnknownParam2inGTAIV;
				float UnknownParam3inGTAIV;
				int UnknownParam4inGTAIV;
				int UnknownParam5inGTAIV;
				unsigned __int32 Flags;
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%d %d %f %d %d %d",
					&param.UnknownParam1inGTAIV,
					&param.UnknownParam2inGTAIV,
					&param.UnknownParam3inGTAIV,
					&param.UnknownParam4inGTAIV,
					&param.UnknownParam5inGTAIV,
					&param.Flags
					);

				this->UnknownParam1inGTAIV = param.UnknownParam1inGTAIV;
				this->UnknownParam2inGTAIV = param.UnknownParam2inGTAIV;
				this->UnknownParam3inGTAIV = param.UnknownParam3inGTAIV;
				this->UnknownParam4inGTAIV = param.UnknownParam4inGTAIV;
				this->UnknownParam5inGTAIV = param.UnknownParam5inGTAIV;
				this->Flags = param.Flags;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementLink::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%d, %d, %.17g, %d, %d, %d",
					this->UnknownParam1inGTAIV,
					this->UnknownParam2inGTAIV,
					this->UnknownParam3inGTAIV,
					this->UnknownParam4inGTAIV,
					this->UnknownParam5inGTAIV,
					this->Flags
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