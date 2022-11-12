/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModel3commonElements.h"
#include "CModelTXDparent.h"
#include "../../CVector.h"
#include "../../IMG/IMGstructures.h"

#include <string>

namespace File
{
	namespace IDE
	{
		struct tObjsParams {
			unsigned __int32 ModelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			char TXDname[IMG_MAX_FILENAME_LENGTH + 1];
			unsigned __int32 Flags;
			float DrawDistance;
			float UnkGTAIV_5;

			//  Lower left corner of the bounding box for the object. 
			CVector Min;

			// Upper right corner of the bounding box for the object.
			CVector Max;

			// Center of the bounding sphere for the object. 
			CVector Sphere;

			float Radius;
			char LODmodelName[IMG_MAX_FILENAME_LENGTH + 1];

			// Bully scholarschip
			int UnkBullyScholarschip7;
			float UnkBullyScholarschip8;
			int UnkBullyScholarschip9;
			int UnkBullyScholarschip10;
			int UnkBullyScholarschip11;
			int UnkBullyScholarschip12;
			int UnkBullyScholarschip13;
		};

		class CModelObject : public CModel3commonElements
		{
		public:
			// VARIABLES

			// Object count
			unsigned __int32 ObjectCount;

			// Draw distance for each clump
			float DrawDistance[3];

			// Flags
			unsigned __int32 Flags;

			// Unknown parameter 5
			float UnkGTAIV_5;

			//  Lower left corner of the bounding box for the object. 
			CVector Min;

			// Upper right corner of the bounding box for the object.
			CVector Max;

			// Center of the bounding sphere for the object. 
			CVector Sphere;

			// Radius
			float Radius;

			// LOD model
			std::string LODmodelName;


			// Bully scholarschip
			int UnkBullyScholarschip7;
			float UnkBullyScholarschip8;
			int UnkBullyScholarschip9;
			int UnkBullyScholarschip10;
			int UnkBullyScholarschip11;
			int UnkBullyScholarschip12;
			int UnkBullyScholarschip13;

			// FUNCTIONS

			// Constructor
			CModelObject() : CModel3commonElements(SECTION_IDE_OBJS){ this->InitValues(); }
			CModelObject(eSectionType type) : CModel3commonElements(type) { }

			// Clone
			virtual CModelObject* clone() const { return new CModelObject(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelObject* ToModelObject()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelObject* ToModelObject() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}