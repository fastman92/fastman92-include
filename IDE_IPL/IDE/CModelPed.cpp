/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CModelPed.h"
#include "../../SectionFile/CSectionFileReader.h"

using namespace Game;

namespace File
{
	namespace IDE
	{
		// Sets default values
		void CModelPed::InitValues()
		{
			this->CModel3commonElements::InitValues();
			this->IsFemale = false;
			this->Size = "Medium";
			this->Props = "null";
			this->DefaultPedType = "UNDEFINED_PED_TYPE";
			this->PedStat = "PED_STAT";
			this->AnimGroup = "undefined_anim_group";			
			this->AnimGroup2 = "undefined_anim_group2";
			this->AnimGroup3 = "undefined_anim_group3";
			this->AnimGroup4 = "undefined_anim_group4";
			this->GestureGroup = "undefined_gesture_group";
			this->GesturePhoneGroup = "undefined_gesture_phone_group";
			this->FacialGroup = "undefined_facial_group";
			this->VisemeGroup = "undefined_viseme_group";
			this->CarsCanDriveMask = 0;
			this->Flags = 0;
			this->AnimFile = "undefined_anim_file";
			this->BlendshapeFile = "undefined_blendshape_file";
			this->Radio1 = 0;
			this->Radio2 = 0;
			this->AudioPedType = "PED_TYPE_UNDEFINED";
			this->FirstVoice = "VOICE_UNDEFINED";
			this->LastVoice = "VOICE_UNDEFINED";

			this->Unique = -1;
			this->ActionTreeRoot = "undefined_action_tree_root";
			this->ActionTreeFile = "undefined_action_tree_file";
			this->AiTreeRoot = "undefined_ai_tree_root";
			this->AiTreeFile = "undefined_ai_tree_file";
			this->UnknownParam17inBullyScholarschip = "undefined_param_17";
		}

		// Imports entry.
		unsigned __int32 CModelPed::ImportEntry(Game::eGameNameSimplified game, const char* line)
		{
			this->InitValues();

			this->ImportedLine = line;
			std::string xLine = CSectionFileReader::GetLinePreparedForScanf(line);

			tPedsParams param;

			if (game == GAME_SIMPLE_NAME_GTA_III)
			{
				
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %x",
					&param.ModelID,

					param.ModelName,
					param.TXDname,

					param.DefaultPedType,
					param.PedStat,
					param.AnimGroup,

					&param.CarsCanDriveMask
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->DefaultPedType = param.DefaultPedType;
				this->PedStat = param.PedStat;
				this->AnimGroup = param.AnimGroup;
				this->CarsCanDriveMask = param.CarsCanDriveMask;				
			}
			else if (game == GAME_SIMPLE_NAME_GTA_VC)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %x %s %d %d",
					&param.ModelID,

					param.ModelName,
					param.TXDname,

					param.DefaultPedType,
					param.PedStat,
					param.AnimGroup,

					&param.CarsCanDriveMask,
					param.AnimFile,

					&param.Radio1,
					&param.Radio2
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->DefaultPedType = param.DefaultPedType;
				this->PedStat = param.PedStat;
				this->AnimGroup = param.AnimGroup;
				this->CarsCanDriveMask = param.CarsCanDriveMask;
				this->Flags = param.Flags;
				this->AnimFile = param.AnimFile;
				this->Radio1 = param.Radio1;
				this->Radio2 = param.Radio2;
			}

			else if (game == GAME_SIMPLE_NAME_GTA_SA)
			{
				sscanf(xLine.c_str(), "%d %s %s %s %s %s %x %x %s %d %d %s %s %s",
					&param.ModelID,

					param.ModelName,
					param.TXDname,

					param.DefaultPedType,
					param.PedStat,
					param.AnimGroup,
					
					&param.CarsCanDriveMask,
					&param.Flags,
					param.AnimFile,

					&param.Radio1,
					&param.Radio2,

					param.AudioPedType,
					param.FirstVoice,
					param.LastVoice
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;
				this->DefaultPedType = param.DefaultPedType;
				this->PedStat = param.PedStat;
				this->AnimGroup = param.AnimGroup;
				this->CarsCanDriveMask = param.CarsCanDriveMask;
				this->Flags = param.Flags;
				this->AnimFile = param.AnimFile;
				this->Radio1 = param.Radio1;
				this->Radio2 = param.Radio2;
				this->AudioPedType = param.AudioPedType;
				this->FirstVoice = param.FirstVoice;
				this->LastVoice = param.LastVoice;
			}
			else if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				sscanf(xLine.c_str(), "%s %s %s   %s %s %s %s %s   %x %s %s %d %d   %s %s %s",
					
					param.ModelName,
					param.Props,
					param.DefaultPedType,

					param.AnimGroup,
					param.GestureGroup,
					param.GesturePhoneGroup,
					param.FacialGroup,
					param.VisemeGroup,

					&param.Flags,
					param.AnimFile,
					param.BlendshapeFile,
					&param.Radio1,
					&param.Radio2,

					param.AudioPedType,
					param.FirstVoice,
					param.LastVoice
					);

				this->ModelName = param.ModelName;
				this->Props = param.Props;
				this->DefaultPedType = param.DefaultPedType;

				this->AnimGroup = param.AnimGroup;
				this->GestureGroup = param.GestureGroup;
				this->GesturePhoneGroup = param.GesturePhoneGroup;
				this->FacialGroup = param.FacialGroup;
				this->VisemeGroup = param.VisemeGroup;

				this->Flags = param.Flags;
				this->AnimFile = param.AnimFile;
				this->BlendshapeFile = param.BlendshapeFile;
				this->Radio1 = param.Radio1;
				this->Radio2 = param.Radio2;
				
				this->AudioPedType = param.AudioPedType;
				this->FirstVoice = param.FirstVoice;
				this->LastVoice = param.LastVoice;
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				sscanf(xLine.c_str(), "%d %s %s %d %s %s %s %s %s %s %s %d %s %s %s %s %s",
					&param.ModelID,

					param.ModelName,
					param.TXDname,

					&param.IsFemale,
					param.Size,
					param.DefaultPedType,
					param.PedStat,
					
					param.AnimGroup,
					param.AnimGroup2,
					param.AnimGroup3,
					param.AnimGroup4,

					&param.Unique,
					param.ActionTreeRoot,
					param.ActionTreeFile,
					param.AiTreeRoot,
					param.AiTreeFile,
					param.UnknownParam17inBullyScholarschip
					);

				this->ModelID = param.ModelID;
				this->ModelName = param.ModelName;
				this->TXDname = param.TXDname;

				this->IsFemale = param.IsFemale != 0;
				this->Size = param.Size;

				this->DefaultPedType = param.DefaultPedType;
				this->PedStat = param.PedStat;

				this->AnimGroup = param.AnimGroup;
				this->AnimGroup2 = param.AnimGroup2;
				this->AnimGroup3 = param.AnimGroup3;
				this->AnimGroup4 = param.AnimGroup4;

				this->Unique = param.Unique;
				this->ActionTreeRoot = param.ActionTreeRoot;
				this->ActionTreeFile = param.ActionTreeFile;
				this->AiTreeRoot = param.AiTreeRoot;
				this->AiTreeFile = param.AiTreeFile;
				this->UnknownParam17inBullyScholarschip = param.UnknownParam17inBullyScholarschip;
			}

			return this->ModelID;
		}

		// Exports entry. Returns length of output string.
		int CModelPed::ExportEntry(Game::eGameNameSimplified game, char* line)
		{
			if (game == GAME_SIMPLE_NAME_GTA_III)
			{
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %x",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),

					this->DefaultPedType.c_str(),
					this->PedStat.c_str(),
					this->AnimGroup.c_str(),

					this->CarsCanDriveMask
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_VC)
			{
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %x, %s, %d, %d",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),

					this->DefaultPedType.c_str(),
					this->PedStat.c_str(),
					this->AnimGroup.c_str(),

					this->CarsCanDriveMask,

					this->AnimFile.c_str(),

					this->Radio1,
					this->Radio2
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_SA)
			{
				return sprintf(line, "%d, %s, %s, %s, %s, %s, %x, %x, %s, %d, %d, %s, %s, %s",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),

					this->DefaultPedType.c_str(),
					this->PedStat.c_str(),
					this->AnimGroup.c_str(),

					this->CarsCanDriveMask,
					this->Flags,		

					this->AnimFile.c_str(),

					this->Radio1,
					this->Radio2,
											
					this->AudioPedType.c_str(),
					this->FirstVoice.c_str(),
					this->LastVoice.c_str()					
					);
			}
			else if (game == GAME_SIMPLE_NAME_GTA_IV)
			{
				return sprintf(line, "%s, %s, %s, %s, %s, %s, %s, %s, %x, %s, %s, %d, %d, %s, %s, %s",

					this->ModelName.c_str(),
					this->Props.c_str(),
					this->DefaultPedType.c_str(),

					this->AnimGroup.c_str(),
					this->GestureGroup.c_str(),
					this->GesturePhoneGroup.c_str(),
					this->FacialGroup.c_str(),
					this->VisemeGroup.c_str(),

					this->Flags,
					this->AnimFile.c_str(),
					this->BlendshapeFile.c_str(),
					this->Radio1,
					this->Radio2,

					this->AudioPedType.c_str(),
					this->FirstVoice.c_str(),
					this->LastVoice.c_str()
					);
			}
			else if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
			{
				return sprintf(line, "%d, %s, %s, %d, %s, %s, %s, %s, %s, %s, %s, %d, %s, %s, %s, %s, %s",
					this->ModelID,

					this->ModelName.c_str(),
					this->TXDname.c_str(),

					this->IsFemale,
					this->Size.c_str(),
					this->DefaultPedType.c_str(),
					this->PedStat.c_str(),

					this->AnimGroup.c_str(),
					this->AnimGroup2.c_str(),
					this->AnimGroup3.c_str(),
					this->AnimGroup4.c_str(),

					this->Unique,
					this->ActionTreeRoot.c_str(),
					this->ActionTreeFile.c_str(),
					this->AiTreeRoot.c_str(),
					this->AiTreeFile.c_str(),
					this->UnknownParam17inBullyScholarschip.c_str()
					);
			}
			else
			{
				*line = NULL;
				return 0;
			}
		}
	}
}