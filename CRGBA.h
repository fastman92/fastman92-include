/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "Assertions.h"

class CRGBA
{
public:
	union{
		struct{
			unsigned char red, green, blue, alpha;
		};

		// unsigned int colorInt;
	};

	// Empty constructor
	CRGBA() {}

	// Constructor with parameters
	CRGBA(
		unsigned char red,
		unsigned char green,
		unsigned char blue,
		unsigned char alpha
	)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}
};

class CBGRA
{
public:
	union {
		struct {
			unsigned char blue, green, red, alpha;
		};

		unsigned int colorInt;
	};
};

VALIDATE_SIZE(CRGBA, 4);