/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CListOfUniqueFiles.h"

// Default constructor
tUniqueFileListEntry::tUniqueFileListEntry()
{
	this -> filePath[0] = NULL;
	this -> pFilename = NULL;
}

// Copy constructor
tUniqueFileListEntry::tUniqueFileListEntry(const tUniqueFileListEntry& other)
{
	*this = other;
}

// Assignment
tUniqueFileListEntry& tUniqueFileListEntry::operator=(const tUniqueFileListEntry& right)
{
	memcpy(this -> filePath, right.filePath, sizeof(this -> filePath));
	this -> pFilename = right.pFilename != NULL ? &this -> filePath[right.pFilename - right.filePath] : NULL;
	memcpy(this -> directoryPath, right.directoryPath, sizeof(this -> directoryPath));
		
	return *this;
}

// CListOfUniqueFiles constructor
CListOfUniqueFiles::CListOfUniqueFiles()
{
	this -> m_uniqueID = 0;
}

// Adds new file path
int CListOfUniqueFiles::AddNewFile(const char* filename)
{
	tUniqueFileListEntry entry;
	GetFullPathNameA(filename, sizeof(entry.filePath), entry.filePath, &entry.pFilename);

	int directoryLen = entry.pFilename - entry.filePath;
	memcpy(entry.directoryPath, entry.filePath, directoryLen);
	entry.directoryPath[directoryLen] = NULL;

	int ID = this -> m_uniqueID++;
		
	this -> m_filePaths[ID] = entry;
		
	return ID;
}

// Returns pointer to file entry by ID
tUniqueFileListEntry* CListOfUniqueFiles::GetFileEntryByID(int ID)
{
	auto it = this -> m_filePaths.find(ID);

	return it != this -> m_filePaths.end() ? &it -> second : NULL;
}

// Clears m_filePaths 
void CListOfUniqueFiles::Clear()
{
	this -> m_filePaths.clear();
}