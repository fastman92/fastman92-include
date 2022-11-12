/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../SectionFile/CSectionFileReader.h"
#include "../../SectionFile/CSectionFileElementBase.h"
#include "../IPLorIDEfileReaderEx.h"
#include "../../Collectible/CollectibleFileReader.h"
#include "../../eGame.h"

namespace File
{
	namespace IPL
	{
		// Every data element will derive from CPlacementBaseInfo
		class IPLfileReaderEx : public IPLorIDEfileReaderEx<CSectionFileReaderExLoader<CSectionFileReaderEx>>
		{
			friend void AddBullyEntry(
			struct tBinarySectionBullyScholarshipUserData* pUserData,
			class CSectionFileElementBase* ptr
				);

		private:
			bool bUpdateLODindicesWhenLoading;
			int LODbaseIndex;

			// Set LOD base index
			void SetLODbaseIndex();

			// Registers unsupported section
			void RegisterUnsupportedSection(const char* name, int type);
			
		protected:
			// Process model info
			virtual void ProcessEntry(CSectionFileElementBase* pElement);

		public:
			Collectible::CollectibleFileReaderEx* pCollectibleFileReader;

			// Constructor
			IPLfileReaderEx();

			// Registers collectible file reader
			void RegisterCollectibleFileReader(Collectible::CollectibleFileReaderEx* pCollectibleFileReader);

			// Enables/disables updating of LOD indices when loading
			void EnableUpdatingOfLODindicesWhenLoading(bool bEnable);

			// Loads file
			virtual bool LoadFile(const char* filename);

			// Loads a binary file
			virtual bool LoadBinaryFile(const char* filename);

			// Saves a binary file
			virtual bool SaveBinaryFile(const char* filename);

			// Sets game version and registers sections.
			void SetGameVersion(Game::eGameName game);
		};
	}
}