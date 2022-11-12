/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModelBaseInfo.h"
#include "CModel3commonElements.h"
#include <string>

namespace File
{
	namespace IDE
	{
		class CModel3commonElements : public CModelBaseInfo
		{
		public:
			// VARIABLES

			// Model name
			std::string ModelName;

			// TXD name
			std::string TXDname;

			// FUNCTIONS

			// Constructor
			CModel3commonElements(eSectionType type) : CModelBaseInfo(type) { this->InitValues(); }

			// Clone
			virtual CModel3commonElements* clone() const { return new CModel3commonElements(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModel3commonElements* ToModel3commonElements()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModel3commonElements* ToModel3commonElements() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}