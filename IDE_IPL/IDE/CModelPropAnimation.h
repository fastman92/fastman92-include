/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModel3commonElements.h"
#include <string>

namespace File
{
	namespace IDE
	{
		class CModelPropAnimation : public CModel3commonElements
		{
		public:
			/// VARIABLES ///
			std::string AGRname;
			std::string PedAGRname;
			bool AlphaTest;
			int SecondaryCollisionModel;
			int ManualTargetLock;

			/// FUNCTIONS ///

			// Constructor
			CModelPropAnimation() : CModel3commonElements(SECTION_IDE_PANM) { this->InitValues(); };

			// Clone
			virtual CModelPropAnimation* clone() const { return new CModelPropAnimation(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelPropAnimation* ToModelPropAnimation()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelPropAnimation* ToModelPropAnimation() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}