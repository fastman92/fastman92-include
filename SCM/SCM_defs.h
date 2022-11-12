#pragma once
#include <string>
#include <Windows.h>

#include "CCommandID.h"
#include "enumMemberNamePair.h"

#include <eGame.h>

/*
 Number of variables in default main.scm files:
	GTA LCS: 4369
	GTA VCS: 6395

*/

#define _countOfType(type) (sizeof(type) / sizeof(**(type*)0))
#define _countOfAndPointer(Array) _countof(Array), Array
#define makeReferenceToSupportedFormatsArray(Array) { _countOfAndPointer(Array) }

namespace SCM
{
	using namespace Game;

	namespace Format
	{
		static const int UNDEFINED = -1;

		static const int SCM_VARIABLE_SIZE = 4;

		static const int MAX_COMMAND_LEN = 64;

		static const int SCM_LOWEST_GLOBAL_VARIABLE = 2;

		static const int SCM_STORIES_OFFSET_MOVEMENT = 8;

		static const int SCM_STORIES_GLOBAL_VARIABLE_MULTIPLIER = 256;

		static const int MAX_NUMBER_OF_COMMAND_ARGUMENTS = 60;

		enum eVariableValueType
		{
			VARIABLE_TYPE_INT,
			VARIABLE_TYPE_FLOAT,
			VARIABLE_TYPE_TEXT_LABEL,
			VARIABLE_TYPE_REFERENCE,

			VARIABLE_TYPE_UNKNOWN
		};

		enum eIdentifierScope
		{
			IDENTIFIER_SCOPE_GLOBAL,
			IDENTIFIER_SCOPE_LOCAL,

			IDENTIFIER_SCOPE_INTERNAL,
			IDENTIFIER_SCOPE_ANYWHERE,
		};

		static enumMemberNamePair<eIdentifierScope> enumStrIdentifierScopePairs[] =
		{
			{IDENTIFIER_SCOPE_GLOBAL, "GLOBAL"},
			{IDENTIFIER_SCOPE_LOCAL, "LOCAL"},
			{IDENTIFIER_SCOPE_INTERNAL, "INTERNAL"},
			{IDENTIFIER_SCOPE_ANYWHERE, "ANYWHERE"}
		};
		
		const unsigned int tCommandNameMaxLength = 64;

		typedef char tCommandName[tCommandNameMaxLength];

		struct tIVeraCommandName
		{
			tCommandName commandName;
		};

		struct tIIIeraCommandName
		{
			uint32_t commandID;
		};

		const uint32_t COMMAND_NAME_UNDEFINED = (uint32_t)-1;

		const unsigned int MaxNumberOfCommands = 1 << ((sizeof(CompiledFormat::tCompiledCommandID)*8)-1);

		const unsigned int COMMAND_ID_WRITTEN_IN_HEX_MAX_LENGTH = sizeof(CompiledFormat::tCompiledCommandID)*2;

		typedef __int64 tInt;

		enum eVersionIdentifier : BYTE
		{
			VERSION_III = 0x6C,
			VERSION_VC = 0x6D,
			VERSION_SA = 0x73,

			VERSION_STORIES = 0x6D
		};

		struct tCompiledExternalInfo
		{
			char Name[20];
			DWORD Offset;
			DWORD Size;		// size in bytes
		};
	};

	namespace Common
	{
		// Reads intermediate command hex represantation e.g 0001
		// endptr may be NULL
		bool ReadIntermediateCommandNumberinHexRepresentation(SCM::CompiledFormat::tCompiledCommandID* pID, const char* pStr, char** endptr);

		// Reads intermediate command hex represantation e.g 0001 and skips equality operator
		// endptr may be NULL
		bool ReadIntermediateCommandNumberinHexRepresentationAndSkipEqualityOperator(SCM::CompiledFormat::tCompiledCommandID* pID, const char* pStr, char** endptr);
	}

	// To be used with in-case sentitive map with string key
	struct __lesscasecmp
	{
	   bool operator() (const std::wstring& a, const std::wstring& b) const
	   {
		  return (_wcsicmp(a.c_str ( ), b.c_str ( )) < 0);
	   }
	};

	#pragma pack(push, 1)
	enum eMessageOutputType {SCM_UNDEFINED, SCM_SUCCESS, SCM_ERROR, SCM_FATAL_ERROR, SCM_WARNING};

	struct tSupportedFormats
	{
		unsigned int NumberOfSupportedSCMformats;
		const eGameNameSimplified* pSupportedSCMFormats;
	};

	static const eGameNameSimplified AllGameFormatsSupported[] = {		
		GAME_SIMPLE_NAME_GTA_III,
		GAME_SIMPLE_NAME_GTA_VC,
		GAME_SIMPLE_NAME_GTA_SA,
		GAME_SIMPLE_NAME_GTA_LCS,
		GAME_SIMPLE_NAME_GTA_VCS
	};

	template <typename enumMemberType, typename nameType = const char*> struct enumMemberNamePairWithSupportedFormats : public enumMemberNamePair<enumMemberType, nameType>
	{		
		// Constructor
		template<size_t SCMformatsCount> enumMemberNamePairWithSupportedFormats(enumMemberType enumMember, nameType name, const eGameName (&supportedSCMformats)[SCMformatsCount])
		{
			this -> enumMember = enumMember;
			this -> name = name;

			this -> supportedArguments.pSupportedSCMFormats = supportedSCMformats;
			this -> supportedArguments.NumberOfSupportedSCMformats = SCMformatsCount;
		}		

		// Checks if given SCM format is supported
		bool enumMemberNamePairWithSupportedFormats::IsThisSCMformatSupported(eGameName format) const
		{
			for(unsigned int i = 0; i < this -> supportedArguments.NumberOfSupportedSCMformats; i++)
				if(this -> supportedArguments.pSupportedSCMFormats[i] == format)
					return true;

			return false;
		}

		tSupportedFormats supportedArguments;
	};
	#pragma pack(pop)

	namespace CompiledFormat
	{
		/*
		struct tCompiledVariableInfoNoValueType
		{

		};
		*/

		typedef __int16 tVariableIndex;
		typedef __int32 tVariableOffset;

		struct tCompiledVariableInfoNoType
		{
			tVariableOffset offset;
			Format::eIdentifierScope scope;
		};

		struct tCompiledVariableInfo : tCompiledVariableInfoNoType
		{
			Format::eVariableValueType valueType;
		};

		struct tStoriesCallFunctionCommandBeginning
		{
			BYTE NumberOfConstantParams;
			BYTE NumberOfVariableParams;
			BYTE Unknown;
		};

		struct tCompiledArrayInfo
		{
			tCompiledVariableInfoNoType ArrayOffset;

			tCompiledVariableInfo ArrayIndex;

			BYTE ArraySize;

			Format::eVariableValueType ArrayValueType;
		};

		struct tIF_CommandConditionInfo
		{
			unsigned int maxNumberOfConditions;

			unsigned int OneConditionAND;
			unsigned int TwoConditionsOR;
		};

		class CIfConditionProperty
		{
			static const tIF_CommandConditionInfo NonStoriesIfConditionProperty;

			static const tIF_CommandConditionInfo StoriesIfConditionProperty;

			// Returns pointer to IF property by game
			const tIF_CommandConditionInfo* GetIfPropertyByGame(eGameName game);
		};		
		
		struct tStoriesGlobalArrayVariable
		{
			BYTE PrimaryIndex;
			BYTE IndexLocalVariable;
			BYTE Size;
		};

		struct tStoriesLocalArrayVariable
		{
			BYTE IndexLocalVariable;
			BYTE Size;
		};

		struct tNonStoriesArrayVariable{
			tVariableIndex PrimaryOffset;
			tVariableIndex Index;
			uint8_t Size;
			uint8_t Flags;
		};

		struct tStoriesFunctionCALLcommandBeginning
		{
			uint8_t NumberOfConstantParams;
			uint8_t NumberOfVariableParams;
			uint8_t Unknown;
		};	
		
		// Returns the number of bytes to skip from the beginning
		unsigned int GetNumberOfBytesToSkipInMAINscm(Game::eGameName game);

		// Type for used object in main.scm
		typedef char tUsedObjectName[24];
	}
}