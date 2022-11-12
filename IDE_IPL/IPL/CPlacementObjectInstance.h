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
		struct tInstParams {
			unsigned __int32 ModelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			unsigned __int32 Flags;
			int InteriorNum;
			float fInteriorNum;
			int LODnum;
			float field_70_inBullyScholarchip;
			float UnknownParam12inGTAIV;
			int UnknownParam11inGTAIV;
			char CollectibleName[IMG_MAX_FILENAME_LENGTH + 1];
		};

		class CPlacementObjectInstance : public CPlacementWithModel
		{
		public:
			// VARIABLES
			CHashStrPair CollectibleName;

			unsigned __int32 Flags;
			int InteriorNum;
			CVector Pos;
			CVector Scale;
			CQuaternion Rot;
			float field_70_inBullyScholarchip;
			int LODnum;
			int UnknownParam11inGTAIV;
			float UnknownParam12inGTAIV;

			// FUNCTIONS

			// Constructor
			CPlacementObjectInstance() : CPlacementWithModel(SECTION_IPL_INST)
			{ this->InitValues(); }

			// Constructor
			CPlacementObjectInstance(eSectionType sectionType) : CPlacementWithModel(sectionType)
			{ this->InitValues(); }

			// Clone
			virtual CPlacementObjectInstance* clone() const { return new CPlacementObjectInstance(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for each other string hash pair
			virtual void ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Types
			virtual const CPlacementObjectInstance* ToPlacementObjectInstance()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementObjectInstance* ToPlacementObjectInstance() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}