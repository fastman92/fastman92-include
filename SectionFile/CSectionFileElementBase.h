/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <string>
#include "ptr_vector.h"

enum eSectionFileElementType
{
	SECTION_FILE_ELEMENT_TYPE_UNDEFINED,
	SECTION_FILE_ELEMENT_TYPE_SECTION_OF_DATA,
	SECTION_FILE_ELEMENT_TYPE_COMMENT,
	SECTION_FILE_ELEMENT_TYPE_DATA
};

// Forward declarations
class CSectionFileComment;
class CSectionFileElement_SectionOfData;
class CSectionFileReader;
class CSectionFileElementBase_WithSectionInfo;

// CSectionFileElementBase
class CSectionFileElementBase
{
	eSectionFileElementType FileElementType;
	CSectionFileReader* pReader;

public:
	// Constructor
	CSectionFileElementBase(eSectionFileElementType type) { this->FileElementType = type; this->pReader = NULL; }

	// Virtual destructor
	virtual ~CSectionFileElementBase(){}

	// Returns file element type
	eSectionFileElementType	GetFileElementType() const { return this->FileElementType; };

	// Clone
	virtual CSectionFileElementBase* clone() const = 0;

	// Sets reader point
	virtual void SetReaderPointer(CSectionFileReader* pReader);

	// Returns reader pointer
	CSectionFileReader* GetReaderPointer();

	// Types
	bool IsData() const { return this->FileElementType == SECTION_FILE_ELEMENT_TYPE_DATA; }
	bool IsComment() const { return this->FileElementType == SECTION_FILE_ELEMENT_TYPE_COMMENT; }
	bool IsSectionOfData() const { return this->FileElementType == SECTION_FILE_ELEMENT_TYPE_SECTION_OF_DATA; }

	virtual const CSectionFileElementBase_WithSectionInfo* ToElementBaseWithSectionInfo()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
	virtual CSectionFileElementBase_WithSectionInfo* ToElementBaseWithSectionInfo() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

	virtual const CSectionFileComment* ToComment()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
	virtual CSectionFileComment* ToComment()    { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
	
	virtual const CSectionFileElement_SectionOfData* ToSectionOfData()    const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
	virtual CSectionFileElement_SectionOfData* ToSectionOfData()    { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
	
};


// ELEMENT BASE WITH SECTION INFO
class CSectionFileElementBase_WithSectionInfo : public CSectionFileElementBase
{
	int SectionTypeID;

public:
	// Constructor
	CSectionFileElementBase_WithSectionInfo(eSectionFileElementType type, int sectionType) : CSectionFileElementBase(type)
	{
		this->SectionTypeID = sectionType;
	}

	// Returns section type
	int GetSectionType() const { return this->SectionTypeID; };

	// Clone
	virtual CSectionFileElementBase_WithSectionInfo* clone() const { return new CSectionFileElementBase_WithSectionInfo(*this); };

	// Types
	virtual const CSectionFileElementBase_WithSectionInfo* ToElementBaseWithSectionInfo()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
	virtual CSectionFileElementBase_WithSectionInfo* ToElementBaseWithSectionInfo() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
};

// COMMENT
class CSectionFileComment : public CSectionFileElementBase
{
public:
	std::string m_ImportedLine;

	// Constructor
	CSectionFileComment() : CSectionFileElementBase(SECTION_FILE_ELEMENT_TYPE_COMMENT){}

	// Imports entry.
	virtual unsigned __int32 ImportEntry(const char* line);

	// Exports entry. Returns length of output string.
	virtual int ExportEntry(char* line);

	// Clone
	virtual CSectionFileComment* clone() const { return new CSectionFileComment(*this); };

	// Types
	virtual const CSectionFileComment* ToComment()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
	virtual CSectionFileComment* ToComment()    { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
};

// SECTION OF DATA
class CSectionFileElement_SectionOfData : public CSectionFileElementBase_WithSectionInfo
{
public:
	typedef stdx::ptr_vector<CSectionFileElementBase> tVector;
	typedef stdx::ptr_vector_owner<CSectionFileElementBase> tVectorOwner;

	tVector Data;
	tVectorOwner Owner;

	// Constructor
	CSectionFileElement_SectionOfData(int sectionType) :
		CSectionFileElementBase_WithSectionInfo(SECTION_FILE_ELEMENT_TYPE_SECTION_OF_DATA, sectionType),
		Owner(Data)
	{}

	// Copy constructor
	CSectionFileElement_SectionOfData(const CSectionFileElement_SectionOfData& second) :
		CSectionFileElementBase_WithSectionInfo(SECTION_FILE_ELEMENT_TYPE_SECTION_OF_DATA, this->GetSectionType()),
		Owner(Data)
	{
		for (auto it = second.Data.begin(); it != second.Data.end(); ++it)
		{			
			CSectionFileElementBase* ptr = it->clone();
			this->Data.push_back(ptr);
		}
	}

	// Adds entries from other section of data
	void AddEntriesFromOtherSectionOfData(const CSectionFileElement_SectionOfData& other);

	// Removes all entries
	void RemoveAllEntries();

	// Returns count of data elements which match the section type
	unsigned int GetCountOfDataElementsWhichMatchTheSectionType();

	// Clone
	virtual CSectionFileElement_SectionOfData* clone() const { return new CSectionFileElement_SectionOfData(*this); };

	virtual const CSectionFileElement_SectionOfData* ToSectionOfData()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
	virtual CSectionFileElement_SectionOfData* ToSectionOfData()    { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
};

// tEntry should derive from CSectionFileElementBase
// array of CSectionFileElementBase
struct CSectionFileMap
{
public:
	typedef stdx::ptr_vector<CSectionFileElementBase> tVector;
	typedef stdx::ptr_vector_owner<CSectionFileElementBase> tVectorOwner;
	
	tVector Data;

private:
	tVectorOwner Owner;
public:

	// Constructor
	CSectionFileMap() : Owner(Data){};


	// Copy constructor
	CSectionFileMap(const CSectionFileMap& second);

	// Assignment
	CSectionFileMap& operator=(const CSectionFileMap& other);


	// Adds entries from other map
	void AddEntriesFromOtherMap(const CSectionFileMap& other);

	// Adds section
	CSectionFileElement_SectionOfData* AddSection(int sectionType);

	// Clears loaded data
	void ClearLoadedData();
};