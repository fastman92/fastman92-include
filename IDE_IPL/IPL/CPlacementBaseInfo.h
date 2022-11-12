/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../../eGame.h"
#include "../../SectionFile/CSectionFileElementBaseEx.h"
#include "../CIPLorIDEentryBaseInfo.h"
#include <string>

namespace File
{
	namespace IPL
	{
		/*
		enum eSectionType
		{
			SECTION_UNDEFINED,

			SECTION_AUZO,	// Audio zones
			SECTION_BLOK,	// Blocks
			SECTION_BOUNDS,	// No entries, but found GTA V's IPL			
			SECTION_CARS,	// Parked car generators
			SECTION_CULL,	// Culling zones
			SECTION_GRGE,	// Garages
			SECTION_ENEX,	// Entry exits
			SECTION_INST,	// Object instances
			SECTION_JUMP,	// Jump stunts
			SECTION_LIGHTINST,	// Light instances, no entries, but found GTA V's IPL
			SECTION_LINK,	// Path link
			SECTION_LODCHILDREN,	// No entries, but found GTA V's IPL
			SECTION_LODM,	// Lod models			
			SECTION_MAXLOD,	// No entries, but found GTA V's IPL
			SECTION_MILOINST,	// No entries, but found GTA V's IPL
			SECTION_MLO_PLUS,	// Interior placement
			SECTION_MULT,	// No entries, but found GTA IV's IPL
			SECTION_MZON,	// Map zones
			SECTION_OCCL,	// Occlusions
			SECTION_PATH,	// Path group and nodes
			SECTION_PERM,
			SECTION_POIS,
			SECTION_PONT,
			SECTION_PICK,	// Pickups
			SECTION_PNOD,	// No entries, but found GTA V's IPL
			SECTION_PLNK,	// No entries, but found GTA V's IPL
			SECTION_PROJ,	// Projectile instances
			SECTION_PROP,
			SECTION_PREP,
			SECTION_PTHX,
			SECTION_RAIL,
			SECTION_RTFX,	// No entries, but found GTA IV's IPL
			SECTION_SLOW,
			SECTION_SPEC,			
			SECTION_TCYC,	// Timecycle modiffers
			SECTION_TRIG,	// Triggers
			SECTION_VERS,	// Used in GTA V's IPL
			SECTION_VNOD,	// Vehicle nodes			
			SECTION_ZONE	// Zones
		};

		// Forward declarations
		class CPlacementWithModel;
		class CPlacementObjectInstance;
		class CPlacementObjectInstanceSpec;
		class CPlacementBlok;
		class CPlacementCarGenerator;
		class CPlacementGarage;
		class CPlacementLink;
		class CPlacementLodm;
		class CPlacementMapZone;
		class CPlacementMlo;
		class CPlacementOcclusion;
		class CPlacementProjectileInstance;
		class CPlacementPerm;
		class CPlacementPont;
		class CPlacementProp;
		class CPlacementRail;
		class CPlacementTimecycleModifier;
		class CPlacementTrigger;
		class CPlacementVehicleNode;
		class CPlacementZone;

		class CPlacementBaseInfo : public CSectionFileElementBaseEx
		{
		public:
			unsigned __int32 ModelID;

			// Constructor
			CPlacementBaseInfo(int type) : CSectionFileElementBaseEx(SECTION_FILE_ELEMENT_TYPE_DATA, type) {}

			// Clone
			virtual CPlacementBaseInfo* clone() const { return new CPlacementBaseInfo(*this); };
				
			//// Virtual functions ////

			// Sets default values
			virtual void CPlacementBaseInfo::InitValues();

			// Types
			virtual const CPlacementWithModel* ToPlacementWithModel()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementWithModel* ToPlacementWithModel() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementObjectInstance* ToPlacementObjectInstance()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementObjectInstance* ToPlacementObjectInstance() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementObjectInstanceSpec* ToPlacementObjectInstanceSpec()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementObjectInstanceSpec* ToPlacementObjectInstanceSpec() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementProjectileInstance* ToPlacementProjectileInstance()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementProjectileInstance* ToPlacementProjectileInstance() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementCarGenerator* ToPlacementCarGenerator()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementCarGenerator* ToPlacementCarGenerator() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementBlok* ToPlacementBlok()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementBlok* ToPlacementBlok() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementGarage* ToPlacementGarage()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementGarage* ToPlacementGarage() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementLink* ToPlacementLink()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementLink* ToPlacementLink() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementLodm* ToPlacementLodm()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementLodm* ToPlacementLodm() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementMapZone* ToPlacementMapZone()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementMapZone* ToPlacementMapZone() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementMlo* ToPlacementMlo()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementMlo* ToPlacementMlo() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementOcclusion* ToPlacementOcclusion()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementOcclusion* ToPlacementOcclusion() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementPerm* ToPlacementPerm()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementPerm* ToPlacementPerm() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementPont* ToPlacementPont()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementPont* ToPlacementPont() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementProp* ToPlacementProp()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementProp* ToPlacementProp() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementRail* ToPlacementRail()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementRail* ToPlacementRail() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementTimecycleModifier* ToPlacementTimecycleModifier()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementTimecycleModifier* ToPlacementTimecycleModifier() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementTrigger* ToPlacementTrigger()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementTrigger* ToPlacementTrigger() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementVehicleNode* ToPlacementVehicleNode()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementVehicleNode* ToPlacementVehicleNode() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

			virtual const CPlacementZone* ToPlacementZone()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CPlacementZone* ToPlacementZone() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
		*/

		typedef CIPLorIDEentryBaseInfo CPlacementBaseInfo;
	}
}