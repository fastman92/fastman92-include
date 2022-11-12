/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include "CMemoryAccess.h"

class CMemoryAccessWithinCurrentProcess : public CMemoryAccess
{
public:
	// Constructor
	CMemoryAccessWithinCurrentProcess();

	// Reads memory
	virtual const void* Read(tMemoryAcesssPtr address, tMemoryAccessSize size);

	// Writes memory
	virtual bool Write(tMemoryAcesssPtr address, tMemoryAccessSize size, void* ptr);

	// Compares memory
	virtual int Compare(tMemoryAcesssPtr address, const void* ptr2, tMemoryAccessSize size);
};

extern CMemoryAccessWithinCurrentProcess g_memoryAccessWithinCurrentProcess;