/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPlacementCarGenerator.h"

#include "../../SectionFile/CSectionFileReader.h"
#include "../../Hashing/Hashing.h"
#include "../../IMG/IMGstructures.h"

using namespace Game;

#ifndef M_PI
#define M_PI       3.14159265358979323846   // pi
#endif

namespace File
{
	namespace IPL
	{
		// Sets default values
		void CPlacementCarGenerator::InitValues()
		{
			this->CPlacementWithModel::InitValues();
						
			this->Pos = { 0 };
			this->Rot = { 0 };
			this->AngleInRadians = 0.0;
			this->PrimCol = 0;
			this->SecCol = 0;
			this->ThirdColor = 0;
			this->SpecularColor = 0;
			this->Flags = 0;
			this->AlarmProbability = 0;
			this->DoorLockProbability = 0;
			this->MinDelay = 0;
			this->MaxDelay = 0;
		}

		// Imports entry.
		unsigned __int32 CPlacementCarGenerator::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			struct 
			{
				unsigned __int32 ModelNameHash;
				unsigned __int32 ModelID;
				float AngleInRadians;
				unsigned int PrimCol;
				unsigned int SecCol;
				unsigned int ThirdColor;
				unsigned int SpecularColor;
				unsigned __int32 Flags;
				unsigned int AlarmProbability;
				unsigned int DoorLockProbability;
				int MinDelay;
				int MaxDelay;
			} param;

			if (game == GAME_SIMPLE_NAME_GTA_SA)
			{
				sscanf(xLine.c_str(), "%f %f %f %f %d %d %d %d %d %d %d %d",
					&this->Pos.x, &this->Pos.y, &this->Pos.z,
					&param.AngleInRadians,
					&param.ModelID,
					&param.PrimCol,
					&param.SecCol,
					&param.Flags,
					&param.AlarmProbability,
					&param.DoorLockProbability,
					&param.MinDelay,
					&param.MaxDelay
					);
				
				
				this->AngleInRadians = param.AngleInRadians;
				this->ModelID = param.ModelID;
				this->PrimCol = param.PrimCol;
				this->SecCol = param.SecCol;
				this->Flags = param.Flags;
				this->AlarmProbability = param.AlarmProbability;
				this->DoorLockProbability = param.DoorLockProbability;
				this->MinDelay = param.MinDelay;
				this->MaxDelay = param.MaxDelay;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%f %f %f %f %f %f %d %d %d %d %d %d %d %d",
					&this->Pos.x, &this->Pos.y, &this->Pos.z,
					&this->Rot.x, &this->Rot.y, &this->Rot.z,
					&param.ModelNameHash,
					&param.PrimCol,
					&param.SecCol,
					&param.ThirdColor,
					&param.SpecularColor,
					&param.Flags,
					&param.AlarmProbability,
					&param.DoorLockProbability
					);

				this->ModelName.SetHashAndString(game, param.ModelNameHash);
				this->PrimCol = param.PrimCol;
				this->SecCol = param.SecCol;
				this->ThirdColor = param.ThirdColor;
				this->SpecularColor = param.SpecularColor;
				this->Flags = param.Flags;
				this->AlarmProbability = param.AlarmProbability;
				this->DoorLockProbability = param.DoorLockProbability;				
			}

			return -1;
		}

		// Exports entry. Returns length of output string.
		int CPlacementCarGenerator::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_SA)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %d, %d, %d, %d, %d, %d, %d, %d",
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->AngleInRadians,
					this->ModelID,
					this->PrimCol,
					this->SecCol,
					this->Flags,
					this->AlarmProbability,
					this->DoorLockProbability,
					this->MinDelay,
					this->MaxDelay
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %d, %d, %d, %d, %d, %d, %d, %d",
					this->Pos.x, this->Pos.y, this->Pos.z,
					this->Rot.x, this->Rot.y, this->Rot.z,
					this->ModelName.GetHash(),
					this->PrimCol,
					this->SecCol,
					this->ThirdColor,
					this->SpecularColor,
					this->Flags,
					this->AlarmProbability,
					this->DoorLockProbability
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Executes a function for 3D world position vectors
		void CPlacementCarGenerator::Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData)
		{
			this->CPlacementWithModel::Foreach3DworldPositions(func, pUserData);
			func(&this->Pos, pUserData);
		}
	}
}