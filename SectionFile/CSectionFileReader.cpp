/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CSectionFileReader.h"
#include "Shlwapi.h"
#include "StrLexStuff.h"

#include <algorithm>
#include <ctype.h>

// Constructor
CSectionFileReader::CSectionFileReader()
{
	this -> m_RecurrencyLevel = 0;
	this -> m_pLoadedParentFilePath = NULL;
}

// Registers section
void CSectionFileReader::RegisterSection(const char* name, int typeID, tSectionFunc func)
{
	std::string str = name;

	for (std::string::size_type i=0; i<str.length(); ++i)
		str[i] = tolower(str[i]);

	tSectionInfo info;
	strncpy(info.sectionName, str.c_str(), sizeof(info.sectionName));
	info.func = func;
	info.typeID = typeID;

	this -> m_SectionMap.push_back(info);
}

// Clears all registered sections.
void CSectionFileReader::ClearSections()
{
	this -> m_SectionMap.clear();
}

// Finds a section info with specified name
const tSectionInfo* CSectionFileReader::FindSectionInfoWithSpecifiedName(const char* name)
{
	for (auto it = this->m_SectionMap.begin(); it != this->m_SectionMap.end(); ++it)
	{
		if (!_stricmp(it->sectionName, name))
			return &*it;
	}

	return NULL;
}

// Finds a section info with specified type ID
const tSectionInfo* CSectionFileReader::FindSectionInfoWithSpecifiedTypeID(int typeID)
{
	for (auto it = this->m_SectionMap.begin(); it != this->m_SectionMap.end(); ++it)
	{
		if (it->typeID == typeID)
			return &*it;
	}

	return NULL;
}

// Loads file
bool CSectionFileReader::LoadFile(const char* filename)
{
	this -> m_RecurrencyLevel++;

	if(this -> m_RecurrencyLevel > MAX_NUMBER_OF_RECURSION_LEVELS)
	{
		printf("Too many recursion levels reached, base file: '%hs'", this -> m_pLoadedParentFilePath);
		return false;
	}

	bool result;

	char PreviousDirectory[MAX_PATH];

	if (this->m_RecurrencyLevel == 1)
		GetCurrentDirectoryA(sizeof(PreviousDirectory), PreviousDirectory);

	if(FILE* fp = fopen(filename, "r"))
	{
		tLineParsingInfo parsingInfo;

		int loadedFileID = this -> m_listOfLoadedFiles.AddNewFile(filename);

		tUniqueFileListEntry* pLoadedFileEntry = this -> m_listOfLoadedFiles.GetFileEntryByID(loadedFileID);

		if(this -> m_RecurrencyLevel == 1)
				this -> m_pLoadedParentFilePath = pLoadedFileEntry -> filePath;		

		parsingInfo.pFilename = pLoadedFileEntry -> pFilename;			

		char relativePath[MAX_PATH];

		PathRelativePathToA(relativePath, this -> m_pLoadedParentFilePath, FILE_ATTRIBUTE_NORMAL, pLoadedFileEntry -> filePath, FILE_ATTRIBUTE_NORMAL);

		this -> m_listOfLoadedFileRelativePaths[loadedFileID] = relativePath;
		
		SetCurrentDirectoryA(pLoadedFileEntry -> directoryPath);

		// if(this -> m_SectionMap.size() > 0)

		{	
			// Current section iterator
			this->m_pCurSectionInfo = NULL;

			char line[1024];

			parsingInfo.lineNum = 0;
			parsingInfo.pLine = line;
			
			while(parsingInfo.lineNum++, fgets(line, sizeof(line), fp))
			{
				TrimRightOnlyNewLineCharacters(line);

				char* iLine = FindFirstNonWhiteCharacter(line);

				if(!*iLine || *line == '#')
				{
					this -> ProcessComment(&parsingInfo);
					continue;
				}
				
				if(*line == '@')
				{
					char directive[64];

					char* pEnd;
					ReadIdentifier(directive, sizeof(directive), line+1, &pEnd);

					if(!_stricmp(directive, "include"))
					{
						std::string filename;

						if (ReadString<char, std::string>(pEnd, filename, nullptr))
						{														
							this -> LoadFile(filename.c_str());
							SetCurrentDirectoryA(pLoadedFileEntry->directoryPath);
						}
						else
							printf("%hs(%d): can't read directory name.\n", parsingInfo.pFilename, parsingInfo.lineNum);
					}
				}				
				else if(this->m_pCurSectionInfo)
				{
					// Section is active
					if(!_strnicmp(line, "end", 3))
					{
						this->m_pCurSectionInfo = NULL;
						this -> EndSection();	// virtual function executed when section becomes inactive
					}
					else
					{
						// Call function
						tSectionFunc func = this->m_pCurSectionInfo -> func;
						(*this.*func)(&parsingInfo);
					}
				}				
				else
				{
					// No direction, section inactive
					char sectionName[64];

					char* pEnd;

					ReadAnyValue(sectionName, sizeof(sectionName), line, &pEnd);										
					
					this->m_pCurSectionInfo = this->FindSectionInfoWithSpecifiedName(sectionName);
					
					if(this->m_pCurSectionInfo)
						this -> BeginSection();	// virtual function executed when section becomes active
					else
						this -> ProcessComment(&parsingInfo);
				}				
			}

			result = true;
		}
	}
	else
	{
		printf("Unable to open sectional file '%hs'\n", filename);
		result = false;
	}

	if (this->m_RecurrencyLevel == 1)
		SetCurrentDirectoryA(PreviousDirectory);

	this -> m_RecurrencyLevel--;

	return result;
}

// Returns currently processed section name.
const char* CSectionFileReader::GetSectionName()
{
	return this->m_pCurSectionInfo ? this->m_pCurSectionInfo->sectionName : NULL;
}

// Prepares line for scanf - replaces commas ',' with space ' '
void CSectionFileReader::PrepareLineForScanf(char* line)
{
	while(char c = *line)
	{
		if(c == ',')
			*line = ' ';

		line++;
	}
}

// Prepares line for scanf - replaces commas ',' with space ' '
std::string CSectionFileReader::GetLinePreparedForScanf(const char* line)
{
	std::string str = line;

	for (std::string::size_type i=0; i<str.length(); ++i)
		if(str[i] == ',')
			str[i] = ' ';

	return str;
}