/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModel3commonElements.h"
#include "../../IMG/IMGstructures.h"
#include <string>

namespace File
{
	namespace IDE
	{

		struct tPedsParams
		{
			unsigned __int32 ModelID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			char TXDname[IMG_MAX_FILENAME_LENGTH + 1];

			int IsFemale;
			char Size[32];
			char Props[64];
			char DefaultPedType[32];
			char PedStat[32];
			char AnimGroup[IMG_MAX_FILENAME_LENGTH + 1];
			char AnimGroup2[IMG_MAX_FILENAME_LENGTH + 1];
			char AnimGroup3[IMG_MAX_FILENAME_LENGTH + 1];
			char AnimGroup4[IMG_MAX_FILENAME_LENGTH + 1];
			char GestureGroup[64];
			char GesturePhoneGroup[64];
			char FacialGroup[64];
			char VisemeGroup[64];
			unsigned __int32 CarsCanDriveMask;
			unsigned __int32 Flags;
			char AnimFile[IMG_MAX_FILENAME_LENGTH + 1];
			char BlendshapeFile[64];
			int Radio1;
			int Radio2;
			char AudioPedType[32];
			char FirstVoice[64];
			char LastVoice[64];

			int Unique;
			char ActionTreeRoot[64];
			char ActionTreeFile[64];
			char AiTreeRoot[64];
			char AiTreeFile[64];
			char UnknownParam17inBullyScholarschip[64];
		};

		class CModelPed : public CModel3commonElements
		{
		public:
			/// VARIABLES ///
			bool IsFemale;
			std::string Size;
			std::string Props;
			std::string DefaultPedType;
			std::string PedStat;
			std::string AnimGroup;
			std::string AnimGroup2;
			std::string AnimGroup3;
			std::string AnimGroup4;
			std::string GestureGroup;
			std::string GesturePhoneGroup;
			std::string FacialGroup;
			std::string VisemeGroup;
			unsigned __int32 CarsCanDriveMask;
			unsigned __int32 Flags;
			std::string AnimFile;
			std::string BlendshapeFile;
			int Radio1;
			int Radio2;
			std::string AudioPedType;
			std::string FirstVoice;
			std::string LastVoice;

			int Unique;
			std::string ActionTreeRoot;
			std::string ActionTreeFile;
			std::string AiTreeRoot;
			std::string AiTreeFile;
			std::string UnknownParam17inBullyScholarschip;

			/// FUNCTIONS ///

			// Constructor
			CModelPed() : CModel3commonElements(SECTION_IDE_PANM) { this->InitValues(); };

			// Clone
			virtual CModelPed* clone() const { return new CModelPed(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelPed* ToModelPed()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelPed* ToModelPed() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}