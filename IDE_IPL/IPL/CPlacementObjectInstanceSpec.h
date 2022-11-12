/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementObjectInstance.h"
#include "../../CVector.h"
#include "../../IMG/IMGstructures.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		class CPlacementObjectInstanceSpec : public CPlacementObjectInstance
		{
		public:
			// VARIABLES
			CHashStrPair AreaName;
			int AreaType;

			// FUNCTIONS

			// Constructor
			CPlacementObjectInstanceSpec() : CPlacementObjectInstance(SECTION_IPL_SPEC)
			{
				this->InitValues();
			}

			// Clone
			virtual CPlacementObjectInstanceSpec* clone() const { return new CPlacementObjectInstanceSpec(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for each other string hash pair
			virtual void ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData);

			// Types
			virtual const CPlacementObjectInstanceSpec* ToPlacementObjectInstanceSpec()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementObjectInstanceSpec* ToPlacementObjectInstanceSpec() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}