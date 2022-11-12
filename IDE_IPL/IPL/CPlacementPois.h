/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPlacementWithModel.h"
#include "../../CVector.h"
#include "../../CQuaternion.h"

namespace File
{
	namespace IPL
	{
		struct tPoisParams
		{
			char UnknownHeaderParam1inBullyScholarschip[256];
			int32_t UnknownHeaderParam2inBullyScholarschip;
			uint32_t CountOfElements;

			char UnknownElementParam1inBullyScholarschip[256];
			char UnknownElementParam2inBullyScholarschip[256];
			char UnknownElementParam3inBullyScholarschip[256];
			char UnknownElementParam4inBullyScholarschip[256];
			int32_t UnknownElementParam5inBullyScholarschip;
			CVector Pos;
			CVector Rot;
			int32_t UnknownParamsFrom12inBullyScholarschip[11];
			float UnknownElementParam23inBullyScholarschip;
			int32_t UnknownElementParam24inBullyScholarschip;
			int32_t UnknownElementParam25inBullyScholarschip;
		};

		enum ePlacementPoisEntryType
		{
			PLACEMENT_POIS_ENTRY_TYPE_HEADER,
			PLACEMENT_POIS_ENTRY_TYPE_ELEMENT
		};

		class CPlacementPois : public CPlacementBaseInfo
		{
			ePlacementPoisEntryType PoisEntryType;

		public:
			// VARIABLES

			// if header
			std::string UnknownHeaderParam1inBullyScholarschip;
			int UnknownHeaderParam2inBullyScholarschip;

			// if element
			std::string UnknownElementParam1inBullyScholarschip;
			std::string UnknownElementParam2inBullyScholarschip;
			std::string UnknownElementParam3inBullyScholarschip;
			std::string UnknownElementParam4inBullyScholarschip;
			int UnknownElementParam5inBullyScholarschip;
			CVector Pos;
			CVector Rot;
			bool UnknownElementParam12inBullyScholarschip;
			bool UnknownElementParam13inBullyScholarschip;
			bool UnknownElementParam14inBullyScholarschip;
			bool UnknownElementParam15inBullyScholarschip;
			bool UnknownElementParam16inBullyScholarschip;
			bool UnknownElementParam17inBullyScholarschip;
			bool UnknownElementParam18inBullyScholarschip;
			bool UnknownElementParam19inBullyScholarschip;
			bool UnknownElementParam20inBullyScholarschip;
			bool UnknownElementParam21inBullyScholarschip;
			bool UnknownElementParam22inBullyScholarschip;
			float UnknownElementParam23inBullyScholarschip;
			bool UnknownElementParam24inBullyScholarschip;
			int32_t UnknownElementParam25inBullyScholarschip;

			// FUNCTIONS

			// Constructor
			CPlacementPois();

			// Constructor
			CPlacementPois(ePlacementPoisEntryType PoisEntryType);

			// Clone
			virtual CPlacementPois* clone() const { return new CPlacementPois(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Executes a function for 3D world position vectors
			virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData);

			// Returns pois entry type
			ePlacementPoisEntryType GetPoisEntryType() const;

			// Returns element's scope. 0 by default.
			virtual unsigned int GetElementScopeNumber() const;

			// Returns element's number of scopes
			virtual unsigned int GetElementNumberOfScopes() const;

			// Types
			virtual const CPlacementPois* ToPlacementPois()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementPois* ToPlacementPois() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}