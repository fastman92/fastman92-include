/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "BullyScholarschipEdition_Hash.h"
#include <stdio.h>
#include <ctype.h>

// Calculates BullyScholarschip Edition hash from upcase string
unsigned long BullyScholarschipEdition_hash_fromUpCaseString(const char* string)
{
	register unsigned __int32 hash = 0;
	
	while (*string)
		hash = toupper(*string++) + 131 * hash;

	return hash & 0x7FFFFFFF;
}

// Calculates BullyScholarschip Edition string from hash
// Works for strings that have no more than 4 characters in length
const char* BullyScholarschipEdition_stringFromHash(unsigned __int32 hash, char* outString)
{
	int patternLength = 131;

	unsigned __int32 Xoffset = hash;

	while (Xoffset > 0)
	{
		if (Xoffset % patternLength == 0)
			Xoffset = (Xoffset / patternLength) - 1;
		else
			Xoffset /= patternLength;

		outString++;
	}

	*outString-- = NULL;

	Xoffset = hash;	

	while (Xoffset > 0)
	{
		int offsetMod = Xoffset % patternLength;

		*(outString) = (offsetMod == 0) ? patternLength - 1 : offsetMod;

		if (offsetMod == 0)
			Xoffset = (Xoffset / patternLength) - 1;
		else
			Xoffset /= patternLength;

		outString--;
	}

	return 0;
}