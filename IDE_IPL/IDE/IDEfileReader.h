/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../SectionFile/CSectionFileReader.h"
#include "../../SectionFile/CSectionFileElementBase.h"
#include "../IPLorIDEfileReaderEx.h"


#include "eGame.h"

namespace File
{
	namespace IDE
	{
		// Every data element will derive from CModelBaseInfo

		class IDEfileReaderEx : public IPLorIDEfileReaderEx<CSectionFileReaderExLoader<CSectionFileReaderEx>>
		{
		public:
			// Sets game version and registers sections.
			void SetGameVersion(Game::eGameName game);

			// Loads a binary file
			virtual bool LoadBinaryFile(const char* filename);

			// Saves a binary file
			virtual bool SaveBinaryFile(const char* filename);
		};
	}
}