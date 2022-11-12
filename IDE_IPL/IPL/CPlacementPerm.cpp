/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementPerm.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Constructor
		CPlacementPerm::CPlacementPerm() : CPlacementBaseInfo(SECTION_IPL_PERM)
		{
			this->InitValues();
		}

		CPlacementPerm::CPlacementPerm(ePlacementPermEntryType PermEntryType) : CPlacementBaseInfo(SECTION_IPL_PERM)
		{
			this->PermEntryType = PermEntryType;
			this->InitValues();
		}

		// Sets default values
		void CPlacementPerm::InitValues()
		{
			this->CPlacementBaseInfo::InitValues();
		}

		// Imports entry.
		unsigned __int32 CPlacementPerm::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tPermParams param;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				float FloatValue;

				if (sscanf(xLine.c_str(), "%s %f %f %f",
					&param.UnknownParam1inBullyScholarschip,
					&param.UnknownParam2inBullyScholarschip,
					&param.UnknownParam3inBullyScholarschip,
					&param.UnknownParam4inBullyScholarschip
					) == 4)
				{
					this->PermEntryType = PLACEMENT_PERM_ENTRY_TYPE_HEADER;
					this->UnknownParam1inBullyScholarschip = param.UnknownParam1inBullyScholarschip;
					this->UnknownParam2inBullyScholarschip = param.UnknownParam2inBullyScholarschip;
					this->UnknownParam3inBullyScholarschip = param.UnknownParam3inBullyScholarschip;
					this->UnknownParam4inBullyScholarschip = param.UnknownParam4inBullyScholarschip;
				}
				else if (sscanf(xLine.c_str(), "%f", &FloatValue) == 1)
				{
					this->PermEntryType = PLACEMENT_PERM_ENTRY_TYPE_SUB_ENTRY;
					this->FloatValue = FloatValue;
				}
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementPerm::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				if (this->PermEntryType == PLACEMENT_PERM_ENTRY_TYPE_HEADER)
				{
					return sprintf(line, "%s, %.17g, %.17g, %.17g",
						this->UnknownParam1inBullyScholarschip.c_str(),
						this->UnknownParam2inBullyScholarschip,
						this->UnknownParam3inBullyScholarschip,
						this->UnknownParam4inBullyScholarschip
						);
				}
				else if(this->PermEntryType == PLACEMENT_PERM_ENTRY_TYPE_SUB_ENTRY)
					return sprintf(line, "%.17g",
						this->FloatValue
						);
			}

			*line = NULL;
			return 0;
		}

		// Returns rail entry type
		ePlacementPermEntryType CPlacementPerm::GetPermEntryType() const
		{
			return this->PermEntryType;
		}
	}
}