/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementSlow.h"

#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementSlow::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
						
			this->Box = { 0 };
		}

		// Imports entry.
		unsigned __int32 CPlacementSlow::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%f %f %f %f %f %f",
					&this->Box.m_vInf.x, &this->Box.m_vInf.y, &this->Box.m_vInf.z,
					&this->Box.m_vSup.x, &this->Box.m_vSup.y, &this->Box.m_vSup.z
					);
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementSlow::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
					this->Box.m_vInf.x, this->Box.m_vInf.y, this->Box.m_vInf.z,
					this->Box.m_vSup.x, this->Box.m_vSup.y, this->Box.m_vSup.z
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementSlow::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Box.m_vInf, pUserData);
			func(&this->Box.m_vSup, pUserData);
		}
	}
}