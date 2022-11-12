/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#define _CRT_NONSTDC_NO_DEPRECATE // for chdir

#include "fileIO.h"
#include <string.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>

#ifdef IS_PLATFORM_WIN
#include <direct.h>

#include <Shlobj.h>
#include <Windows.h>
#endif

#ifdef IS_PLATFORM_ANDROID
#include <sys/stat.h>
#include <unistd.h>
#endif

// Loads line from file without commas
bool LoadLineWithoutCommas(char * str, int num, FILE * stream)
{
	if (fgets(str, num, stream))
	{
		int l = 0;

		while (str[l] != 0)
		{
			if (str[l] == ',')
				str[l] = ' ';

			l++;
		}

		if (l > 0)
		{
			int i = l - 1;

			do
			{
				if (str[i] == '\r' || str[i] == '\n')
					str[i] = 0;
				else
					break;
			} while (i >= 0);
		}

		return true;
	}
	else
		return false;
}

// Returns file size
int64_t GetFileSize(const char* path)
{
	#ifdef IS_PLATFORM_WIN
	HANDLE hFile = CreateFileA(path, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return -1; // error condition, could call GetLastError to find out more

	LARGE_INTEGER size;
	if (!GetFileSizeEx(hFile, &size))
	{
		CloseHandle(hFile);
		return -1; // error condition, could call GetLastError to find out more
	}

	CloseHandle(hFile);
	return size.QuadPart;
	#elif defined(IS_PLATFORM_ANDROID)
	struct stat filestatus;

	if (stat(path, &filestatus) == 0)
		return filestatus.st_size;
	else
		return -1;
	#else
	return -1;
	#endif
}

// Returns file size
int64_t GetFileSize(const wchar_t* path)
{
	#ifdef IS_PLATFORM_WIN
	HANDLE hFile = CreateFileW(path, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return -1; // error condition, could call GetLastError to find out more

	LARGE_INTEGER size;
	if (!GetFileSizeEx(hFile, &size))
	{
		CloseHandle(hFile);
		return -1; // error condition, could call GetLastError to find out more
	}

	CloseHandle(hFile);
	return size.QuadPart;
	#else
	return -1;
	#endif
}

#ifdef IS_PLATFORM_WIN
// Browses a directory and executes a function for each file
// if called function returns true, files aren't scanned anymore
bool BrowseDirectory(const char* dirPath, bool(*func)(const char* filename, void* pUserData), void* pUserData)
{
	wchar_t PreviousDirectory[MAX_PATH];
	GetCurrentDirectoryW(_countof(PreviousDirectory), PreviousDirectory);

	if (!SetCurrentDirectoryA(dirPath))
		return false;
	
	_WIN32_FIND_DATAA fd;

	HANDLE File = FindFirstFileA("*", &fd);

	if (File != INVALID_HANDLE_VALUE)
	{
		const void* fileContent = NULL;

		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				// avoid standard library functions to reduce dll size

				if (func(fd.cFileName, pUserData))
					break;
			}

		} while (FindNextFileA(File, &fd));
		FindClose(File);
	}

	SetCurrentDirectoryW(PreviousDirectory);

	return true;
}

// Opens directory if exists or creates and opens directory if it doesn't initially exists
bool OpenOrCreateDirectory(const char* dirname)
{
	if (SetCurrentDirectoryA(dirname) || (!SHCreateDirectoryExA(NULL, dirname, NULL) && SetCurrentDirectoryA(dirname)))
		return true;
	else
	{
		char AbsoluteDirname[MAX_PATH];
		GetFullPathNameA(dirname, _countof(AbsoluteDirname), AbsoluteDirname, NULL);

		if (!SHCreateDirectoryExA(NULL, AbsoluteDirname, NULL) && SetCurrentDirectoryA(dirname))
			return true;
		else
			return false;
	}
}

DWORD GetFilePointer(HANDLE hFile) {
	return SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
}

LONGLONG GetFilePointerEx(HANDLE hFile) {
	LARGE_INTEGER liOfs = { 0 };
	LARGE_INTEGER liNew = { 0 };
	SetFilePointerEx(hFile, liOfs, &liNew, FILE_CURRENT);
	return liNew.QuadPart;
}
#endif


bool FileExistsA(const char* szPath)
{
	#ifdef IS_PLATFORM_WIN
	DWORD dwAttrib = GetFileAttributesA(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	#else
	return false;
	#endif
}

bool FileExistsW(const wchar_t* szPath)
{
	#ifdef IS_PLATFORM_WIN
	DWORD dwAttrib = GetFileAttributesW(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	#else
	return false;
	#endif
}

// Returns pointer to filename from path
char* GetFilenameFromPath(const char* path)
{
	int len = strlen(path);

	if (len)
	{
		const char* onlyFilename = path + len;

		while (onlyFilename >= path)
		{
			if (*onlyFilename == '\\' || *onlyFilename == '/')
				break;

			onlyFilename--;
		}

		return (char*)(onlyFilename + 1);
	}
	else
		return (char*)path;
}

// Reads 4 byte aligned string
void FileRead4byteAlignedString(FILE* fp, char* str)
{
	char data[4];

	while (fread(&data, 4, 1, fp))
	{
		if (data[3])
			*(int32_t*)str = *(int32_t*)data;
		else
		{
			for (int i = 0; i < 4; i++)
			{
				str[i] = data[i];

				if (!str[i])
					break;
			}

			break;
		}

		str += 4;
	}
}

// Writes 4 byte aligned string
void FileWrite4byteAlignedString(FILE* fp, const char* str)
{
	while (true)
	{
		char data[4] = { 0 };				

		for (int i = 0; i < 4; i++)
		{
			if (str[i])
				data[i] = str[i];
			else
				break;
		}

		fwrite(&data, sizeof(data), 1, fp);

		if (!data[3])
			break;

		str += 4;
	}
}

// Reads int32
uint32_t FileReadInt32(FILE* fp)
{
	int32_t value;
	fread(&value, sizeof(value), 1, fp);
	return value;
}

// Reads float
float FileReadFloat(FILE* fp)
{
	float value;
	fread(&value, sizeof(value), 1, fp);
	return value;
}

// Writes float
void FileWriteFloat(FILE* fp, float value)
{
	fwrite(&value, sizeof(value), 1, fp);
}

// Writes int32
void FileWriteInt32(FILE* fp, int32_t value)
{
	fwrite(&value, sizeof(value), 1, fp);
}

// Writes Pascal string
void FileWritePascalString(FILE* fp, const char* str)
{
	unsigned int len = strlen(str);

	uint8_t lenToWrite;

	if (len > 255)
		lenToWrite = 255;
	else
		lenToWrite = len;

	fwrite(&len, 1, 1, fp);
	fwrite(str, lenToWrite, 1, fp);
}

// Reads Pascal string
void FileReadPascalString(FILE* fp, char* outputStr, unsigned int bufferSize)
{
	uint8_t len;
	fread(&len, sizeof(len), 1, fp);	

	unsigned int neededSize = len + 1;
	
	unsigned int sizeToRead = len;
	unsigned int sizeToSkip = 0;

	if (neededSize > bufferSize)
	{
		sizeToSkip = neededSize - bufferSize;
		sizeToRead -= sizeToSkip;
	}

	if(sizeToRead)
		fread(outputStr, sizeToRead, 1, fp);

	outputStr[sizeToRead] = 0;

	if (sizeToSkip)
		fseek(fp, sizeToSkip, SEEK_CUR);
}

// Sets a current directory
bool SetCurrentWorkingDirectory_OS_independent(const char* directoryPath)
{
	return chdir(directoryPath) == 0;
}

#if IS_PLATFORM_WIN
// Create directory recursively
int mkdir_p(const char *path)
{
	/* Adapted from http://stackoverflow.com/a/2336245/119527 */
	const size_t len = strlen(path);
	char _path[4096];
	char *p;

	errno = 0;

	/* Copy string so its mutable */
	if (len > sizeof(_path) - 1) {
		errno = ENAMETOOLONG;
		return -1;
	}
	strcpy(_path, path);

	/* Iterate the string */
	for (p = _path + 1; *p; p++) {
		if (*p == '\\') {
			/* Temporarily truncate */
			*p = '\0';

			if (_mkdir(_path) != 0) {
				if (errno != EEXIST)
					return -1;
			}

			*p = '/';
		}
	}

	if (_mkdir(_path) != 0) {
		if (errno != EEXIST)
			return -1;
	}

	return 0;
}
#endif

#if defined(IS_PLATFORM_ANDROID)
// Create directory recursively
int mkdir_p(const char *path, mode_t mode)
{
	/* Adapted from http://stackoverflow.com/a/2336245/119527 */
	const size_t len = strlen(path);
	char _path[PATH_MAX];
	char *p;

	errno = 0;

	/* Copy string so its mutable */
	if (len > sizeof(_path) - 1) {
		errno = ENAMETOOLONG;
		return -1;
	}
	strcpy(_path, path);

	/* Iterate the string */
	for (p = _path + 1; *p; p++) {
		if (*p == '/') {
			/* Temporarily truncate */
			*p = '\0';
			
			if (mkdir(_path, mode) != 0) {
				if (errno != EEXIST)
					return -1;
			}

			*p = '/';
		}
	}

	if (mkdir(_path, mode) != 0) {
		if (errno != EEXIST)
			return -1;
	}

	return 0;
}
#endif