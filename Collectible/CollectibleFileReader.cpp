/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CollectibleFileReader.h"

#include "../fileIO.h"

#include <stdio.h>

using namespace Game;

namespace File
{
	namespace Collectible
	{
		// Sets game version and registers sections.
		void CollectibleFileReader::SetGameVersion(Game::eGameName game)
		{
			this->ClearSections();

			this->m_gameInfo = Game::GetSimpleGameAndPlatformByExactMember(game);
			Game::eGameNameSimplified gameSimple = this->m_gameInfo.gameSimple;
		
			if (gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				static const char* sectionNames[] =
				{
					"Gnome",
					"Radio",
					"RubberBand",
					"GG_Card",
					"Pumpkin",
					"Tombstone",
					"Artifact"
				};

				for (int i = 0; i < _countof(sectionNames); i++)
					this->RegisterSection(
						sectionNames[i],
						i + 1,
						static_cast<tSectionFunc>(&CollectibleFileReader::DecodeCollectibleSection)
						);
			}
		}

		// Decodes section and calls ProcessModelEntry
		void CollectibleFileReader::DecodeCollectibleSection(tLineParsingInfo* pParsingInfo)
		{
			CCollectible object(this->m_pCurSectionInfo->typeID);

			object.SetReaderPointer(this);
			object.ImportEntry(this->m_gameInfo.gameSimple, pParsingInfo->pLine);

			this->ProcessEntry(&object);
		}

		// Finds entry by hash
		CCollectible* CollectibleFileReaderEx::FindEntryByHash(unsigned __int32 hash)
		{
			for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
			{
				CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData();

				if (!pSection)
					continue;

				for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
				{
					if (!secondIt->IsData())
						continue;

					CCollectible* pElement = (CCollectible*)&*secondIt;					

					if (!pElement)
						continue;

					if (pElement->CollectibleName.GetHash() == hash)
						return pElement;
				}
			}


			return NULL;
		}
	}
}