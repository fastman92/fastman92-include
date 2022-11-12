/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

#define F92_MEM_PAGE_NOACCESS          0x01     
#define F92_MEM_PAGE_READONLY          0x02     
#define F92_MEM_PAGE_READWRITE         0x04     
#define F92_MEM_PAGE_WRITECOPY         0x08     
#define F92_MEM_PAGE_EXECUTE           0x10     
#define F92_MEM_PAGE_EXECUTE_READ      0x20     
#define F92_MEM_PAGE_EXECUTE_READWRITE 0x40     
#define F92_MEM_PAGE_EXECUTE_WRITECOPY 0x80 

struct tMemoryPermissionChangeRequest
{
	// input
	void* lpAddress;
	size_t dwSize;

	uint32_t flNewProtect;	// system specific value

	// output
	bool bIsOldProtectSet;
	uint32_t lpflOldProtect;	// system specific value
};

// Retuns native new protect flags
uint32_t GetNativeNewProtect(uint32_t flags);

// Sets memory permission
bool SetMemoryPermission(tMemoryPermissionChangeRequest* pChangeRequest);