/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementObjectInstance.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"

using namespace Game;

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementObjectInstance::InitValues()
		{
			this->CPlacementWithModel::InitValues();
			this->CollectibleName.Initialize("undefined");
			this->Flags = 0;
			this->InteriorNum = 0;
			this->Pos = { 0 };
			this->Scale = { 0 };
			this->Rot = { 0 };
			this->LODnum = -1;
			this->field_70_inBullyScholarchip = 0.0;
			this->UnknownParam11inGTAIV = -1;
			this->UnknownParam12inGTAIV = -1.0;
		}

		// Imports entry.
		unsigned __int32 CPlacementObjectInstance::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tInstParams param;

			if (game == GAME_SIMPLE_NAME_GTA_III || game == GAME_SIMPLE_NAME_GTA_VC)
			{
				param.fInteriorNum = 0.0;

				if ((game == GAME_SIMPLE_NAME_GTA_VC &&
					sscanf(xLine.c_str(), "%d %s %f %f %f %f %f %f %f %f %f %f %f",
						&param.ModelID,
						param.ModelName,
						&param.fInteriorNum,
						&this->Pos.x,
						&this->Pos.y,
						&this->Pos.z,
						&this->Scale.x,
						&this->Scale.y,
						&this->Scale.z,
						&this->Rot.imag.x,
						&this->Rot.imag.y,
						&this->Rot.imag.z,
						&this->Rot.real
						) != 13)
					|| game != GAME_SIMPLE_NAME_GTA_VC)
				{
					sscanf(xLine.c_str(), "%d %s %f %f %f %f %f %f %f %f %f %f",
						&param.ModelID,
						param.ModelName,
						&this->Pos.x,
						&this->Pos.y,
						&this->Pos.z,
						&this->Scale.x,
						&this->Scale.y,
						&this->Scale.z,
						&this->Rot.imag.x,
						&this->Rot.imag.y,
						&this->Rot.imag.z,
						&this->Rot.real
						);
				}

				this->ModelID = param.ModelID;
				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->InteriorNum = (int)param.fInteriorNum;				
			}
			else if (game == Game::GAME_SIMPLE_NAME_GTA_SA)
			{
				sscanf(xLine.c_str(), "%d %s %d %f %f %f %f %f %f %f %d",
					&param.ModelID,
					param.ModelName,
					&param.InteriorNum,
					&this->Pos.x,
					&this->Pos.y,
					&this->Pos.z,
					&this->Rot.imag.x,
					&this->Rot.imag.y,
					&this->Rot.imag.z,
					&this->Rot.real,
					&param.LODnum				
					);

				this->ModelID = param.ModelID;				
				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->InteriorNum = param.InteriorNum;
				this->LODnum = param.LODnum;
			}
			else if (game == Game::GAME_SIMPLE_NAME_GTA_IV)
			{
				param.UnknownParam12inGTAIV = -1.0;

				sscanf(xLine.c_str(), "%s %d %f %f %f %f %f %f %f %d %d %f",
					param.ModelName,
					&param.Flags,
					&this->Pos.x,
					&this->Pos.y,
					&this->Pos.z,
					&this->Rot.imag.x,
					&this->Rot.imag.y,
					&this->Rot.imag.z,
					&this->Rot.real,
					&param.LODnum,
					&param.UnknownParam11inGTAIV,
					&param.UnknownParam12inGTAIV
					);

				this->ModelID = param.ModelID;
				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->Flags = param.Flags;
				this->LODnum = param.LODnum;
				this->UnknownParam11inGTAIV = param.UnknownParam11inGTAIV;
				this->UnknownParam12inGTAIV = param.UnknownParam12inGTAIV;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %f %f %f %f %f %f %f %f %f %f %f %f %s",
					&param.ModelID,
					param.ModelName,
					&param.fInteriorNum,
					&this->Pos.x,
					&this->Pos.y,
					&this->Pos.z,
					&this->Scale.x,
					&this->Scale.y,
					&this->Scale.z,
					&this->Rot.imag.x,
					&this->Rot.imag.y,
					&this->Rot.imag.z,
					&this->Rot.real,
					&param.field_70_inBullyScholarchip,
					param.CollectibleName
					);

				this->ModelID = param.ModelID;
				this->ModelName.SetStringAndHash(game, param.ModelName);
				this->InteriorNum = (int)param.fInteriorNum;
				this->field_70_inBullyScholarchip = param.field_70_inBullyScholarchip;
				this->CollectibleName.SetStringAndHash(game, param.CollectibleName);
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CPlacementObjectInstance::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_III || game == GAME_SIMPLE_NAME_GTA_VC)
			{
				if (game == GAME_SIMPLE_NAME_GTA_VC && this->InteriorNum != 0)
					return sprintf(line, "%d, %s, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
						this->ModelID,
						this->ModelName.GetString().c_str(),
						(float)this->InteriorNum,
						this->Pos.x,
						this->Pos.y,
						this->Pos.z,
						this->Scale.x,
						this->Scale.y,
						this->Scale.z,
						this->Rot.imag.x,
						this->Rot.imag.y,
						this->Rot.imag.z,
						this->Rot.real
						);
				else
					return sprintf(line, "%d, %s, %f, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g",
						this->ModelID,
						this->ModelName.GetString().c_str(),
						this->Pos.x,
						this->Pos.y,
						this->Pos.z,
						this->Scale.x,
						this->Scale.y,
						this->Scale.z,
						this->Rot.imag.x,
						this->Rot.imag.y,
						this->Rot.imag.z,
						this->Rot.real
						);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_SA)
			{
				return sprintf(line, "%d, %s, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d",
					this->ModelID,
					this->ModelName.GetString().c_str(),
					this->InteriorNum,
					this->Pos.x,
					this->Pos.y,
					this->Pos.z,
					this->Rot.imag.x,
					this->Rot.imag.y,
					this->Rot.imag.z,
					this->Rot.real,
					this->LODnum
					);
			}
			else if (game == Game::GAME_SIMPLE_NAME_GTA_IV)
			{
				int l = sprintf(line, "%s, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d, %d",
					this->ModelName.GetString().c_str(),
					this->Flags,
					this->Pos.x,
					this->Pos.y,
					this->Pos.z,
					this->Rot.imag.x,
					this->Rot.imag.y,
					this->Rot.imag.z,
					this->Rot.real,
					this->LODnum,
					this->UnknownParam11inGTAIV
					);

				if (this->UnknownParam12inGTAIV != -1.0)
					l += sprintf(line + l, ", %.17g", this->UnknownParam12inGTAIV);

				return l;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s",
					this->ModelID,
					this->ModelName.GetString().c_str(),
					(float)this->InteriorNum,
					this->Pos.x,
					this->Pos.y,
					this->Pos.z,
					this->Scale.x,
					this->Scale.y,
					this->Scale.z,
					this->Rot.imag.x,
					this->Rot.imag.y,
					this->Rot.imag.z,
					this->Rot.real,
					this->field_70_inBullyScholarchip,
					this->CollectibleName.GetString().c_str()
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for each other string hash pair
		void CPlacementObjectInstance::ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData)
		{
			this->CPlacementWithModel::ForeachOtherStrHashPairs(func, pUserData);
			func(&this->CollectibleName, pUserData);
		}

		// Executes a function for 3D world position vectors
		void CPlacementObjectInstance::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementBaseInfo::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}