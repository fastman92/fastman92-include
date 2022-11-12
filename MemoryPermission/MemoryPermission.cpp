/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/


#include "MemoryPermission.h"

#ifdef IS_PLATFORM_ANDROID
#include <sys/mman.h>
#include <unistd.h>
#endif

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

// Retuns native new protect flags
uint32_t GetNativeNewProtect(uint32_t flags)
{
	uint32_t result = 0;

#ifdef IS_PLATFORM_WIN
	if (flags & F92_MEM_PAGE_NOACCESS)
		result |= PAGE_NOACCESS;
	if (flags & F92_MEM_PAGE_READONLY)
		result |= PAGE_READONLY;
	else if (flags & F92_MEM_PAGE_READWRITE)
		result |= PAGE_READWRITE;
	else if (flags & F92_MEM_PAGE_WRITECOPY)
		result |= PAGE_WRITECOPY;
	else if (flags & F92_MEM_PAGE_EXECUTE)
		result |= PAGE_EXECUTE;
	else if (flags & F92_MEM_PAGE_EXECUTE_READ)
		result |= PAGE_EXECUTE_READ;
	else if (flags & F92_MEM_PAGE_EXECUTE_READWRITE)
		result |= PAGE_EXECUTE_READWRITE;
	else if (flags & F92_MEM_PAGE_EXECUTE_WRITECOPY)
		result |= PAGE_EXECUTE_WRITECOPY;
#endif

#if defined(IS_PLATFORM_ANDROID) || defined(IS_PLATFORM_LINUX)
	if (flags & F92_MEM_PAGE_NOACCESS)
		result |= PROT_NONE;
	else if (flags & F92_MEM_PAGE_READONLY)
		result |= PROT_READ;
	else if (flags & F92_MEM_PAGE_READWRITE)
		result |= PROT_READ | PROT_WRITE;
	else if (flags & F92_MEM_PAGE_WRITECOPY)
		result |= PROT_WRITE;
	else if (flags & F92_MEM_PAGE_EXECUTE)
		result |= PROT_EXEC;
	else if (flags & F92_MEM_PAGE_EXECUTE_READ)
		result |= PROT_EXEC | PROT_READ ;
	else if (flags & F92_MEM_PAGE_EXECUTE_READWRITE)
		result |= PROT_EXEC | PROT_READ | PROT_WRITE;
	else if (flags & F92_MEM_PAGE_EXECUTE_WRITECOPY)
		result |= PROT_READ | PROT_WRITE | PROT_EXEC;
#endif

	return result;
}

// Sets memory permission
bool SetMemoryPermission(tMemoryPermissionChangeRequest* pChangeRequest)
{	
#ifdef IS_PLATFORM_WIN
	DWORD oldProtect;
	bool result = VirtualProtect(
		(PVOID)pChangeRequest->lpAddress,
		pChangeRequest->dwSize,
		pChangeRequest->flNewProtect,
		&oldProtect) != false;

	if (result)
	{
		pChangeRequest->lpflOldProtect = oldProtect;
		pChangeRequest->bIsOldProtectSet = true;
	}
	else
	{
		pChangeRequest->lpflOldProtect = 0;
		pChangeRequest->bIsOldProtectSet = false;
	}

	return result;
#elif defined(IS_PLATFORM_ANDROID) | defined(IS_PLATFORM_LINUX)
	int pagesize = sysconf(_SC_PAGE_SIZE);

	char *start =
		(char *)(((uintptr_t)pChangeRequest->lpAddress) & ~(pagesize - 1));
	char *end =
		(char *)(((uintptr_t)pChangeRequest->lpAddress + pChangeRequest->dwSize + pagesize - 1) & ~(pagesize - 1));

	bool result = mprotect(start, end - start, pChangeRequest->flNewProtect) == 0;

	pChangeRequest->lpflOldProtect = 0;
	pChangeRequest->bIsOldProtectSet = false;

	return result;
#else
	pChangeRequest->lpflOldProtect = 0;
	pChangeRequest->bIsOldProtectSet = false;
	return false;
#endif
}