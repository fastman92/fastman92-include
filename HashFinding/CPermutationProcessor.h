/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "HashFinder.h"
#include <Windows.h>

class CPermutationProcessor;

typedef bool(*tPermutationFunc)(const char* permutation, void* pUserData);

struct tPermutationRequest;

class CPermutationProcessor
{
	friend void ProcessRequestBruteForceHandler(tHashFindRequest* pRequest, int handlerID);

protected:
	// Used pattern
	char pattern[256];

	// Length of pattern
	size_t patternLength;
	
	bool bCharToIndexMapInitialized;

	// Array used to get index of character in pattern.
	unsigned __int8 charToIndexMap[256];

public:
	// Constructor
	CPermutationProcessor();

	// Sets pattern
	void SetPattern(const char* pattern);

	// Returns pattern length
	int GetPatternLength();
	
	// Assign indexes to map of pattern
	void MakeIndexToCharMap();

	// Finds index of character.
	unsigned __int8 FindIndexOfCharacter(char c);

	// Returns character by index
	unsigned __int8 GetCharacterByIndex(unsigned int index);

private:
	// Process request brute force
	void ProcessRequestBruteForce(tHashFindRequest* pRequest, int handlerID);	

	// Permutates string and executes function per thread
	void ProcessRequestBruteForcePerThread(tHashFindRequest* pRequest, int handlerID, int threadNum);	

public:
	// Writes a string - last possible permutation for specified length
	void GetLastPermutationStringForSpecifiedLength(int permutationLength, char* lastPermutation);

	// Returns last permutation ordinal num for specified length
	unsigned __int64 GetLastPermutationOrdinalNumForSpecifiedLength(int permutationLength);

	// Returns permutation string by an ordinal number
	void GetPermutationStringByOrdinalNum(__int64 ordinalNum, char* outString);

	// Returns permutation as integer, number of permutation
	unsigned __int64 GetOrdinalNumOfPermutationString(const char* permutationString);

	// Returns number of possible permutations for specified permutation length
	__int64 GetMaxNumberOfPermutations(int maxPermutationLength);
};

// ProcessRequestBruteForceHandler
static void ProcessRequestBruteForceHandler(tHashFindRequest* pRequest, int handlerID)
{
	tPermutationRequestData* ptr = (tPermutationRequestData*)pRequest->handlers[handlerID].pAdditionalData;
	ptr->pInstance->ProcessRequestBruteForce(pRequest, handlerID);
};