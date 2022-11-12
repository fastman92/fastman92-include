/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <string>
#include <list>
#include <map>

#include "CListOfUniqueFiles.h"

struct tLineParsingInfo
{
	const char* pFilename;
	char* pLine;
	// const char* pCurDirectory;
	int lineNum;
};

class CSectionFileReader;
typedef void (CSectionFileReader::* tSectionFunc)(tLineParsingInfo* pParsingInfo);

struct tSectionInfo
{
	char sectionName[16];
	tSectionFunc func;
	int typeID;
};

// Abstract class
class CSectionFileReader
{
protected:
	unsigned int m_RecurrencyLevel;

	static const unsigned int MAX_NUMBER_OF_RECURSION_LEVELS = 32;	
	
	typedef std::list<tSectionInfo> tSectionMap;

	tSectionMap m_SectionMap;

	// Current section iterator
	const tSectionInfo* m_pCurSectionInfo;

	// Paths to files that were read
	CListOfUniqueFiles m_listOfLoadedFiles;

	// Map <unique ID, relative path>
	std::map<int, std::string> m_listOfLoadedFileRelativePaths;

	// Path to loaded file
	char* m_pLoadedParentFilePath;

public:
	// Constructor
	CSectionFileReader();

	// Registers section
	void RegisterSection(const char* name, int typeID, tSectionFunc func);

	// Clears all registered sections.
	void ClearSections();

	// Finds a section info with specified name
	const tSectionInfo* FindSectionInfoWithSpecifiedName(const char* name);

	// Finds a section info with specified type ID
	const tSectionInfo* FindSectionInfoWithSpecifiedTypeID(int typeID);

	// Loads file
	virtual bool LoadFile(const char* filename);

	// Returns currently processed section name.
	const char* GetSectionName();

	// Prepares line for scanf - replaces commas ',' with space ' '
	static void PrepareLineForScanf(char* line);

	// Prepares line for scanf - replaces commas ',' with space ' '
	static std::string GetLinePreparedForScanf(const char* line);

	/// Virtual functions ///

	// Function executed when section is started.
	virtual void BeginSection(){};

	// Function executed when section is ended up.
	virtual void EndSection(){};

	// Processes comment
	virtual void ProcessComment(tLineParsingInfo* pParsingInfo){};
};