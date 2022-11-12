/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "../../SectionFile/CSectionFileReader.h"
#include "CModelObject.h"


using namespace Game;

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModelObject::InitValues()
		{
			this->CModelBaseInfo::InitValues();
			this->ObjectCount = 1;
			memset(this->DrawDistance, NULL, sizeof(this->DrawDistance));
			this->Flags = 0;
			this->UnkGTAIV_5 = 0.0;
			this->Min = { 0 };
			this->Max = { 0 };
			this->Sphere = { 0 };
			this->Radius = 0.0;
			this->LODmodelName = "null";
			this->UnkBullyScholarschip7 = 0;
			this->UnkBullyScholarschip8 = 0;
			this->UnkBullyScholarschip9 = 0;
			this->UnkBullyScholarschip10 = 0;
			this->UnkBullyScholarschip11 = 0;
			this->UnkBullyScholarschip12 = 0;
			this->UnkBullyScholarschip13 = 0;
		}

		// Imports entry.
		unsigned __int32 CModelObject::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tObjsParams param;

			if (game == Game::GAME_SIMPLE_NAME_GTA_IV)
			{
				this->ObjectCount = 1;

				if (sscanf(
					xLine.c_str(),
					"%s %s %f %d %f %f %f %f %f %f %f %f %f %f %f %s",
					param.ModelName,
					param.TXDname,
					&param.DrawDistance,
					&param.Flags,
					&param.UnkGTAIV_5,
					&param.Min.x,
					&param.Min.y,
					&param.Min.z,
					&param.Max.x,
					&param.Max.y,
					&param.Max.z,
					&param.Sphere.x,
					&param.Sphere.y,
					&param.Sphere.z,
					&param.Radius,
					param.LODmodelName) == 16)
				{
					this->ModelName = param.ModelName;
					this->TXDname = param.TXDname;
					this->DrawDistance[0] = param.DrawDistance;	
					this->Flags = param.Flags;
					this->UnkGTAIV_5 = param.UnkGTAIV_5;
					this->Min = param.Min;
					this->Max = param.Max;
					this->Sphere = param.Sphere;
					this->Radius = param.Radius;
					this->LODmodelName = param.LODmodelName;
				}
				else
				{
					param.Radius = 0.0;
					param.LODmodelName[0] = NULL;

					int numRead = sscanf(
						xLine.c_str(),
						"%s %s %f %d %f %f %f %f %f %f %f %f %f %f %s",
						param.ModelName,
						param.TXDname,
						&param.DrawDistance,
						&param.Flags,
						&param.Min.x,
						&param.Min.y,
						&param.Min.z,
						&param.Max.x,
						&param.Max.y,
						&param.Max.z,
						&param.Sphere.x,
						&param.Sphere.y,
						&param.Sphere.z,
						&param.Radius,
						param.LODmodelName);

					
					this->ModelName = param.ModelName;
					this->TXDname = param.TXDname;
					this->DrawDistance[0] = param.DrawDistance;
					this->Flags = param.Flags;

					if (numRead >= 14)
					{
						this->Min = param.Min;
						this->Max = param.Max;
						this->Sphere = param.Sphere;
						this->Radius = param.Radius;
						this->LODmodelName = param.LODmodelName;
					}
				}
			}
			else if (Game::GameSimple::IsGTAIIIeraGame(game))
			{
				this->ObjectCount = 1;

				if (sscanf(xLine.c_str(), "%d %s %s %f %d", &param.ModelID, param.ModelName, param.TXDname, this->DrawDistance, &this->Flags) != 5
					|| this->DrawDistance[0] <= 4.0
					)
				{
					if (sscanf(xLine.c_str(), "%d %s %s %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount) != 4)
						return -1;

					switch (this->ObjectCount)
					{
					case 1:
						sscanf(xLine.c_str(), "%d %s %s %d %f %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, this->DrawDistance, &this->Flags);
						break;
					case 2:
						sscanf(xLine.c_str(), "%d %s %s %d %f %f %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, this->DrawDistance, this->DrawDistance + 1, &this->Flags);
						break;
					case 3:
						sscanf(xLine.c_str(), "%d %s %s %d %f %f %f %d", &param.ModelID, param.ModelName, param.TXDname, &this->ObjectCount, this->DrawDistance, this->DrawDistance + 1, this->DrawDistance + 2, &this->Flags);
						break;
					}
				}

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{				
				sscanf(xLine.c_str(), "%d %s %s %d %f %d %d %f %d %d %d %d %d",
					&param.ModelID,
					param.ModelName,
					param.TXDname,
					&this->ObjectCount,
					this->DrawDistance,
					&this->Flags,					
					&param.UnkBullyScholarschip7,
					&param.UnkBullyScholarschip8,
					&param.UnkBullyScholarschip9,
					&param.UnkBullyScholarschip10,
					&param.UnkBullyScholarschip11,
					&param.UnkBullyScholarschip12,
					&param.UnkBullyScholarschip13
				);
				
				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;

				this->UnkBullyScholarschip7 = param.UnkBullyScholarschip7;
				this->UnkBullyScholarschip8 = param.UnkBullyScholarschip8;
				this->UnkBullyScholarschip9 = param.UnkBullyScholarschip9;
				this->UnkBullyScholarschip10 = param.UnkBullyScholarschip10;
				this->UnkBullyScholarschip11 = param.UnkBullyScholarschip11;
				this->UnkBullyScholarschip12 = param.UnkBullyScholarschip12;
				this->UnkBullyScholarschip13 = param.UnkBullyScholarschip13;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModelObject::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			*line = NULL;

			if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				if (this->UnkGTAIV_5 == 0.0
					&& this->Min.x == 0.0 && this->Min.y == 0.0 && this->Min.z == 0.0
					&& this->Max.x == 0.0 && this->Max.y == 0.0 && this->Max.z == 0.0
					&& this->Sphere.x == 0.0 && this->Sphere.y == 0.0 && this->Sphere.z == 0.0
					&& this->Radius == 0.0
					&& (this->LODmodelName == "null" || this->LODmodelName.empty())
					)
				{
					return sprintf(line, "%s, %s, %.17g, %d",
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->DrawDistance[0],
						this->Flags
						);
				}
				else if (this->UnkGTAIV_5 == 0.0)
				{
					return sprintf(line, "%s, %s, %.17g, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s",
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->DrawDistance[0],
						this->Flags,
						this->Min.x,
						this->Min.y,
						this->Min.z,
						this->Max.x,
						this->Max.y,
						this->Max.z,
						this->Sphere.x,
						this->Sphere.y,
						this->Sphere.z,
						this->Radius,
						this->LODmodelName.c_str()
						);
				}
				else
				{
					return sprintf(line, "%s, %s, %.17g, %d, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %.17g, %s",
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->DrawDistance[0],
						this->Flags,
						this->UnkGTAIV_5,
						this->Min.x,
						this->Min.y,
						this->Min.z,
						this->Max.x,
						this->Max.y,
						this->Max.z,
						this->Sphere.x,
						this->Sphere.y,
						this->Sphere.z,
						this->Radius,
						this->LODmodelName.c_str()
						);
				}				
			}
			else if (Game::GameSimple::IsGTAIIIeraGame(game))
			{
				if (this->ObjectCount == 1 && this->DrawDistance[0] >= 4.0)
				{
					return sprintf(line, "%d, %s, %s, %.17g, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->DrawDistance[0],
						this->Flags
						);
				}
				else if (this->ObjectCount == 1)
					return sprintf(line, "%d, %s, %s, %d, %.17g, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->ObjectCount,
						this->DrawDistance[0],
						this->Flags
						);
				else if (this->ObjectCount == 2)
					return sprintf(line,
						"%d, %s, %s, %d, %.17g, %.17g, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->ObjectCount,
						this->DrawDistance[0],
						this->DrawDistance[1],
						this->Flags
						);
				else if (this->ObjectCount == 3)
					return sprintf(line, "%d, %s, %s, %d, %.17g, %.17g, %.17g, %d",
						this->ModelID,
						this->ModelName.c_str(),
						this->TXDname.c_str(),
						this->ObjectCount,
						this->DrawDistance[0],
						this->DrawDistance[1],
						this->DrawDistance[2],
						this->Flags
						);
				else
					return 0;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %s, %d, %.17g, %d, %d, %.17g, %d, %d, %d, %d, %d",
					this->ModelID,
					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->ObjectCount,
					this->DrawDistance[0],
					this->Flags,					
					this->UnkBullyScholarschip7,
					this->UnkBullyScholarschip8,
					this->UnkBullyScholarschip9,
					this->UnkBullyScholarschip10,
					this->UnkBullyScholarschip11,
					this->UnkBullyScholarschip12,
					this->UnkBullyScholarschip13
					);
			}
			else
				return 0;
		}
	}
}