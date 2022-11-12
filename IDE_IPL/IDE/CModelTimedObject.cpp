/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../../SectionFile/CSectionFileReader.h"
#include "CModelTimedObject.h"

using namespace Game;

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModelTimedObject::InitValues()
		{
			this->CModelObject::InitValues();
			this->TimeOn = 0;
			this->TimeOff = 0;
		}

		// Imports entry.
		unsigned __int32 CModelTimedObject::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct : tObjsParams {
				int TimeOn;
				int TimeOff;
			} param;

			param.TimeOn = 0;
			param.TimeOff = 0;

			if (Game::GameSimple::IsGTAIIIeraGame(game))
			{
				this->ObjectCount = 1;

				if (sscanf(xLine.c_str(), "%d %s %s %f %d %d %d", &param.ModelID, param.ModelName, param.TXDname, this->DrawDistance, &this->Flags, &param.TimeOn, &param.TimeOff) != 7
					|| this->DrawDistance[0] <= 4.0
					)
				{
					if (sscanf(xLine.c_str(), "%d %s %s %d %d %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, &param.TimeOn, &param.TimeOff) != 4)
						return -1;

					switch (this->ObjectCount)
					{
					case 1:
						sscanf(xLine.c_str(), "%d %s %s %d %f %d %d %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, this->DrawDistance, &this->Flags, &param.TimeOn, &param.TimeOff);
						break;
					case 2:
						sscanf(xLine.c_str(), "%d %s %s %d %f %f %d %d %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, this->DrawDistance, this->DrawDistance + 1, &this->Flags, &param.TimeOn, &param.TimeOff);
						break;
					case 3:
						sscanf(xLine.c_str(), "%d %s %s %d %f %f %f %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, this->DrawDistance, this->DrawDistance + 1, this->DrawDistance + 2, &this->Flags);
						break;
					}
				}

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->TimeOn = param.TimeOn;
				this->TimeOff = param.TimeOff;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %s %d %f %d %d %f %d %d %d %d %d %d %d",
					&param.ModelID,
					param.ModelName,
					param.TXDname,
					&this->ObjectCount,
					this->DrawDistance,
					&this->Flags,
					&param.UnkBullyScholarschip7,
					&param.UnkBullyScholarschip8,
					&param.UnkBullyScholarschip9,
					&param.UnkBullyScholarschip10,
					&param.UnkBullyScholarschip11,
					&param.UnkBullyScholarschip12,
					&param.UnkBullyScholarschip13,
					&param.TimeOn,
					&param.TimeOff
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;

				this->UnkBullyScholarschip7 = param.UnkBullyScholarschip7;
				this->UnkBullyScholarschip8 = param.UnkBullyScholarschip8;
				this->UnkBullyScholarschip9 = param.UnkBullyScholarschip9;
				this->UnkBullyScholarschip10 = param.UnkBullyScholarschip10;
				this->UnkBullyScholarschip11 = param.UnkBullyScholarschip11;
				this->UnkBullyScholarschip12 = param.UnkBullyScholarschip12;
				this->UnkBullyScholarschip13 = param.UnkBullyScholarschip13;

				this->TimeOn = param.TimeOn;
				this->TimeOff = param.TimeOff;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModelTimedObject::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (Game::GameSimple::IsGTAIIIeraGame(game))
			{
				if (this->ObjectCount == 1 && this->DrawDistance[0] >= 4.0)
				{
					return sprintf(line, "%d, %s, %s, %.17g, %d, %d, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->DrawDistance[0],
						this->Flags,
						this->TimeOn,
						this->TimeOff
						);
				}
				else if (this->ObjectCount == 1)
					return sprintf(line, "%d, %s, %s, %d, %.17g, %d, %d, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->ObjectCount,
						this->DrawDistance[0],
						this->Flags,
						this->TimeOn,
						this->TimeOff
						);
				else if (this->ObjectCount == 2)
					return sprintf(line, "%d, %s, %s, %d, %.17g, %.17g, %d, %d, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->ObjectCount,
						this->DrawDistance[0],
						this->DrawDistance[1],
						this->Flags,
						this->TimeOn,
						this->TimeOff
						);
				else if (this->ObjectCount == 3)
					return sprintf(line, "%d, %s, %s, %d, %.17g, %.17g, %.17g, %d, %d, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->ObjectCount,
						this->DrawDistance[0],
						this->DrawDistance[1],
						this->DrawDistance[2],
						this->Flags,
						this->TimeOn,
						this->TimeOff
						);
				else
					return 0;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %s, %d, %.17g, %d, %d, %.17g, %d, %d, %d, %d, %d, %d, %d",
					this->ModelID,
					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->ObjectCount,
					this->DrawDistance[0],
					this->Flags,
					this->UnkBullyScholarschip7,
					this->UnkBullyScholarschip8,
					this->UnkBullyScholarschip9,
					this->UnkBullyScholarschip10,
					this->UnkBullyScholarschip11,
					this->UnkBullyScholarschip12,
					this->UnkBullyScholarschip13,
					this->TimeOn,
					this->TimeOff
					);
			}
			else
				return 0;
		}
	}
}