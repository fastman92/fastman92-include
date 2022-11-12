/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CMemoryAccess.h"

// Constructor
CMemoryAccess::CMemoryAccess()
{
	this->SetBigEndianState(
		IsCurrentMachineBigEndian()
		? VALUE_ENCODING_BIG_ENDIAN : VALUE_ENCODING_LITTLE_ENDIAN
	);
}

// Sets big endian state
void CMemoryAccess::SetBigEndianState(eValueEncoding bIsBigEndian)
{
	this->bIsBigEndian = bIsBigEndian;
}

// Returns big endian state
eValueEncoding CMemoryAccess::GetBigEndianState()
{
	return this->bIsBigEndian;
}