/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModelObject.h"

namespace File
{
	namespace IDE
	{
		class CModelTimedObject : public CModelObject
		{
		public:
			// VARIABLES
			int TimeOn;
			int TimeOff;

			// FUNCTIONS

			// Constructor
			CModelTimedObject() : CModelObject(SECTION_IDE_TOBJ){ this->InitValues(); }

			// Clone
			virtual CModelTimedObject* clone() const { return new CModelTimedObject(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelTimedObject* ToModelTimedObject()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelTimedObject* ToModelTimedObject() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}