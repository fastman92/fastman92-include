/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../eGame.h"
#include "../SectionFile/CSectionFileElementBaseEx.h"

namespace File
{
	enum eSectionType
	{
		SECTION_UNDEFINED,

		SECTION_2DFX,	// 2d effects

		// IDE sections
		SECTION_IDE_ACCS,	// Accessories
		SECTION_IDE_AGRPS,
		SECTION_IDE_AMAT,
		SECTION_IDE_ANIM,	// Animations
		SECTION_IDE_CARS,	// Vehicles
		SECTION_IDE_CASH,
		SECTION_IDE_CLTH,	// Clothes
		SECTION_IDE_HAND,
		SECTION_IDE_HIER,
		SECTION_IDE_ITEM,	// Items
		SECTION_IDE_MLO,
		SECTION_IDE_OBJS,	// Objects
		SECTION_IDE_PANM,	// Prop animations
		SECTION_IDE_PATH,	// Paths
		SECTION_IDE_PEDS,	// Pederastians
		SECTION_IDE_SCND,
		SECTION_IDE_TANM,
		SECTION_IDE_TOBJ,	// Time objects
		SECTION_IDE_TREE,
		SECTION_IDE_TXDP,	// TXD parent
		SECTION_IDE_WEAP,	// Weapons

		// IPL sections
		SECTION_IPL_AUZO,	// Audio zones
		SECTION_IPL_BLOK,	// Blocks
		SECTION_IPL_BOUNDS,	// No entries, but found GTA V's IPL			
		SECTION_IPL_CARS,	// Parked car generators
		SECTION_IPL_CULL,	// Culling zones
		SECTION_IPL_GRGE,	// Garages
		SECTION_IPL_ENEX,	// Entry exits
		SECTION_IPL_INST,	// Object instances
		SECTION_IPL_JUMP,	// Jump stunts
		SECTION_IPL_LIGHTINST,	// Light instances, no entries, but found GTA V's IPL
		SECTION_IPL_LINK,	// Path link
		SECTION_IPL_LODCHILDREN,	// No entries, but found GTA V's IPL
		SECTION_IPL_LODM,	// Lod models			
		SECTION_IPL_MAXLOD,	// No entries, but found GTA V's IPL
		SECTION_IPL_MILOINST,	// No entries, but found GTA V's IPL
		SECTION_IPL_MLO_PLUS,	// Interior placement
		SECTION_IPL_MULT,	// No entries, but found GTA IV's IPL
		SECTION_IPL_MZON,	// Map zones
		SECTION_IPL_OCCL,	// Occlusions
		SECTION_IPL_PATH,	// Path group and nodes
		SECTION_IPL_PERM,
		SECTION_IPL_POIS,
		SECTION_IPL_PONT,
		SECTION_IPL_PICK,	// Pickups
		SECTION_IPL_PNOD,	// No entries, but found GTA V's IPL
		SECTION_IPL_PLNK,	// No entries, but found GTA V's IPL
		SECTION_IPL_PROJ,	// Projectile instances
		SECTION_IPL_PROP,
		SECTION_IPL_PREP,
		SECTION_IPL_PTHX,
		SECTION_IPL_RAIL,
		SECTION_IPL_RTFX,	// No entries, but found GTA IV's IPL
		SECTION_IPL_SLOW,
		SECTION_IPL_SPEC,
		SECTION_IPL_TCYC,	// Timecycle modiffers
		SECTION_IPL_TRIG,	// Triggers
		SECTION_IPL_VERS,	// Used in GTA V's IPL
		SECTION_IPL_VNOD,	// Vehicle nodes			
		SECTION_IPL_ZONE	// Zones
	};

	// Forward declarations
	// IDE sections
	
	class CModel2dEffect;

	namespace IDE
	{
		class CModel3commonElements;
		class CModelObject;
		class CModelPath;
		class CModelPed;
		class CModelPropAnimation;
		class CModelTimedObject;
		class CModelTXDparent;
		class CModelWeapon;
		class CModelVehicle;
	}


	// IPL sections
	namespace IPL
	{
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
		class CPlacementPois;
		class CPlacementPont;
		class CPlacementProp;
		class CPlacementRail;
		class CPlacementTimecycleModifier;
		class CPlacementTrigger;
		class CPlacementVehicleNode;
		class CPlacementZone;
	}

	class CIPLorIDEentryBaseInfo : public CSectionFileElementBaseEx
	{
	public:
		unsigned __int32 ModelID;

		// Constructor
		CIPLorIDEentryBaseInfo(int type) : CSectionFileElementBaseEx(SECTION_FILE_ELEMENT_TYPE_DATA, type) {}

		// Destructor
		virtual ~CIPLorIDEentryBaseInfo() {}

		//// Virtual functions ////

		// Sets default values
		virtual void CIPLorIDEentryBaseInfo::InitValues();

		// Types
		virtual const CModel2dEffect* ToModel2dEffect()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual CModel2dEffect* ToModel2dEffect() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		// Returns element's scope. 0 by default.
		virtual unsigned int GetElementScopeNumber() const { return 0; }

		// Returns element's number of scopes
		virtual unsigned int GetElementNumberOfScopes() const { return 1; }
		
		// IDE sections
		virtual const IDE::CModel3commonElements* ToModel3commonElements()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModel3commonElements* ToModel3commonElements() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IDE::CModelObject* ToModelObject()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModelObject* ToModelObject() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IDE::CModelTimedObject* ToModelTimedObject()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModelTimedObject* ToModelTimedObject() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IDE::CModelPath* ToModelPath()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IDE::CModelPath* ToModelPath() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IDE::CModelPed* ToModelPed()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModelPed* ToModelPed() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IDE::CModelPropAnimation* ToModelPropAnimation()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModelPropAnimation* ToModelPropAnimation() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IDE::CModelVehicle* ToModelVehicle()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IDE::CModelVehicle* ToModelVehicle() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IDE::CModelTXDparent* ToTXDparent()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModelTXDparent* ToTXDparent() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IDE::CModelWeapon* ToModelWeapon()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IDE::CModelWeapon* ToModelWeapon() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		// IPL sections
		virtual const IPL::CPlacementWithModel* ToPlacementWithModel()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual  IPL::CPlacementWithModel* ToPlacementWithModel() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IPL::CPlacementObjectInstance* ToPlacementObjectInstance()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementObjectInstance* ToPlacementObjectInstance() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const  IPL::CPlacementObjectInstanceSpec* ToPlacementObjectInstanceSpec()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementObjectInstanceSpec* ToPlacementObjectInstanceSpec() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementProjectileInstance* ToPlacementProjectileInstance()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementProjectileInstance* ToPlacementProjectileInstance() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementCarGenerator* ToPlacementCarGenerator()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementCarGenerator* ToPlacementCarGenerator() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementBlok* ToPlacementBlok()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementBlok* ToPlacementBlok() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementGarage* ToPlacementGarage()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementGarage* ToPlacementGarage() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementLink* ToPlacementLink()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementLink* ToPlacementLink() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementLodm* ToPlacementLodm()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementLodm* ToPlacementLodm() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementMapZone* ToPlacementMapZone()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementMapZone* ToPlacementMapZone() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementMlo* ToPlacementMlo()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementMlo* ToPlacementMlo() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementOcclusion* ToPlacementOcclusion()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementOcclusion* ToPlacementOcclusion() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementPerm* ToPlacementPerm()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementPerm* ToPlacementPerm() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementPois* ToPlacementPois()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementPois* ToPlacementPois() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementPont* ToPlacementPont()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementPont* ToPlacementPont() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementProp* ToPlacementProp()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementProp* ToPlacementProp() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementRail* ToPlacementRail()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementRail* ToPlacementRail() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementTimecycleModifier* ToPlacementTimecycleModifier()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementTimecycleModifier* ToPlacementTimecycleModifier() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementTrigger* ToPlacementTrigger()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementTrigger* ToPlacementTrigger() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementVehicleNode* ToPlacementVehicleNode()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementVehicleNode* ToPlacementVehicleNode() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

		virtual const IPL::CPlacementZone* ToPlacementZone()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
		virtual IPL::CPlacementZone* ToPlacementZone() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
	};
	
}