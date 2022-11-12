/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include <Windows.h>
#include "../../CVector.h"
#include "../../CQuaternion.h"
#include "../../CBox.h"

#define IMG_MAX_FILENAME_LENGTH 39

namespace File
{
	namespace IPL
	{
		namespace Structure
		{
			#pragma pack(push, 1)
			struct tGTASA_binaryIPL_header
			{
				DWORD magicID;
				DWORD numberOfObjectInstances;
				DWORD field_8;
				DWORD field_C;
				DWORD field_10;
				DWORD numberOfParkedCarGenerators;
				DWORD field_18;
				DWORD OffsetToItemInstances;
				DWORD SizeOfItemInstances;
				DWORD field_24;
				DWORD field_28;
				DWORD field_2C;
				DWORD field_30;
				DWORD field_34;
				DWORD field_38;
				DWORD OffsetToCarGenerators;
				DWORD field_40;
				DWORD field_44;
				DWORD field_48;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(tGTASA_binaryIPL_header, 0x4C);

			#pragma pack(push, 1)
			class CFileObjectInstanceInGTASA
			{
			public:
				CVector position;
				CQuaternion rotation;
				int modelID;
				int interiorID;
				int lodIndex;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileObjectInstanceInGTASA, 0x28);

			#pragma pack(push, 1)
			struct CFileCarGeneratorInGTASA
			{
				CVector Pos;
				float AngleInRadians;
				int ModelID;
				int PrimCol;
				int SecCol;
				int Flags;
				int AlarmProbability;
				int DoorLockProbability;
				int MinDelay;
				int MaxDelay;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileCarGeneratorInGTASA, 0x30);


			/////////////////
			
			// header


			#pragma pack(push, 1)
			struct tBullyScholarshipEdition_binaryIPB_header
			{
				int magicID;
				char field_4[15];
			};
			#pragma pack(pop)

			VALIDATE_SIZE(tBullyScholarshipEdition_binaryIPB_header, 0x13);

			static const unsigned __int8 BullyScholarshipIPBheaderBytes[] =
			{
				0x49, 0x70,	0x6C, 0x24,
				0x53, 0xE7,	0xB5, 0xFC,
				0xB6, 0x07,	0x66, 0x7A,
				0xE5, 0xB6, 0x83, 0xEB,
				0xBF, 0xDE,	0xB4
			};

			VALIDATE_SIZE(BullyScholarshipIPBheaderBytes, sizeof(tBullyScholarshipEdition_binaryIPB_header));
			
			static const tBullyScholarshipEdition_binaryIPB_header& BullyScholarshipIPBheader
				= *(tBullyScholarshipEdition_binaryIPB_header*)BullyScholarshipIPBheaderBytes;

			#pragma pack(push, 1)
			struct CFileObjectInstanceInBullyScholarship
			{
				int modelID;
				char modelName[64];
				float InteriorID;
				CVector Pos;
				CVector Scale;
				CQuaternion Rot;
				float field_70;
				unsigned __int32 CollectibleHash;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileObjectInstanceInBullyScholarship, 0x78);

			#pragma pack(push, 1)
			struct CFileObjectInstanceSpecInBullyScholarship : public CFileObjectInstanceInBullyScholarship
			{
				unsigned __int32 AreaNameHash;
				int AreaType;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileObjectInstanceSpecInBullyScholarship, 0x80);

			#pragma pack(push, 1)
			struct CFileProjectileInstanceInBullyScholarship
			{
				unsigned __int32 ModelID;
				char ModelName[64];
				float field_44;
				CVector Pos;
				CVector Scale;
				CVector Rot;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileProjectileInstanceInBullyScholarship, 0x6C);

			#pragma pack(push, 1)
			struct CFileTriggerInBullyScholarship
			{
				__int32 param2;
				CVector Pos;
				CVector Rot;
				float param9;
				float param10;
				float param11;
				float param12;
				CVector vec_2C;
				int param16;
				int param17;
				int param18;
				int param19;
				int param20;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileTriggerInBullyScholarship, 0x4C);

			#pragma pack(push, 1)
			struct CFileOcclusionInBullyScholarship
			{
				float midX;
				float midY;
				float midZ;
				float widthX;
				float widthY;
				float height;
				float angle;
			};
			#pragma pack(pop)

			VALIDATE_SIZE(CFileOcclusionInBullyScholarship, 0x1C);

			// GTA IV

			// IPL: inst
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileObjectInstanceVersion3InGTAIV_template
			{
				CVector_template<Wrapper> Pos;
				CQuaternion_template<Wrapper> Rot;
				Wrapper<unsigned __int32> ModelNameHash;
				Wrapper<unsigned __int32> Flags;
				Wrapper<int> LODindex;
				Wrapper<int> field_28;
				Wrapper<float> field_2C;
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileObjectInstanceVersion3InGTAIV);

			VALIDATE_SIZE(CFileObjectInstanceVersion3InGTAIV, 0x30);

			// IPL: cars
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileCarGeneratorInGTAIV_template
			{
				CVector_template<Wrapper> Pos;
				CVector_template<Wrapper> Rot;
				Wrapper<unsigned __int32> ModelNameHash;
				Wrapper<int> PrimCol;
				Wrapper<int> SecCol;
				Wrapper<int> ThirdColor;
				Wrapper<int> SpecularColor;
				Wrapper<unsigned __int32> Flags;
				Wrapper<int> AlarmProbability;
				Wrapper<int> DoorLockProbability;
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileCarGeneratorInGTAIV);

			VALIDATE_SIZE(CFileCarGeneratorInGTAIV, 0x38);

			// IPL: grge
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileGarageInGTAIV_template
			{
				CVector_template<Wrapper> Pos;
				CVector2D_template<Wrapper> Line;
				CVector_template<Wrapper> Cube;
				Wrapper<unsigned __int32> Flags;
				Wrapper<unsigned __int32> Type;
				char Name[8];
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileGarageInGTAIV);

			VALIDATE_SIZE(CFileGarageInGTAIV, 0x30);

			// IPL: zone
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileZoneInGTAIV_template
			{
				char ZoneName[24];
				char GXTlabel[12];
				CVector_template<Wrapper> BoxCornerFirst;
				CVector_template<Wrapper> BoxCornerSecond;
				char field_3C[8];
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileZoneInGTAIV);

			VALIDATE_SIZE(CFileZoneInGTAIV, 0x44);

			// IPL: vnod
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileVehicleNode_template
			{
				CVector_template<Wrapper> Pos;
				Wrapper<int> UnknownParam4inGTAIV;
				Wrapper<int> UnknownParam5inGTAIV;
				Wrapper<int> UnknownParam6inGTAIV;
				Wrapper<int> UnknownParam7inGTAIV;
				Wrapper<int> UnknownParam8inGTAIV;
				Wrapper<float> UnknownParam9inGTAIV;
				Wrapper<int> UnknownParam10inGTAIV;
				Wrapper<unsigned __int32> Flags;
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileVehicleNode);

			VALIDATE_SIZE(CFileVehicleNode, 0x2C);

			// IPL: mlo+
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileMloInBinaryFile_template
			{
				char ModelName[24];
				Wrapper<unsigned __int32> Flags;
				Wrapper<int> InstMloIndex;
				Wrapper<int> CountParam5inGTAIV;
				CVector_template<Wrapper> Pos;
				CQuaternion_template<Wrapper> Rot;
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileMloInBinaryFile);

			VALIDATE_SIZE(CFileMloInBinaryFile, 0x40);

			DEFINE_ENDIAN_STRUCTURE(CFileSlow, CBox_template);

			// IPL: blok
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileBlok_template
			{
				Wrapper<int> Always1;
				char Description[92];	// BlockName,UnknownParam6inGTAIV,Author,DateTime
				Wrapper<int> UnknownParam4inGTAIV;
				CVector2D_template<Wrapper> CornerPoints[4];
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileBlok);

			VALIDATE_SIZE(CFileBlok, 0x84);

			// IPL: link


			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileLink_template
			{
				Wrapper<int> UnknownParam1inGTAIV;
				Wrapper<int> UnknownParam2inGTAIV;
				Wrapper<float> UnknownParam3inGTAIV;
				Wrapper<int> UnknownParam4inGTAIV;
				Wrapper<int> UnknownParam5inGTAIV;
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileLink);

			VALIDATE_SIZE(CFileLink, 0x14);

			// IPL: lodm
#define NUMBER_OF_HASHES_IN_GTAIV_LODM 10


			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileLodm_template
			{
				CBox_template<Wrapper> Box;
				Wrapper<int> Flags;
				Wrapper<unsigned __int32> ModelNameHashes[NUMBER_OF_HASHES_IN_GTAIV_LODM];
				char ModelNames[NUMBER_OF_HASHES_IN_GTAIV_LODM][32];
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileLodm);

			VALIDATE_SIZE(CFileLodm, 0x184);

			// IPL: tcyc
			#pragma pack(push, 1)
			template <template<class> class Wrapper> struct CFileTimecycleModifier_template
			{
				CBox_template<Wrapper> Box;
				Wrapper<float> UnknownParam7inGTAIV;
				Wrapper<float> UnknownParam8inGTAIV;
				Wrapper<int> UnknownParam9inGTAIV;
				Wrapper<int> UnknownParam10inGTAIV;
				Wrapper<unsigned __int32> ModifierNameHash;
			};
			#pragma pack(pop)

			DEFINE_ENDIAN_STRUCTURE_DEFAULT(CFileTimecycleModifier);
		}
	}
}