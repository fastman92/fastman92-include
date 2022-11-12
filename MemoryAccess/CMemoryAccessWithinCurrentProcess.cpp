/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CMemoryAccessWithinCurrentProcess.h"
#include "../Endianness/Endianness.h"
#include <string.h>

// Constructor
CMemoryAccessWithinCurrentProcess::CMemoryAccessWithinCurrentProcess()
{
	this->SetBigEndianState(GetCurrentMachineValueEncoding());
}

// Reads memory
const void* CMemoryAccessWithinCurrentProcess::Read(tMemoryAcesssPtr address, tMemoryAccessSize size)
{
	return (const void*)address;
}

// Writes memory
bool CMemoryAccessWithinCurrentProcess::Write(tMemoryAcesssPtr address, tMemoryAccessSize size, void* ptr)
{
	memcpy((void*)address, ptr, size);
	return true;
}

// Compares memory
int CMemoryAccessWithinCurrentProcess::Compare(tMemoryAcesssPtr address, const void* ptr2, tMemoryAccessSize size)
{
	return memcmp((const void*)address, ptr2, size);
}

CMemoryAccessWithinCurrentProcess g_memoryAccessWithinCurrentProcess;