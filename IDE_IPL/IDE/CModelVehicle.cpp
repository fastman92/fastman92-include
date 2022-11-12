/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelVehicle.h"
#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IDE
	{
		static const enumMemberNamePair<eVehicleType> VehicleTypeEnumMemberNames[] =
		{
			MAKE_VEHICLE_TYPE_LIST(PUT_ENUM_MEMBER_NAME_FOR_PAIR)
		};

		// Returns eVehicleType by name.
		eVehicleType GetVehicleTypeEnumMemberByName(const char* name)
		{
			const enumMemberNamePair<eVehicleType>* pair = getEnumPairFromArrayByName(VehicleTypeEnumMemberNames, name);

			return pair != NULL ? pair->enumMember : VEHICLE_TYPE_UNDEFINED;
		}

		// Finds name by vehicle type enum member
		const char* GetVehicleTypeEnumNameByMember(eVehicleType type)
		{
			return getNameByEnumMemberFromArray(VehicleTypeEnumMemberNames, type);
		}

		// Sets default values
		void CModelVehicle::InitValues()
		{
			this->CModelBaseInfo::InitValues();
			this->VehicleType = "undefined";
			this->HandlingName = "undefined";
			this->GameName = "undefined";
			this->Anim1 = "undefined";
			this->Anim2 = "undefined";
			this->Class = "normal";
			this->Frequency = 100;
			this->Level = 7;
			this->FlagsInt = 0;
			this->ComponentRules = 0;
			this->WheelModelID = -1;
			this->WheelRadius_Front = 1.0;
			this->WheelRadius_Rear = 1.0;
			this->WheelUpgradeClass = -1;
			this->MaxNum = 999;
			this->DefDirtLevel = 0.0;
			this->LodMult = 0;
			this->Swankness = 1.0;
			this->FlagsArray.clear();
		}

		// Imports entry.
		unsigned __int32 CModelVehicle::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tCarsParams param;

			if (game == GAME_SIMPLE_NAME_GTA_III)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %s %d %d %x %d %f",
					&param.ID,

					param.ModelName,
					param.TXDname,
					param.VehicleType,
					param.HandlingName,
					param.GameName,
					param.Class,
					&param.Frequency,
					&param.Level,
					&param.CompRules,
					&param.WheelModelID,
					&param.WheelScale
					);

				this->ModelID = param.ID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->VehicleType = param.VehicleType;
				this->HandlingName = param.HandlingName;
				this->GameName = param.GameName;
				this->Anim1 = param.Anim1;
				this->Class = param.Class;
				this->Frequency = param.Frequency;
				this->Level = param.Level;
				this->ComponentRules = param.CompRules;
				this->WheelModelID = param.WheelModelID;
				this->WheelRadius_Front = param.WheelScale;
				this->WheelRadius_Rear = param.WheelScale;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_VC)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %s %s %d %d %x %d %f",
					&param.ID,

					param.ModelName,
					param.TXDname,
					param.VehicleType,
					param.HandlingName,
					param.GameName,
					param.Anim1,
					param.Class,
					&param.Frequency,
					&param.Level,
					&param.CompRules,
					&param.WheelModelID,
					&param.WheelScale
					);

				this->ModelID = param.ID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->VehicleType = param.VehicleType;
				this->HandlingName = param.HandlingName;
				this->GameName = param.GameName;
				this->Anim1 = param.Anim1;
				this->Class = param.Class;
				this->Frequency = param.Frequency;
				this->Level = param.Level;
				this->ComponentRules = param.CompRules;
				this->WheelModelID = param.WheelModelID;
				this->WheelRadius_Front = param.WheelScale;
				this->WheelRadius_Rear = param.WheelScale;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_SA)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %s %s %d %d %x %d %f %f %d",
					&param.ID,

					param.ModelName,
					param.TXDname,
					param.VehicleType,
					param.HandlingName,
					param.GameName,
					param.Anim1,
					param.Class,
					&param.Frequency,
					&param.FlagsInt,
					&param.CompRules,
					&param.WheelModelID,
					&param.WheelRadius_Front,
					&param.WheelRadius_Rear,
					&param.WheelUpgradeClass
					);

				this->ModelID = param.ID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->VehicleType = param.VehicleType;
				this->HandlingName = param.HandlingName;
				this->GameName = param.GameName;
				this->Anim1 = param.Anim1;
				this->Class = param.Class;
				this->Frequency = param.Frequency;
				this->FlagsInt = param.FlagsInt;
				this->ComponentRules = param.CompRules;
				this->WheelModelID = param.WheelModelID;
				this->WheelRadius_Front = param.WheelRadius_Front;
				this->WheelRadius_Rear = param.WheelRadius_Rear;
				this->WheelUpgradeClass = param.WheelUpgradeClass;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%s %s %s %s %s %s %s %d %d %f %f %f %d %f %d %s",
					param.ModelName,
					param.TXDname,
					param.VehicleType,
					param.HandlingName,
					param.GameName,
					param.Anim1,
					param.Anim2,
					&param.Frequency,
					&param.MaxNum,
					&param.WheelRadius_Front,
					&param.WheelRadius_Rear,
					&param.DefDirtLevel,
					&param.LodMult,
					&param.Swankness,
					&param.FlagsInt,
					param.FlagsStr
					);

				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->VehicleType = param.VehicleType;
				this->HandlingName = param.HandlingName;
				this->GameName = param.GameName;
				this->Anim1 = param.Anim1;
				this->Anim2 = param.Anim2;
				this->Frequency = param.Frequency;
				this->MaxNum = param.MaxNum;
				this->WheelRadius_Front = param.WheelRadius_Front;
				this->WheelRadius_Rear = param.WheelRadius_Rear;
				this->DefDirtLevel = param.DefDirtLevel;
				this->LodMult = param.LodMult;
				this->Swankness = param.Swankness;
				this->FlagsInt = param.FlagsInt;

				this->ImportFlagsStr(param.FlagsStr);
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %s %s %s %d %d %d %d %f",
					&param.ID,

					param.ModelName,
					param.TXDname,
					param.VehicleType,
					param.HandlingName,
					param.GameName,
					param.Anim1,
					param.Anim2,
					param.Class,
					&param.Frequency,
					&param.Level,
					&param.CompRules,
					&param.WheelModelID,
					&param.WheelScale
					);

				this->ModelID = param.ID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->VehicleType = param.VehicleType;
				this->HandlingName = param.HandlingName;
				this->GameName = param.GameName;
				this->Anim1 = param.Anim1;
				this->Anim2 = param.Anim2;
				this->Class = param.Class;
				this->Frequency = param.Frequency;
				this->Level = param.Level;
				this->ComponentRules = param.CompRules;
				this->WheelModelID = param.WheelModelID;
				this->WheelRadius_Front = param.WheelScale;
				this->WheelRadius_Rear = param.WheelScale;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModelVehicle::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			if (game == GAME_SIMPLE_NAME_GTA_III)
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %s, %d, %d, %x, %d, %.17g",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->VehicleType.c_str(),
					this->HandlingName.c_str(),
					this->GameName.c_str(),
					this->Class.c_str(),
					this->Frequency,
					this->Level,
					this->ComponentRules,
					this->WheelModelID,
					this->WheelRadius_Front
					);
			else if (game == GAME_SIMPLE_NAME_GTA_VC)
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %s, %s, %d, %d, %x, %d, %.17g",
					ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->VehicleType.c_str(),
					this->HandlingName.c_str(),
					this->GameName.c_str(),
					this->Anim1.c_str(),
					this->Class.c_str(),
					this->Frequency,
					this->Level,
					this->ComponentRules,
					this->WheelModelID,
					this->WheelRadius_Front
					);
			else if (game == GAME_SIMPLE_NAME_GTA_SA)
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %s, %s, %d, %d, %x, %d, %.17g, %.17g, %d",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->VehicleType.c_str(),
					this->HandlingName.c_str(),
					this->GameName.c_str(),
					this->Anim1.c_str(),
					this->Class.c_str(),
					this->Frequency,
					this->FlagsInt,
					this->ComponentRules,
					this->WheelModelID,
					this->WheelRadius_Front,
					this->WheelRadius_Rear,
					this->WheelUpgradeClass
					);
			else if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				int l = sprintf(line, "%s, %s, %s, %s, %s, %s, %s, %d, %d, %.17g, %.17g, %.17g, %d, %.17g, %d, ",
					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->VehicleType.c_str(),
					this->HandlingName.c_str(),
					this->GameName.c_str(),
					this->Anim1.c_str(),
					this->Anim2.c_str(),
					this->Frequency,
					this->MaxNum,
					this->WheelRadius_Front,
					this->WheelRadius_Rear,
					this->DefDirtLevel,
					this->LodMult,
					this->Swankness,
					this->FlagsInt
					);

				l += this->ExportFlagsStr(line + l);
				return l;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %s, %s, %s, %d, %d, %d, %d, %.17g",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),
					this->VehicleType.c_str(),
					this->HandlingName.c_str(),
					this->GameName.c_str(),
					this->Anim1.c_str(),
					this->Anim2.c_str(),
					this->Class.c_str(),
					this->Frequency,
					this->Level,
					this->ComponentRules,
					this->WheelModelID,
					this->WheelScale
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}

		// Exports FlagStr, returns length of string
		void CModelVehicle::ImportFlagsStr(const char* str)
		{
			this->FlagsArray.clear();

			if (!*str || *str == '-')
				return;

			while (true)
			{
				std::string flag;

				do
				{
					flag.push_back(*str);

					str++;

					if (*str == '+')
						break;
					else if (!*str)
					{
						this->FlagsArray.push_back(flag);
						return;
					}
				} while (true);

				this->FlagsArray.push_back(flag);

				str++;
			}
		}

		// Exports FlagStr
		int CModelVehicle::ExportFlagsStr(char* str)
		{
			if (this->FlagsArray.size() == 0)
			{
				strcpy(str, "-");
				return 1;
			}
			else
			{
				int l = 0;

				strcpy(str, this->FlagsArray.begin()->c_str());
				l += strlen(this->FlagsArray.begin()->c_str());

				for (auto it = this->FlagsArray.begin() + 1; it != this->FlagsArray.end(); it++)
				{
					*(str + l) = '+';
					l += 1;
					strcpy(str + l, it->c_str());
					l += strlen(it->c_str());
				}

				return l;
			}
		}
	}
}