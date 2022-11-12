/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModelBaseInfo.h"
#include <string>

namespace File
{
	namespace IDE
	{
		class CModelTXDparent : public CModelBaseInfo
		{
		public:
			// VARIABLES
			std::string TextureName;
			std::string TextureParentName;

			// FUNCTIONS

			// Constructor
			CModelTXDparent() : CModelBaseInfo(SECTION_IDE_TXDP){ this->InitValues(); }

			// Clone
			virtual CModelTXDparent* clone() const { return new CModelTXDparent(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelTXDparent* ToTXDparent()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelTXDparent* ToTXDparent()    { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}