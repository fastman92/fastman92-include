/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModel2dEffect.h"
#include "../SectionFile/CSectionFileReader.h"
#include "../StrLexStuff.h"

using namespace Game;

namespace File
{
	// Sets default values
	void CModel2dEffect::InitValues()
	{
		this->CIPLorIDEentryBaseInfo::InitValues();
		this->Pos = { 0 };		
		memset(&this->Color, 0, sizeof(this->Color));
		this->UnknownParam8inGTAIII_VC_BullyScholarschip = 0;
		this->EffectType = 0;

		this->Corona = "coronastar";
		this->Shadow = "shad_exp";
		this->Distance = 0.0;
		this->OuterRange = 0.0;
		this->Size = 0.0;
		this->InnerRange = 0.0;
		this->ShadowIntensity = 0;
		this->Flash = 0;
		this->Wet = 0;
		this->Flare = 0;
		this->Flags = 0;

		this->UnknownParam17inBullyScholarschip = 0;
		this->UnknownParam18inBullyScholarschip = 0;
		this->UnknownParam19inBullyScholarschip = 0.0;
		this->UnknownParam20inBullyScholarschip = 0;
		this->UnknownParam21inBullyScholarschip = 0;
		this->UnknownParam22inBullyScholarschip = 0;
		this->UnknownParam23inBullyScholarschip = 0;
		this->UnknownParam24inBullyScholarschip = 0;
	}

	// Imports entry.
	unsigned __int32 CModel2dEffect::ImportEntry(Game::eGameNameSimplified game, const char* line)
	{
		this->InitValues();

		this->ImportedLine = line;
		std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

		struct
		{
			unsigned __int32 ModelID;

			CVector Pos;
			unsigned int ColorR;
			unsigned int ColorG;
			unsigned int ColorB;

			int UnknownParam8inBullyScholarschip;
			int EffectType;

			char Corona[32];
			char Shadow[32];
			char CoronaWithoutQuoteMarks[32];
			char ShadowWithoutQuoteMarks[32];
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
		} param;

		if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
		{
			sscanf(xLine.c_str(), "%d %f %f %f %d %d %d %d %d %s %s %f %f %f %f %d %d %d %f %d %d %d %d %d",
				&param.ModelID,

				&param.Pos.x, &param.Pos.y, &param.Pos.z,
				&param.ColorR, &param.ColorG, &param.ColorB,
				&param.UnknownParam8inBullyScholarschip,
				&param.EffectType,
				param.Corona,
				param.Shadow,
				&param.Distance,
				&param.OuterRange,
				&param.Size,
				&param.InnerRange,
				&param.ShadowIntensity,

				&param.UnknownParam17inBullyScholarschip,
				&param.UnknownParam18inBullyScholarschip,
				&param.UnknownParam19inBullyScholarschip,
				&param.UnknownParam20inBullyScholarschip,
				&param.UnknownParam21inBullyScholarschip,
				&param.UnknownParam22inBullyScholarschip,
				&param.UnknownParam23inBullyScholarschip,
				&param.UnknownParam24inBullyScholarschip
				);
				

			ReadAnyValue(param.CoronaWithoutQuoteMarks, sizeof(param.CoronaWithoutQuoteMarks), param.Corona, NULL);
			ReadAnyValue(param.ShadowWithoutQuoteMarks, sizeof(param.ShadowWithoutQuoteMarks), param.Shadow, NULL);

			this->ModelID = param.ModelID;
			this->Pos = param.Pos;
			this->Color.red = param.ColorR;
			this->Color.green = param.ColorG;
			this->Color.blue = param.ColorB;
			this->UnknownParam8inGTAIII_VC_BullyScholarschip = param.UnknownParam8inBullyScholarschip;
			this->EffectType = param.EffectType;
			this->Corona = param.CoronaWithoutQuoteMarks;
			this->Shadow = param.ShadowWithoutQuoteMarks;
			this->Distance = param.Distance;
			this->OuterRange = param.OuterRange;
			this->Size = param.Size;
			this->InnerRange = param.InnerRange;
			this->ShadowIntensity = param.ShadowIntensity;

			this->UnknownParam17inBullyScholarschip = param.UnknownParam17inBullyScholarschip;
			this->UnknownParam18inBullyScholarschip = param.UnknownParam18inBullyScholarschip;
			this->UnknownParam19inBullyScholarschip = param.UnknownParam19inBullyScholarschip;
			this->UnknownParam20inBullyScholarschip = param.UnknownParam20inBullyScholarschip;
			this->UnknownParam21inBullyScholarschip = param.UnknownParam21inBullyScholarschip;
			this->UnknownParam22inBullyScholarschip = param.UnknownParam22inBullyScholarschip;
			this->UnknownParam23inBullyScholarschip = param.UnknownParam23inBullyScholarschip;
			this->UnknownParam24inBullyScholarschip = param.UnknownParam24inBullyScholarschip;
		}

		return this->ModelID;
	}

	// Exports entry. Returns length of output string.
	int CModel2dEffect::ExportEntry(Game::eGameNameSimplified game, char* line)
	{
		if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
		{
			return sprintf(line, "%d, %.17g, %.17g, %.17g, %d, %d, %d, %d, %d, \"%s\", \"%s\", %.17g, %.17g, %.17g, %.17g, %d, %d, %d, %.17g, %d, %d, %d, %d, %d",
				this->ModelID,
				this->Pos.x, this->Pos.y, this->Pos.z,
				this->Color.red, this->Color.green, this->Color.blue,
				this->UnknownParam8inGTAIII_VC_BullyScholarschip,
				this->EffectType,
				this->Corona.c_str(),
				this->Shadow.c_str(),
				this->Distance,
				this->OuterRange,
				this->Size,
				this->InnerRange,
				this->ShadowIntensity,

				this->UnknownParam17inBullyScholarschip,
				this->UnknownParam18inBullyScholarschip,
				this->UnknownParam19inBullyScholarschip,
				this->UnknownParam20inBullyScholarschip,
				this->UnknownParam21inBullyScholarschip,
				this->UnknownParam22inBullyScholarschip,
				this->UnknownParam23inBullyScholarschip,
				this->UnknownParam24inBullyScholarschip
				);
		}

		*line = NULL;
		return 0;
	}
}