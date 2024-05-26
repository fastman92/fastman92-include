/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"
#include "CompressedVector.h"
#include "CVector.h"
#include <stdint.h>

namespace Game_GTASA
{
	// path structures
	const int PATH_COORD_MULTIPLIER = 8;

	// Elements counts in path file
	class tStandardPathFileHeaderCounts
	{
	public:
		uint32_t numberOfPathNodes;
		uint32_t numberOfPathVehicleNodes;
		uint32_t numberOfPathPedNodes;

		uint32_t numberOfCarPathLinks;

		uint32_t numberOfAdjacentAddresses;
	};

	// fastman92 path header
	struct tPathFileHeaderFirstPart
	{
		union
		{
			uint32_t numberOfPathNodes;
			uint32_t magicID;	// magicID = 0xFFFFFFFF when different path format.
		};
	};

	VALIDATE_SIZE(tPathFileHeaderFirstPart, 4);

	//////////////////////	

	class CNodeAddress
	{
	public:
	  uint16_t areaId;
	  uint16_t nodeId;
	};

	VALIDATE_SIZE(CNodeAddress, 4);

	class CLinkAddress
	{
	public:
		unsigned short m_wCarPathLinkId : 10;
		unsigned short m_wAreaId : 6;
	};

	VALIDATE_SIZE(CLinkAddress, 0x2);

	class CLinkAddress_extended
	{
	public:
		unsigned short m_wCarPathLinkId;
		unsigned short m_wAreaId;
	};

	VALIDATE_SIZE(CLinkAddress_extended, 0x4);

	// standard GTA SA
	class CPathNode
	{
	public:
		enum {
			SPECIAL_NONE = 0x0,
			SPECIAL_PARKING_PARALLEL = 0x1,
			SPECIAL_PARKING_PERPENDICULAR = 0x2,
			SPECIAL_VALET = 0x3,
			SPECIAL_NIGHTCLUB = 0x4,
			SPECIAL_DELIVERIES = 0x5,
			SPECIAL_VALET_UNLOAD = 0x6,
			SPECIAL_NIGHTCLUB_UNLOAD = 0x7,
			SPECIAL_DRIVE_THROUGH = 0x8,
			SPECIAL_DRIVE_THROUGH_WINDOW = 0x9,
			SPECIAL_DELIVERIES_UNLOAD = 0xA
		};

		CPathNode *pNext;
		CPathNode *pPrevious;
		CompressedVector Coors;	// unused when fastman92 path format VER2 or higher is used
		int16_t DistanceToTarget;
		int16_t IndexAdjacentNodes;	// ID into link array
		CNodeAddress Address;

		uint8_t Width;
		uint8_t Group;		// unused when fastman92 path format VER3 or higher is used

		union
		{
			uint32_t m_dwFlags;
			struct {
				uint8_t NumberAdjNodes : 4;	// + 0
				uint8_t OnDeadEnd : 1;	// + 4
				uint8_t SwitchedOff : 1;	// + 5
				uint8_t RoadBlock : 1;	// + 6
				uint8_t WaterNode : 1;	// + 7
				uint8_t SwitchedOffOriginal : 1;	// + 8
				uint8_t AlreadyFound : 1;	// + 9
				uint8_t DontWanderHere : 1;	// + 10
				uint8_t InteriorNode : 1;	// + 11
				uint8_t Speed : 2; // + 12
				uint8_t Dummy : 2;	// + 14
				uint8_t Density : 4;	// + 16
				uint8_t SpecialFunction : 4;	// + 20
			};
		};

		// Returns number of links
		int GetNumberOfLinks() { return this -> m_dwFlags & 0xF; }

		// Sets the position in vector
		void GetPosition(CVector& out)
		{
			out.x = (float)this->Coors.x / PATH_COORD_MULTIPLIER;
			out.y = (float)this->Coors.y / PATH_COORD_MULTIPLIER;
			out.z = (float)this->Coors.z / PATH_COORD_MULTIPLIER;
		}
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPathNode, 0x1C);

	// standard GTA SA
	class CPathNodeSerialize
	{
	public:
		uint32_t pNext;	// fakePtr
		uint32_t pPrevious;	// fakePtr
		CompressedVector Coors;	// unused when fastman92 path format VER2 or higher is used
		int16_t DistanceToTarget;
		int16_t IndexAdjacentNodes;	// ID into link array
		CNodeAddress Address;

		uint8_t Width;
		uint8_t Group;		// unused when fastman92 path format VER3 or higher is used

		union
		{
			uint32_t m_dwFlags;
		};
	};

	VALIDATE_SIZE(CPathNodeSerialize, 0x1C);
	
	// fastman92 path format VER2
	class CPathNode_fastman92_version_2 : public CPathNode
	{
	public:
		CompressedVector_extended CoorsExtended;

		// Sets the position in vector
		void GetPosition(CVector& out)
		{
			out.x = (float)this->CoorsExtended.x / PATH_COORD_MULTIPLIER;
			out.y = (float)this->CoorsExtended.y / PATH_COORD_MULTIPLIER;
			out.z = (float)this ->CoorsExtended.z / PATH_COORD_MULTIPLIER;
		}
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPathNode_fastman92_version_2, 0x28);

	class CPathNode_fastman92_version_2_Serialize : public CPathNodeSerialize
	{
	public:
		CompressedVector_extended CoorsExtended;
	};

	VALIDATE_SIZE(CPathNode_fastman92_version_2_Serialize, 0x28);

	// fastman92 path format VER4
	class CPathNode_fastman92_version_4 : public CPathNode_fastman92_version_2
	{
	public:
		uint16_t GroupExtended;
	};

	VALIDATE_SIZE_ONLY_ON_32_BIT_ARCHITECTURE(CPathNode_fastman92_version_4, 0x2C);

	class CPathNode_fastman92_version_4_Serialize : public CPathNode_fastman92_version_2_Serialize
	{
	public:
		uint16_t GroupExtended;
	};

	VALIDATE_SIZE(CPathNode_fastman92_version_4_Serialize, 0x2C);

	class CCarPathLink
	{
	public:
		struct
		{
			int16_t x;
			int16_t y;
		} Coors;	// unused when path limit hacked
		CNodeAddress attachedPathNode;
		int8_t dirX;
		int8_t dirY;
		char m_nPathNodeWidth;
		uint16_t m_wFlags;
	};

	VALIDATE_SIZE(CCarPathLink, 0xE);

	class CCarPathLink_fastman92_version_4 : public CCarPathLink
	{
	public:
		struct {
			int32_t x;
			int32_t y;
		} CoorsExtended;
	};

	VALIDATE_SIZE(CCarPathLink_fastman92_version_4, 0x18);

	// other
	class CForbiddenArea
	{
	public:
	  float x1;
	  float x2;
	  float y1;
	  float y2;
	  float z1;
	  float z2;
	  char bEnable;
	  char type;
	};

	VALIDATE_SIZE(CForbiddenArea, 0x1C);

	class CPathIntersectionInfo
	{
	public:
		unsigned char m_bRoadCross : 1;
		unsigned char m_bPedTrafficLight : 1;
	};

	VALIDATE_SIZE(CPathIntersectionInfo, 0x1);

	// path type
	enum ePathType
	{
		PATH_TYPE_UNDEFINED,

		PATH_TYPE_VEHICLE,
		PATH_TYPE_PED
	};

	//////////////////////////////
	// To be phased out, best not to use it anymore:
	#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable: 4200 )
	#endif
	struct tFastman92PathFileSecondPart
	{
		uint32_t format;	// should have a value "FM92"
		uint8_t sizeofNextValue;
		char value[];	// number of bytes depends on sizeofNextValue
	};

	#ifdef _MSC_VER
	#pragma warning ( pop )
	#endif

	VALIDATE_SIZE(tFastman92PathFileSecondPart, 8);

	namespace details
	{
		struct tFastman92PathFileHeaderThirdFormat
		{
			uint32_t formatVersion;	// should have a value "VER2" or "VER3"
		};
	}

	struct tFastman92PathFileHeaderThirdPart
		: details::tFastman92PathFileHeaderThirdFormat,
		tStandardPathFileHeaderCounts {};

	VALIDATE_SIZE(tFastman92PathFileHeaderThirdPart, 24);

	// fastman92 path format VER3
	// comes with alignment problem, version 4 fixes it
	#pragma pack(push, 1)
	class CPathNode_fastman92_version_3_Serialize : public CPathNode_fastman92_version_2_Serialize
	{
	public:
		uint16_t GroupExtended;
	};
	#pragma pack(pop)

	VALIDATE_SIZE(CPathNode_fastman92_version_3_Serialize, 0x2A);

	// comes with alignment problem, version 4 fixes it
	#pragma pack(push, 1)
	class CCarPathLink_fastman92_version_2 : public CCarPathLink
	{
	public:
		struct {
			int32_t x;
			int32_t y;
		} CoorsExtended;
	};
	#pragma pack(pop)

	VALIDATE_SIZE(CCarPathLink_fastman92_version_2, 0x16);
}

// GTA V
namespace Game_GTAV
{
	const int PATH_COORD_XY_MULTIPLIER = 4;
	const int PATH_COORD_Z_MULTIPLIER = 32;
}