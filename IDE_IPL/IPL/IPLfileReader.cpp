/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "IPLfileReader.h"

#include "CPlacementBaseInfo.h"
#include "CPlacementObjectInstance.h"
#include "CPlacementObjectInstanceSpec.h"
#include "CPlacementProjectileInstance.h"
#include "CPlacementBlok.h"
#include "CPlacementCarGenerator.h"
#include "CPlacementGarage.h"
#include "CPlacementLink.h"
#include "CPlacementLodm.h"
#include "CPlacementMapZone.h"
#include "CPlacementMlo.h"
#include "CPlacementOcclusion.h"
#include "CPlacementPerm.h"
#include "CPlacementPois.h"
#include "CPlacementPont.h"
#include "CPlacementProp.h"
#include "CPlacementRail.h"
#include "CPlacementSlow.h"
#include "CPlacementTimecycleModifier.h"
#include "CPlacementTrigger.h"
#include "CPlacementVehicleNode.h"
#include "CPlacementZone.h"

#include "../../SectionFile/BinarySectionFile.h"

#include "../../BitwiseOperation.h"
#include "../../IMG/IMGstructures.h"
#include "IPLstructures.h"
#include "../../fileIO.h"
#include <stdio.h>
#include <stdint.h>

using namespace Game;

namespace File
{
	namespace IPL
	{
		using namespace Structure;

		// Sets game version and registers sections.
		void IPLfileReaderEx::SetGameVersion(Game::eGameName game)
		{
			this->ClearSections();

			this->m_gameInfo = Game::GetSimpleGameAndPlatformByExactMember(game);
			Game::eGameNameSimplified gameSimple = this->m_gameInfo.gameSimple;

			this->RegisterSection("inst", SECTION_IPL_INST, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementObjectInstance>));

			if (gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				this->RegisterSection("prop", SECTION_IPL_PROP, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementProp>));
				this->RegisterSection("pont", SECTION_IPL_PONT, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementPont>));
				this->RegisterSection("pois", SECTION_IPL_POIS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementPois>));
				this->RegisterSection("spec", SECTION_IPL_SPEC, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementObjectInstanceSpec>));
				this->RegisterSection("proj", SECTION_IPL_PROJ, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementProjectileInstance>));
				this->RegisterSection("rail", SECTION_IPL_RAIL, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementRail>));
				this->RegisterSection("perm", SECTION_IPL_PERM, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementPerm>));
				this->RegisterSection("trig", SECTION_IPL_TRIG, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementTrigger>));
			}

			if (gameSimple == GAME_SIMPLE_NAME_GTA_SA || gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("cars", SECTION_IPL_CARS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementCarGenerator>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_SA || gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("grge", SECTION_IPL_GRGE, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementGarage>));

			if (game == GAME_SIMPLE_NAME_GTA_III || game == GAME_SIMPLE_NAME_GTA_VC
				|| gameSimple == GAME_SIMPLE_NAME_GTA_SA || gameSimple == GAME_SIMPLE_NAME_GTA_IV
				|| gameSimple == GAME_SIMPLE_NAME_GTA_V)
			{
				this->RegisterSection("zone", SECTION_IPL_ZONE, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementZone>));
				this->RegisterSection("mzon", SECTION_IPL_MZON, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementMapZone>));
			}

			if (gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("lodm", SECTION_IPL_LODM, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementLodm>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("link", SECTION_IPL_LINK, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementLink>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("vnod", SECTION_IPL_VNOD, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementVehicleNode>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("blok", SECTION_IPL_BLOK, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementBlok>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("slow", SECTION_IPL_SLOW, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementSlow>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("mlo+", SECTION_IPL_MLO_PLUS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementMlo>));

			if(gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("tcyc", SECTION_IPL_TCYC, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementTimecycleModifier>));
			
			if (gameSimple == GAME_SIMPLE_NAME_GTA_III
				|| gameSimple == GAME_SIMPLE_NAME_GTA_VC
				|| gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION
				|| gameSimple == GAME_SIMPLE_NAME_GTA_SA
				|| gameSimple == GAME_SIMPLE_NAME_GTA_IV
				)
				this->RegisterSection("occl", SECTION_IPL_OCCL, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CPlacementOcclusion>));
		}

		// Registers unsupported section
		void IPLfileReaderEx::RegisterUnsupportedSection(const char* name, int type)
		{
			this->RegisterSection(
				name,
				type,
				static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSectionUsingType<CPlacementBaseInfo, SECTION_UNDEFINED>)
				);
		}

		/////////////// IDEfileReaderEx ///////////////

		// Writes 3 common elements
		void WriteNothing(FILE* fp, const CPlacementBaseInfo* ptr) {}

		struct tBinarySectionBullyScholarshipUserData : tBinarySectionStandardUserData
		{
			eGameNameSimplified gameSimple;
		};

		void AddBullyEntry(tBinarySectionBullyScholarshipUserData* pUserData, CSectionFileElementBase* ptr)
		{
			IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pUserData->pReader;

			if (ptr->IsData())
			{
				CSectionFileElementBaseEx* ptrEx = (CSectionFileElementBaseEx*)ptr;
				ptrEx->UpdateLine(pIPLreader->m_gameInfo.gameSimple);
				pIPLreader->ProcessEntry(ptrEx);
			}
			else if (CSectionFileComment* pComment = ptr->ToComment())
				pIPLreader->ProcessEntry(pComment);

			delete ptr;
		}

		struct tBullyScholarshipEditionBinarySectionDescriptor
		{
			int sectionType;
			unsigned __int32 typeIDinBinaryFile;
			bool(*LoadFunc)(void* pUserData);
			void(*SaveFunc)(void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr);
		};

		// Writes string, which can be default
		void FileWritePascalStringCanBeDefault(FILE* fp, const char* str)
		{
			if (!_stricmp(str, "default"))
				FileWritePascalString(fp, "");
			else
				FileWritePascalString(fp, str);
		}

		// Sets string or defaults it
		void SetStringCanBeDefault(std::string& str, const char* newStr)
		{
			if (newStr[0])
				str = newStr;
			else
				str = "default";			
		}

		CSectionFileComment* CreateUnsupportedEntryComment(IPLfileReaderEx* pReader)
		{
			CSectionFileComment* pComment = new CSectionFileComment();
			pComment->SetReaderPointer(pReader);
			pComment->ImportEntry("Entry was skipped.");
			return pComment;
		}

		// Set Bully inst
		void LoadBullyInstData(
			tBinarySectionBullyScholarshipUserData* pUserData,
			CPlacementObjectInstance* pPlacement,
			const CFileObjectInstanceInBullyScholarship* data)
		{
			IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pUserData->pReader;

			pPlacement->ModelID = data->modelID;

			pPlacement->ModelName.SetStringAndHash(
				pUserData->gameSimple,
				data->modelName);

			pPlacement->InteriorNum = (int)data->InteriorID;
			pPlacement->Pos = data->Pos;
			pPlacement->Scale = data->Scale;
			pPlacement->Rot = data->Rot;

			pPlacement->field_70_inBullyScholarchip = data->field_70;

			pPlacement->CollectibleName.SetHashAndString(
				pUserData->gameSimple,
				data->CollectibleHash);

			auto pCollectibleFileReader = pIPLreader->pCollectibleFileReader;

			if (pCollectibleFileReader)
			{
				Collectible::CCollectible* pCollectible
					= pCollectibleFileReader->FindEntryByHash(data->CollectibleHash);

				if (pCollectible)
					pPlacement->CollectibleName.SetStringAndHash(
						pUserData->gameSimple,
						pCollectible->CollectibleName.GetString().c_str());
			}
		}

		// Stores Bully inst
		void StoresBullyInstData(
			tBinarySectionBullyScholarshipUserData* pUserData,
			const CPlacementObjectInstance* pPlacement,
			CFileObjectInstanceInBullyScholarship* data)
		{
			data->modelID = pPlacement->ModelID;

			strncpy(data->modelName,
				pPlacement->ModelName.GetString().c_str(),
				sizeof(data->modelName)
				);			

			data->InteriorID = (float)pPlacement->InteriorNum;
			data->Pos = pPlacement->Pos;
			data->Scale = pPlacement->Scale;
			data->Rot = pPlacement->Rot;
			data->field_70 = pPlacement->field_70_inBullyScholarchip;
			data->CollectibleHash = pPlacement->CollectibleName.GetHash();
		}
		
		// Bully scholarschip descriptor array
		static const struct tBullyScholarshipEditionBinarySectionDescriptor BullyScholarschipDescriptors[] =
		{
			{
				SECTION_IPL_INST,
				'tsni',
				[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;

					CFileObjectInstanceInBullyScholarship data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return false;

					CPlacementObjectInstance* pPlacement = new CPlacementObjectInstance();
					pPlacement->SetReaderPointer(pMyUserData->pReader);
					LoadBullyInstData(pMyUserData, pPlacement, &data);
					AddBullyEntry(pMyUserData, pPlacement);
					return true;
				},
				[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					const CPlacementObjectInstance* pPlacement = (const CPlacementObjectInstance*)ptr;

					CFileObjectInstanceInBullyScholarship data;
					StoresBullyInstData(pMyUserData, pPlacement, &data);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				}
			},
			
			{
				SECTION_IPL_SPEC,
				'ceps',
				[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;

					CFileObjectInstanceSpecInBullyScholarship data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return false;

					CPlacementObjectInstanceSpec* pPlacement = new CPlacementObjectInstanceSpec();
					pPlacement->SetReaderPointer(pMyUserData->pReader);
					LoadBullyInstData(pMyUserData, pPlacement, &data);

					pPlacement->AreaName.SetHashAndString(
						pMyUserData->gameSimple,
						data.AreaNameHash);

					pPlacement->AreaType = data.AreaType;

					AddBullyEntry(pMyUserData, pPlacement);
					return true;
				},					
					
				[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					const CPlacementObjectInstanceSpec* pPlacement = (const CPlacementObjectInstanceSpec*)ptr;

					CFileObjectInstanceSpecInBullyScholarship data;
					StoresBullyInstData(pMyUserData, pPlacement, &data);

					data.AreaNameHash = pPlacement->AreaName.GetHash();
					data.AreaType = pPlacement->AreaType;

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				}								
			},

			{
				SECTION_IPL_PROJ,
				'jorp',
				[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;

					CFileProjectileInstanceInBullyScholarship data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return false;
					
					CPlacementProjectileInstance* pPlacement = new CPlacementProjectileInstance();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->ModelID = data.ModelID;

					pPlacement->ModelName.SetStringAndHash(
						pMyUserData->gameSimple,
						data.ModelName);

					pPlacement->UnknownParam3inBullyScholarschip = data.field_44;

					pPlacement->Pos = data.Pos;
					pPlacement->Scale = data.Scale;
					pPlacement->Rot = data.Rot;

					AddBullyEntry(pMyUserData, pPlacement);
					return true;

				},				
				[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionStandardUserData* pMyUserData = (tBinarySectionStandardUserData*)pUserData;
					const CPlacementProjectileInstance* pPlacement = (const CPlacementProjectileInstance*)ptr;
					
					CFileProjectileInstanceInBullyScholarship data;

					data.ModelID = pPlacement->ModelID;

					strncpy(data.ModelName,
						pPlacement->ModelName.GetString().c_str(),
						sizeof(data.ModelName)
						);

					data.field_44 = pPlacement->UnknownParam3inBullyScholarschip;
					data.Pos = pPlacement->Pos;
					data.Scale = pPlacement->Scale;
					data.Rot = pPlacement->Rot;
					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				}				
			},

			{
				SECTION_IPL_TRIG,
				'girt',
				[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;


					char Name[256];
					FileReadPascalString(pMyUserData->fp, Name, sizeof(Name));					

					CFileTriggerInBullyScholarship data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))					
						return false;

					CPlacementTrigger* pPlacement = new CPlacementTrigger();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->UnknownParam1inBullyScholarschip = Name;
					pPlacement->UnknownParam2inBullyScholarschip = data.param2;					
					pPlacement->Pos = data.Pos;
					pPlacement->Rot = data.Rot;
					pPlacement->UnknownParam9inBullyScholarschip = data.param9;
					pPlacement->UnknownParam10inBullyScholarschip = data.param10;
					pPlacement->UnknownParam11inBullyScholarschip = data.param11;
					pPlacement->UnknownParam12inBullyScholarschip = data.param12;
					pPlacement->UnknownVectorFromParam13inBullyScholarschip = data.vec_2C;

					AddBullyEntry(pMyUserData, pPlacement);
					return true;

				},										
				[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionStandardUserData* pMyUserData = (tBinarySectionStandardUserData*)pUserData;
					const CPlacementTrigger* pPlacement = (const CPlacementTrigger*)ptr;
					
					CFileTriggerInBullyScholarship data = { 0 };

					FileWritePascalString(pMyUserData->fp, pPlacement->UnknownParam1inBullyScholarschip.c_str());
					data.param2 = pPlacement->UnknownParam2inBullyScholarschip;
					data.Pos = pPlacement->Pos;
					data.Rot = pPlacement->Rot;
					data.param9 = pPlacement->UnknownParam9inBullyScholarschip;
					data.param10 = pPlacement->UnknownParam10inBullyScholarschip;
					data.param11 = pPlacement->UnknownParam11inBullyScholarschip;
					data.param12 = pPlacement->UnknownParam12inBullyScholarschip;
					data.vec_2C = pPlacement->UnknownVectorFromParam13inBullyScholarschip;

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				}							
			},

			{
				SECTION_IPL_PROP,
				'porp',
				[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;

					char propName[256];
					FileReadPascalString(pMyUserData->fp, propName, sizeof(propName));
					
					CPlacementProp* pPlacement = new CPlacementProp();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->PropName = propName;
					AddBullyEntry(pMyUserData, pPlacement);
					return true;
				},
				[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionStandardUserData* pMyUserData = (tBinarySectionStandardUserData*)pUserData;
					const CPlacementProp* pPlacement = (const CPlacementProp*)ptr;
					FileWritePascalString(pMyUserData->fp, pPlacement->PropName.c_str());				
				}
			},

			{
				SECTION_IPL_RAIL,
				'liar',
				[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;
					
					char pathName[256];
					int32_t UnknownParam2inBullyScholarschip;

					FileReadPascalString(pMyUserData->fp, pathName, sizeof(pathName));
					fread(&UnknownParam2inBullyScholarschip, sizeof(UnknownParam2inBullyScholarschip), 1, pMyUserData->fp);

					uint32_t CountOfPositions;
					fread(&CountOfPositions, sizeof(CountOfPositions), 1, pMyUserData->fp);					
					
					CPlacementRail* pHeader = new CPlacementRail(PLACEMENT_RAIL_ENTRY_TYPE_HEADER);
					pHeader->SetReaderPointer(pMyUserData->pReader);
					pHeader->PathName = pathName;
					pHeader->UnknownParam2inBullyScholarschip = UnknownParam2inBullyScholarschip;
					AddBullyEntry(pMyUserData, pHeader);

					CVector Pos;

					for (unsigned int i = 0; i < CountOfPositions; i++)
					{
						fread(&Pos, sizeof(CVector), 1, pMyUserData->fp);
						CPlacementRail* pPos = new CPlacementRail(PLACEMENT_RAIL_ENTRY_TYPE_POS);
						pPos->SetReaderPointer(pMyUserData->pReader);
						pPos->Pos = Pos;
						AddBullyEntry(pMyUserData, pPos);
					}

					return true;
				},
					NULL
#if FALSE
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionStandardUserData* pMyUserData = (tBinarySectionStandardUserData*)pUserData;
					const CPlacementRail* pPlacement = (const CPlacementRail*)ptr;
					FILE* fp = pMyUserData->fp;

					ePlacementRailEntryType elementType = pPlacement->GetRailEntryType();

					if (elementType == PLACEMENT_RAIL_ENTRY_TYPE_HEADER)
					{
						FileWritePascalString(pMyUserData->fp, pPlacement->PathName.c_str());
						FileWriteFloat(pMyUserData->fp, pPlacement->UnknownParam2inBullyScholarschip);

						FileWriteInt32(fp, pPlacement->NumberOfEntriesFollowing);
					}
					else if (elementType == PLACEMENT_RAIL_ENTRY_TYPE_POS)
						fwrite(&pPlacement->Pos, sizeof(CVector), 1, fp);
				}
#endif
			},

			{
				SECTION_IPL_PERM,
				'mrep',
					[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;

					tPermParams p;

					FileReadPascalString(pMyUserData->fp, p.UnknownParam1inBullyScholarschip, sizeof(p.UnknownParam1inBullyScholarschip));

					fread(&p.UnknownParam2inBullyScholarschip, sizeof(p.UnknownParam2inBullyScholarschip), 1, pMyUserData->fp);
					fread(&p.UnknownParam3inBullyScholarschip, sizeof(p.UnknownParam3inBullyScholarschip), 1, pMyUserData->fp);
					fread(&p.UnknownParam4inBullyScholarschip, sizeof(p.UnknownParam4inBullyScholarschip), 1, pMyUserData->fp);
					
					unsigned __int32 CountOfSubElements;
					fread(&CountOfSubElements, sizeof(CountOfSubElements), 1, pMyUserData->fp);
					
					CPlacementPerm* pHeader = new CPlacementPerm(PLACEMENT_PERM_ENTRY_TYPE_HEADER);
					pHeader->SetReaderPointer(pMyUserData->pReader);
					SetStringCanBeDefault(pHeader->UnknownParam1inBullyScholarschip, p.UnknownParam1inBullyScholarschip);
					pHeader->UnknownParam2inBullyScholarschip = p.UnknownParam2inBullyScholarschip;
					pHeader->UnknownParam3inBullyScholarschip = p.UnknownParam3inBullyScholarschip;
					pHeader->UnknownParam4inBullyScholarschip = p.UnknownParam4inBullyScholarschip;
					AddBullyEntry(pMyUserData, pHeader);
					
					for (unsigned int i = 0; i < CountOfSubElements; i++)
					{
						float FloatValue;
						fread(&FloatValue, sizeof(FloatValue), 1, pMyUserData->fp);
					
						CPlacementPerm* pPos = new CPlacementPerm(PLACEMENT_PERM_ENTRY_TYPE_SUB_ENTRY);
						pPos->SetReaderPointer(pMyUserData->pReader);
						pPos->FloatValue = FloatValue;
						AddBullyEntry(pMyUserData, pPos);	
					}

					return true;
				},
					NULL
			},

			{
				SECTION_IPL_PONT,
				'tnop',
					[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;
										
					tPontParams p;

					FileReadPascalString(pMyUserData->fp, p.UnknownParam1inBullyScholarschip, sizeof(p.UnknownParam1inBullyScholarschip));
					fread(&p.UnknownParam2inBullyScholarschip, sizeof(p.UnknownParam2inBullyScholarschip), 1, pMyUserData->fp);
					fread(&p.Pos, sizeof(p.Pos), 1, pMyUserData->fp);
					fread(&p.Rot, sizeof(p.Rot), 1, pMyUserData->fp);
					fread(&p.UnknownParam9inBullyScholarschip, sizeof(p.UnknownParam9inBullyScholarschip), 1, pMyUserData->fp);
					FileReadPascalString(pMyUserData->fp, p.UnknownParam10inBullyScholarschip, sizeof(p.UnknownParam10inBullyScholarschip));
					FileReadPascalString(pMyUserData->fp, p.UnknownParam11inBullyScholarschip, sizeof(p.UnknownParam11inBullyScholarschip));
					FileReadPascalString(pMyUserData->fp, p.UnknownParam12inBullyScholarschip, sizeof(p.UnknownParam12inBullyScholarschip));
					fread(&p.UnknownParamsFrom13inBullyScholarschip, sizeof(p.UnknownParamsFrom13inBullyScholarschip), 1, pMyUserData->fp);
					FileReadPascalString(pMyUserData->fp, p.UnknownParam19inBullyScholarschip, sizeof(p.UnknownParam19inBullyScholarschip));
					FileReadPascalString(pMyUserData->fp, p.UnknownParam20inBullyScholarschip, sizeof(p.UnknownParam20inBullyScholarschip));

					CPlacementPont* pPlacement = new CPlacementPont();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->UnknownParam1inBullyScholarschip = p.UnknownParam1inBullyScholarschip;
					pPlacement->UnknownParam2inBullyScholarschip = p.UnknownParam2inBullyScholarschip;
					pPlacement->Pos = p.Pos;
					pPlacement->Rot = p.Rot;
					pPlacement->UnknownParam9inBullyScholarschip = p.UnknownParam9inBullyScholarschip;
					SetStringCanBeDefault(pPlacement->UnknownParam10inBullyScholarschip, p.UnknownParam10inBullyScholarschip);					
					SetStringCanBeDefault(pPlacement->UnknownParam11inBullyScholarschip, p.UnknownParam11inBullyScholarschip);
					SetStringCanBeDefault(pPlacement->UnknownParam12inBullyScholarschip, p.UnknownParam12inBullyScholarschip);
					pPlacement->UnknownParam13inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[0];
					pPlacement->UnknownParam14inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[1];
					pPlacement->UnknownParam15inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[2];
					pPlacement->UnknownParam16inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[3];
					pPlacement->UnknownParam17inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[4];
					pPlacement->UnknownParam18inBullyScholarschip = p.UnknownParamsFrom13inBullyScholarschip[5];
					SetStringCanBeDefault(pPlacement->UnknownParam19inBullyScholarschip, p.UnknownParam19inBullyScholarschip);
					SetStringCanBeDefault(pPlacement->UnknownParam20inBullyScholarschip, p.UnknownParam20inBullyScholarschip);

					AddBullyEntry(pMyUserData, pPlacement);
					return true;
				},
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionStandardUserData* pMyUserData = (tBinarySectionStandardUserData*)pUserData;
					const CPlacementPont* pPlacement = (const CPlacementPont*)ptr;
					FILE* fp = pMyUserData->fp;

					FileWritePascalString(fp, pPlacement->UnknownParam1inBullyScholarschip.c_str());
					FileWriteInt32(fp, pPlacement->UnknownParam2inBullyScholarschip);
					fwrite(&pPlacement->Pos, sizeof(pPlacement->Pos), 1, fp);
					fwrite(&pPlacement->Rot, sizeof(pPlacement->Rot), 1, fp);
					fwrite(
						&pPlacement->UnknownParam9inBullyScholarschip,
						sizeof(pPlacement->UnknownParam9inBullyScholarschip),
						1,
						fp);
					FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownParam10inBullyScholarschip.c_str());
					FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownParam11inBullyScholarschip.c_str());
					FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownParam12inBullyScholarschip.c_str());
					FileWriteInt32(fp, pPlacement->UnknownParam13inBullyScholarschip);
					FileWriteInt32(fp, pPlacement->UnknownParam14inBullyScholarschip);
					FileWriteInt32(fp, pPlacement->UnknownParam15inBullyScholarschip);
					FileWriteInt32(fp, pPlacement->UnknownParam16inBullyScholarschip);
					FileWriteInt32(fp, pPlacement->UnknownParam17inBullyScholarschip);
					FileWriteInt32(fp, pPlacement->UnknownParam18inBullyScholarschip);
					FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownParam19inBullyScholarschip.c_str());
					FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownParam20inBullyScholarschip.c_str());
				}
			},

			{
				SECTION_IPL_POIS,
				'siop',
					[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;
					FILE* fp = pMyUserData->fp;

					/*
						pascal_string
						4 byte value
						4 byte value count

						array[number of elements according to count]
						{
						1, pascal_string
						2, pascal_string (seems empty)
						3, pascal_string
						4, pascal_string
						5, int32 value
						6, CVector Pos
						9, CVector Rot
						12, 11 DWORD values, casted into boolean values later on
						23, float
						24, DWORD value, casted into boolean values later on
						25, byte
						}
					*/

					tPoisParams p;

					CPlacementPois* pHeader = new CPlacementPois(PLACEMENT_POIS_ENTRY_TYPE_HEADER);
					pHeader->SetReaderPointer(pMyUserData->pReader);
					
					FileReadPascalString(fp, p.UnknownHeaderParam1inBullyScholarschip, sizeof(p.UnknownHeaderParam1inBullyScholarschip));
					fread(&p.UnknownHeaderParam2inBullyScholarschip, sizeof(p.UnknownHeaderParam2inBullyScholarschip), 1, fp);

					pHeader->UnknownHeaderParam1inBullyScholarschip = p.UnknownHeaderParam1inBullyScholarschip;
					pHeader->UnknownHeaderParam2inBullyScholarschip = p.UnknownHeaderParam2inBullyScholarschip;

					AddBullyEntry(pMyUserData, pHeader);
					
					fread(&p.CountOfElements, sizeof(p.CountOfElements), 1, fp);
					
					for (int i = 0; i < p.CountOfElements; i++)
					{
						FileReadPascalString(fp, p.UnknownElementParam1inBullyScholarschip, sizeof(p.UnknownElementParam1inBullyScholarschip));
						FileReadPascalString(fp, p.UnknownElementParam2inBullyScholarschip, sizeof(p.UnknownElementParam2inBullyScholarschip));
						FileReadPascalString(fp, p.UnknownElementParam3inBullyScholarschip, sizeof(p.UnknownElementParam3inBullyScholarschip));
						FileReadPascalString(fp, p.UnknownElementParam4inBullyScholarschip, sizeof(p.UnknownElementParam4inBullyScholarschip));
						
						fread(&p.UnknownElementParam5inBullyScholarschip, sizeof(p.UnknownElementParam5inBullyScholarschip), 1, fp);

						fread(&p.Pos, sizeof(p.Pos), 1, fp);
						fread(&p.Rot, sizeof(p.Rot), 1, fp);

						fread(p.UnknownParamsFrom12inBullyScholarschip, sizeof(p.UnknownParamsFrom12inBullyScholarschip), 1, fp);

						fread(&p.UnknownElementParam23inBullyScholarschip, sizeof(p.UnknownElementParam23inBullyScholarschip), 1, fp);

						fread(&p.UnknownElementParam24inBullyScholarschip, sizeof(p.UnknownElementParam24inBullyScholarschip), 1, fp);
						fread(&p.UnknownElementParam25inBullyScholarschip, sizeof(p.UnknownElementParam25inBullyScholarschip), 1, fp);
						
						CPlacementPois* pElement = new CPlacementPois(PLACEMENT_POIS_ENTRY_TYPE_ELEMENT);
						pElement->SetReaderPointer(pMyUserData->pReader);
						
						pElement->UnknownElementParam1inBullyScholarschip = p.UnknownElementParam1inBullyScholarschip;
						SetStringCanBeDefault(pElement->UnknownElementParam2inBullyScholarschip, p.UnknownElementParam2inBullyScholarschip);
						pElement->UnknownElementParam3inBullyScholarschip = p.UnknownElementParam3inBullyScholarschip;
						pElement->UnknownElementParam4inBullyScholarschip = p.UnknownElementParam4inBullyScholarschip;
						pElement->UnknownElementParam5inBullyScholarschip = p.UnknownElementParam5inBullyScholarschip;
						pElement->Pos = p.Pos;
						pElement->Rot = p.Rot;

						pElement->UnknownElementParam12inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[0];
						pElement->UnknownElementParam13inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[1];
						pElement->UnknownElementParam14inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[2];
						pElement->UnknownElementParam15inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[3];
						pElement->UnknownElementParam16inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[4];
						pElement->UnknownElementParam17inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[5];
						pElement->UnknownElementParam18inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[6];
						pElement->UnknownElementParam19inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[7];
						pElement->UnknownElementParam20inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[8];
						pElement->UnknownElementParam21inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[9];
						pElement->UnknownElementParam22inBullyScholarschip = p.UnknownParamsFrom12inBullyScholarschip[10];
						pElement->UnknownElementParam23inBullyScholarschip = p.UnknownElementParam23inBullyScholarschip;
						pElement->UnknownElementParam24inBullyScholarschip = p.UnknownElementParam24inBullyScholarschip;
						pElement->UnknownElementParam25inBullyScholarschip = p.UnknownElementParam25inBullyScholarschip;

						AddBullyEntry(pMyUserData, pElement);
					}
										
					return true;
				},
				NULL
			},

			{
				SECTION_IPL_OCCL,
				'lcco',
					[](void* pUserData)
				{
					tBinarySectionBullyScholarshipUserData* pMyUserData = (tBinarySectionBullyScholarshipUserData*)pUserData;
					IPLfileReaderEx* pIPLreader = (IPLfileReaderEx*)pMyUserData->pReader;

					CFileOcclusionInBullyScholarship data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return false;

					CPlacementOcclusion* pPlacement = new CPlacementOcclusion();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->MidX = data.midX;
					pPlacement->MidY = data.midY;
					pPlacement->BottomZ = data.midZ;
					pPlacement->WidthX = data.widthX;
					pPlacement->WidthY = data.widthY;
					pPlacement->Height = data.height;
					pPlacement->Rot.z = data.angle;

					AddBullyEntry(pMyUserData, pPlacement);
					return true;

				},
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionStandardUserData* pMyUserData = (tBinarySectionStandardUserData*)pUserData;
					const CPlacementOcclusion* pPlacement = (const CPlacementOcclusion*)ptr;

					CFileOcclusionInBullyScholarship data = { 0 };

					data.midX = pPlacement->MidX;
					data.midY = pPlacement->MidY;
					data.midZ = pPlacement->BottomZ;
					data.widthX = pPlacement->WidthX;
					data.widthY = pPlacement->WidthY;
					data.height = pPlacement->Height;
					data.angle = pPlacement->Rot.z;

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				}
			},

			{
				SECTION_UNDEFINED,
				NULL,
				NULL,
				NULL
			}
		};

		const int GTAIVnumberOfSections = 16;

		struct tGTAIVbinarySectionDescriptor
		{
			int sectionType;
			unsigned int sectionSizeWhenNotImplemented;
			CPlacementBaseInfo* (*LoadFunc)(void* pUserData);
			void(*SaveFunc)(void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr);
			int sectionIndexInCountArray;
		};

		struct tBinarySectionGTAIVUserData : tBinarySectionStandardUserData
		{
			eGameNameSimplified gameSimple;
			eValueEncoding valueEncoding;


			// used in save function
			unsigned int sectionNumInFile;
			unsigned __int32* pSectionCountArray;
		};
		
#define DEFINE_GTAIV_UNSUPPORTED_SECTION(sectionIdentifier, itemSize, indexInCountArray) \
	{ sectionIdentifier, itemSize, NULL, NULL, indexInCountArray }

		// GTA IV descriptor array
		static const struct tGTAIVbinarySectionDescriptor GTAIVDescriptors[] =
		{
			// section 0
			{
				SECTION_IPL_INST,
				NULL,
				[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileObjectInstanceVersion3InGTAIV_variedEncoding data;
					
					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementObjectInstance* pPlacement = new CPlacementObjectInstance();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->Pos.x = data.Pos.x.GetValue(valueEncoding);
					pPlacement->Pos.y = data.Pos.y.GetValue(valueEncoding);
					pPlacement->Pos.z = data.Pos.z.GetValue(valueEncoding);

					pPlacement->Rot.imag.x = data.Rot.imag.x.GetValue(valueEncoding);
					pPlacement->Rot.imag.y = data.Rot.imag.y.GetValue(valueEncoding);
					pPlacement->Rot.imag.z = data.Rot.imag.z.GetValue(valueEncoding);
					pPlacement->Rot.real = data.Rot.real.GetValue(valueEncoding);

					pPlacement->ModelName.SetHashAndString(
						pMyUserData->gameSimple, data.ModelNameHash.GetValue(valueEncoding)
						);					

					pPlacement->Flags = data.Flags.GetValue(valueEncoding);
					pPlacement->LODnum = data.LODindex.GetValue(valueEncoding);
					pPlacement->UnknownParam11inGTAIV = data.field_28.GetValue(valueEncoding);
					pPlacement->UnknownParam12inGTAIV = data.field_2C.GetValue(valueEncoding);

					return pPlacement;
				},
				[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementObjectInstance* pPlacement = (const CPlacementObjectInstance*)ptr;

					CFileObjectInstanceVersion3InGTAIV_variedEncoding data;
					
					data.Pos.x.SetValue(pPlacement->Pos.x, valueEncoding);
					data.Pos.y.SetValue(pPlacement->Pos.y, valueEncoding);
					data.Pos.z.SetValue(pPlacement->Pos.z, valueEncoding);

					data.Rot.imag.x.SetValue(pPlacement->Rot.imag.x, valueEncoding);
					data.Rot.imag.y.SetValue(pPlacement->Rot.imag.y, valueEncoding);
					data.Rot.imag.z.SetValue(pPlacement->Rot.imag.z, valueEncoding);
					data.Rot.real.SetValue(pPlacement->Rot.real, valueEncoding);										

					data.ModelNameHash.SetValue(pPlacement->ModelName.GetHash(), valueEncoding);
					data.Flags.SetValue(pPlacement->Flags, valueEncoding);
					data.LODindex.SetValue(pPlacement->LODnum, valueEncoding);
					data.field_28.SetValue(pPlacement->UnknownParam11inGTAIV, valueEncoding);
					data.field_2C.SetValue(pPlacement->UnknownParam12inGTAIV, valueEncoding);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				}
				,
					0
			},

			// section 1
			{
				SECTION_IPL_ZONE,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileZoneInGTAIV_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementZone* pPlacement = new CPlacementZone();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->ZoneName = data.ZoneName;
					pPlacement->GXTlabel = data.GXTlabel;

					pPlacement->BoxCornerFirst.x = data.BoxCornerFirst.x.GetValue(valueEncoding);
					pPlacement->BoxCornerFirst.y = data.BoxCornerFirst.y.GetValue(valueEncoding);
					pPlacement->BoxCornerFirst.z = data.BoxCornerFirst.z.GetValue(valueEncoding);

					pPlacement->BoxCornerSecond.x = data.BoxCornerSecond.x.GetValue(valueEncoding);
					pPlacement->BoxCornerSecond.y = data.BoxCornerSecond.y.GetValue(valueEncoding);
					pPlacement->BoxCornerSecond.z = data.BoxCornerSecond.z.GetValue(valueEncoding);

					return pPlacement;
				},

					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementZone* pPlacement = (const CPlacementZone*)ptr;

					CFileZoneInGTAIV_variedEncoding data;
					
					strncpy(data.ZoneName,
						pPlacement->ZoneName.c_str(),
						sizeof(data.ZoneName)
						);

					strncpy(data.GXTlabel,
						pPlacement->GXTlabel.c_str(),
						sizeof(data.GXTlabel)
						);


					data.BoxCornerFirst.x.SetValue(pPlacement->BoxCornerFirst.x, valueEncoding);
					data.BoxCornerFirst.y.SetValue(pPlacement->BoxCornerFirst.y, valueEncoding);
					data.BoxCornerFirst.z.SetValue(pPlacement->BoxCornerFirst.z, valueEncoding);

					data.BoxCornerSecond.x.SetValue(pPlacement->BoxCornerSecond.x, valueEncoding);
					data.BoxCornerSecond.y.SetValue(pPlacement->BoxCornerSecond.y, valueEncoding);
					data.BoxCornerSecond.z.SetValue(pPlacement->BoxCornerSecond.z, valueEncoding);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					1
			},

			// section 2
			{
				SECTION_IPL_GRGE,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileGarageInGTAIV_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementGarage* pPlacement = new CPlacementGarage();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->Pos.x = data.Pos.x.GetValue(valueEncoding);
					pPlacement->Pos.y = data.Pos.y.GetValue(valueEncoding);
					pPlacement->Pos.z = data.Pos.z.GetValue(valueEncoding);

					pPlacement->Line.x = data.Line.x.GetValue(valueEncoding);
					pPlacement->Line.y = data.Line.y.GetValue(valueEncoding);

					pPlacement->Cube.x = data.Cube.x.GetValue(valueEncoding);
					pPlacement->Cube.y = data.Cube.y.GetValue(valueEncoding);
					pPlacement->Cube.z = data.Cube.z.GetValue(valueEncoding);

					pPlacement->Flags = data.Flags.GetValue(valueEncoding);
					pPlacement->Type = data.Type.GetValue(valueEncoding);
					pPlacement->Name = data.Name;

					return pPlacement;
				},

					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementGarage* pPlacement = (const CPlacementGarage*)ptr;

					CFileGarageInGTAIV_variedEncoding data;

					data.Pos.x.SetValue(pPlacement->Pos.x, valueEncoding);
					data.Pos.y.SetValue(pPlacement->Pos.y, valueEncoding);
					data.Pos.z.SetValue(pPlacement->Pos.z, valueEncoding);

					data.Line.x.SetValue(pPlacement->Line.x, valueEncoding);
					data.Line.y.SetValue(pPlacement->Line.y, valueEncoding);

					data.Cube.x.SetValue(pPlacement->Cube.x, valueEncoding);
					data.Cube.y.SetValue(pPlacement->Cube.y, valueEncoding);
					data.Cube.z.SetValue(pPlacement->Cube.z, valueEncoding);

					data.Flags.SetValue(pPlacement->Flags, valueEncoding);
					data.Type.SetValue(pPlacement->Type, valueEncoding);

					strncpy(data.Name,
						pPlacement->Name.c_str(),
						sizeof(data.Name)
						);


					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					2
			},

			// section 3
			{
				SECTION_IPL_CARS,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileCarGeneratorInGTAIV_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementCarGenerator* pPlacement = new CPlacementCarGenerator();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->Pos.x = data.Pos.x.GetValue(valueEncoding);
					pPlacement->Pos.y = data.Pos.y.GetValue(valueEncoding);
					pPlacement->Pos.z = data.Pos.z.GetValue(valueEncoding);

					pPlacement->Rot.x = data.Rot.x.GetValue(valueEncoding);
					pPlacement->Rot.y = data.Rot.y.GetValue(valueEncoding);
					pPlacement->Rot.z = data.Rot.z.GetValue(valueEncoding);

					pPlacement->ModelName.SetHashAndString(
						pMyUserData->gameSimple, data.ModelNameHash.GetValue(valueEncoding)
						);

					pPlacement->PrimCol = data.PrimCol.GetValue(valueEncoding);
					pPlacement->SecCol = data.SecCol.GetValue(valueEncoding);
					pPlacement->ThirdColor = data.ThirdColor.GetValue(valueEncoding);
					pPlacement->SpecularColor = data.SpecularColor.GetValue(valueEncoding);
					pPlacement->Flags = data.Flags.GetValue(valueEncoding);
					pPlacement->AlarmProbability = data.AlarmProbability.GetValue(valueEncoding);
					pPlacement->DoorLockProbability = data.DoorLockProbability.GetValue(valueEncoding);

					return pPlacement;
				},
					
					
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementCarGenerator* pPlacement = (const CPlacementCarGenerator*)ptr;

					CFileCarGeneratorInGTAIV_variedEncoding data;

					data.Pos.x.SetValue(pPlacement->Pos.x, valueEncoding);
					data.Pos.y.SetValue(pPlacement->Pos.y, valueEncoding);
					data.Pos.z.SetValue(pPlacement->Pos.z, valueEncoding);

					data.Rot.x.SetValue(pPlacement->Rot.x, valueEncoding);
					data.Rot.y.SetValue(pPlacement->Rot.y, valueEncoding);
					data.Rot.z.SetValue(pPlacement->Rot.z, valueEncoding);

					data.ModelNameHash.SetValue(pPlacement->ModelName.GetHash(), valueEncoding);

					data.PrimCol.SetValue(pPlacement->PrimCol, valueEncoding);
					data.SecCol.SetValue(pPlacement->SecCol, valueEncoding);
					data.ThirdColor.SetValue(pPlacement->ThirdColor, valueEncoding);
					data.SpecularColor.SetValue(pPlacement->SpecularColor, valueEncoding);

					data.Flags.SetValue(pPlacement->Flags, valueEncoding);
					data.AlarmProbability.SetValue(pPlacement->AlarmProbability, valueEncoding);
					data.DoorLockProbability.SetValue(pPlacement->DoorLockProbability, valueEncoding);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
				3
			},

			// DEFINE_GTAIV_UNSUPPORTED_SECTION(SECTION_TCYC, 44, 4),	// section 4

			// section 4
			{
				SECTION_IPL_TCYC,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					
					CFileTimecycleModifier_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementTimecycleModifier* pPlacement = new CPlacementTimecycleModifier();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->Box.m_vInf.x = data.Box.m_vInf.x.GetValue(valueEncoding);
					pPlacement->Box.m_vInf.y = data.Box.m_vInf.y.GetValue(valueEncoding);
					pPlacement->Box.m_vInf.z = data.Box.m_vInf.z.GetValue(valueEncoding);

					pPlacement->Box.m_vSup.x = data.Box.m_vSup.x.GetValue(valueEncoding);
					pPlacement->Box.m_vSup.y = data.Box.m_vSup.y.GetValue(valueEncoding);
					pPlacement->Box.m_vSup.z = data.Box.m_vSup.z.GetValue(valueEncoding);

					pPlacement->UnknownParam7inGTAIV = data.UnknownParam7inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam8inGTAIV = data.UnknownParam8inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam9inGTAIV = data.UnknownParam9inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam10inGTAIV = data.UnknownParam10inGTAIV.GetValue(valueEncoding);

					pPlacement->ModifierName.SetHashAndString(
						pMyUserData->gameSimple,
						data.ModifierNameHash.GetValue(valueEncoding)
						);

					return pPlacement;
				},
					
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementTimecycleModifier* pPlacement = (const CPlacementTimecycleModifier*)ptr;

					CFileTimecycleModifier_variedEncoding data;

					data.Box.m_vInf.x.SetValue(pPlacement->Box.m_vInf.x, valueEncoding);
					data.Box.m_vInf.y.SetValue(pPlacement->Box.m_vInf.y, valueEncoding);
					data.Box.m_vInf.z.SetValue(pPlacement->Box.m_vInf.z, valueEncoding);

					data.Box.m_vSup.x.SetValue(pPlacement->Box.m_vSup.x, valueEncoding);
					data.Box.m_vSup.y.SetValue(pPlacement->Box.m_vSup.y, valueEncoding);
					data.Box.m_vSup.z.SetValue(pPlacement->Box.m_vSup.z, valueEncoding);

					data.UnknownParam7inGTAIV.SetValue(pPlacement->UnknownParam7inGTAIV, valueEncoding);
					data.UnknownParam8inGTAIV.SetValue(pPlacement->UnknownParam8inGTAIV, valueEncoding);
					data.UnknownParam9inGTAIV.SetValue(pPlacement->UnknownParam9inGTAIV, valueEncoding);
					data.UnknownParam10inGTAIV.SetValue(pPlacement->UnknownParam10inGTAIV, valueEncoding);
					data.ModifierNameHash.SetValue(pPlacement->ModifierName.GetHash(), valueEncoding);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					4
			},

			// section 5
			{
				SECTION_IPL_VNOD,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileVehicleNode_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementVehicleNode* pPlacement = new CPlacementVehicleNode();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->Pos.x = data.Pos.x.GetValue(valueEncoding);
					pPlacement->Pos.y = data.Pos.y.GetValue(valueEncoding);
					pPlacement->Pos.z = data.Pos.z.GetValue(valueEncoding);

					pPlacement->UnknownParam4inGTAIV = data.UnknownParam4inGTAIV.GetValue(valueEncoding) != 0;
					pPlacement->UnknownParam5inGTAIV = data.UnknownParam5inGTAIV.GetValue(valueEncoding) != 0;
					pPlacement->UnknownParam6inGTAIV = data.UnknownParam6inGTAIV.GetValue(valueEncoding) != 0;
					pPlacement->UnknownParam7inGTAIV = data.UnknownParam7inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam8inGTAIV = data.UnknownParam8inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam9inGTAIV = data.UnknownParam9inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam10inGTAIV = data.UnknownParam10inGTAIV.GetValue(valueEncoding);

					unsigned __int32 Flags = data.Flags.GetValue(valueEncoding);					
					pPlacement->UnknownParam11inGTAIV = BitwiseOperation::TestBit(Flags, 0);
					pPlacement->UnknownParam12inGTAIV = BitwiseOperation::TestBit(Flags, 1);
					pPlacement->UnknownParam13inGTAIV = BitwiseOperation::TestBit(Flags, 2);

					return pPlacement;
				},


					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementVehicleNode* pPlacement = (const CPlacementVehicleNode*)ptr;

					CFileVehicleNode_variedEncoding data;

					data.Pos.x.SetValue(pPlacement->Pos.x, valueEncoding);
					data.Pos.y.SetValue(pPlacement->Pos.y, valueEncoding);
					data.Pos.z.SetValue(pPlacement->Pos.z, valueEncoding);

					data.UnknownParam4inGTAIV.SetValue(pPlacement->UnknownParam4inGTAIV, valueEncoding);
					data.UnknownParam5inGTAIV.SetValue(pPlacement->UnknownParam5inGTAIV, valueEncoding);
					data.UnknownParam6inGTAIV.SetValue(pPlacement->UnknownParam6inGTAIV, valueEncoding);
					data.UnknownParam7inGTAIV.SetValue(pPlacement->UnknownParam7inGTAIV, valueEncoding);
					data.UnknownParam8inGTAIV.SetValue(pPlacement->UnknownParam8inGTAIV, valueEncoding);
					data.UnknownParam9inGTAIV.SetValue(pPlacement->UnknownParam9inGTAIV, valueEncoding);
					data.UnknownParam10inGTAIV.SetValue(pPlacement->UnknownParam10inGTAIV, valueEncoding);

					unsigned __int32 Flags = 0;

					Flags = BitwiseOperation::ChangeOneBit(Flags, 0, pPlacement->UnknownParam11inGTAIV);
					Flags = BitwiseOperation::ChangeOneBit(Flags, 1, pPlacement->UnknownParam12inGTAIV);
					Flags = BitwiseOperation::ChangeOneBit(Flags, 2, pPlacement->UnknownParam13inGTAIV);

					data.Flags.SetValue(Flags, valueEncoding);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					5
			},

			// section 6
			{
				SECTION_IPL_LINK,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileLink_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementLink* pPlacement = new CPlacementLink();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->UnknownParam1inGTAIV = data.UnknownParam1inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam2inGTAIV = data.UnknownParam2inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam3inGTAIV = data.UnknownParam3inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam4inGTAIV = data.UnknownParam4inGTAIV.GetValue(valueEncoding);
					pPlacement->UnknownParam5inGTAIV = data.UnknownParam5inGTAIV.GetValue(valueEncoding);
					pPlacement->Flags = 0;

					return pPlacement;
				},


					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementLink* pPlacement = (const CPlacementLink*)ptr;

					CFileLink_variedEncoding data;

					data.UnknownParam1inGTAIV.SetValue(pPlacement->UnknownParam1inGTAIV, valueEncoding);
					data.UnknownParam2inGTAIV.SetValue(pPlacement->UnknownParam2inGTAIV, valueEncoding);
					data.UnknownParam3inGTAIV.SetValue(pPlacement->UnknownParam3inGTAIV, valueEncoding);
					data.UnknownParam4inGTAIV.SetValue(pPlacement->UnknownParam4inGTAIV, valueEncoding);
					data.UnknownParam5inGTAIV.SetValue(pPlacement->UnknownParam5inGTAIV, valueEncoding);

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					6
			},


			// section 15
			{
				SECTION_IPL_BLOK,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileBlok_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementBlok* pPlacement = new CPlacementBlok();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					while(true)
					{
						const char* pStr = NULL;

						if (pStr = strtok(data.Description, ","))
							pPlacement->BlockName = pStr;
						else
							break;

						if (pStr = strtok(NULL, ","))
							pPlacement->UnknownParam6inGTAIV = pStr;
						else
							break;

						if (pStr = strtok(NULL, ","))
							pPlacement->Author = pStr;
						else
							break;

						if (pStr = strtok(NULL, ","))
							pPlacement->DateTime = pStr;

						break;
					}

					pPlacement->UnknownParam4inGTAIV = data.UnknownParam4inGTAIV.GetValue(valueEncoding);
					
					for (int i = 0; i < _countof(pPlacement->CornerPoints); i++)
					{
						pPlacement->CornerPoints[i].x = data.CornerPoints[i].x.GetValue(valueEncoding);
						pPlacement->CornerPoints[i].y = data.CornerPoints[i].y.GetValue(valueEncoding);
					}

					return pPlacement;
				},
					
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementBlok* pPlacement = (const CPlacementBlok*)ptr;

					CFileBlok_variedEncoding data;

					data.Always1.SetValue(1, valueEncoding);					

					{
						std::string Description
							= pPlacement->BlockName + "," + pPlacement->UnknownParam6inGTAIV
							+ "," + pPlacement->Author + "," + pPlacement->DateTime;
						
						strncpy(data.Description, Description.c_str(), sizeof(data.Description));
					}

					data.UnknownParam4inGTAIV.SetValue(pPlacement->UnknownParam4inGTAIV, valueEncoding);
					
					for (int i = 0; i < _countof(pPlacement->CornerPoints); i++)
					{
						data.CornerPoints[i].x.SetValue(pPlacement->CornerPoints[i].x, valueEncoding);
						data.CornerPoints[i].y.SetValue(pPlacement->CornerPoints[i].y, valueEncoding);
					}

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					15
			},

			// section 8
			{
				SECTION_IPL_MLO_PLUS,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileMloInBinaryFile_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementMlo* pPlacement = new CPlacementMlo();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->ModelName.SetStringAndHash(
						pMyUserData->gameSimple,
						data.ModelName);

					pPlacement->Flags = data.Flags.GetValue(valueEncoding);;
					pPlacement->InstMloIndex = data.InstMloIndex.GetValue(valueEncoding);
					pPlacement->CountParam5inGTAIV = data.CountParam5inGTAIV.GetValue(valueEncoding);

					pPlacement->Pos.x = data.Pos.x.GetValue(valueEncoding);
					pPlacement->Pos.y = data.Pos.y.GetValue(valueEncoding);
					pPlacement->Pos.z = data.Pos.z.GetValue(valueEncoding);

					pPlacement->Rot.imag.x = data.Rot.imag.x.GetValue(valueEncoding);
					pPlacement->Rot.imag.y = data.Rot.imag.y.GetValue(valueEncoding);
					pPlacement->Rot.imag.z = data.Rot.imag.z.GetValue(valueEncoding);
					pPlacement->Rot.real = data.Rot.real.GetValue(valueEncoding);

					return pPlacement;
				},


					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementMlo* pPlacement = (const CPlacementMlo*)ptr;

					CFileMloInBinaryFile_variedEncoding data;

					strncpy(data.ModelName,
						pPlacement->ModelName.GetString().c_str(),
						sizeof(data.ModelName)
						);

					data.Flags.SetValue(pPlacement->Flags, valueEncoding);
					data.InstMloIndex.SetValue(pPlacement->InstMloIndex, valueEncoding);
					data.CountParam5inGTAIV.SetValue(pPlacement->CountParam5inGTAIV, valueEncoding);

					data.Pos.x.SetValue(pPlacement->Pos.x, valueEncoding);
					data.Pos.y.SetValue(pPlacement->Pos.y, valueEncoding);
					data.Pos.z.SetValue(pPlacement->Pos.z, valueEncoding);
					
					data.Rot.imag.x.SetValue(pPlacement->Rot.imag.x, valueEncoding);
					data.Rot.imag.y.SetValue(pPlacement->Rot.imag.y, valueEncoding);
					data.Rot.imag.z.SetValue(pPlacement->Rot.imag.z, valueEncoding);
					data.Rot.real.SetValue(pPlacement->Rot.real, valueEncoding);



					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					8
			},

			// section 9
			{
				SECTION_IPL_LODM,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileLodm_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementLodm* pPlacement = new CPlacementLodm();
					pPlacement->SetReaderPointer(pMyUserData->pReader);

					pPlacement->Box.m_vInf.x = data.Box.m_vInf.x.GetValue(valueEncoding);
					pPlacement->Box.m_vInf.y = data.Box.m_vInf.y.GetValue(valueEncoding);
					pPlacement->Box.m_vInf.z = data.Box.m_vInf.z.GetValue(valueEncoding);

					pPlacement->Box.m_vSup.x = data.Box.m_vSup.x.GetValue(valueEncoding);
					pPlacement->Box.m_vSup.y = data.Box.m_vSup.y.GetValue(valueEncoding);
					pPlacement->Box.m_vSup.z = data.Box.m_vSup.z.GetValue(valueEncoding);

					int Flags = data.Flags.GetValue(valueEncoding);
					pPlacement->CountOfModels = BitwiseOperation::ReadValueFromBits(Flags, 0, 4);

					if (pPlacement->CountOfModels > _countof(data.ModelNameHashes))
						pPlacement->CountOfModels = _countof(data.ModelNameHashes);

					if(pPlacement->CountOfModels > _countof(pPlacement->ModelNameArray))
						pPlacement->CountOfModels = _countof(pPlacement->ModelNameArray);					

					pPlacement->UnknownParamFlagPosition24inGTAIV = BitwiseOperation::ReadValueFromBits(Flags, 24, 8);

					for (unsigned int i = 0; i < pPlacement->CountOfModels; i++)
					{
						pPlacement->ModelNameArray[i].SetHashAndString(
							pMyUserData->gameSimple,
							data.ModelNameHashes[i].GetValue(valueEncoding)
							);

						pPlacement->ModelNameArray[i].SetStringAndHash(
							pMyUserData->gameSimple,
							data.ModelNames[i],
							false);
					}

					return pPlacement;
				},

										
					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementLodm* pPlacement = (const CPlacementLodm*)ptr;

					CFileLodm_variedEncoding data;

					data.Box.m_vInf.x.SetValue(pPlacement->Box.m_vInf.x, valueEncoding);
					data.Box.m_vInf.y.SetValue(pPlacement->Box.m_vInf.y, valueEncoding);
					data.Box.m_vInf.z.SetValue(pPlacement->Box.m_vInf.z, valueEncoding);

					data.Box.m_vSup.x.SetValue(pPlacement->Box.m_vSup.x, valueEncoding);
					data.Box.m_vSup.y.SetValue(pPlacement->Box.m_vSup.y, valueEncoding);
					data.Box.m_vSup.z.SetValue(pPlacement->Box.m_vSup.z, valueEncoding);

					unsigned int CountOfModels = pPlacement->CountOfModels;

					if (CountOfModels > _countof(data.ModelNameHashes))
						CountOfModels = _countof(data.ModelNameHashes);

					int Flags = (CountOfModels & 0xF) | (pPlacement->UnknownParamFlagPosition24inGTAIV << 24);

					data.Flags.SetValue(Flags, valueEncoding);
					
					// initialize arrays
					for (unsigned int i = 0; i < NUMBER_OF_HASHES_IN_GTAIV_LODM; i++)
					{
						data.ModelNameHashes[i].SetValue(0, valueEncoding);
						*data.ModelNames[i] = NULL;
					}
					
					// write into arrays
					for (unsigned int i = 0; i < CountOfModels; i++)
					{
						data.ModelNameHashes[i].SetValue(pPlacement->ModelNameArray[i].GetHash(), valueEncoding);

						strncpy(
							data.ModelNames[i],
							pPlacement->ModelNameArray[i].GetString().c_str(),
							_countof(data.ModelNames[i])
							);
					}

					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},				
					9
			},

			// section 10
			{
				SECTION_IPL_SLOW,
				NULL,
					[](void* pUserData) -> CPlacementBaseInfo*
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;

					CFileSlow_variedEncoding data;

					if (!fread(&data, sizeof(data), 1, pMyUserData->fp))
						return NULL;

					CPlacementSlow* pPlacement = new CPlacementSlow();
					pPlacement->SetReaderPointer(pMyUserData->pReader);
					
					pPlacement->Box.m_vInf.x = data.m_vInf.x.GetValue(valueEncoding);
					pPlacement->Box.m_vInf.y = data.m_vInf.y.GetValue(valueEncoding);
					pPlacement->Box.m_vInf.z = data.m_vInf.z.GetValue(valueEncoding);

					pPlacement->Box.m_vSup.x = data.m_vSup.x.GetValue(valueEncoding);
					pPlacement->Box.m_vSup.y = data.m_vSup.y.GetValue(valueEncoding);
					pPlacement->Box.m_vSup.z = data.m_vSup.z.GetValue(valueEncoding);

					return pPlacement;
				},


					[](void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr)
				{
					tBinarySectionGTAIVUserData* pMyUserData = (tBinarySectionGTAIVUserData*)pUserData;
					eValueEncoding valueEncoding = pMyUserData->valueEncoding;
					const CPlacementSlow* pPlacement = (const CPlacementSlow*)ptr;

					CFileSlow_variedEncoding data;

					data.m_vInf.x.SetValue(pPlacement->Box.m_vInf.x, valueEncoding);
					data.m_vInf.y.SetValue(pPlacement->Box.m_vInf.y, valueEncoding);
					data.m_vInf.z.SetValue(pPlacement->Box.m_vInf.z, valueEncoding);

					data.m_vSup.x.SetValue(pPlacement->Box.m_vSup.x, valueEncoding);
					data.m_vSup.y.SetValue(pPlacement->Box.m_vSup.y, valueEncoding);
					data.m_vSup.z.SetValue(pPlacement->Box.m_vSup.z, valueEncoding);


					fwrite(&data, sizeof(data), 1, pMyUserData->fp);
				},
					10
			},
		};

		static_assert(_countof(GTAIVDescriptors) <= GTAIVnumberOfSections, "Invalid array count of GTAIVDescriptors");
		
		// Constructor
		IPLfileReaderEx::IPLfileReaderEx()
		{
			this->bUpdateLODindicesWhenLoading = true;
		}

		// Registers collectible file reader
		void IPLfileReaderEx::RegisterCollectibleFileReader(Collectible::CollectibleFileReaderEx* pCollectibleFileReader)
		{
			this->pCollectibleFileReader = pCollectibleFileReader;
		}

		// Enables/disables updating of LOD indices when loading
		void IPLfileReaderEx::EnableUpdatingOfLODindicesWhenLoading(bool bEnable)
		{
			this->bUpdateLODindicesWhenLoading = bEnable;
		}

		// Set LOD base index
		void IPLfileReaderEx::SetLODbaseIndex()
		{
			if (this->bUpdateLODindicesWhenLoading)
			{
				this->LODbaseIndex = 0;

				const tSectionInfo* pSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(SECTION_IPL_INST);
								
				if (!pSectionInfo)
					return;

				// Gets count of inst entries
				this->LODbaseIndex = CountDataElementsWithSpecifiedSectionType(SECTION_IPL_INST);
			}
		}

		// Loads file
		bool IPLfileReaderEx::LoadFile(const char* filename)
		{
			this->SetLODbaseIndex();

			return this->CSectionFileReaderExLoader::LoadFile(filename);
		}

		// Process model info
		void IPLfileReaderEx::ProcessEntry(CSectionFileElementBase* pElement)
		{
			if (this->bUpdateLODindicesWhenLoading && pElement->IsData())
			{		
				CPlacementObjectInstance* pObjectInstance = ((CPlacementBaseInfo*)pElement)->ToPlacementObjectInstance();

				if (pObjectInstance && pObjectInstance->LODnum != -1)
				{
					pObjectInstance->LODnum += this->LODbaseIndex;
					pObjectInstance->UpdateLine(this->m_gameInfo.gameSimple);
				}
			}

			this->CSectionFileReaderExLoader::ProcessEntry(pElement);
		}

		// Loads a binary file
		bool IPLfileReaderEx::LoadBinaryFile(const char* filename)
		{
			this->SetLODbaseIndex();

			FILE* fp = NULL;

			if (this->m_gameInfo.gameSimple == GAME_SIMPLE_NAME_GTA_SA)
			{
				if (fp = fopen(filename, "rb"))
				{
					Structure::tGTASA_binaryIPL_header header;

					fread(&header, sizeof(header), 1, fp);

					if (header.magicID != 'yrnb')
						goto CloseFileAndReturnFalse;

					// IPL:inst
					if (header.numberOfObjectInstances
						&& (this->m_pCurSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(SECTION_IPL_INST)))
					{
						this->BeginSection();

						fseek(fp, header.OffsetToItemInstances, SEEK_SET);

						Structure::CFileObjectInstanceInGTASA data;

						unsigned int i = 0;

						do
						{
							if (!fread(&data, sizeof(data), 1, fp))
								goto CloseFileAndReturnFalse;

							CPlacementObjectInstance object;				

							{
								object.ModelID = data.modelID;

								char modelName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH+1];
								sprintf(modelName, "id_%d", object.ModelID);
								object.ModelName.SetStringAndHash(this->m_gameInfo.gameSimple, modelName);

								object.Pos = data.position;
								object.Rot = data.rotation;
								object.InteriorNum = data.interiorID;
								object.LODnum = data.lodIndex;
							}

							object.UpdateLine(this->m_gameInfo.gameSimple);
							this->ProcessEntry(&object);

						} while (++i < header.numberOfObjectInstances);

						this->EndSection();
						this->m_pCurSectionInfo = nullptr;
					}

					// IPL:cars
					if (header.numberOfParkedCarGenerators
						&& (this->m_pCurSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(SECTION_IPL_CARS)))
					{
						this->BeginSection();

						fseek(fp, header.OffsetToCarGenerators, SEEK_SET);

						Structure::CFileCarGeneratorInGTASA data;

						unsigned int i = 0;

						do
						{
							if (!fread(&data, sizeof(data), 1, fp))
								goto CloseFileAndReturnFalse;

							CPlacementCarGenerator generator;

							{
								generator.Pos = data.Pos;
								generator.AngleInRadians = data.AngleInRadians;
								generator.ModelID = data.ModelID;
								generator.PrimCol = data.PrimCol;
								generator.SecCol = data.SecCol;
								generator.Flags = data.Flags;
								generator.AlarmProbability = data.AlarmProbability;
								generator.DoorLockProbability = data.DoorLockProbability;
								generator.MinDelay = data.MinDelay;
								generator.MaxDelay = data.MaxDelay;
							}

							generator.UpdateLine(this->m_gameInfo.gameSimple);
							this->ProcessEntry(&generator);

						} while (++i < header.numberOfParkedCarGenerators);

						this->EndSection();
						this->m_pCurSectionInfo = nullptr;
					}
						
					fclose(fp);
					return true;
				}
			}

			else if (this->m_gameInfo.gameSimple == GAME_SIMPLE_NAME_GTA_IV)
			{
				if (fp = fopen(filename, "rb"))
				{
					tBinarySectionGTAIVUserData userData;
					userData.pReader = this;
					userData.fp = fp;
					userData.gameSimple = this->m_gameInfo.gameSimple;

					eValueEncoding valueEncoding = Game::GamePlatform::IsPlatformBigEndian(this->m_gameInfo.platform);				

					userData.valueEncoding = valueEncoding;
					
					tVariedEncoding<unsigned __int32> version;

					if (!fread(&version, sizeof(version), 1, fp) || version.GetValue(valueEncoding) != 3)
						goto CloseFileAndReturnFalse;
					
					tVariedEncoding<unsigned __int32> sectionCountArray[GTAIVnumberOfSections];

					if (!fread(sectionCountArray, sizeof(sectionCountArray), 1, fp))
						goto CloseFileAndReturnFalse;

					int numberOfSectionsToRead = _countof(GTAIVDescriptors);

					/*
					for (int i = 0; i < GTAIVnumberOfSections; i++)
					{
						unsigned __int32 countOfEntriesInSection = sectionCountArray[i].GetValue(valueEncoding);

						printf("count Index: %d value: %d\n", i, countOfEntriesInSection);
					}
					*/

					// read sections
					for (int i = 0; i < numberOfSectionsToRead; i++)
					{
						const tGTAIVbinarySectionDescriptor* pDescriptor = &GTAIVDescriptors[i];
						unsigned __int32 countOfEntriesInSection = sectionCountArray[pDescriptor->sectionIndexInCountArray].GetValue(valueEncoding);
										
						if (!pDescriptor->sectionSizeWhenNotImplemented)
						{
							if (!pDescriptor->LoadFunc)
								break;

							if (countOfEntriesInSection == 0)
								continue;
							
							this->m_pCurSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(pDescriptor->sectionType);

							if (!this->m_pCurSectionInfo)
								goto CloseFileAndReturnFalse;

							this->BeginSection();	// virtual function executed when section becomes active
							
							// load entries from section
							for (unsigned int j = 0; j < countOfEntriesInSection; j++)
							{
								CSectionFileElementBaseEx* ptr = (CSectionFileElementBaseEx*)pDescriptor->LoadFunc(&userData);

								if (!ptr)
									goto CloseFileAndReturnFalse;

								ptr->UpdateLine(this->m_gameInfo.gameSimple);
								this->ProcessEntry(ptr);

								delete ptr;
							}

							this->EndSection();
							this->m_pCurSectionInfo = NULL;
						}
						else
							fseek(fp, countOfEntriesInSection * pDescriptor->sectionSizeWhenNotImplemented, SEEK_CUR);
					}

					fclose(fp);
					return true;
				}
			}
			else if (this->m_gameInfo.gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				if (fp = fopen(filename, "rb"))
				{
					tBinarySectionBullyScholarshipUserData userData;
					userData.pReader = this;
					userData.fp = fp;
					userData.gameSimple = this->m_gameInfo.gameSimple;

					tBullyScholarshipEdition_binaryIPB_header header;

					if(!fread(&header, sizeof(header), 1, fp))
						goto CloseFileAndReturnFalse;

					if (memcmp(
						&header,
						&BullyScholarshipIPBheader,
						sizeof(tBullyScholarshipEdition_binaryIPB_header))
						)
						goto CloseFileAndReturnFalse;
					
					__int32 numberOfSections;

					if(!fread(&numberOfSections, sizeof(numberOfSections), 1, fp))
						goto CloseFileAndReturnFalse;

					// read sections
					for (int i = 0; i < numberOfSections; i++)
					{
						unsigned __int32 identifier;

						if (!fread(&identifier, sizeof(identifier), 1, fp))
							goto CloseFileAndReturnFalse;

						const tBullyScholarshipEditionBinarySectionDescriptor* pDescriptor =
							FindBinaryDescriptorByIdentifierInFile(
								BullyScholarschipDescriptors,
								identifier
								);

						if (!pDescriptor || !pDescriptor->LoadFunc)
						{
							// printf("ftell: 0x%X identifier: %s\n", ftell(fp), (char*)&identifier);
							goto CloseFileAndReturnFalse;
						}

						this->m_pCurSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(pDescriptor->sectionType);

						if (!this->m_pCurSectionInfo)
							goto CloseFileAndReturnFalse;

						this->BeginSection();	// virtual function executed when section becomes active

						unsigned __int32 NumberOfEntries = 0;
						fread(&NumberOfEntries, sizeof(NumberOfEntries), 1, fp);

						for (unsigned int i = 0; i < NumberOfEntries; i++)
						{
							if(!pDescriptor->LoadFunc(&userData))
								goto CloseFileAndReturnFalse;
						}

						this->EndSection();
						this->m_pCurSectionInfo = NULL;

					}					

					fclose(fp);
					return true;
				}				
			}

			return false;

		CloseFileAndReturnFalse:
			fclose(fp);
			return false;
		}
		
		// Saves Bully section with header
		void SaveBullySection(
			const tBullyScholarshipEditionBinarySectionDescriptor* pDescriptor,
			CSectionFileElement_SectionOfData* pSection,
			FILE* fp,
			bool(*IsHeader)(const CSectionFileElementBase_WithSectionInfo* pElement),
			bool(*IsSubElement)(const CSectionFileElementBase_WithSectionInfo* pElement),
			void(*SaveHeader)(FILE* fp, const CSectionFileElementBase_WithSectionInfo* ptr),
			void(*SaveSubElement)(FILE* fp, const CSectionFileElementBase_WithSectionInfo* ptr)
			)
		{
			// Write section identifier
			fwrite(
				&pDescriptor->typeIDinBinaryFile,
				sizeof(pDescriptor->typeIDinBinaryFile),
				1,
				fp
				);

			unsigned __int32 countOfEntriesInSection = 0;

			int offsetToCountOfSectionEntries = ftell(fp);
			fseek(fp, 4, SEEK_CUR);

			auto secondIt = pSection->Data.begin();

			long offsetToCountOfPositions = -1;
			__int32 countOfPositions = 0;			

			for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
			{
				if (!secondIt->IsData())
					continue;			

				const CSectionFileElementBase_WithSectionInfo* pElement
					= secondIt->ToElementBaseWithSectionInfo();

				if (pElement->GetSectionType() != pSection->GetSectionType())
					continue;
				
				if (IsHeader(pElement))
				{
					if (offsetToCountOfPositions != -1) // is not first?
					{
						long cur = ftell(fp);
						fseek(fp, offsetToCountOfPositions, SEEK_SET);
						fwrite(&countOfPositions, 4, 1, fp);
						fseek(fp, cur, SEEK_SET);
					}

					countOfEntriesInSection++;
					countOfPositions = 0;

					SaveHeader(fp, pElement);

					offsetToCountOfPositions = ftell(fp);

					fseek(fp, 4, SEEK_CUR);
				}
				else if (offsetToCountOfPositions != -1 && IsSubElement(pElement))
				{
					SaveSubElement(fp, pElement);

					countOfPositions++;
				}
			}

			long cur = ftell(fp);

			if (offsetToCountOfPositions != -1) // is not first?
			{
				fseek(fp, offsetToCountOfPositions, SEEK_SET);
				fwrite(&countOfPositions, 4, 1, fp);
			}

			fseek(fp, offsetToCountOfSectionEntries, SEEK_SET);
			fwrite(&countOfEntriesInSection, 4, 1, fp);
			fseek(fp, cur, SEEK_SET);
		}
		
		// Saves a binary file		
		bool IPLfileReaderEx::SaveBinaryFile(const char* filename)
		{
			Game::eGameNameSimplified gameSimple = this->m_gameInfo.gameSimple;

			if (this->m_gameInfo.gameSimple == GAME_SIMPLE_NAME_GTA_SA)
			{
				if (FILE* fp = fopen(filename, "wb"))
				{
					// Header
					Structure::tGTASA_binaryIPL_header header = { 0 };
					header.magicID = 'yrnb';
					
					struct tUserData
					{
						IPLfileReaderEx* pIPLreader;
						FILE* fp;
						Structure::tGTASA_binaryIPL_header* pHeader;
					} userData;

					userData.pIPLreader = this;
					userData.fp = fp;
					userData.pHeader = &header;

					fseek(fp, sizeof(header), SEEK_SET);

					////////////////

					// IPL:inst
					{
						header.OffsetToItemInstances = ftell(fp);

						this->ForeachSectionsAndElementsWithSpecifiedType(
							SECTION_IPL_INST,

							[](CSectionFileElementBase_WithSectionInfo* pElement, void* pUserData)
						{
							tUserData* pMyData = (tUserData*)pUserData;
							CPlacementObjectInstance* pElementObjectInstance = (CPlacementObjectInstance*)pElement;

							Structure::CFileObjectInstanceInGTASA data;

							data.position = pElementObjectInstance->Pos;
							data.rotation = pElementObjectInstance->Rot;
							data.modelID = pElementObjectInstance->ModelID;
							data.interiorID = pElementObjectInstance->InteriorNum;
							data.lodIndex = pElementObjectInstance->LODnum;

							fwrite(&data, sizeof(data), 1, pMyData->fp);

							pMyData->pHeader->numberOfObjectInstances++;

							return false;
						}
							,

							&userData);
					}

					// IPL:cars
					{
						header.OffsetToCarGenerators = ftell(fp);

						this->ForeachSectionsAndElementsWithSpecifiedType(
							SECTION_IPL_CARS,

							[](CSectionFileElementBase_WithSectionInfo* pElement, void* pUserData)
						{
							tUserData* pMyData = (tUserData*)pUserData;
							CPlacementCarGenerator* pElementCarGen = (CPlacementCarGenerator*)pElement;

							Structure::CFileCarGeneratorInGTASA data;
	
							data.Pos = pElementCarGen->Pos;
							data.AngleInRadians = pElementCarGen->AngleInRadians;
							data.ModelID = pElementCarGen->ModelID;
							data.PrimCol = pElementCarGen->PrimCol;
							data.SecCol = pElementCarGen->SecCol;
							data.Flags = pElementCarGen->Flags;
							data.AlarmProbability = pElementCarGen->AlarmProbability;
							data.DoorLockProbability = pElementCarGen->DoorLockProbability;
							data.MinDelay = pElementCarGen->MinDelay;
							data.MaxDelay = pElementCarGen->MaxDelay;

							fwrite(&data, sizeof(data), 1, pMyData->fp);

							pMyData->pHeader->numberOfParkedCarGenerators++;

							return false;
						}
							,

							&userData);
					}

					// write header
					fseek(fp, 0, SEEK_SET);
					fwrite(&header, sizeof(header), 1, fp);

					fclose(fp);
					return true;
				}				
			}
			else if (this->m_gameInfo.gameSimple == GAME_SIMPLE_NAME_GTA_IV)
			{
				if (FILE* fp = fopen(filename, "wb"))
				{
					tBinarySectionGTAIVUserData userData;
					userData.pReader = this;
					userData.fp = fp;
					userData.gameSimple = this->m_gameInfo.gameSimple;

					eValueEncoding valueEncoding = Game::GamePlatform::IsPlatformBigEndian(this->m_gameInfo.platform);

					userData.valueEncoding = valueEncoding;

					tVariedEncoding<unsigned __int32> version;
					version.SetValue(3, valueEncoding);
					fwrite(&version, sizeof(version), 1, fp);

					long offsetToSectionCountArray = ftell(fp);

					unsigned __int32 sectionCountArray[GTAIVnumberOfSections] = { 0 };
					userData.pSectionCountArray = sectionCountArray;

					fseek(fp, sizeof(sectionCountArray), SEEK_CUR);
					
					int numberOfSectionsToWrite = _countof(GTAIVDescriptors);

					// foreach GTA IV descriptors of sections
					for (int i = 0; i < numberOfSectionsToWrite; i++)
					{
						const tGTAIVbinarySectionDescriptor* pDescriptor = &GTAIVDescriptors[i];
						userData.sectionNumInFile = i;

						if (!pDescriptor->SaveFunc
							|| !this->FindSectionInfoWithSpecifiedTypeID(pDescriptor->sectionType)
							)
							continue;

						this->ForeachSectionsAndElementsWithSpecifiedType(
							pDescriptor->sectionType,

							[](CSectionFileElementBase_WithSectionInfo* pElement, void* pUserData)
							{
								tBinarySectionGTAIVUserData* pMyUserData
									= (tBinarySectionGTAIVUserData*)pUserData;

								const tGTAIVbinarySectionDescriptor* pDescriptor = &GTAIVDescriptors[pMyUserData->sectionNumInFile];								

								pDescriptor->SaveFunc(pUserData, pElement);
								pMyUserData->pSectionCountArray[pDescriptor->sectionIndexInCountArray]++;

								return false;
							},
							&userData);
					}

					// write section counts
					fseek(fp, offsetToSectionCountArray, SEEK_SET);

					tVariedEncoding<unsigned __int32> sectionCountArrayWithCorrentEndian[GTAIVnumberOfSections];

					for (int i = 0; i < GTAIVnumberOfSections; i++)
						sectionCountArrayWithCorrentEndian[i].SetValue(sectionCountArray[i], valueEncoding);

					fwrite(
						sectionCountArrayWithCorrentEndian,
						sizeof(sectionCountArrayWithCorrentEndian),
						1,
						fp);

					fclose(fp);
					return true;
				}
			}
			else if (this->m_gameInfo.gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				if (FILE* fp = fopen(filename, "wb"))
				{
					tBinarySectionBullyScholarshipUserData userData;
					userData.pReader = this;
					userData.fp = fp;
					userData.gameSimple = gameSimple;

					fwrite(
						&BullyScholarshipIPBheader,
						sizeof(BullyScholarshipIPBheader),
						1,
						fp
						);

					// Get count of sections
					__int32 countOfSections = 0;

					for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
					{
						CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData();

						if (!pSection)
							continue;

						int sectionType = pSection->GetSectionType();

						if (sectionType == SECTION_IPL_RAIL || sectionType == SECTION_IPL_PERM || sectionType == SECTION_IPL_POIS)
							countOfSections++;
						else
						{
							const tBullyScholarshipEditionBinarySectionDescriptor* pDescriptor = FindBinaryDescriptorBySectionType(
								BullyScholarschipDescriptors,
								pSection->GetSectionType()
							);

							if (pDescriptor && pDescriptor->SaveFunc)
								countOfSections++;
						}
					}

					fwrite(&countOfSections, sizeof(countOfSections), 1, fp);

					//////////////////////
					// Browse sections
					for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
					{
						CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData();

						if (!pSection)
							continue;
						
						const tBullyScholarshipEditionBinarySectionDescriptor* pDescriptor = FindBinaryDescriptorBySectionType(
							BullyScholarschipDescriptors,
							pSection->GetSectionType()
							);

						if (!pDescriptor)
							continue;

						if (pDescriptor->SaveFunc)
						{
							// Write section identifier
							fwrite(
								&pDescriptor->typeIDinBinaryFile,
								sizeof(pDescriptor->typeIDinBinaryFile),
								1,
								fp
								);

							// Get count of entries in section
							__int32 countOfEntriesInSection = 0;

							for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
							{
								if (!secondIt->IsData())
									continue;

								const CIPLorIDEentryBaseInfo* pElement
									= (const CIPLorIDEentryBaseInfo*)secondIt->ToElementBaseWithSectionInfo();

								if (pElement->GetSectionType() == pSection->GetSectionType() && pElement->GetElementScopeNumber() == 0)
									countOfEntriesInSection++;
							}

							fwrite(&countOfEntriesInSection, sizeof(countOfEntriesInSection), 1, fp);							

							// Write entries
							for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
							{
								if (!secondIt->IsData())
									continue;

								const CIPLorIDEentryBaseInfo* pElement
									= (const CIPLorIDEentryBaseInfo*)secondIt->ToElementBaseWithSectionInfo();

								if (pElement->GetSectionType() == pSection->GetSectionType())
									pDescriptor->SaveFunc(&userData, pElement);
							}
						}
						else if (pSection->GetSectionType() == SECTION_IPL_RAIL)
						{
							SaveBullySection(pDescriptor, pSection, fp,
								[](const CSectionFileElementBase_WithSectionInfo* pElement)
							{ return ((const CPlacementRail*)pElement)->GetRailEntryType() == PLACEMENT_RAIL_ENTRY_TYPE_HEADER; },
								[](const CSectionFileElementBase_WithSectionInfo* pElement)
							{ return ((const CPlacementRail*)pElement)->GetRailEntryType() == PLACEMENT_RAIL_ENTRY_TYPE_POS; },

								[](FILE* fp, const CSectionFileElementBase_WithSectionInfo* pElement)
							{
								const CPlacementRail* pPlacement = (const CPlacementRail*)pElement;
								FileWritePascalString(fp, pPlacement->PathName.c_str());
								__int32 UnknownParam2inBullyScholarschip = pPlacement->UnknownParam2inBullyScholarschip;
								fwrite(&UnknownParam2inBullyScholarschip, sizeof(UnknownParam2inBullyScholarschip), 1, fp);
							},
								[](FILE* fp, const CSectionFileElementBase_WithSectionInfo* pElement)
							{ 
								const CPlacementRail* pPlacement = (const CPlacementRail*)pElement;
								fwrite(&pPlacement->Pos, sizeof(CVector), 1, fp);
							}
								);
						}
						else if (pSection->GetSectionType() == SECTION_IPL_PERM)
						{
							SaveBullySection(pDescriptor, pSection, fp,
								[](const CSectionFileElementBase_WithSectionInfo* pElement)
							{ return ((const CPlacementPerm*)pElement)->GetPermEntryType() == PLACEMENT_PERM_ENTRY_TYPE_HEADER; },
								[](const CSectionFileElementBase_WithSectionInfo* pElement)
							{ return ((const CPlacementPerm*)pElement)->GetPermEntryType() == PLACEMENT_PERM_ENTRY_TYPE_SUB_ENTRY; },

								[](FILE* fp, const CSectionFileElementBase_WithSectionInfo* pElement)
							{
								const CPlacementPerm* pPlacement = (const CPlacementPerm*)pElement;

								FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownParam1inBullyScholarschip.c_str());
								FileWriteFloat(fp, pPlacement->UnknownParam2inBullyScholarschip);
								FileWriteFloat(fp, pPlacement->UnknownParam3inBullyScholarschip);
								FileWriteFloat(fp, pPlacement->UnknownParam4inBullyScholarschip);
							},
								[](FILE* fp, const CSectionFileElementBase_WithSectionInfo* pElement)
							{
								const CPlacementPerm* pPlacement = (const CPlacementPerm*)pElement;
								fwrite(&pPlacement->FloatValue, sizeof(float), 1, fp);
							}
							);
						}
						else if (pSection->GetSectionType() == SECTION_IPL_POIS)
						{
							SaveBullySection(pDescriptor, pSection, fp,
								[](const CSectionFileElementBase_WithSectionInfo* pElement)
							{ return ((const CPlacementPois*)pElement)->GetPoisEntryType() == PLACEMENT_POIS_ENTRY_TYPE_HEADER; },
								[](const CSectionFileElementBase_WithSectionInfo* pElement)
							{ return ((const CPlacementPois*)pElement)->GetPoisEntryType() == PLACEMENT_POIS_ENTRY_TYPE_ELEMENT; },

								[](FILE* fp, const CSectionFileElementBase_WithSectionInfo* pElement)
							{
								const CPlacementPois* pPlacement = (const CPlacementPois*)pElement;
								FileWritePascalString(fp, pPlacement->UnknownHeaderParam1inBullyScholarschip.c_str());
								int32_t UnknownHeaderParam2inBullyScholarschip = pPlacement->UnknownHeaderParam2inBullyScholarschip;
								fwrite(&UnknownHeaderParam2inBullyScholarschip, sizeof(UnknownHeaderParam2inBullyScholarschip), 1, fp);
							},
								[](FILE* fp, const CSectionFileElementBase_WithSectionInfo* pElement)
							{
								const CPlacementPois* pPlacement = (const CPlacementPois*)pElement;
								
								FileWritePascalString(fp, pPlacement->UnknownElementParam1inBullyScholarschip.c_str());
								FileWritePascalStringCanBeDefault(fp, pPlacement->UnknownElementParam2inBullyScholarschip.c_str());
								FileWritePascalString(fp, pPlacement->UnknownElementParam3inBullyScholarschip.c_str());
								FileWritePascalString(fp, pPlacement->UnknownElementParam4inBullyScholarschip.c_str());
								FileWriteInt32(fp, pPlacement->UnknownElementParam5inBullyScholarschip);
								fwrite(&pPlacement->Pos, sizeof(CVector), 1, fp);
								fwrite(&pPlacement->Rot, sizeof(CVector), 1, fp);
								FileWriteInt32(fp, pPlacement->UnknownElementParam12inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam13inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam14inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam15inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam16inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam17inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam18inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam19inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam20inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam21inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam22inBullyScholarschip);
								FileWriteFloat(fp, pPlacement->UnknownElementParam23inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam24inBullyScholarschip);
								FileWriteInt32(fp, pPlacement->UnknownElementParam25inBullyScholarschip);
							}
							);
						}
					}

					fclose(fp);
					return true;
				}
			}

			return false;
		}
	}
}