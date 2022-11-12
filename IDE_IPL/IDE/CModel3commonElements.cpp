/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelCash.h"
#include "../../SectionFile/CSectionFileReader.h"
#include "../../IMG/IMGstructures.h"

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModel3commonElements::InitValues()
		{
			this->CModelBaseInfo::InitValues();
			this->ModelName = "undefined";
			this->TXDname = "undefined";
		}

		// Imports entry.
		unsigned __int32 CModel3commonElements::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();
			this->ImportedLine = line;

			unsigned __int32 modelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			char TXDname[IMG_MAX_FILENAME_LENGTH + 1];
	
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			sscanf(xLine.c_str(), "%d %s %s", &modelID, ModelName, TXDname);

			this->ModelID = modelID;
			this->ModelName = ModelName;
			this->TXDname = TXDname;

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModel3commonElements::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			return sprintf(line, "%d, %s, %s", this->ModelID, this->ModelName.c_str(), this->TXDname.c_str());
		}
	}
}