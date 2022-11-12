/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

#ifdef IS_PLATFORM_ANDROID
#include "inih/cpp/INIReader.h"
#endif

class CIniReader
{
#ifdef IS_PLATFORM_WIN
	char m_fullPath[260];
#elif defined(IS_PLATFORM_ANDROID)
	INIReader reader;
#endif

public:
	// Opens .ini file
	bool Open(const char* filename);

	// Closes INI file
	void Close();

	// Reads the string
	void GetString(
		const char* lpAppName,
		const char* lpKeyName,
		const char* lpDefault,
		char* lpReturnedString,
		uint32_t nSize
		);

	// Reads the integer value
	int GetInt(
		const char* lpAppName,
		const char* lpKeyName,
		int nDefault = 0
		);

	// Reads the bool value
	bool GetBool(
		const char* lpAppName,
		const char* lpKeyName,
		bool bDefault = false
		);

	// Reads the double value
	double GetDouble(
		const char* lpAppName,
		const char* lpKeyName,
		double nDefault = 0.0
		);

	// Reads the float value
	float GetFloat(
		const char* lpAppName,
		const char* lpKeyName,
		float nDefault = 0.0
		);

	// Reads the integer value
	bool GetIntEx(
		const char* lpAppName,
		const char* lpKeyName,
		int* pResult,
		int nDefault = 0
		);

	// Reads the bool value
	bool GetBoolEx(
		const char* lpAppName,
		const char* lpKeyName,
		bool* pResult,
		bool bDefault = false
		);

	// Reads the float value
	bool GetFloatEx(
		const char* lpAppName,
		const char* lpKeyName,
		float* pResult,
		float nDefault = 0.0
		);

	// Reads the double value
	bool GetDoubleEx(
		const char* lpAppName,
		const char* lpKeyName,
		double* pResult,
		double nDefault = 0.0
		);

	// Retrieves the names of all sections in an initialization file.
	void GetSectionNames(
		char* lpszReturnBuffer,
		unsigned int nSize
		);
};
// #endif