/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CIniReader.h"

#ifdef IS_PLATFORM_WIN
#include <Windows.h>

#include <fileIO.h>
#endif

#include <string>
#include <stdlib.h>

// Opens .ini file
bool CIniReader::Open(const char* filename)
{
#ifdef IS_PLATFORM_WIN
	GetFullPathNameA(filename, _countof(this->m_fullPath), this->m_fullPath, NULL);

	return FileExistsA(this->m_fullPath);
#elif defined(IS_PLATFORM_ANDROID)
	reader.LoadFile(filename);

	return reader.ParseError() == 0;
#else
	return false;
#endif
}

// Closes INI file
void CIniReader::Close()
{
#ifdef IS_PLATFORM_WIN
	this->m_fullPath[0] = NULL;
#elif defined(IS_PLATFORM_ANDROID)
	this->reader.ClearLoadedData();
#endif
}

// Reads the string
void CIniReader::GetString(
	const char* lpAppName,
	const char* lpKeyName,
	const char* lpDefault,
	char* lpReturnedString,
	uint32_t nSize
	)
{
	if (!lpDefault)
		lpDefault = "";

#ifdef IS_PLATFORM_WIN
	GetPrivateProfileStringA(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, this->m_fullPath);
#elif defined(IS_PLATFORM_ANDROID)
	const std::string value = this->reader.GetString(lpAppName, lpKeyName, lpDefault);
	strncpy(lpReturnedString, value.c_str(), nSize);
	lpReturnedString[nSize - 1] = NULL;	// NULL character
#else
	strncpy(lpReturnedString, lpDefault, nSize);
	lpReturnedString[nSize - 1] = NULL;	// NULL character
#endif
}

// Reads the integer value
int CIniReader::GetInt(
	const char* lpAppName,
	const char* lpKeyName,
	int nDefault
	)
{
	int value;
	this->GetIntEx(lpAppName, lpKeyName, &value, nDefault);
	return value;
}

// Reads the bool value
bool CIniReader::GetBool(
	const char* lpAppName,
	const char* lpKeyName,
	bool bDefault
	)
{
	return this->GetInt(lpAppName, lpKeyName, bDefault) != 0;
}

// Reads the double value
double CIniReader::GetDouble(
	const char* lpAppName,
	const char* lpKeyName,
	double nDefault
	)
{
	char cTmp[100];
	this->GetString(lpAppName, lpKeyName, NULL, cTmp, sizeof(cTmp));

	if (strlen(cTmp))
		return atof(cTmp);
	else
		return nDefault;
}

// Reads the float value
float CIniReader::GetFloat(
	const char* lpAppName,
	const char* lpKeyName,
	float nDefault
	)
{
	return (float)this->GetDouble(lpAppName, lpKeyName, nDefault);
}

// Reads the integer value
bool CIniReader::GetIntEx(
	const char* lpAppName,
	const char* lpKeyName,
	int* pResult,
	int nDefault
	)
{
	char cTmp[100];

	this->GetString(lpAppName, lpKeyName, NULL, cTmp, sizeof(cTmp));

	if (cTmp[0])
	{
		*pResult = atoi(cTmp);
		return true;
	}
	else
	{
		*pResult = nDefault;
		return false;
	}
}

// Reads the bool value
bool CIniReader::GetBoolEx(
	const char* lpAppName,
	const char* lpKeyName,
	bool* pResult,
	bool bDefault
	)
{
	int result;

	bool bSuccess = this->GetIntEx(lpAppName, lpKeyName, &result, bDefault);
	*pResult = result != 0;

	return bSuccess;
}

// Reads the float value
bool CIniReader::GetFloatEx(
	const char* lpAppName,
	const char* lpKeyName,
	float* pResult,
	float nDefault
	)
{
	double fResult;
	bool bResult = this->GetDoubleEx(lpAppName, lpKeyName, &fResult, nDefault);
	*pResult = fResult;
	return bResult;
}

// Reads the double value
bool CIniReader::GetDoubleEx(
	const char* lpAppName,
	const char* lpKeyName,
	double* pResult,
	double nDefault
	)
{
	char cTmp[100];
	this->GetString(lpAppName, lpKeyName, NULL, cTmp, sizeof(cTmp));

	if (strlen(cTmp))
	{
		*pResult = atof(cTmp);
		return true;
	}
	else
	{
		*pResult = nDefault;
		return false;
	}
}

// Retrieves the names of all sections in an initialization file.
void CIniReader::GetSectionNames(
	char* lpszReturnBuffer,
	unsigned int nSize
	)
{
#ifdef IS_PLATFORM_WIN
	GetPrivateProfileSectionNamesA(lpszReturnBuffer, nSize, this->m_fullPath);
#else
	*lpszReturnBuffer = 0;
#endif
}