#include "eGame.h"
#include "CSannyBuilderIniManager.h"
#include "CSannyBuilderKeywordManager.h"
#include "CNumberOfCommandArguments.h"
#include "CCustomGlobalVariableNameManager.h"
#include "GMemFile.h"
#include <map>
#include <string>
#include <vector>

#define MAX_NUMBER_OF_MISSIONS 250

namespace SCM
{
	struct tLabelReference
	{
		DWORD fromOffset;	// offset to 32-bit value
		char toLabel[64];

		int lineNum;
	};

	class CSCMSimpleCompiler : private SCM::CommandSystem::CNumberOfCommandArguments
	{
		// Returns number of arguments for command
		int GetMinimumNumberOfArgumentsForCommand(eCommandName ID);

		// Returns number of known arguments and their types
		int GetNumberOfLastKnownArgumentType(eCommandName ID);

		// Returns true if command is variadic
		bool IsCommandVariadic(eCommandName ID);

		// Returns true if argument is meant to be a string, very important function if script is decompiled from game where immediate strings exist
		bool IsArgumentAstring(eCommandName ID, int argumentNum);

		// Checks if specified argument of command is meant to be a label pointer
		bool IsArgumentALabelPointer(eCommandName ID, int argumentNum);

		////////////////////
		// Sanny Builder INI file manager
		CommandSystem::CSannyBuilderIniManager m_INIOpcodeManager;

		// Sanny Builder keyword manager
		CommandSystem::CSannyBuilderKeywordManager m_KeywordManager;

		// Label reference placeholder.
		static const DWORD LabelReferencePlaceholder = 0xCCCCCCCC;

		// True if compilation had to be aborted.
		bool bAbortCompilation;

		enum eCompilationMode
		{
			COMPILATION_MODE_NORMAL,
			COMPILATION_MODE_HEX_END
		};

		eGameName gameID;

		enum eCompilationStage
		{
			COMPILATION_STAGE_DEFINE_NUMBER_OF_GLOBAL_VARIABLES,
			COMPILATION_STAGE_DEFINE_SAVED_VARIABLES,
			COMPILATION_STAGE_DEFINE_OBJECTS,
			COMPILATION_STAGE_DEFINE_MISSION_VARIABLE_START_ID,
			COMPILATION_STAGE_DEFINE_MISSION_NUMBER_OF_VARIABLES,
			COMPILATION_STAGE_DEFINE_MISSIONS,
			COMPILATION_STAGE_CODE
		};

		// Pointer to base of main.scm content, in case of GTA LCS/VCS it's pMAINscmContent + 8
		char* m_pBaseToMAINscmContent;

		int curLineNum;

		eCompilationMode compilationMode;

		eCompilationStage compilationStage;

		DWORD MainScriptSize;
		DWORD LargestMissionScriptSize;

		BYTE missionReferenceAddedArray[MAX_NUMBER_OF_MISSIONS];

		WORD MissionGlobalVariableStartID;
		WORD NumberOfGlobalMissionVariables;

		DWORD NumberOfMissions;

		DWORD OffsetToLargestMissionSize;

		DWORD offsetToMissionOffsetArray;

		DWORD currentObjectID;

		DWORD NumberOfUsedObjects;

		DWORD NumberOfGlobalVariables;

		DWORD OffsetToSizeOfSavedVariableArray;

		DWORD OffsetToSavedVariableArray;

		GMemFile OutputFile;

		DWORD curOffset;

		unsigned __int8 curSegmentID;

		// Array of label references.
		std::vector<tLabelReference> LabelReferenceArray;

		// Map of label offsets
		std::map<std::string, DWORD, __lesscasecmp> LabelOffsetMap;

		// Custom variable name manager
		SannyBuilder::CCustomGlobalVariableNameManager customVariableNameManager;

		// Function to compare if something is identifier.
		int IdentifierCmp(const char * str1, const char * str2);

		// Adds label reference
		void AddLabelReference(int lineNum, DWORD codeOffset, const char* toLabel);

		// Adds label reference
		void AddLabelReferenceFromCurOffset(int lineNum, const char* toLabel);

		// Registers label
		bool RegisterLabel(const char* name, DWORD codeOffset);

		// Registers label
		bool RegisterLabelFromCurOffset(const char* name);

		// Returns label offset
		DWORD GetLabelOffset(const char* name);

		// Returns true if label exists.
		bool DoesLabelExist(const char* name);

		// Aborts compilation.
		void AbortCompilation();

		// Writes a segment label name to variable
		void GetSegmentLabelName(char* outStr, int segmentNum);

		// Registers label for current segment
		void RegisterLabelForCurrentSegment();

		// Sets code compilation mode.
		void SetCodeCompilationStage();

		// Sets compilation mode.
		void SetCompilationStage(eCompilationStage mode);

		// Initializes segment writer
		void InitializeSegmentWriter();

		// Writes segment header.
		void WriteSegmentHeader(char segmentMark);

		// Initializes compilation
		void InitializeCompilation();

		// Puts command ID into variable by parsing a line.
		bool GetCommandIDforParsing(const char* sourceCode, CompiledFormat::CCommandID& commandID, char** pEnd);

		// Reads label reference
		bool ReadLabelReferenceFromSourceCode(const char* sourceCode, char* result, char** pEnd);

		// Reads global variable
		bool ReadGlobalVariableOffsetFromSourceCode(const char* sourceCode, CompiledFormat::tVariableOffset& result, char** pEnd);

		// Reads a model name
		bool ReadModelNameFromDefineInSourceCode(const char* sourceCode, char* result, char** pEnd);

		// Writes to label reference offsets.
		void ResolveLabelOffsets();

		// Returns true if all label references have already been added.
		bool HaveAllMissionLabelReferencesBeenAdded();

		// Finds sizes.
		void FindMAINscmSizeValues();

		// Performs post-compilation tasks
		void DoPostCompilationTasks();

		// Parses command line
		void ParseCommandLine(CompiledFormat::CCommandID& ID, const char* sourceCode);

		// Compiles code
		// void CompileCode();

	public:
		// Destructor
		~CSCMSimpleCompiler();

		// Init
		void Init(eGameName game, const char* SannyBuilderGameINIfilename);

		// Loads keywords
		void LoadCommandKeywords(const char* filename);

		// Loads global variable names.
		void LoadGlobalVariableNames(const char* filename);

		// Compiles a source file
		void Compile(const char* filename);

		// Saves main.scm to file
		bool SaveMAINscmToFile(const char* filename, DWORD alignToSize = 0);
	};
}