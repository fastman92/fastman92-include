/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementBlok.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementBlok::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();

			const char* nullStr = "(null)";

			this->BlockName = nullStr;
			this->Author = nullStr;
			this->DateTime = "(null):(null):unknown:(null):(null):(null)";
			this->UnknownParam4inGTAIV = 0;
			this->UnknownParam5inGTAIV = 0;
			this->UnknownParam6inGTAIV = "unknown";

			memset(this->CornerPoints, NULL, sizeof(this->CornerPoints));
		}

		// Imports entry.
		unsigned __int32 CPlacementBlok::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct {
				char BlockName[64];
				char Author[64];
				char DateTime[64];
				int UnknownParam4inGTAIV;	// flags? type?
				int UnknownParam5inGTAIV;
				char UnknownParam6inGTAIV[64];	// seems to be always "unknown" in all entries
				CVector2D CornerPoints[4];
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				param.UnknownParam4inGTAIV = 0;
				memset(param.CornerPoints, NULL, sizeof(param.CornerPoints));

				sscanf(xLine.c_str(), "%s %s %s %d %d %s %f %f %f %f %f %f %f %f",
					param.BlockName,
					param.Author,
					param.DateTime,
					&param.UnknownParam4inGTAIV,
					&param.UnknownParam5inGTAIV,
					param.UnknownParam6inGTAIV,
					&param.CornerPoints[0].x,
					&param.CornerPoints[0].y,
					&param.CornerPoints[1].x,
					&param.CornerPoints[1].y,
					&param.CornerPoints[2].x,
					&param.CornerPoints[2].y,
					&param.CornerPoints[3].x,
					&param.CornerPoints[3].y
					);

				this->BlockName = param.BlockName;
				this->Author = param.Author;
				this->DateTime = param.DateTime;
				this->UnknownParam4inGTAIV = param.UnknownParam4inGTAIV;
				this->UnknownParam5inGTAIV = param.UnknownParam5inGTAIV;
				this->UnknownParam6inGTAIV = param.UnknownParam6inGTAIV;

				if (this->UnknownParam4inGTAIV != 128)
					memcpy(this->CornerPoints, param.CornerPoints, sizeof(this->CornerPoints));
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementBlok::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				int l = sprintf(line, "%s, %s, %s, %d, %d, %s",
					this->BlockName.c_str(),
					this->Author.c_str(),
					this->DateTime.c_str(),
					this->UnknownParam4inGTAIV,
					this->UnknownParam5inGTAIV,
					this->UnknownParam6inGTAIV.c_str()
					);

				if(this->UnknownParam4inGTAIV != 128)
					l += sprintf(line + l, ", %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
						this->CornerPoints[0].x,
						this->CornerPoints[0].y,
						this->CornerPoints[1].x,
						this->CornerPoints[1].y,
						this->CornerPoints[2].x,
						this->CornerPoints[2].y,
						this->CornerPoints[3].x,
						this->CornerPoints[3].y
						);
				
				return l;
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 2D world position vectors
		void CPlacementBlok::Foreach2DworldPositions(tHashVector2DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach2DworldPositions(func, pUserData);
			
			for (int i = 0; i < _countof(this->CornerPoints); i++)
				func(&this->CornerPoints[i], pUserData);
		}
	}
}