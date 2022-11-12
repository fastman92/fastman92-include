/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CIPLorIDEentryBaseInfo.h"
#include "../CVector.h"
#include "../CRGBA.h"

namespace File
{
	class CModel2dEffect : public CIPLorIDEentryBaseInfo
	{
	public:
		// VARIABLES
		CVector Pos;
		CRGBA Color;
		int UnknownParam8inGTAIII_VC_BullyScholarschip;
		int EffectType;

		std::string Corona;
		std::string Shadow;
		float Distance;
		float OuterRange;
		float Size;
		float InnerRange;
		int ShadowIntensity;
		int Flash;
		int Wet;
		int Flare;
		int Flags;

		int UnknownParam17inBullyScholarschip;
		int UnknownParam18inBullyScholarschip;
		float UnknownParam19inBullyScholarschip;
		int UnknownParam20inBullyScholarschip;
		int UnknownParam21inBullyScholarschip;
		int UnknownParam22inBullyScholarschip;
		int UnknownParam23inBullyScholarschip;
		int UnknownParam24inBullyScholarschip;

		// FUNCTIONS

		// Constructor
		CModel2dEffect() : CIPLorIDEentryBaseInfo(SECTION_2DFX) { this->InitValues(); }

		// Clone
		virtual CModel2dEffect* clone() const { return new CModel2dEffect(*this); };

		// Sets default values
		virtual void InitValues();

		// Imports entry.
		virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

		// Exports entry. Returns length of output string.
		virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

		// Types
		virtual const CModel2dEffect* ToModel2dEffect()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual CModel2dEffect* ToModel2dEffect() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
	};
}