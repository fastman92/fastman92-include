/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelTXDparent.h"
#include "../../SectionFile/CSectionFileReader.h"
#include "../../IMG/IMGstructures.h"

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModelTXDparent::InitValues()
		{
			this->CModelBaseInfo::InitValues();
			this->TextureName.clear();
			this->TextureParentName.clear();
		}

		// Imports entry.
		unsigned __int32 CModelTXDparent::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			char name[IMG_MAX_FILENAME_LENGTH + 1];
			char parentName[IMG_MAX_FILENAME_LENGTH + 1];

			this -> ImportedLine = line;

			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			sscanf(xLine.c_str(), "%s %s", name, parentName);

			this -> TextureName = name;
			this -> TextureParentName = parentName;

			return -1;	// no ID
		}

		// Exports entry. Returns length of output string.
		int CModelTXDparent::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			return sprintf(line, "%s, %s", this -> TextureName.c_str(), this -> TextureParentName.c_str());
		}
	}
}