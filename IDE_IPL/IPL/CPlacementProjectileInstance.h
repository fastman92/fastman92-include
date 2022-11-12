/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"
#include "../../IMG/IMGstructures.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		struct tProjParams {
			unsigned __int32 ModelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			float UnknownParam3inGTAIV;
		};

		class CPlacementProjectileInstance : public CPlacementWithModel
		{
		public:
			// VARIABLES
			float UnknownParam3inBullyScholarschip;
			CVector Pos;
			CVector Scale;
			CVector Rot;

			// FUNCTIONS

			// Constructor
			CPlacementProjectileInstance() : CPlacementWithModel(SECTION_IPL_PROJ)
			{ this->InitValues(); }

			// Clone
			virtual CPlacementProjectileInstance* clone() const { return new CPlacementProjectileInstance(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementProjectileInstance* ToPlacementProjectileInstance()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementProjectileInstance* ToPlacementProjectileInstance() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}