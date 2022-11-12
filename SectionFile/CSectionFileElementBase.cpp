/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CSectionFileElementBase.h"

// Adds entries from other section of data
void CSectionFileElement_SectionOfData::AddEntriesFromOtherSectionOfData(const CSectionFileElement_SectionOfData& other)
{
	for (auto it = other.Data.begin(); it != other.Data.end(); ++it)
	{
		CSectionFileElementBase* ptr = it->clone();
		this->Data.push_back(ptr);
	}
}

// Removes all entries
void CSectionFileElement_SectionOfData::RemoveAllEntries()
{
	while (true)
	{
		auto it = this->Data.begin();

		if (it == this->Data.end())
			break;

		delete this->Data.detach(it);
	}
}

// Returns count of data elements which match the section type
unsigned int CSectionFileElement_SectionOfData::GetCountOfDataElementsWhichMatchTheSectionType()
{
	int curSectionType = this->GetSectionType();
	unsigned int count = 0;

	for (auto it = this->Data.begin(); it != this->Data.end(); ++it)
		if (it->IsData() && it->ToElementBaseWithSectionInfo()->GetSectionType() == curSectionType)
			count++;

	return count;
}

// Sets reader point
void CSectionFileElementBase::SetReaderPointer(CSectionFileReader* pReader)
{
	this->pReader = pReader;
}

// Returns reader pointer
CSectionFileReader* CSectionFileElementBase::GetReaderPointer()
{
	return this->pReader;
}

// Imports entry.
unsigned __int32 CSectionFileComment::ImportEntry(const char* line)
{
	this -> m_ImportedLine = line;

	return -1;	// ID
}

// Exports entry. Returns length of output string.
int CSectionFileComment::ExportEntry(char* line)
{
	return sprintf(line, "%s", this -> m_ImportedLine.c_str());
}

// Copy constructor
CSectionFileMap::CSectionFileMap(const CSectionFileMap& second) : Owner(Data)
{
	this->AddEntriesFromOtherMap(second);
}

// Assignment
CSectionFileMap& CSectionFileMap::operator=(const CSectionFileMap& other)
{
	if (&other == this)
		return *this;

	this->ClearLoadedData();
	this->AddEntriesFromOtherMap(other);

	return *this;
}

// Adds entries from other map
void CSectionFileMap::AddEntriesFromOtherMap(const CSectionFileMap& other)
{
	for (auto it = other.Data.begin(); it != other.Data.end(); ++it)
	{
		CSectionFileElementBase* ptr = it->clone();
		this->Data.push_back(ptr);
	}
}

// Adds section
CSectionFileElement_SectionOfData* CSectionFileMap::AddSection(int sectionType)
{
	CSectionFileElement_SectionOfData* ptr = new CSectionFileElement_SectionOfData(sectionType);

	this->Data.push_back(ptr);
	return ptr;
}

// Clears loaded data
void CSectionFileMap::ClearLoadedData()
{
	while (true)
	{
		auto it = this->Data.begin();

		if (it == this->Data.end())
			break;

		delete this->Data.detach(it);
	}
}