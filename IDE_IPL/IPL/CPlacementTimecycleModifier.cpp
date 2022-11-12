/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementTimecycleModifier.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementTimecycleModifier::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
						
			this->Box = { 0 };
			this->UnknownParam7inGTAIV = 0.0;
			this->UnknownParam8inGTAIV = 0.0;
			this->UnknownParam9inGTAIV = 0;
			this->UnknownParam10inGTAIV = 0;
			this->ModifierName.Initialize("undefined");
		}

		// Imports entry.
		unsigned __int32 CPlacementTimecycleModifier::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct
			{
				float UnknownParam7inGTAIV;
				float UnknownParam8inGTAIV;
				int UnknownParam9inGTAIV;
				int UnknownParam10inGTAIV;
				char ModifierName[128];
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%f %f %f %f %f %f %f %f %d %d %s",
					&this->Box.m_vInf.x, &this->Box.m_vInf.y, &this->Box.m_vInf.z,
					&this->Box.m_vSup.x, &this->Box.m_vSup.y, &this->Box.m_vSup.z,
					&param.UnknownParam7inGTAIV,
					&param.UnknownParam8inGTAIV,
					&param.UnknownParam9inGTAIV,
					&param.UnknownParam10inGTAIV,
					param.ModifierName
					);

				this->UnknownParam7inGTAIV = param.UnknownParam7inGTAIV;
				this->UnknownParam8inGTAIV = param.UnknownParam8inGTAIV;
				this->UnknownParam9inGTAIV = param.UnknownParam9inGTAIV;
				this->UnknownParam10inGTAIV = param.UnknownParam10inGTAIV;
				this->ModifierName.SetStringAndHash(game, param.ModifierName);
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementTimecycleModifier::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d, %d, %s",
					this->Box.m_vInf.x, this->Box.m_vInf.y, this->Box.m_vInf.z,
					this->Box.m_vSup.x, this->Box.m_vSup.y, this->Box.m_vSup.z,
					this->UnknownParam7inGTAIV,
					this->UnknownParam8inGTAIV,
					this->UnknownParam9inGTAIV,
					this->UnknownParam10inGTAIV,
					this->ModifierName.GetString().c_str()
					);				
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementTimecycleModifier::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Box.m_vInf, pUserData);
			func(&this->Box.m_vSup, pUserData);
		}

		// Executes a function for each other string hash pair
		void CPlacementTimecycleModifier::ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::ForeachOtherStrHashPairs(func, pUserData);
			func(&this->ModifierName, pUserData);
		}
	}
}