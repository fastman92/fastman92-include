/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		struct tPermParams
		{
			char UnknownParam1inBullyScholarschip[256];
			float UnknownParam2inBullyScholarschip;
			float UnknownParam3inBullyScholarschip;
			float UnknownParam4inBullyScholarschip;
		};

		enum ePlacementPermEntryType
		{
			PLACEMENT_PERM_ENTRY_TYPE_HEADER,
			PLACEMENT_PERM_ENTRY_TYPE_SUB_ENTRY
		};

		class CPlacementPerm : public CPlacementBaseInfo
		{
			ePlacementPermEntryType PermEntryType;

		public:
			// VARIABLES

			// if header
			std::string UnknownParam1inBullyScholarschip;
			float UnknownParam2inBullyScholarschip;
			float UnknownParam3inBullyScholarschip;
			float UnknownParam4inBullyScholarschip;

			// if sub-entry
			float FloatValue;

			// FUNCTIONS

			// Constructor
			CPlacementPerm();

			// Constructor
			CPlacementPerm(ePlacementPermEntryType PermEntryType);

			// Clone
			virtual CPlacementPerm* clone() const { return new CPlacementPerm(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Returns rail entry type
			ePlacementPermEntryType GetPermEntryType() const;

			// Types
			virtual const CPlacementPerm* ToPlacementPerm()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementPerm* ToPlacementPerm() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}