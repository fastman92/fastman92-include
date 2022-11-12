/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelPropAnimation.h"
#include "../../SectionFile/CSectionFileReader.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModelPropAnimation::InitValues()
		{
			this->CModel3commonElements::InitValues();
			this->AGRname = "null";
			this->PedAGRname = "null";
			this->AlphaTest = false;
			this->SecondaryCollisionModel = 0;
			this->ManualTargetLock = 0;
		}
		 
		// Imports entry.
		unsigned __int32 CModelPropAnimation::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct param
			{
				unsigned __int32 ModelID;
				char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
				char TXDname[IMG_MAX_FILENAME_LENGTH + 1];

				char AGRname[IMG_MAX_FILENAME_LENGTH + 1];
				char PedAGRname[IMG_MAX_FILENAME_LENGTH + 1];
				int AlphaTest;
				int SecondaryCollisionModel;
				int ManualTargetLock;
			} param;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %d %d %d",
					&param.ModelID,

					param.ModelName,
					param.TXDname,
					param.AGRname,
					param.PedAGRname,

					&param.AlphaTest,
					&param.SecondaryCollisionModel,
					&param.ManualTargetLock
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;

				this->AGRname = param.AGRname;
				this->PedAGRname = param.PedAGRname;
				this->AlphaTest = param.AlphaTest != 0;
				this->SecondaryCollisionModel = param.SecondaryCollisionModel;
				this->ManualTargetLock = param.ManualTargetLock;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModelPropAnimation::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %s, %s, %s, %d, %d, %d",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->AGRname.c_str(),
					this->PedAGRname.c_str(),

					this->AlphaTest,
					this->SecondaryCollisionModel,
					this->ManualTargetLock
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