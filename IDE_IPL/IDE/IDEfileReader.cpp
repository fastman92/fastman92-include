/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "IDEfileReader.h"

#include "../CModel2dEffect.h"
#include "CModelAccessory.h"
#include "CModelCash.h"
#include "CModelCloth.h"
#include "CModelItem.h"
#include "CModelObject.h"
#include "CModelPath.h"
#include "CModelPed.h"
#include "CModelPropAnimation.h"
#include "CModelScnd.h"
#include "CModelTimedObject.h"
#include "CModelTXDparent.h"
#include "CModelVehicle.h"
#include "CModelWeapon.h"
#include "../../IMG/IMGstructures.h"
#include "../../fileIO.h"

#include <stdio.h>

using namespace Game;

namespace File
{
	namespace IDE
	{
		// Sets game version and registers sections.
		void IDEfileReaderEx::SetGameVersion(Game::eGameName game)
		{
			this->ClearSections();

			this->m_gameInfo = Game::GetSimpleGameAndPlatformByExactMember(game);
			Game::eGameNameSimplified gameSimple = this->m_gameInfo.gameSimple;

			this->RegisterSection("objs", SECTION_IDE_OBJS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelObject>));

			if(gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
				this->RegisterSection("2dfx", SECTION_2DFX, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModel2dEffect>));

			if(GameSimple::IsGTAIIIeraGame(gameSimple) || gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
				this->RegisterSection("tobj", SECTION_IDE_TOBJ, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelTimedObject>));

			this->RegisterSection("cars", SECTION_IDE_CARS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelVehicle>));

			this->RegisterSection("peds", SECTION_IDE_PEDS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelPed>));

			this->RegisterSection("path", SECTION_IDE_PATH, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelPath>));

			if (gameSimple == GAME_SIMPLE_NAME_GTA_SA
				|| gameSimple == GAME_SIMPLE_NAME_GTA_IV)
				this->RegisterSection("txdp", SECTION_IDE_TXDP, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelTXDparent>));

			if(gameSimple == GAME_SIMPLE_NAME_GTA_VC
				|| gameSimple == GAME_SIMPLE_NAME_GTA_SA
				|| gameSimple == GAME_SIMPLE_NAME_GTA_IV
				|| gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION
				)
				this->RegisterSection("weap", SECTION_IDE_WEAP, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelWeapon>));

			if (gameSimple == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				this->RegisterSection("accs", SECTION_IDE_ACCS, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelAccessory>));
				this->RegisterSection("cash", SECTION_IDE_CASH, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelCash>));
				this->RegisterSection("clth", SECTION_IDE_CLTH, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelCloth>));
				this->RegisterSection("item", SECTION_IDE_ITEM, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelItem>));
				this->RegisterSection("scnd", SECTION_IDE_SCND, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelScnd>));

				this->RegisterSection("panm", SECTION_IDE_PANM, static_cast<tSectionFunc>(&CSectionFileReaderEx::DecodeSection<CModelPropAnimation>));
			}
		}

		/////////////// IDEfileReaderEx ///////////////

		struct tBinaryDescriptor
		{
			eSectionType type;
			unsigned __int32 typeIDinBinaryFile;
			CModelBaseInfo*(*LoadFunc)(FILE* fp);
			void(*SaveFunc)(FILE* fp, const CModelBaseInfo* pModelInfo);
		};

		// Writes 3 common elements
		void WriteNothing(FILE* fp, const CModelBaseInfo* ptr) {}

		// Reads 3 common elements
		void Read3commonElements(FILE* fp, CModel3commonElements* pModelInfo)
		{
			char ModelName[IMG_MAX_FILENAME_LENGTH + 1];
			char TXDname[IMG_MAX_FILENAME_LENGTH + 1];

			pModelInfo->ModelID = FileReadInt32(fp);
			FileRead4byteAlignedString(fp, ModelName);
			FileRead4byteAlignedString(fp, TXDname);

			pModelInfo->ModelName = ModelName;
			pModelInfo->TXDname = TXDname;
		}

		// Writes 3 common elements
		void Write3commonElements(FILE* fp, const CModelBaseInfo* ptr)
		{
			const CModel3commonElements* p3commonElements = ptr->ToModel3commonElements();

			FileWriteInt32(fp, p3commonElements->ModelID);
			FileWrite4byteAlignedString(fp,	p3commonElements->ModelName.c_str());
			FileWrite4byteAlignedString(fp, p3commonElements->TXDname.c_str());
		}

		// Reads model object info
		void ReadModelObjectInfo(FILE* fp, CModelObject* pModelInfo)
		{
			int type = FileReadInt32(fp);

			if (type == 0)
			{
				Read3commonElements(fp, pModelInfo);
				pModelInfo->ObjectCount = FileReadInt32(fp);
				pModelInfo->DrawDistance[0] = FileReadFloat(fp);
				pModelInfo->Flags = FileReadInt32(fp);
				pModelInfo->UnkBullyScholarschip7 = FileReadInt32(fp);
				pModelInfo->UnkBullyScholarschip8 = FileReadFloat(fp);
				pModelInfo->UnkBullyScholarschip9 = FileReadInt32(fp);
				pModelInfo->UnkBullyScholarschip10 = FileReadInt32(fp);
				pModelInfo->UnkBullyScholarschip11 = FileReadInt32(fp);
				pModelInfo->UnkBullyScholarschip12 = FileReadInt32(fp);
				pModelInfo->UnkBullyScholarschip13 = FileReadInt32(fp);
			}
		}

		// Writes model object info
		void WriteModelObjectInfo(FILE* fp, const CModelObject* pModelInfo)
		{
			FileWriteInt32(fp, 0);	// type

			Write3commonElements(fp, pModelInfo);
			FileWriteInt32(fp, pModelInfo->ObjectCount);
			FileWriteFloat(fp, pModelInfo->DrawDistance[0]);
			FileWriteInt32(fp, pModelInfo->Flags);
			FileWriteInt32(fp, pModelInfo->UnkBullyScholarschip7);
			FileWriteFloat(fp, pModelInfo->UnkBullyScholarschip8);
			FileWriteInt32(fp, pModelInfo->UnkBullyScholarschip9);
			FileWriteInt32(fp, pModelInfo->UnkBullyScholarschip10);
			FileWriteInt32(fp, pModelInfo->UnkBullyScholarschip11);
			FileWriteInt32(fp, pModelInfo->UnkBullyScholarschip12);
			FileWriteInt32(fp, pModelInfo->UnkBullyScholarschip13);
		}
		
		// Bully scholarschip descriptor array
		const struct tBinaryDescriptor BullyScholarschipFunctions[] =
		{			
			{
				SECTION_2DFX,
				'2dfx',
			[](FILE* fp)
		{

			char Corona[32];
			char Shadow[32];

			File::CModel2dEffect* pModelInfo = new File::CModel2dEffect();

			pModelInfo->ModelID = FileReadInt32(fp);
			pModelInfo->Pos.x = FileReadFloat(fp);
			pModelInfo->Pos.y = FileReadFloat(fp);
			pModelInfo->Pos.z = FileReadFloat(fp);
			pModelInfo->Color.red = FileReadInt32(fp);
			pModelInfo->Color.green = FileReadInt32(fp);
			pModelInfo->Color.blue = FileReadInt32(fp);

			pModelInfo->UnknownParam8inGTAIII_VC_BullyScholarschip = FileReadInt32(fp);
			pModelInfo->EffectType = FileReadInt32(fp);

			FileRead4byteAlignedString(fp, Corona);
			pModelInfo->Corona = Corona;

			FileRead4byteAlignedString(fp, Shadow);
			pModelInfo->Shadow = Shadow;

			pModelInfo->Distance = FileReadFloat(fp);
			pModelInfo->OuterRange = FileReadFloat(fp);
			pModelInfo->Size = FileReadFloat(fp);
			pModelInfo->InnerRange = FileReadFloat(fp);
			pModelInfo->ShadowIntensity = FileReadInt32(fp);
			pModelInfo->UnknownParam17inBullyScholarschip = FileReadInt32(fp);
			pModelInfo->UnknownParam18inBullyScholarschip = FileReadInt32(fp);
			pModelInfo->UnknownParam19inBullyScholarschip = FileReadFloat(fp);
			pModelInfo->UnknownParam20inBullyScholarschip = FileReadInt32(fp);
			pModelInfo->UnknownParam21inBullyScholarschip = FileReadInt32(fp);
			pModelInfo->UnknownParam22inBullyScholarschip = FileReadInt32(fp);
			pModelInfo->UnknownParam23inBullyScholarschip = FileReadInt32(fp);
			pModelInfo->UnknownParam24inBullyScholarschip = FileReadInt32(fp);

			//ReadModelObjectInfo(fp, pModelInfo);

			return (CModelBaseInfo*)pModelInfo;
		},

			[](FILE* fp, const CModelBaseInfo* ptr)
			{
				const File::CModel2dEffect* pModelInfo = ptr->ToModel2dEffect();

				FileWriteInt32(fp, pModelInfo->ModelID);
				FileWriteFloat(fp, pModelInfo->Pos.x);
				FileWriteFloat(fp, pModelInfo->Pos.y);
				FileWriteFloat(fp, pModelInfo->Pos.z);
				FileWriteInt32(fp, pModelInfo->Color.red);
				FileWriteInt32(fp, pModelInfo->Color.green);
				FileWriteInt32(fp, pModelInfo->Color.blue);
				FileWriteInt32(fp, pModelInfo->UnknownParam8inGTAIII_VC_BullyScholarschip);
				FileWriteInt32(fp, pModelInfo->EffectType);

				FileWrite4byteAlignedString(fp, pModelInfo->Corona.c_str());
				FileWrite4byteAlignedString(fp, pModelInfo->Shadow.c_str());

				FileWriteFloat(fp, pModelInfo->Distance);
				FileWriteFloat(fp, pModelInfo->OuterRange);
				FileWriteFloat(fp, pModelInfo->Size);
				FileWriteFloat(fp, pModelInfo->InnerRange);
				FileWriteInt32(fp, pModelInfo->ShadowIntensity);
				FileWriteInt32(fp, pModelInfo->UnknownParam17inBullyScholarschip);
				FileWriteInt32(fp, pModelInfo->UnknownParam18inBullyScholarschip);
				FileWriteFloat(fp, pModelInfo->UnknownParam19inBullyScholarschip);
				FileWriteInt32(fp, pModelInfo->UnknownParam20inBullyScholarschip);
				FileWriteInt32(fp, pModelInfo->UnknownParam21inBullyScholarschip);
				FileWriteInt32(fp, pModelInfo->UnknownParam22inBullyScholarschip);
				FileWriteInt32(fp, pModelInfo->UnknownParam23inBullyScholarschip);
				FileWriteInt32(fp, pModelInfo->UnknownParam24inBullyScholarschip);

			}

			},

			{
				SECTION_IDE_ACCS,
				'accs',
				[](FILE* fp)
				{
					CModel3commonElements* pEntry = new CModelAccessory();
					Read3commonElements(fp, pEntry);
					return (CModelBaseInfo*)pEntry;
				},
				&Write3commonElements
			},

			{
				SECTION_IDE_CASH,
				'cash',
				[](FILE* fp)
				{
					CModel3commonElements* pEntry = new CModelCash();
					Read3commonElements(fp, pEntry);
					return (CModelBaseInfo*)pEntry;
				},
				&Write3commonElements
			},			
					
			{
				SECTION_IDE_CARS,
				'cars',
					
				[](FILE* fp)
				{
					tCarsParams params;
					CModelVehicle* pModelInfo = new CModelVehicle();
					Read3commonElements(fp, pModelInfo);


					FileRead4byteAlignedString(fp, params.VehicleType);
					pModelInfo->VehicleType = params.VehicleType;					

					FileRead4byteAlignedString(fp, params.HandlingName);
					pModelInfo->HandlingName = params.HandlingName;

					FileRead4byteAlignedString(fp, params.GameName);
					pModelInfo->GameName = params.GameName;

					FileRead4byteAlignedString(fp, params.Anim1);
					pModelInfo->Anim1 = params.Anim1;

					FileRead4byteAlignedString(fp, params.Anim2);
					pModelInfo->Anim2 = params.Anim2;
					
					FileRead4byteAlignedString(fp, params.Class);
					pModelInfo->Class = params.Class;

					pModelInfo->Frequency = FileReadInt32(fp);
					pModelInfo->Level = FileReadInt32(fp);
					pModelInfo->ComponentRules = FileReadInt32(fp);
					pModelInfo->WheelModelID = FileReadInt32(fp);
					pModelInfo->WheelScale = FileReadFloat(fp);
					
					return (CModelBaseInfo*)pModelInfo;
				},

				[](FILE* fp, const CModelBaseInfo* ptr)
				{
					const CModelVehicle* pModelVehicle = ptr->ToModelVehicle();
					
					Write3commonElements(fp, pModelVehicle);
					FileWrite4byteAlignedString(fp, pModelVehicle->VehicleType.c_str());
					FileWrite4byteAlignedString(fp, pModelVehicle->HandlingName.c_str());
					FileWrite4byteAlignedString(fp, pModelVehicle->GameName.c_str());
					FileWrite4byteAlignedString(fp, pModelVehicle->Anim1.c_str());
					FileWrite4byteAlignedString(fp, pModelVehicle->Anim2.c_str());
					FileWrite4byteAlignedString(fp, pModelVehicle->Class.c_str());
					FileWriteInt32(fp, pModelVehicle->Frequency);
					FileWriteInt32(fp, pModelVehicle->Level);
					FileWriteInt32(fp, pModelVehicle->ComponentRules);
					FileWriteInt32(fp, pModelVehicle->WheelModelID);
					FileWriteFloat(fp, pModelVehicle->WheelScale);
				}
			},
			
			{
				SECTION_IDE_CLTH,
				'clth',
				[](FILE* fp)
				{
					CModel3commonElements* pEntry = new CModelCloth();
					Read3commonElements(fp, pEntry);
					return (CModelBaseInfo*)pEntry;
				},
				&Write3commonElements
			},

			{
				SECTION_IDE_ITEM,
				'item',
				[](FILE* fp)
				{
					CModel3commonElements* pEntry = new CModelItem();
					Read3commonElements(fp, pEntry);
					return (CModelBaseInfo*)pEntry;
				},
				&Write3commonElements
			},

			{
				SECTION_IDE_OBJS,
				'objs',
				[](FILE* fp)
				{					
					CModelObject* pModelInfo = new CModelObject();

					ReadModelObjectInfo(fp, pModelInfo);
					
					return (CModelBaseInfo*)pModelInfo;
				},
					
				[](FILE* fp, const CModelBaseInfo* ptr)
				{
					WriteModelObjectInfo(fp, ptr->ToModelObject());
				}
				
			},



			{
				SECTION_IDE_PATH,
				'path',
					[](FILE* fp)
				{
					return (CModelBaseInfo*)new CModelPath;
				},
				&WriteNothing
			},

			{
				SECTION_IDE_PANM,
				'panm',
					[](FILE* fp)
				{
					char AGRname[IMG_MAX_FILENAME_LENGTH + 1];
					char PedAGRname[IMG_MAX_FILENAME_LENGTH + 1];


					CModelPropAnimation* pModelInfo = new CModelPropAnimation();
					Read3commonElements(fp, pModelInfo);

					FileRead4byteAlignedString(fp, AGRname);
					pModelInfo->AGRname = AGRname;

					FileRead4byteAlignedString(fp, PedAGRname);
					pModelInfo->PedAGRname = PedAGRname;

					pModelInfo->AlphaTest = FileReadInt32(fp) != 0;
					pModelInfo->SecondaryCollisionModel = FileReadInt32(fp);
					pModelInfo->ManualTargetLock = FileReadInt32(fp);				

					return (CModelBaseInfo*)pModelInfo;
				},
					
					
					[](FILE* fp, const CModelBaseInfo* ptr)
				{

					const CModelPropAnimation* pModelInfo = ptr->ToModelPropAnimation();

					Write3commonElements(fp, pModelInfo);

					FileWrite4byteAlignedString(fp, pModelInfo->AGRname.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->PedAGRname.c_str());

					FileWriteInt32(fp, pModelInfo->AlphaTest);
					FileWriteInt32(fp, pModelInfo->SecondaryCollisionModel);
					FileWriteInt32(fp, pModelInfo->ManualTargetLock);

				}
				

			},

					
			{
				SECTION_IDE_PEDS,
				'peds',
					[](FILE* fp)
				{
					tPedsParams params;

					CModelPed* pModelInfo = new CModelPed();
					Read3commonElements(fp, pModelInfo);
					pModelInfo->IsFemale = FileReadInt32(fp) != 0;

					FileRead4byteAlignedString(fp, params.Size);
					pModelInfo->Size = params.Size;

					FileRead4byteAlignedString(fp, params.DefaultPedType);
					pModelInfo->DefaultPedType = params.DefaultPedType;

					FileRead4byteAlignedString(fp, params.PedStat);
					pModelInfo->PedStat = params.PedStat;

					FileRead4byteAlignedString(fp, params.AnimGroup);
					pModelInfo->AnimGroup = params.AnimGroup;

					FileRead4byteAlignedString(fp, params.AnimGroup2);
					pModelInfo->AnimGroup2 = params.AnimGroup2;

					FileRead4byteAlignedString(fp, params.AnimGroup3);
					pModelInfo->AnimGroup3 = params.AnimGroup3;

					FileRead4byteAlignedString(fp, params.AnimGroup4);
					pModelInfo->AnimGroup4 = params.AnimGroup4;

					pModelInfo->Unique = FileReadInt32(fp);

					FileRead4byteAlignedString(fp, params.ActionTreeRoot);
					pModelInfo->ActionTreeRoot = params.ActionTreeRoot;

					FileRead4byteAlignedString(fp, params.ActionTreeFile);
					pModelInfo->ActionTreeFile = params.ActionTreeFile;

					FileRead4byteAlignedString(fp, params.AiTreeRoot);
					pModelInfo->AiTreeRoot = params.AiTreeRoot;

					FileRead4byteAlignedString(fp, params.AiTreeFile);
					pModelInfo->AiTreeFile = params.AiTreeFile;

					FileRead4byteAlignedString(fp, params.UnknownParam17inBullyScholarschip);
					pModelInfo->UnknownParam17inBullyScholarschip = params.UnknownParam17inBullyScholarschip;

					return (CModelBaseInfo*)pModelInfo;
				},
					

					
					[](FILE* fp, const CModelBaseInfo* ptr)
				{

					const CModelPed* pModelInfo = ptr->ToModelPed();

					Write3commonElements(fp, pModelInfo);

					FileWriteInt32(fp, pModelInfo->IsFemale);
					FileWrite4byteAlignedString(fp, pModelInfo->Size.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->DefaultPedType.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->PedStat.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->AnimGroup.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->AnimGroup2.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->AnimGroup3.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->AnimGroup4.c_str());
					FileWriteInt32(fp, pModelInfo->Unique);
					FileWrite4byteAlignedString(fp, pModelInfo->ActionTreeRoot.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->ActionTreeFile.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->AiTreeRoot.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->AiTreeFile.c_str());
					FileWrite4byteAlignedString(fp, pModelInfo->UnknownParam17inBullyScholarschip.c_str());
				}
				


			},
			

			{
				SECTION_IDE_TOBJ,
				'tobj',
				[](FILE* fp)
				{
					CModelTimedObject* pModelInfo = new CModelTimedObject();

					ReadModelObjectInfo(fp, pModelInfo);

					pModelInfo->TimeOn = FileReadInt32(fp);
					pModelInfo->TimeOff = FileReadInt32(fp);

					return (CModelBaseInfo*)pModelInfo;
				},
					[](FILE* fp, const CModelBaseInfo* ptr)
				{
					const CModelTimedObject* pModelInfo = ptr->ToModelTimedObject();

					WriteModelObjectInfo(fp, pModelInfo);

					FileWriteInt32(fp, pModelInfo->TimeOn);
					FileWriteInt32(fp, pModelInfo->TimeOff);
				}
			},

			{
				SECTION_IDE_SCND,
				'scnd',
				[](FILE* fp)
				{
					CModel3commonElements* pEntry = new CModelScnd();
					Read3commonElements(fp, pEntry);
					return (CModelBaseInfo*)pEntry;
				},
				&Write3commonElements
			},



			{
				SECTION_IDE_WEAP,
				'weap',
					[](FILE* fp)
				{
					tWeapParams params;
					CModelWeapon* pModelInfo = new CModelWeapon();
					Read3commonElements(fp, pModelInfo);					

					FileRead4byteAlignedString(fp, params.Anim1);
					pModelInfo->Anim1 = params.Anim1;

					FileRead4byteAlignedString(fp, params.Anim2);
					pModelInfo->Anim2 = params.Anim2;

					pModelInfo->ObjectCount = FileReadInt32(fp);
					pModelInfo->DrawDistance[0] = FileReadFloat(fp);

					pModelInfo->UnkBullyScholarschip8 = FileReadInt32(fp);
					pModelInfo->UnkBullyScholarschip9 = FileReadInt32(fp);

					return (CModelBaseInfo*)pModelInfo;
					
				},
				[](FILE* fp, const CModelBaseInfo* ptr)
				{
					const CModelWeapon* pModelVehicle = ptr->ToModelWeapon();

					Write3commonElements(fp, pModelVehicle);
					FileWrite4byteAlignedString(fp, pModelVehicle->Anim1.c_str());
					FileWrite4byteAlignedString(fp, pModelVehicle->Anim2.c_str());
					FileWriteInt32(fp, pModelVehicle->ObjectCount);
					FileWriteFloat(fp, pModelVehicle->DrawDistance[0]);
					FileWriteInt32(fp, pModelVehicle->UnkBullyScholarschip8);
					FileWriteInt32(fp, pModelVehicle->UnkBullyScholarschip9);
				}
			}
			
		};

		// Finds a descriptor
		const tBinaryDescriptor* FindBullyScholarschipDescriptorByType(int type)
		{
			auto it = std::find_if(
				BullyScholarschipFunctions,
				BullyScholarschipFunctions + _countof(BullyScholarschipFunctions),
				[&](const tBinaryDescriptor& descriptor)
			{
				return descriptor.type == type;
			}
			);

			if (it != BullyScholarschipFunctions + _countof(BullyScholarschipFunctions))
				return it;
			else
				return NULL;				
		}
		
		// Finds a descriptor
		const tBinaryDescriptor* FindBullyScholarschipDescriptorByTypeInBinaryFile(int typeInBinaryFile)
		{
			auto it = std::find_if(
				BullyScholarschipFunctions,
				BullyScholarschipFunctions + _countof(BullyScholarschipFunctions),
				[&](const tBinaryDescriptor& descriptor)
			{
				return descriptor.typeIDinBinaryFile == typeInBinaryFile;
			}
			);

			if (it != BullyScholarschipFunctions + _countof(BullyScholarschipFunctions))
				return it;
			else
				return NULL;
		}


		// Loads a binary file
		bool IDEfileReaderEx::LoadBinaryFile(const char* filename)
		{
			Game::eGameNameSimplified gameSimple = this->m_gameInfo.gameSimple;

			if (gameSimple != Game::GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
				return false;

			bool result = true;

			if (FILE* fp = fopen(filename, "rb"))
			{
				int realFileSizeOfIDEfile;
				fread(&realFileSizeOfIDEfile, sizeof(realFileSizeOfIDEfile), 1, fp);

				while (ftell(fp) < (realFileSizeOfIDEfile + 4))
				{
					unsigned __int32 identifier;

					fread(&identifier, sizeof(identifier), 1, fp);

					const tBinaryDescriptor* pDescriptor = FindBullyScholarschipDescriptorByTypeInBinaryFile(identifier);

					if (!pDescriptor || !pDescriptor->LoadFunc)
					{
						result = false;
						// printf("here: 0x%X pos: 0x%X\n", identifier, ftell(fp));

						break;
					}

					this->m_pCurSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(pDescriptor->type);

					if (!this->m_pCurSectionInfo)
					{
						//printf("bhere: 0x%X pos: 0x%X type: %d\n", identifier, ftell(fp), pDescriptor->type);

						result = false;
						break;
					}

					this->BeginSection();	// virtual function executed when section becomes active

					unsigned __int32 NumberOfEntries = 0;
					fread(&NumberOfEntries, sizeof(NumberOfEntries), 1, fp);

					for (unsigned int i = 0; i < NumberOfEntries; i++)
					{
						CModelBaseInfo* ptr = pDescriptor->LoadFunc(fp);
						ptr->SetReaderPointer(this);
						ptr->UpdateLine(this->m_gameInfo.gameSimple);
						this->ProcessEntry(ptr);

						delete ptr;
					}

					unsigned __int32 lowestID;
					unsigned __int32 highestID = 0;
					fread(&lowestID, sizeof(lowestID), 1, fp);
					fread(&highestID, sizeof(highestID), 1, fp);

					this->EndSection();
					this->m_pCurSectionInfo = NULL;
				}

				fclose(fp);
			}
			else
				return false;
			
			return result;
		}

		// Saves a binary file		
		bool IDEfileReaderEx::SaveBinaryFile(const char* filename)
		{
			Game::eGameNameSimplified gameSimple = this->m_gameInfo.gameSimple;

			if (gameSimple != Game::GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
				return false;

			if (FILE* fp = fopen(filename, "wb"))
			{
				// File size
				uint32_t filesize = NULL;
				
				fwrite(&filesize, sizeof(filesize), 1, fp);

				for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
				{
					CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData();

					if (!pSection)
						continue;
					
					const tBinaryDescriptor* pDescriptor = FindBullyScholarschipDescriptorByType(pSection->GetSectionType());

					if (!pDescriptor || !pDescriptor->SaveFunc)
						continue;

					////////////
					// Save a section

					unsigned __int32 lowestID = UINT_MAX;
					unsigned __int32 highestID = 0;

					unsigned int NumberOfEntriesOffset = ftell(fp);
					unsigned __int32 NumberOfEntries = 0;

					fwrite(&pDescriptor->typeIDinBinaryFile, sizeof(pDescriptor->typeIDinBinaryFile), 1, fp);
					NumberOfEntriesOffset = ftell(fp);

					fwrite(&NumberOfEntries, sizeof(NumberOfEntries), 1, fp);

					// loop
					for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
					{
						if (!secondIt->IsData())
							continue;

						NumberOfEntries++;

						const CModelBaseInfo* pIDEentry = static_cast<const CModelBaseInfo*>(&*secondIt);

						if (pIDEentry->ModelID > highestID)
							highestID = pIDEentry->ModelID;

						if (pIDEentry->ModelID < lowestID)
							lowestID = pIDEentry->ModelID;

						pDescriptor->SaveFunc(fp, pIDEentry);
					}

					unsigned int currentOffset = ftell(fp);

					fseek(fp, NumberOfEntriesOffset, SEEK_SET);
					fwrite(&NumberOfEntries, sizeof(NumberOfEntries), 1, fp);

					if (NumberOfEntries == 0)
					{
						lowestID = -1;
						highestID = -1;
					}

					// printf("section %s IDs: %d %d\n", pSection->SectionName.c_str(), lowestID, highestID);

					fseek(fp, currentOffset, SEEK_SET);
					fwrite(&lowestID, sizeof(lowestID), 1, fp);
					fwrite(&highestID, sizeof(highestID), 1, fp);
				}

				// set filesize
				filesize = ftell(fp) - 4;
				fseek(fp, 0, SEEK_SET);
				fwrite(&filesize, sizeof(filesize), 1, fp);

				fclose(fp);

				return true;
			}

			return false;
		}
	}
}