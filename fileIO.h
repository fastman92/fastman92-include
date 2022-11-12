/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include <stdio.h>
#include <stdint.h>

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

#ifdef IS_PLATFORM_ANDROID
#include <sys/stat.h>
#endif
#include <sys/stat.h>

// Loads line from file without commas
bool LoadLineWithoutCommas(char * str, int num, FILE * stream);

// Returns file size
int64_t GetFileSize(const char* path);

// Returns file size
int64_t GetFileSize(const wchar_t* path);

#ifdef IS_PLATFORM_WIN
// Browses a directory and executes a function for each file
// if called function returns true, files aren't scanned anymore
bool BrowseDirectory(const char* dirPath, bool(*func)(const char* filename, void* pUserData), void* pUserData = NULL);

// Opens directory if exists or creates and opens directory if it doesn't initially exists
bool OpenOrCreateDirectory(const char* dirname);

DWORD    GetFilePointer(HANDLE hFile);

LONGLONG GetFilePointerEx(HANDLE hFile);
#endif

bool FileExistsA(const char* szPath);
bool FileExistsW(const wchar_t szPath);

// Returns pointer to filename from path
char* GetFilenameFromPath(const char* path);

// Reads 4 byte aligned string
void FileRead4byteAlignedString(FILE* fp, char* str);

// Writes 4 byte aligned string
void FileWrite4byteAlignedString(FILE* fp, const char* str);

// Reads int32
uint32_t FileReadInt32(FILE* fp);

// Reads float
float FileReadFloat(FILE* fp);

// Writes float
void FileWriteFloat(FILE* fp, float value);

// Writes int32
void FileWriteInt32(FILE* fp, int32_t value);

// Writes Pascal string
void FileWritePascalString(FILE* fp, const char* str);

// Reads Pascal string
void FileReadPascalString(FILE* fp, char* outputStr, unsigned int bufferSize);

// Sets a current directory
bool SetCurrentWorkingDirectory_OS_independent(const char* directoryPath);

#ifdef IS_PLATFORM_WIN
// Create directory recursively
int mkdir_p(const char *path);
#endif

#ifdef IS_PLATFORM_ANDROID
// Create directory recursively
int mkdir_p(const char *path, mode_t mode);
#endif