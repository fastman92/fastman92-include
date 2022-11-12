/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementProp.h"
#include "../../IMG/IMGstructures.h"
#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementProp::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
			this->PropName = "undefined";
		}

		// Imports entry.
		unsigned __int32 CPlacementProp::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();
			this->ImportedLine = line;

			char name[128];
			sscanf(line, "%s", name);

			this->PropName = name;

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementProp::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			return sprintf(line, "%s", this->PropName.c_str());
		}
	}
}