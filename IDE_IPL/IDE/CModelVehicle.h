/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CModelBaseInfo.h"
#include "CModel3commonElements.h"
#include "enumMemberNamePair.h"
#include "../../IMG/IMGstructures.h"
#include <string>
#include <vector>

namespace File
{
	namespace IDE
	{
		#define MAKE_VEHICLE_TYPE_LIST(formatMacro) \
			formatMacro(VEHICLE_TYPE_UNDEFINED) \
			\
			formatMacro(VEHICLE_TYPE_CAR) \
			formatMacro(VEHICLE_TYPE_MTRUCK) \
			formatMacro(VEHICLE_TYPE_TRUCK) \
			formatMacro(VEHICLE_TYPE_HELI) \
			formatMacro(VEHICLE_TYPE_PLANE) \
			formatMacro(VEHICLE_TYPE_BOAT) \
			formatMacro(VEHICLE_TYPE_TRAIN) \
			formatMacro(VEHICLE_TYPE_F_PLANE) \
			formatMacro(VEHICLE_TYPE_BIKE) \
			formatMacro(VEHICLE_TYPE_BMX) \
			formatMacro(VEHICLE_TYPE_TRAILER) 

		enum eVehicleType
		{
			MAKE_VEHICLE_TYPE_LIST(PUT_ENUM_MEMBER_FROM_LIST)
		};			

		// Returns eVehicleType by name.
		eVehicleType GetVehicleTypeEnumMemberByName(const char* name);

		// Finds name by vehicle type enum member
		const char* GetVehicleTypeEnumNameByMember(eVehicleType type);

		struct tCarsParams
		{
			unsigned __int32 ID;
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			char TXDname[IMG_MAX_FILENAME_LENGTH + 1];
			char HandlingName[16];
			char VehicleType[8];
			char GameName[12];
			char Anim1[IMG_MAX_FILENAME_LENGTH + 1];
			char Anim2[IMG_MAX_FILENAME_LENGTH + 1];
			char Class[16];
			unsigned __int32 Frequency;
			unsigned __int32 Level;
			unsigned __int32 FlagsInt;
			unsigned __int32 CompRules;
			unsigned __int32 WheelModelID;

			float WheelScale;
			float WheelRadius_Front;
			float WheelRadius_Rear;
			unsigned __int32 WheelUpgradeClass;

			unsigned __int32 MaxNum;

			float DefDirtLevel;
			unsigned __int32 LodMult;
			float Swankness;
			char FlagsStr[512];
		};

		class CModelVehicle : public CModel3commonElements
		{
		public:
			// Constructor
			CModelVehicle() : CModel3commonElements(SECTION_IDE_CARS) { this->InitValues(); };

			// Type
			std::string VehicleType;

			// HandlingName
			std::string HandlingName;

			// Game name
			std::string GameName;

			// Anims
			std::string Anim1;	// GTA IV: front
			std::string Anim2;	// GTA IV: rear

			// Class
			std::string Class;

			// Frequency
			unsigned __int32 Frequency;

			// Level
			unsigned __int32 Level;

			// Flags
			unsigned __int32 FlagsInt;

			// Component rules
			unsigned __int32 ComponentRules;

			// Wheel model ID
			unsigned __int32 WheelModelID;

			// WheelRadius for both front/rear wheels.
			// float WheelScale;

			// Wheel scale
			union
			{
				struct
				{
					float WheelRadius_Front;
					float WheelRadius_Rear;
				};

				float WheelScale;
			};

			// Unknown1
			unsigned __int32 WheelUpgradeClass;

			// Maximum number of vehicles to exist at a time.
			unsigned __int32 MaxNum;

			// DefDirtLevel
			float DefDirtLevel;

			// LodMult
			unsigned __int32 LodMult;

			// Swankness
			float Swankness;

			// Flag string
			std::vector<std::string> FlagsArray;

			/// FUNCTIONS ///

			// Imports FlagStr
			void ImportFlagsStr(const char* str);

			// Exports FlagStr, returns length of string
			int ExportFlagsStr(char* str);

			// Clone
			virtual CModelVehicle* clone() const { return new CModelVehicle(*this); };

			// Sets default values
			virtual void InitValues();

			// Imports entry.
			virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

			// Exports entry. Returns length of output string.
			virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

			// Types
			virtual const CModelVehicle* ToModelVehicle()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelVehicle* ToModelVehicle()    { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}