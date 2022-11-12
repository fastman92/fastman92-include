/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModel3commonElements.h"
#include <string>
#include "../../IMG/IMGstructures.h"

namespace File
{
	namespace IDE
	{
		struct tWeapParams
		{
			unsigned __int32 ModelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			char TXDname[IMG_MAX_FILENAME_LENGTH + 1];
			char Anim1[IMG_MAX_FILENAME_LENGTH + 1];
			char Anim2[IMG_MAX_FILENAME_LENGTH + 1];
			unsigned int ObjectCount;
			float DrawDistance;
			unsigned __int32 Flags;

			// Unknowns
			int UnkBullyScholarschip8;
			int UnkBullyScholarschip9;
		};

		class CModelWeapon : public CModel3commonElements
		{
		public:
			// Anims
			std::string Anim1;
			std::string Anim2;

			// Object count
			unsigned __int32 ObjectCount;

			// Draw distance for each clump
			float DrawDistance[1];

			// Unknowns
			int UnkBullyScholarschip8;
			int UnkBullyScholarschip9;

			// Flags
			int Flags;

			/// FUNCTIONS ///

			// Constructor
			CModelWeapon() : CModel3commonElements(SECTION_IDE_WEAP){ this->InitValues(); };

			// Clone
			virtual CModelWeapon* clone() const { return new CModelWeapon(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelWeapon* ToModelWeapon()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelWeapon* ToModelWeapon()    { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}