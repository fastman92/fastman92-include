/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "GTAIV_CRC32.h"
#include <stdint.h>

unsigned long int GTAIV_CRC32_fromString(const char* text)
{	
	unsigned long int retHash = 0;

	char c;

	const char* iText = text;

	if ( *text == '\"' )
		iText = text + 1;

	for ( c = *iText; *iText; c = *iText )
	{
		if ( *text == '\"' && c == 0x22 )
			break;

		++iText;

		if ( (uint8_t)(c - 'A') > '\x19' )
		{
			if ( c == '\\' )
				c = 47;
		}
		else
			c += 32;

		retHash = (1025 * (retHash + c) >> 6) ^ 1025 * (retHash + c);
	}

	return 32769 * (9 * retHash ^ (9 * retHash >> 11));
}