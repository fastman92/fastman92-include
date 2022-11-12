/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementVehicleNode.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementVehicleNode::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
						
			this->Pos = { 0 };
			this->UnknownParam4inGTAIV = false;
			this->UnknownParam5inGTAIV = false;
			this->UnknownParam6inGTAIV = false;
			this->UnknownParam7inGTAIV = 0;
			this->UnknownParam8inGTAIV = 0;
			this->UnknownParam9inGTAIV = 0;
			this->UnknownParam10inGTAIV = 0;
			this->UnknownParam11inGTAIV = false;
			this->UnknownParam12inGTAIV = false;
			this->UnknownParam13inGTAIV = false;

		}

		// Imports entry.
		unsigned __int32 CPlacementVehicleNode::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct 
			{
				int UnknownParam4inGTAIV;
				int UnknownParam5inGTAIV;
				int UnknownParam6inGTAIV;
				int UnknownParam7inGTAIV;
				int UnknownParam8inGTAIV;
				float UnknownParam9inGTAIV;
				int UnknownParam10inGTAIV;
				int UnknownParam11inGTAIV;
				int UnknownParam12inGTAIV;
				int UnknownParam13inGTAIV;
			} param;
			
			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				param.UnknownParam9inGTAIV = 1.0;
				param.UnknownParam10inGTAIV = 0;
				param.UnknownParam11inGTAIV = 0;
				param.UnknownParam12inGTAIV = 0;
				param.UnknownParam13inGTAIV = 0;

				sscanf(xLine.c_str(), "%f %f %f %d %d %d %d %d %f %d %d %d %d",
					&this->Pos.x, &this->Pos.y, &this->Pos.z,
					&param.UnknownParam4inGTAIV,
					&param.UnknownParam5inGTAIV,
					&param.UnknownParam6inGTAIV,
					&param.UnknownParam7inGTAIV,
					&param.UnknownParam8inGTAIV,
					&param.UnknownParam9inGTAIV,
					&param.UnknownParam10inGTAIV,
					&param.UnknownParam11inGTAIV,
					&param.UnknownParam12inGTAIV,
					&param.UnknownParam13inGTAIV
					);

				this->UnknownParam4inGTAIV = param.UnknownParam4inGTAIV != 0;
				this->UnknownParam5inGTAIV = param.UnknownParam5inGTAIV != 0;
				this->UnknownParam6inGTAIV = param.UnknownParam6inGTAIV != 0;
				this->UnknownParam7inGTAIV = param.UnknownParam7inGTAIV;
				this->UnknownParam8inGTAIV = param.UnknownParam8inGTAIV;
				this->UnknownParam9inGTAIV = param.UnknownParam9inGTAIV;
				this->UnknownParam10inGTAIV = param.UnknownParam10inGTAIV;
				this->UnknownParam11inGTAIV = param.UnknownParam11inGTAIV != 0;
				this->UnknownParam12inGTAIV = param.UnknownParam12inGTAIV != 0;
				this->UnknownParam13inGTAIV = param.UnknownParam13inGTAIV != 0;
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementVehicleNode::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				
				return sprintf(line, "%.17g, %.17g, %.17g, %d, %d, %d, %d, %d, %.17g, %d, %d, %d, %d",
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->UnknownParam4inGTAIV,
					this->UnknownParam5inGTAIV,
					this->UnknownParam6inGTAIV,
					this->UnknownParam7inGTAIV,
					this->UnknownParam8inGTAIV,
					this->UnknownParam9inGTAIV,
					this->UnknownParam10inGTAIV,
					this->UnknownParam11inGTAIV,
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
		void CPlacementVehicleNode::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}