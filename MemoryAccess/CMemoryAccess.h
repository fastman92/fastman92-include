/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include <stdint.h>
#include "../Endianness/Endianness.h"

typedef uintptr_t tMemoryAcesssPtr;
typedef tMemoryAcesssPtr tMemoryAccessSize;

class CMemoryAccess
{
private:
	// Is big endian memory?
	eValueEncoding bIsBigEndian;

public:
	// Constructor
	CMemoryAccess();

	// Reads memory
	virtual const void* Read(tMemoryAcesssPtr address, tMemoryAccessSize size) = 0;
	
	// Writes memory
	virtual bool Write(tMemoryAcesssPtr address, tMemoryAccessSize size, void* ptr) = 0;

	// Compares memory
	virtual int Compare(tMemoryAcesssPtr address, const void* ptr2, tMemoryAccessSize size) = 0;

	// Sets big endian state
	void SetBigEndianState(eValueEncoding bIsBigEndian);

	// Returns big endian state
	eValueEncoding GetBigEndianState();
};