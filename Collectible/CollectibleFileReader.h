/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../SectionFile/CSectionFileReader.h"
#include "../SectionFile/CSectionFileElementBase.h"
#include "../SectionFile/CSectionFileReaderEx.h"
#include "CCollectible.h"

#include "eGame.h"

namespace File
{
	namespace Collectible
	{
		// Every data element will derive from CModelBaseInfo

		class CollectibleFileReader : public CSectionFileReaderEx
		{
		public:     			
			// Sets game version and registers sections.
			void SetGameVersion(Game::eGameName game);

			// Decodes section and calls ProcessModelEntry
			void DecodeCollectibleSection(tLineParsingInfo* pParsingInfo);
		};

		class CollectibleFileReaderEx : public CSectionFileReaderExLoader<CollectibleFileReader>
		{
		public:

			// Finds entry by hash
			CCollectible* FindEntryByHash(unsigned __int32 hash);
		};
	}
}