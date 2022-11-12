/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../eGame.h"
#include "../SectionFile/CSectionFileElementBaseEx.h"

#include <string>

namespace File
{
	namespace Collectible
	{
		// Forward declarations

		class CCollectible : public CSectionFileElementBaseEx
		{
		public:
			// VARIABLES
			CHashStrPair CollectibleName;
		
			// Constructor
			CCollectible(int type) : CSectionFileElementBaseEx(SECTION_FILE_ELEMENT_TYPE_DATA, type) { this->InitValues(); }

			// Clone
			virtual CCollectible* clone() const { return new CCollectible(*this); };

			//// Virtual functions ////

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);
		};
	}
}