#include "CSCMSimpleCompiler.h"
#include "CIntermediateCommandLine.h"
#include "eArgumentStuff.h"
#include "CSettingManager.h"
#include "StrLexStuff.h"

namespace SCM
{
	using namespace CommandSystem;
	using namespace ArgumentStuff;
	using namespace CompiledFormat;
	using namespace Format;

	// Returns number of arguments for command
	int CSCMSimpleCompiler::GetMinimumNumberOfArgumentsForCommand(eCommandName ID)
	{
		SCM::CommandSystem::CSannyBuilderIniEntry* pEntry = this -> m_INIOpcodeManager.GetEntryByID(ID);

		return pEntry != NULL ? pEntry -> GetNumberOfParams() : COMMAND_NOT_FOUND;
	}

	// Returns number of known arguments and their types
	int CSCMSimpleCompiler::GetNumberOfLastKnownArgumentType(eCommandName ID)
	{
		SCM::CommandSystem::CSannyBuilderIniEntry* pEntry = this -> m_INIOpcodeManager.GetEntryByID(ID);

		return pEntry ? pEntry -> GetNumberOfLastKnownArgumentType() : -1;
	}

	// Returns true if command is variadic
	bool CSCMSimpleCompiler::IsCommandVariadic(eCommandName ID)
	{
		return this -> GetMinimumNumberOfArgumentsForCommand(ID) == VARIABLE_NUMBER_OF_ARGUMENTS;
	}

	// Returns true if argument is meant to be a string, very important function if script is decompiled from game where immediate strings exist
	bool CSCMSimpleCompiler::IsArgumentAstring(eCommandName ID, int argumentNum)
	{		
		SCM::CommandSystem::CSannyBuilderIniEntry* pEntry = this -> m_INIOpcodeManager.GetEntryByID(ID);

		return pEntry ? IsSannyBuilderIniEntryOpcodeArgumentTypeAstring(pEntry -> GetArgumentTypeAlone(argumentNum)) : false;
	}

	// Checks if specified argument of command is meant to be a label pointer
	bool CSCMSimpleCompiler::IsArgumentALabelPointer(eCommandName ID, int argumentNum)
	{
		SCM::CommandSystem::CSannyBuilderIniEntry* pEntry = this -> m_INIOpcodeManager.GetEntryByID(ID);

		return pEntry ? pEntry -> GetArgumentTypeAlone(argumentNum) == SANNY_BUILDER_INI_OPCODE_VALUE_TYPE_LABEL_POINTER : false;
	}
	
	/////// CSCMSimpleCompiler functions ///////

	// Function to compare if something is identifier.
	int CSCMSimpleCompiler::IdentifierCmp(const char * str1, const char * str2)
	{
		return _stricmp(str1, str2);
	}

	// Adds label reference
	void CSCMSimpleCompiler::AddLabelReference(int lineNum, DWORD codeOffset, const char* toLabel)
	{
		tLabelReference newReference;
		newReference.lineNum = lineNum;

		newReference.fromOffset = codeOffset;		
		strncpy(newReference.toLabel, toLabel, sizeof(newReference.toLabel));

		this -> LabelReferenceArray.push_back(newReference);
	}

	// Adds label reference
	void CSCMSimpleCompiler::AddLabelReferenceFromCurOffset(int lineNum, const char* toLabel)
	{
		this -> AddLabelReference(lineNum, this -> OutputFile.Tell(), toLabel);
	}

	// Registers label
	bool CSCMSimpleCompiler::RegisterLabel(const char* name, DWORD codeOffset)
	{
		if(!this -> DoesLabelExist(name))
		{
			this -> LabelOffsetMap[name] = codeOffset;
			return true;
		}

		return false;
	}

	// Registers label
	bool CSCMSimpleCompiler::RegisterLabelFromCurOffset(const char* name)
	{
		return this -> RegisterLabel(name, this -> OutputFile.Tell());
	}

	// Returns label offset
	DWORD CSCMSimpleCompiler::GetLabelOffset(const char* name)
	{
		auto it = this -> LabelOffsetMap.find(name);

		return it != this -> LabelOffsetMap.end() ? it -> second : NULL;
	}

	// Returns true if label exists.
	bool CSCMSimpleCompiler::DoesLabelExist(const char* name)
	{
		auto it = this -> LabelOffsetMap.find(name);

		return it != this -> LabelOffsetMap.end();
	}

	// Aborts compilation.
	void CSCMSimpleCompiler::AbortCompilation()
	{
		this -> bAbortCompilation = true;
	}

	// Writes a segment label name to variable
	void CSCMSimpleCompiler::GetSegmentLabelName(char* outStr, int segmentNum)
	{
		sprintf(outStr, "SEGMENT_OFFSET_%d", segmentNum);
	}

	// Registers label for current segment
	void CSCMSimpleCompiler::RegisterLabelForCurrentSegment()
	{
		char segmentLabelName[64];
		this -> GetSegmentLabelName(segmentLabelName, this -> curSegmentID);

		this -> RegisterLabelFromCurOffset(segmentLabelName);
	}

	// Sets code compilation mode.
	void CSCMSimpleCompiler::SetCodeCompilationStage()
	{
		this -> SetCompilationStage(COMPILATION_STAGE_CODE);

		this -> RegisterLabelForCurrentSegment();
	}

	// Sets compilation mode.
	void CSCMSimpleCompiler::SetCompilationStage(eCompilationStage mode)
	{
		this -> compilationStage = mode;
	}

	// Initializes segment writer
	void CSCMSimpleCompiler::InitializeSegmentWriter()
	{
		this -> curSegmentID = 1;
	}

	// Writes segment header.
	void CSCMSimpleCompiler::WriteSegmentHeader(char segmentMark)
	{
		char segmentLabelName[64];
		this -> RegisterLabelForCurrentSegment();

		WORD opcodeID = 0x0002;		// GOTO
		eArgumentDataTypesFormat_GTA_LCS_VCS type = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_INT_32BITS;

		this -> OutputFile.Write(&opcodeID, sizeof(opcodeID));
		this -> OutputFile.Write(&type, sizeof(type));

		this -> GetSegmentLabelName(segmentLabelName, this -> curSegmentID + 1);

		this -> AddLabelReference(this -> curLineNum, this -> OutputFile.Tell(), segmentLabelName);

		this -> OutputFile.Write(&LabelReferencePlaceholder, sizeof(LabelReferencePlaceholder));
		this -> OutputFile.Write(&segmentMark, sizeof(segmentMark));

		this -> curSegmentID++;
	}

	// Destructor
	CSCMSimpleCompiler::~CSCMSimpleCompiler()
	{
		delete this -> OutputFile.GetPtr();
	}

	// Initializes compilation
	void CSCMSimpleCompiler::InitializeCompilation()
	{
		if(!this -> OutputFile.GetPtr())
		{
			int size = 5*1024*1024;
			this -> m_pBaseToMAINscmContent = new char[size];

			this -> OutputFile.Open(this -> m_pBaseToMAINscmContent, 0, size);			
		}

		this -> bAbortCompilation = false;

		this -> compilationMode = COMPILATION_MODE_NORMAL;
		this -> SetCompilationStage(COMPILATION_STAGE_DEFINE_NUMBER_OF_GLOBAL_VARIABLES);

		this -> InitializeSegmentWriter();

		this -> LabelReferenceArray.clear();

		this -> LabelOffsetMap.clear();
	}

	// Init
	void CSCMSimpleCompiler::Init(eGameName game, const char* SannyBuilderGameINIfilename)
	{
		this -> gameID = game;

		this -> m_INIOpcodeManager.Load(SannyBuilderGameINIfilename);

		for(tSannyBuilderIniEntriesMap::iterator it = this -> m_INIOpcodeManager.m_INIcommandEntries.begin();
			it != m_INIOpcodeManager.m_INIcommandEntries.end();
			it++)
			this -> RegisterCommand(it -> first);

		this -> PrepareListsOfSpecialCommands();

		// this -> m_CommandsWithSpecialArgument.WithLabelArgument.PrintListofSpecialCommands();
	}

	// Puts command ID into variable by parsing a line.
	bool CSCMSimpleCompiler::GetCommandIDforParsing(const char* sourceCode, CCommandID& commandID, char** pEnd)
	{
		char* iLine = FindFirstNonWhiteCharacter(sourceCode);

		for(int i = 0; i < 4; i++)
			if(!isxdigit(iLine[i]))
				return false;

		if(iLine[4] != ':')
			return false;	

		tCompiledCommandID ID = (tCompiledCommandID)strtol(iLine, NULL, 16);

		commandID.SetIDFromCompiledCommandID(ID);

		if(pEnd)
			*pEnd = iLine + 5;

		return true;
	}

	// Reads label reference
	bool CSCMSimpleCompiler::ReadLabelReferenceFromSourceCode(const char* sourceCode, char* result, char** pEnd)
	{
		char* iLine = FindFirstNonWhiteCharacter(sourceCode);		

		if(*iLine == '@')
		{
			const char* identifier = iLine + 1;

			do
				iLine++;
			while(IsValidIdentifierContinuation(*iLine));

			memcpy(result, identifier, iLine - identifier);

			result[iLine - identifier] = NULL;

			if(pEnd)
				*pEnd = iLine;

			return true;
		}

		return false;
	}

	// Reads global variable
	bool CSCMSimpleCompiler::ReadGlobalVariableOffsetFromSourceCode(const char* sourceCode, CompiledFormat::tVariableOffset& result, char** pEnd)
	{
		sourceCode = FindFirstNonWhiteCharacter(sourceCode);

		tVariableIndex varID;

		if(*sourceCode == '$')
		{
			const char* identifier = sourceCode + 1;

			if(isdigit(*identifier))	// for example $62
			{
				char* newPtr;
				varID = (tVariableIndex) _strtoi64(identifier, &newPtr, 10);

				if(newPtr != identifier)
				{
					if(pEnd)
						*pEnd = newPtr;

					result = varID * SCM_VARIABLE_SIZE;

					return true;
				}
			}
			else if(IsValidIdentifierBeginningChar(*identifier))	// for example $PLAYER_ACTOR
			{
				int l = 0;
				char varName[64];

				do
					varName[l++] = identifier[l];
				while(l < sizeof(varName) && IsValidIdentifierContinuation(identifier[l]));

				varName[l] = NULL;

				if(varID = this -> customVariableNameManager.GetGlobalVarIDByID(varName))
				{				
					result = varID * SCM_VARIABLE_SIZE;
					return true;
				}
				else
					return false;
			}
		}

		return false;
	}

	// Reads a model name
	bool CSCMSimpleCompiler::ReadModelNameFromDefineInSourceCode(const char* sourceCode, char* result, char** pEnd)
	{
		char* iLine = FindFirstNonWhiteCharacter(sourceCode);

		const char* beginning = iLine;

		if(*iLine == '(')
		{
			iLine++;

			if(IsValidIdentifierBeginningChar(*iLine))
			{
				do
					iLine++;
				while(IsValidIdentifierContinuation(*iLine));

				if(*iLine == ')')
				{
					*result = NULL;

					if(pEnd)
						*pEnd = iLine + 1;

					return true;
				}
			}
		}
		else if(IsValidIdentifierBeginningChar(*iLine))
		{
			do
				iLine++;
			while(IsValidIdentifierContinuation(*iLine));

			memcpy(result, beginning, iLine - beginning);

			result[iLine - beginning] = NULL;

			if(pEnd)
				*pEnd = iLine;

			return true;
		}

		return false;
	}

	// Loads keywords
	void CSCMSimpleCompiler::LoadCommandKeywords(const char* filename)
	{
		this -> m_KeywordManager.Load(filename);
	}

	// Loads global variable names.
	void CSCMSimpleCompiler::LoadGlobalVariableNames(const char* filename)
	{
		this -> customVariableNameManager.Load(filename);
	}

	// Writes to label reference offsets.
	void CSCMSimpleCompiler::ResolveLabelOffsets()
	{
		for(tLabelReference& reference : this -> LabelReferenceArray)
		{
			if(DWORD offset = this -> GetLabelOffset(reference.toLabel))
			{
				printf("Resolving label refererence from 0x%X to %s on line %d\n", reference.fromOffset, reference.toLabel, reference.lineNum);

				*(DWORD*)&this -> m_pBaseToMAINscmContent[reference.fromOffset] = offset;
			}
			else
			{
				printf("(%d) Cannot resolve reference to label %s\n", reference.lineNum, reference.toLabel);
				this -> AbortCompilation();
				return;
			}
		}
		
	}

	// Returns true if all label references have already been added.
	bool CSCMSimpleCompiler::HaveAllMissionLabelReferencesBeenAdded()
	{
		for(DWORD i = 0; i < this -> NumberOfMissions; i++)
		{
			if(!this -> missionReferenceAddedArray[i])
				return false;
		}

		return true;
	}

	// Finds sizes.
	void CSCMSimpleCompiler::FindMAINscmSizeValues()
	{
		if(this -> NumberOfMissions > 0)
		{
			this -> MainScriptSize = OutputFile.GetSize();
			this -> LargestMissionScriptSize = 0;
		}
		else
		{
			this -> MainScriptSize = OutputFile.GetSize();
			this -> LargestMissionScriptSize = 0;
		}
	}

	// Performs post-compilation tasks
	void CSCMSimpleCompiler::DoPostCompilationTasks()
	{
		this -> FindMAINscmSizeValues();

		*(DWORD*)&this -> m_pBaseToMAINscmContent[this -> OffsetToLargestMissionSize] = this -> LargestMissionScriptSize;
		this -> ResolveLabelOffsets();
	}

	// Checks if number falls in range
	bool IsNumberInRange(__int32 num, __int32 range_low, __int32 range_high)
	{
		return num >= range_low && num <= range_high;
	}

	// Parses command line
	void CSCMSimpleCompiler::ParseCommandLine(CCommandID& ID, const char* sourceCode)
	{
		CSannyBuilderIniEntry* pEntry = this -> m_INIOpcodeManager.GetEntryByID((eCommandName)ID.ID);

		if(!pEntry)
		{
			printf("(%d) Opcode with number of %04X does not exist.\n", curLineNum, ID.ID);
			return this -> AbortCompilation();
		}

		CIntermediateCommandLine commandLine;

		commandLine.SetCommandID(ID);
	
		const char* iLine = sourceCode;

		CIntermediateArgument* argument;

		char identifier[64];

		int sourceCodeArgNum = 1;
				
		while(true)
		{
			const char* beginning = FindFirstNonWhiteCharacter(iLine);
			
			if(*beginning == NULL)
				break;

			const char* end;			
			
			if(*beginning == '\'')
			{
				const char* strBeginning = beginning + 1;

				if(end = strchr(beginning+1, '\''))
				{
					char str[16];

					int l = end - strBeginning;

					if(l > 7)
					{
						printf("(%d) String cannot be longer than 7 characters.\n", curLineNum);
						return this -> AbortCompilation();
					}

					memcpy(str, strBeginning, end - strBeginning);
					str[l] = NULL;

					argument = commandLine.AllocateNthArgument(pEntry -> GetOriginalArgumentNumBySourceCodeArgumentNum(sourceCodeArgNum++));

					argument -> SetStaticShortOrLong(str);

					end += 1;
				}
				else
				{
					printf("(%d) Unmatched string quotation mark.\n");
					return this -> AbortCompilation();
				}
			}
			else
			{
				end = FindNextWhiteCharacter(beginning);

				if(*beginning == '$')	// global variable?
				{
					/*
					bool bGoodDecimalNum = true;

					const char* numBeginning = beginning + 1;					

					for(const char* i = numBeginning; i < end; i++)
						if(!isdigit(*i))
						{
							bGoodDecimalNum = false;
							break;
						}					

					if(!bGoodDecimalNum)
					{
						printf("(%d) Bad global variable ID.\n", curLineNum);
						return this -> AbortCompilation();
					}

					tVariableIndex varID = (tVariableIndex)strtol(numBeginning, NULL, 10);
					*/

					tVariableOffset varOffset;

					if(!this -> ReadGlobalVariableOffsetFromSourceCode(beginning, varOffset, NULL))
					{
						printf("(%d) Bad global variable ID.\n", curLineNum);
						return this -> AbortCompilation();
					}

					tVariableIndex varID = varOffset / SCM_VARIABLE_SIZE;

					argument = commandLine.AllocateNthArgument(pEntry -> GetOriginalArgumentNumBySourceCodeArgumentNum(sourceCodeArgNum++));					

					argument -> SetSingleVariable(
						varID * SCM_VARIABLE_SIZE,
						eIdentifierScope::IDENTIFIER_SCOPE_GLOBAL,
						eVariableValueType::VARIABLE_TYPE_UNKNOWN
						);									
				}
				else if(*beginning == '@')	// label?
				{
					char* pEnd;

					if(!this -> ReadLabelReferenceFromSourceCode(beginning, identifier, &pEnd))
					{
						printf("(%d) Wrong label name.\n");
						return this -> AbortCompilation();
					}					

					argument = commandLine.AllocateNthArgument(pEntry -> GetOriginalArgumentNumBySourceCodeArgumentNum(sourceCodeArgNum++));

					argument -> SetLabelReferenceName(identifier);
				}
				else if(*(end-1) == '@')	// local number variables
				{
					bool bGoodDecimalNum = true;

					const char* numBeginning = beginning;				

					for(const char* i = numBeginning; i < end-1; i++)
						if(!isdigit(*i))
						{
							bGoodDecimalNum = false;
							break;
						}

					tVariableIndex varID = (tVariableIndex)strtol(numBeginning, NULL, 10);

					argument = commandLine.AllocateNthArgument(pEntry -> GetOriginalArgumentNumBySourceCodeArgumentNum(sourceCodeArgNum++));

					argument -> SetSingleVariable(
						varID * SCM_VARIABLE_SIZE,
						eIdentifierScope::IDENTIFIER_SCOPE_LOCAL,
						eVariableValueType::VARIABLE_TYPE_UNKNOWN
						);
				}
				else
				{					
					bool isFloat = false;

					const char* pTest = *beginning == '-' ? beginning+1 : beginning;

					if(isdigit(*pTest))
					{
						for(const char* i = beginning; i < end; i++)
						{
							if(*i == '.')
							{
								isFloat = true;
								break;
							}
						}
					}

					if(isFloat)
					{
						char floatStr[20];

						memcpy(floatStr, beginning, end-beginning);
						floatStr[end-beginning] = NULL;

						float floatNum;
						sscanf(floatStr, "%f", &floatNum);

						argument = commandLine.AllocateNthArgument(pEntry -> GetOriginalArgumentNumBySourceCodeArgumentNum(sourceCodeArgNum++));
						argument -> SetStaticFloat(floatNum);
					}
					else
					{
						char* pointerToIntEnd;

						__int32 num = (__int32)ReadIntegerNum(beginning, &pointerToIntEnd);				
					
						if(pointerToIntEnd != beginning)
						{
							argument = commandLine.AllocateNthArgument(pEntry -> GetOriginalArgumentNumBySourceCodeArgumentNum(sourceCodeArgNum++));
							argument -> SetStaticInt(num);
						}
					}
				}
			}
			
			iLine = end;
		}

		// Write data to output file		
		tCompiledCommandID compiledCommandID = ID.ToCompiledCommandID();

		OutputFile.Write(&compiledCommandID, sizeof(compiledCommandID));

		for(unsigned int i = 0; i < commandLine.numberOfArguments; i++)
		{
			int argumentNum = i + 1;

			argument = commandLine.argumentPtrArray[i];

			eIntermediateArgumentType intermediateArgType = argument -> GetType();

			if(CStaticGameSettingManager::DoesSCMhaveIntermediateStrings(this -> gameID)
				&& this -> IsArgumentAstring((eCommandName)ID.ID, argumentNum)
				&& intermediateArgType != INTERMEDIATE_ARGUMENT_TYPE_STATIC_SHORT_OR_LONG_STRING
				)
			{
				printf("(%d) Argument %d expects string.\n", curLineNum, argumentNum);
				this -> AbortCompilation();
				return;
			}

			eArgumentDataTypesFormat_GTA_LCS_VCS dataType;

			switch(argument -> GetType())
			{
				case INTERMEDIATE_ARGUMENT_TYPE_STATIC_SHORT_OR_LONG_STRING:
					{
						if (this->gameID == GAME_EXACT_GTALCS_PS2)
							OutputFile.Write(&argument -> value.StaticString, 8);	
						else if (this->gameID == GAME_EXACT_GTAVCS_PS2)
						{
							dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::VCS_STATIC_C_STRING;

							OutputFile.Write(&dataType, sizeof(dataType));

							OutputFile.Write(&argument -> value.StaticString, strlen(argument -> value.StaticString) + 1);
						}

						break;
					}
				case INTERMEDIATE_ARGUMENT_TYPE_LABEL_REFERENCE_NAME:
					{
						dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_INT_32BITS;
						OutputFile.Write(&dataType, sizeof(dataType));

						this -> AddLabelReferenceFromCurOffset(curLineNum, argument -> value.LabelReferenceName);
						OutputFile.Write(&this -> LabelReferencePlaceholder, sizeof(this -> LabelReferencePlaceholder));						
						break;
					}
				case INTERMEDIATE_ARGUMENT_TYPE_VARIABLE:
					{						
						tCompiledVariableInfo& variableInfo = argument -> value.SingleVariable;

						tVariableIndex varID = variableInfo.offset / SCM_VARIABLE_SIZE;

						if(variableInfo.scope == IDENTIFIER_SCOPE_GLOBAL)
						{
							if (this->gameID == GAME_EXACT_GTALCS_PS2)
								dataType = (eArgumentDataTypesFormat_GTA_LCS_VCS)((varID / 256) + (int)eArgumentDataTypesFormat_GTA_LCS_VCS::LCS_GLOBAL_VARIABLE_RANGE_FIRST);
							else if (this->gameID == GAME_EXACT_GTAVCS_PS2)
								dataType = (eArgumentDataTypesFormat_GTA_LCS_VCS)((varID / 256) + (int)eArgumentDataTypesFormat_GTA_LCS_VCS::VCS_GLOBAL_VARIABLE_RANGE_FIRST);

							OutputFile.Write(&dataType, sizeof(dataType));
							BYTE remainder = varID % 256;
							OutputFile.Write(&remainder, sizeof(remainder));
						}
						else
						{
							if (this->gameID == GAME_EXACT_GTALCS_PS2)
								dataType = (eArgumentDataTypesFormat_GTA_LCS_VCS)((varID) + (int)eArgumentDataTypesFormat_GTA_LCS_VCS::LCS_LOCAL_VARIABLE_RANGE_FIRST);
							else if (this->gameID == GAME_EXACT_GTAVCS_PS2)
								dataType = (eArgumentDataTypesFormat_GTA_LCS_VCS)((varID) + (int)eArgumentDataTypesFormat_GTA_LCS_VCS::VCS_LOCAL_VARIABLE_RANGE_FIRST);

							OutputFile.Write(&dataType, sizeof(dataType));
						}

						break;
					}
				case INTERMEDIATE_ARGUMENT_TYPE_STATIC_INT:
					{
						__int32 num = argument -> value.StaticInt;

						if(num == 0)
						{
							dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_INT_ZERO;
							OutputFile.Write(&dataType, sizeof(dataType));
						}
						else if(IsNumberInRange(num, -128, 127))
						{
							dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_INT_8BITS;
							OutputFile.Write(&dataType, sizeof(dataType));
							OutputFile.Write(&num, 1);
						}
						else if(IsNumberInRange(num, -32768, 32767))
						{
							dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_INT_16BITS;
							OutputFile.Write(&dataType, sizeof(dataType));
							OutputFile.Write(&num, 2);
						}
						else
						{
							dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_INT_32BITS;
							OutputFile.Write(&dataType, sizeof(dataType));
							OutputFile.Write(&num, 4);
						}

						break;
					}
				case INTERMEDIATE_ARGUMENT_TYPE_STATIC_FLOAT:
					{						
						__int32 floatNum = *(__int32*)&argument -> value.StaticFloat;
						int numberOfLastBytes;

						if(floatNum == 0)
						{
							dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_FLOAT_ZERO;
							OutputFile.Write(&dataType, sizeof(dataType));
						}
						else
						{
							if(!(floatNum & 0x00FFFFFF))	// does float fit in 1 last byte?
							{
								dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_FLOAT_PACKED_POSITIVE_1_LAST_BYTE;
								numberOfLastBytes = 1;
							}
							else if(!(floatNum & 0x0000FFFF))	// does float fit in 2 last bytes
							{
								dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_FLOAT_PACKED_POSITIVE_2_LAST_BYTES;
								numberOfLastBytes = 2;
							}
							else if(!(floatNum & 0x000000FF))	// does float fit in 3 last bytes?
							{
								dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_FLOAT_PACKED_POSITIVE_3_LAST_BYTES;
								numberOfLastBytes = 3;
							}
							else
							{
								dataType = eArgumentDataTypesFormat_GTA_LCS_VCS::STATIC_FLOAT;
								numberOfLastBytes = 4;
							}

							OutputFile.Write(&dataType, sizeof(dataType));
							OutputFile.Write((char*)&floatNum+4-numberOfLastBytes, numberOfLastBytes);
						}

						break;
					}
			}
		}

		eArgumentDataTypesFormat_GTA_LCS_VCS endOfArgs = eArgumentDataTypesFormat_GTA_LCS_VCS::END_OF_ARGUMENTS;

		if(this -> IsCommandVariadic((eCommandName) ID.ID))
			OutputFile.Write(&endOfArgs, sizeof(eArgumentDataTypesFormat_GTA_LCS_VCS));

	}

	// Removes a comment from line
	void RemoveSingleCommentFromLine(char* line)
	{
		while(*line)
		{
			if(*line == '/' && *(line + 1) == '/')
			{
				*line = NULL;
				break;
			}

			line++;
		}
	}

	// Compiles a source file
	void CSCMSimpleCompiler::Compile(const char* filename)
	{
		printf("\n\n", __FUNCTION__);

		this -> InitializeCompilation();

		DWORD zero32bit = 0;

		CCommandID CommandID;

		if(FILE* fp = fopen(filename, "r"))
		{			
			char line[1024];

			this -> curLineNum = 0;

			while(this -> curLineNum++, fgets(line, sizeof(line), fp))
			{			
				char identifier[64];

				RemoveSingleCommentFromLine(line);

				char* iLine = FindFirstNonWhiteCharacter(line);				

				if(!*iLine)
					continue;				

				ReadIdentifier(identifier, sizeof(identifier), iLine, &iLine);

				if(*identifier)
				{
					bool bContinueChecking = true;

					if(!IdentifierCmp(identifier, "END"))
					{
						if(this -> compilationMode != COMPILATION_MODE_NORMAL)
						{
							this -> compilationMode = COMPILATION_MODE_NORMAL;
							bContinueChecking = false;
						}
						else
						{
							printf("(%d) Unmatched end construct.", curLineNum);
							this -> AbortCompilation();
							break;
						}
					}
					else if(this -> compilationMode == COMPILATION_MODE_HEX_END)
					{
						printf("(%d) Only END identifier is allowed in hex...end compilation mode.", curLineNum);
						this -> AbortCompilation();
						break;
					}

					if(!bContinueChecking) ;
					else if(!IdentifierCmp(identifier, "DEFINE"))
					{						
						ReadIdentifier(identifier, sizeof(identifier), iLine, &iLine);

						if(*identifier)
						{
							if(!IdentifierCmp(identifier, "NUMBER_OF_GLOBAL_VARIABLES"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_NUMBER_OF_GLOBAL_VARIABLES)
								{
									printf("Attempt to use DEFINE NUMBER_OF_GLOBAL_VARIABLES not in _DEFINE_NUMBER_OF_GLOBAL_VARIABLES compilation mode.\n");
									this -> AbortCompilation();
									break;
								}

								this -> NumberOfGlobalVariables = (int)ReadIntegerNum(iLine, NULL);						

								WriteSegmentHeader(0x6D);								

								for(DWORD varID = 2; varID < NumberOfGlobalVariables; varID++)
									OutputFile.Write(&zero32bit, sizeof(zero32bit));
							}
							else if(!IdentifierCmp(identifier, "SAVED_VARIABLES"))
							{
								this -> SetCompilationStage(COMPILATION_STAGE_DEFINE_SAVED_VARIABLES);
								WriteSegmentHeader(0);

								this -> OffsetToSizeOfSavedVariableArray = OutputFile.Tell();
								
								OutputFile.Write(&zero32bit, sizeof(zero32bit));	// size of saved variable array

								this -> OffsetToSavedVariableArray = OutputFile.Tell();
							}
							else if(!IdentifierCmp(identifier, "SAVED_VARIABLE"))
							{
								tVariableOffset varOffset;

								if(this -> ReadGlobalVariableOffsetFromSourceCode(iLine, varOffset, NULL))
									OutputFile.Write(&varOffset, sizeof(varOffset));
								else
								{
									printf("(%d) Can't read variable ID.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}				
							}
							else if(!IdentifierCmp(identifier, "OBJECTS"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_SAVED_VARIABLES)
								{
									printf("Attempt to use DEFINE OBJECTS not past the DEFINE_SAVED_VARIABLES compilation mode.\n");
									this -> AbortCompilation();
									break;
								}

								*(DWORD*)&this -> m_pBaseToMAINscmContent[this -> OffsetToSizeOfSavedVariableArray] = (OutputFile.Tell() - this -> OffsetToSavedVariableArray) / sizeof(WORD);								

								this -> currentObjectID = 0;
								this -> NumberOfUsedObjects = (int)ReadIntegerNum(iLine, NULL);	

								this -> OutputFile.Write(&NumberOfUsedObjects, sizeof(NumberOfUsedObjects));

								this -> SetCompilationStage(COMPILATION_STAGE_DEFINE_OBJECTS);
							}
							else if(!IdentifierCmp(identifier, "OBJECT"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_OBJECTS)
								{
									printf("Attempt to use DEFINE OBJECT not in DEFINE_OBJECTS compilation mode.\n");
									this -> AbortCompilation();
									break;
								}

								if(this -> currentObjectID == this -> NumberOfUsedObjects)
								{
									printf("Line %d: too many objects!.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}

								tUsedObjectName modelName;

								if(!this -> ReadModelNameFromDefineInSourceCode(iLine, modelName, NULL))
								{
									printf("Line %d: can't read model name for DEFINE OBJECT.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}

								if(!modelName[0])
									memset(modelName, NULL, sizeof(modelName));

								this -> currentObjectID++;

								OutputFile.Write(modelName, sizeof(tUsedObjectName));
							}
							else if(!IdentifierCmp(identifier, "MISSION_VARIABLE_START_ID"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_OBJECTS)
								{
									printf("Attempt to use DEFINE MISSION_VARIABLE_START_ID past the DEFINE_OBJECTS compilation mode.\n");
									this -> AbortCompilation();
									break;
								}

								this -> SetCompilationStage(COMPILATION_STAGE_DEFINE_MISSION_VARIABLE_START_ID);

								WriteSegmentHeader(0);

								tVariableOffset varOffset;

								if(this -> ReadGlobalVariableOffsetFromSourceCode(iLine, varOffset, NULL))
								{
									this -> MissionGlobalVariableStartID = varOffset / SCM_VARIABLE_SIZE;

									WORD x = this -> MissionGlobalVariableStartID - 2;

									OutputFile.Write(&x, sizeof(x));
								}
								else
								{
									printf("(%d) Can't read variable ID.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}										
							}
							else if(!IdentifierCmp(identifier, "MISSION_NUMBER_OF_VARIABLES"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_MISSION_VARIABLE_START_ID)
								{
									printf("Attempt to use DEFINE OBJECTS not past the DEFINE_MISSION_VARIABLE_START_ID compilation mode.\n");
									this -> AbortCompilation();
									break;
								}

								this -> SetCompilationStage(COMPILATION_STAGE_DEFINE_MISSION_NUMBER_OF_VARIABLES);
								
								this -> NumberOfGlobalMissionVariables = (int)ReadIntegerNum(iLine, NULL);	

								this -> OutputFile.Write(&NumberOfGlobalMissionVariables, sizeof(NumberOfGlobalMissionVariables));

								this -> OffsetToLargestMissionSize = OutputFile.Tell();

								this -> OutputFile.Write(&zero32bit, sizeof(DWORD));
							}
							else if(!IdentifierCmp(identifier, "MISSIONS"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_MISSION_NUMBER_OF_VARIABLES)
								{
									printf("Attempt to use DEFINE MISSIONS not past the DEFINE_MISSION_NUMBER_OF_VARIABLES compilation mode.\n");
									this -> AbortCompilation();
									break;
								}																

								this -> NumberOfMissions = (int)ReadIntegerNum(iLine, NULL);

								this -> OutputFile.Write(&NumberOfMissions, sizeof(NumberOfMissions));

								this -> offsetToMissionOffsetArray = OutputFile.Tell();

								if(this -> NumberOfMissions > 0)
								{
									memset(this -> missionReferenceAddedArray, false, this -> NumberOfMissions * sizeof(this -> missionReferenceAddedArray[0]));

									for(DWORD i = 0; i < NumberOfMissions; i++)
										this -> OutputFile.Write(&zero32bit, sizeof(zero32bit));

									this -> SetCompilationStage(COMPILATION_STAGE_DEFINE_MISSIONS);
								}
								else
									this -> SetCodeCompilationStage();
							}
							else if(!IdentifierCmp(identifier, "MISSION"))
							{
								if(this -> compilationStage != COMPILATION_STAGE_DEFINE_MISSIONS)
								{
									printf("Attempt to use DEFINE MISSION not in DEFINE_MISSIONS compilation mode.\n");
									this -> AbortCompilation();
									break;
								}	

								DWORD missionID = (DWORD)ReadIntegerNum(iLine, &iLine);

								if(missionID >= this -> NumberOfMissions)
								{
									printf("Line %d: Wrong index of mission.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}

								ReadIdentifier(identifier, sizeof(identifier), iLine, &iLine);

								if(IdentifierCmp(identifier, "AT"))
								{
									printf("Line %d: AT past the mission ID is expected.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}

								if(!this -> ReadLabelReferenceFromSourceCode(iLine, identifier, NULL))
								{
									printf("Line %d: Can't read the valid label name.\n", this -> curLineNum);
									this -> AbortCompilation();
									break;
								}

								this -> AddLabelReference(
									this -> curLineNum,
									this -> offsetToMissionOffsetArray + missionID * sizeof(DWORD),
									identifier);

								this -> missionReferenceAddedArray[missionID] = true;

								if(HaveAllMissionLabelReferencesBeenAdded())
									this -> SetCodeCompilationStage();
							}
							else
							{
								printf("Line %d: wrong identifier for for DEFINE.\n", this -> curLineNum);
								this -> AbortCompilation();
								break;
							}				
						}
						else
						{
							printf("Line %d: can't read identifier for DEFINE.\n", this -> curLineNum);
							this -> AbortCompilation();
							break;
						}
					}
					else if(!IdentifierCmp(identifier, "HEX"))
						this -> compilationMode = COMPILATION_MODE_HEX_END;
					else
					{
						bool bIDnegated = false;

						if(!IdentifierCmp(identifier, "NOT"))
						{
							ReadIdentifier(identifier, sizeof(identifier), iLine, &iLine);

							bIDnegated = true;
						}

						eCommandName ID = this -> m_KeywordManager.GetCommandIDByKeywordName(identifier);

						if(ID != COMMAND_NAME_UNDEFINED)
						{
							CommandID.SetIDFromCompiledCommandID((tCompiledCommandID)ID);

							if(bIDnegated)
								CommandID.notFlag = true;

							this -> ParseCommandLine(CommandID, iLine);							
						}
						else
						{
							printf("Line %d: wrong identifier in this place.\n", this -> curLineNum);
							this -> AbortCompilation();
							break;
						}
					}
				}
				else if(this -> compilationMode == COMPILATION_MODE_HEX_END)
				{
				}
				else if(*iLine == ':')
				{
					ReadIdentifier(identifier, sizeof(identifier), iLine+1, NULL);
					this -> RegisterLabelFromCurOffset(identifier);
				}
				else if(GetCommandIDforParsing(iLine, CommandID, &iLine))
				{
					this -> ParseCommandLine(CommandID, iLine);

					if(this -> bAbortCompilation)
						break;
				}
			}	

			if(!this -> bAbortCompilation)
				this -> DoPostCompilationTasks();

			fclose(fp);
		}
		else
			printf("Can't open %hs.", filename);
	}

	// Saves main.scm to file
	bool CSCMSimpleCompiler::SaveMAINscmToFile(const char* filename, DWORD alignToSize)
	{
		if(FILE* fp = fopen(filename, "wb"))
		{
			fwrite(&this -> MainScriptSize, sizeof(this -> MainScriptSize), 1, fp);
			fwrite(&this -> LargestMissionScriptSize, sizeof(this -> LargestMissionScriptSize), 1, fp);

			fwrite(this -> OutputFile.GetPtr(), this -> OutputFile.GetSize(), 1, fp);

			if(alignToSize != 0)
			{
				DWORD filesize = ftell(fp);

				if(filesize < alignToSize)
				{
					DWORD numberOfNULLbytesToWrite = alignToSize - filesize;

					char* zeroMem = new char[numberOfNULLbytesToWrite];
					memset(zeroMem, NULL, numberOfNULLbytesToWrite);
					fwrite(zeroMem, numberOfNULLbytesToWrite, 1, fp);
					delete zeroMem;
				}
			}

			fclose(fp);
			return true;
		}

		return false;
	}
}