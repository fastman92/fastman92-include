/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdlib.h>
#include <string.h>
#include "CalculateHashUsingGameAlgorithm.h"

// Create string with hash
static void CreateStringWithHashLowerCase(char* output, unsigned __int32 hash)
{
	sprintf(output, "hash_%08x", hash);
}

// Extracts hash from string
static bool Extract32bitHashFromString(const char* str, unsigned __int32* pHash)
{
	if (!_strnicmp(str, "hash_", 5))
	{
		*pHash = strtoul(str + 5, NULL, 16);
		return true;
	}

	return false;
}

// Extracts or calculates a hash using game algorithm
static unsigned __int32 ExtractsOrCalculateHashUsingGameAlgorithm(
	Game::eGameNameSimplified game,
	const char* str
	)
{
	unsigned __int32 hash;

	if (Extract32bitHashFromString(str, &hash))
		return hash;
	else
		return CalculateHashUsingGameAlgorithm(game, str);
}