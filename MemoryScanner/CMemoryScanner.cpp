/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CMemoryScanner.h"
#include <string>
//#include "E:\\Most important\\Projects\\fastman92 limit adjuster\\fastman92 limit adjuster\\FormattedOutput.h"

template<typename T> bool MemoryScanExtraConditionFuncGenericType(tMemoryScanControl& control, tMemoryScanFunctionCallback* func, tLowHighValues<T>* pLowHigh)
{
	const void* pValue = control.pMemoryAccessor->Read((tMemoryAcesssPtr)control.ptr, sizeof(T));
	T value = ((tVariedEncoding<T>*)(pValue))->GetValue(control.pMemoryAccessor->GetBigEndianState());

	if (value >= pLowHigh->low && value <= pLowHigh->high)
		return func->funcPtr(control, func->pCustomData);
	else
		return false;
}

// function to be used with the structure tMemoryScanExtraConditionData
bool MemoryScanExtraConditionFunc(tMemoryScanControl& control, void* pCustomData)
{
	tMemoryScanExtraConditionData* pData = (tMemoryScanExtraConditionData*)pCustomData;

	if (pData->findCondition == MEMORY_FIND_CONDITION_RELATIVE_4_BYTE_ADDRESS || pData->findCondition == MEMORY_FIND_CONDITION_RELATIVE_4_BYTE_ADDRESS_IN_INSTRUCTION)
	{		
		uint32_t value = ((tVariedEncoding<uint32_t>*)control.pMemoryAccessor->Read((tMemoryAcesssPtr)control.ptr, sizeof(value)))->GetValue(control.pMemoryAccessor->GetBigEndianState());

		tMemoryAcesssPtr ptr = value + (tMemoryAcesssPtr)control.ptr + 4;

		auto& address = pData->dataToFind.relative4byteAddress;

		tMemoryAcesssPtr addressLow = address.low;
		tMemoryAcesssPtr addressHigh = address.high;

		if (pData->findCondition == MEMORY_FIND_CONDITION_RELATIVE_4_BYTE_ADDRESS_IN_INSTRUCTION)
		{
			if (addressLow >= 4)
				addressLow -= 4;
		}

		if (ptr >= addressLow && ptr <= addressHigh)
			return pData->func.funcPtr(control, pData->func.pCustomData);
	}
	else if (pData->findCondition == MEMORY_FIND_CONDITION_SIGNED_INT8)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.signedInt8);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_UNSIGNED_INT8)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.unsignedInt8);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_SIGNED_INT16)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.signedInt16);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_UNSIGNED_INT16)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.unsignedInt16);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_SIGNED_INT32)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.signedInt32);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_UNSIGNED_INT32)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.unsignedInt32);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_SIGNED_INT64)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.signedInt64);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_UNSIGNED_INT64)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.unsignedInt64);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_FLOAT)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.floatValue);
	else if (pData->findCondition == MEMORY_FIND_CONDITION_DOUBLE)
		MemoryScanExtraConditionFuncGenericType(control, &pData->func, &pData->dataToFind.doubleValue);

	return false;
}

// Constructor
CMemoryScanner::CMemoryScanner()
{
	this->pMemoryAccessor = NULL;
}

// Clears a list of memory regions
void CMemoryScanner::ClearListOfMemoryRegions()
{
	this->m_memoryRegions.clear();
}

// Sets pointer to memory accessor
void CMemoryScanner::SetMemoryAccessor(CMemoryAccess* pMemoryAccessor)
{
	this->pMemoryAccessor = pMemoryAccessor;
}

// Add memory region to search list
void CMemoryScanner::AddMemoryRegionToSearchList(tMemoryAcesssPtr startAddress, tMemoryAccessSize size)
{
	tMemoryRegion region;
	region.start = startAddress;
	region.end = startAddress + size;
	this->m_memoryRegions.push_back(region);
}

#ifdef IS_PLATFORM_WIN
// Adds module sections to search list
void CMemoryScanner::AddModuleSectionsToSearchList(HMODULE hModule)
{	
	if (!hModule)
		hModule = GetModuleHandleA(NULL);

	if (!hModule)
		return;

	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((uintptr_t)(dosHeader)+(dosHeader->e_lfanew));

	//Identify for valid PE file  
	if (ntHeader->Signature == IMAGE_NT_SIGNATURE)
	{
		PIMAGE_OPTIONAL_HEADER opHeader = &ntHeader->OptionalHeader;
		PIMAGE_SECTION_HEADER pSecHeader = IMAGE_FIRST_SECTION(ntHeader);

		for (WORD i = 0; i < ntHeader->FileHeader.NumberOfSections; i++)
		{
			const char* SectionName = (const char*)pSecHeader->Name;

			uintptr_t SectionDataAddress = (uintptr_t)hModule + pSecHeader->VirtualAddress;
			DWORD SectionDataSize = pSecHeader->Misc.VirtualSize;

			this->AddMemoryRegionToSearchList(SectionDataAddress, SectionDataSize);

			/*
			result = CTheDllTricks::SearchForCallDllMain(SectionDataAddress, SectionDataSize);

			if (result)
				return result;
				*/

			/*
			printf_MessageBox(
			"Section name: %s\n"
			"Section data size: 0x%X\n"
			"Section data address: 0x%X to 0x%X\n",

			SectionName,
			SectionDataSize,
			(DWORD)SectionDataAddress,
			(DWORD)SectionDataAddress + SectionDataSize
			);
			*/
			
			/*
			
			printf_MessageBox(
			"Section Header name : %s\n"
			"ActualSize of code or data : 0x%X\n"
			"Size of raw data (rounded to FA) : 0x%X\n"

			,

			pSecHeader->Name,
			pSecHeader->Misc.VirtualSize,
			pSecHeader->SizeOfRawData
			);
			*/
			

			pSecHeader++;
		}
	}
}
#endif

#define GET_ALIGNED_ADDRESS(requested_size, block_size) (requested_size % block_size == 0 ? requested_size : ((requested_size / block_size)+1)*block_size)

// Processes a request
void CMemoryScanner::ProcessSingleRequest(tMemoryScanRequest& request)
{
	request.countOfMatches = 0;
	request.lastAddressFound = NULL;

	if (!request.maxCountOfIterations || !request.ptrAlignment)
		return;

	for (auto it = this->m_memoryRegions.begin(); it != this->m_memoryRegions.end(); it++)
	{
		if (request.searchType == MEMORY_SCAN_REQUEST_SEQUENCE_OF_BYTES)
		{
			const char* pData = request.data.pSequenceOfBytes;

			size_t numberOfBytesChecked = request.minNumberOfBytesNeeded;

			tMemoryAcesssPtr firstAddress = GET_ALIGNED_ADDRESS(it->start, request.ptrAlignment);

			size_t SectionDataSize = it->end - firstAddress;

			if (numberOfBytesChecked > SectionDataSize)
				continue;

			tMemoryAcesssPtr lastAddress = it->start + SectionDataSize - numberOfBytesChecked;

			while (lastAddress >= firstAddress)
			{
				if (!this->pMemoryAccessor->Compare(firstAddress, pData, numberOfBytesChecked))
				{
					request.lastAddressFound = (void*)firstAddress;
					request.countOfMatches++;

					if (request.countOfMatches >= request.maxCountOfIterations)
						return;
				}

				firstAddress += request.ptrAlignment;
			}
		}
		else if (request.searchType == MEMORY_SCAN_REQUEST_FUNCTION)
		{
			tMemoryScanControl control = { 0 };
			control.pMemoryAccessor = this->pMemoryAccessor;

			tMemoryScanFunction func = request.data.func.funcPtr;

			void* pCustomData = request.data.func.pCustomData;

			size_t numberOfBytesChecked = request.minNumberOfBytesNeeded;

			control.ptr = GET_ALIGNED_ADDRESS(it->start, request.ptrAlignment);

			size_t SectionDataSize = it->end - control.ptr;

			if (numberOfBytesChecked > SectionDataSize)
				continue;

			tMemoryAcesssPtr lastAddress = control.ptr + SectionDataSize - numberOfBytesChecked;

			control.numberOfBytesAvailableInSection = SectionDataSize;

			while (lastAddress >= control.ptr)
			{
				if (func(control, pCustomData))
				{
					request.lastAddressFound = (void*)control.ptr;
					request.countOfMatches++;

					if (request.countOfMatches >= request.maxCountOfIterations)
						return;
				}

				if (control.bBreakScanningCompletely)
					return;
				else if (control.bBreakScanningOfCurrentSection)
					break;

				control.numberOfBytesAvailableInSection--;
				control.ptr += request.ptrAlignment;
			}
		}
		else
			return;
	}
}

// Finds address to sequence of bytes
void* CMemoryScanner::FindSequenceOfBytes(const char* data, size_t size, unsigned int ptrAlignment)
{
	tMemoryScanRequest request;
	request.searchType = MEMORY_SCAN_REQUEST_SEQUENCE_OF_BYTES;
	request.minNumberOfBytesNeeded = size;
	request.data.pSequenceOfBytes = data;
	request.maxCountOfIterations = 1;
	request.ptrAlignment = ptrAlignment;

	this->ProcessSingleRequest(request);
	return request.lastAddressFound;
}

// Finds a string
const char* CMemoryScanner::FindString(const char* str)
{
	return (const char*)this->FindSequenceOfBytes(str, strlen(str) + 1, 1);
}

// Finds data using a function
void* CMemoryScanner::FindWithFunction(tMemoryScanFunction func, size_t minNumberOfBytesNeeded, unsigned int ptrAlignment, void* pCustomData)
{
	tMemoryScanRequest request;
	request.searchType = MEMORY_SCAN_REQUEST_FUNCTION;
	request.minNumberOfBytesNeeded = minNumberOfBytesNeeded;
	request.ptrAlignment = ptrAlignment;
	request.data.func.funcPtr = func;
	request.data.func.pCustomData = pCustomData;
	request.maxCountOfIterations = 1;

	this->ProcessSingleRequest(request);
	return request.lastAddressFound;
}