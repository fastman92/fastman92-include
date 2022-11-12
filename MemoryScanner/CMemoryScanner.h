/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../MemoryAccess/CMemoryAccess.h"
#include "../Endianness/Endianness.h"
#include <stdint.h>

#include <vector>

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

struct tMemoryRegion
{
	tMemoryAcesssPtr start;
	tMemoryAcesssPtr end;
};

enum eMemoryScanRequestType
{
	MEMORY_SCAN_REQUEST_SEQUENCE_OF_BYTES,
	MEMORY_SCAN_REQUEST_FUNCTION
};

struct tMemoryScanControl;

typedef bool(*tMemoryScanFunction)(tMemoryScanControl& control, void* pCustomData);

struct tMemoryScanFunctionCallback
{
	tMemoryScanFunction funcPtr;
	void* pCustomData;
};

struct tMemoryScanRequest
{
	/////////// input ///////////	
	eMemoryScanRequestType searchType;
	unsigned int maxCountOfIterations;

	size_t minNumberOfBytesNeeded;
	unsigned int ptrAlignment;		// usually should be 1

	union
	{
		// for MEMORY_SCAN_REQUEST_SEQUENCE_OF_BYTES
		const char* pSequenceOfBytes;

		// for MEMORY_SCAN_REQUEST_FUNCTION
		tMemoryScanFunctionCallback func;

	} data;

	/////////// output ///////////
	void* lastAddressFound;
	unsigned int countOfMatches;
};

// extra condition
enum eMemoryFindCondition
{
	MEMORY_FIND_CONDITION_RELATIVE_4_BYTE_ADDRESS,
	MEMORY_FIND_CONDITION_RELATIVE_4_BYTE_ADDRESS_IN_INSTRUCTION,

	MEMORY_FIND_CONDITION_SIGNED_INT8,
	MEMORY_FIND_CONDITION_UNSIGNED_INT8,
	MEMORY_FIND_CONDITION_SIGNED_INT16,
	MEMORY_FIND_CONDITION_UNSIGNED_INT16,
	MEMORY_FIND_CONDITION_SIGNED_INT32,
	MEMORY_FIND_CONDITION_UNSIGNED_INT32,
	MEMORY_FIND_CONDITION_SIGNED_INT64,
	MEMORY_FIND_CONDITION_UNSIGNED_INT64,
	MEMORY_FIND_CONDITION_FLOAT,
	MEMORY_FIND_CONDITION_DOUBLE
};

template <typename T> struct tLowHighValues
{
	T low;
	T high;
};

struct tMemoryScanExtraConditionData
{
	eMemoryFindCondition findCondition;

	union
	{
		tLowHighValues<tMemoryAcesssPtr> relative4byteAddress;

		tLowHighValues<int8_t> signedInt8;
		tLowHighValues<uint8_t> unsignedInt8;
		tLowHighValues<int16_t> signedInt16;
		tLowHighValues<uint16_t> unsignedInt16;
		tLowHighValues<int32_t> signedInt32;
		tLowHighValues<uint32_t> unsignedInt32;
		tLowHighValues<int64_t> signedInt64;
		tLowHighValues<uint64_t> unsignedInt64;

		tLowHighValues<float> floatValue;
		tLowHighValues<double> doubleValue;
	} dataToFind;

	tMemoryScanFunctionCallback func;
};

// function to be used with the structure tMemoryScanExtraConditionData
bool MemoryScanExtraConditionFunc(tMemoryScanControl& control, void* pCustomData);

// memory scan control
struct tMemoryScanControl
{
	CMemoryAccess* pMemoryAccessor;		// pointer to memory accessor

	tMemoryAcesssPtr ptr;
	size_t numberOfBytesAvailableInSection;

	bool bBreakScanningCompletely;
	bool bBreakScanningOfCurrentSection;
};

// memory scanner class
class CMemoryScanner
{
private:
	std::vector<tMemoryRegion> m_memoryRegions;
	CMemoryAccess* pMemoryAccessor;		// pointer to memory accessor
	
public:
	// Constructor
	CMemoryScanner();
	
	// Clears a list of memory regions
	void ClearListOfMemoryRegions();

	// Sets pointer to memory accessor
	void SetMemoryAccessor(CMemoryAccess* pMemoryAccessor);

	// Add memory region to search list
	void AddMemoryRegionToSearchList(tMemoryAcesssPtr startAddress, tMemoryAccessSize size);

#ifdef IS_PLATFORM_WIN
	// Adds module sections to search list
	void AddModuleSectionsToSearchList(HMODULE hModule);	
#endif

	// Processes a request
	void ProcessSingleRequest(tMemoryScanRequest& request);

	// Finds address to sequence of bytes
	void* FindSequenceOfBytes(const char* data, size_t size, unsigned int ptrAlignment);

	// Finds a string
	const char* FindString(const char* str);

	// Finds data using a function
	void* FindWithFunction(tMemoryScanFunction func, size_t minNumberOfBytesNeeded, unsigned int ptrAlignment, void* pCustomData);
};