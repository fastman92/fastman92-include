/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CCollectible.h"

namespace File
{
	namespace Collectible
	{
		// Sets default values
		void CCollectible::InitValues()
		{
			this->CSectionFileElementBaseEx::InitValues();
			this->CollectibleName.Initialize("undefined");
		}

		// Imports entry.
		unsigned __int32 CCollectible::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();
			this->ImportedLine = line;

			char collectibleName[128];
			sscanf(line, "%s", collectibleName);

			this->CollectibleName.SetStringAndHash(game, collectibleName);

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CCollectible::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			return sprintf(line, "%s", this->CollectibleName.GetString().c_str());
		}
	}
}