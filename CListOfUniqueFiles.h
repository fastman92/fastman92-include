#pragma once
#include <string>
#include <map>
#include <Windows.h>

struct tUniqueFileListEntry
{
	char filePath[MAX_PATH];
	char directoryPath[MAX_PATH];
	char* pFilename;

	// Default constructor
	tUniqueFileListEntry();

	// Copy constructor
	tUniqueFileListEntry(const tUniqueFileListEntry& other);

	// Assignment
	tUniqueFileListEntry& operator=(const tUniqueFileListEntry& right);
};

class CListOfUniqueFiles
{
private:
	int m_uniqueID;

public:
	// Map <unique ID, file entry>
	std::map<int, tUniqueFileListEntry> m_filePaths;

	// CListOfUniqueFiles constructor
	CListOfUniqueFiles();

	// Adds new file path
	int AddNewFile(const char* filename);

	// Returns pointer to file entry by ID
	tUniqueFileListEntry* GetFileEntryByID(int ID);

	// Clears m_filePaths 
	void Clear();
};