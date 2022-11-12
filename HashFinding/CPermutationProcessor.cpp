/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CPermutationProcessor.h"
#include <omp.h>
#include <stdio.h>

// Constructor
CPermutationProcessor::CPermutationProcessor()
{
	this->pattern[0] = NULL;
	this->patternLength = 0;
}

// Sets pattern
void CPermutationProcessor::SetPattern(const char* pattern)
{
	strcpy_s(this->pattern, pattern);
	this->patternLength = strlen(this->pattern);
	this->MakeIndexToCharMap();
}

// Returns pattern length
int CPermutationProcessor::GetPatternLength()
{
	return this->patternLength;
}


// Assign indexes to map of pattern
void CPermutationProcessor::MakeIndexToCharMap()
{
	// Assign indexes to map of pattern
	memset(this->charToIndexMap, NULL, sizeof(this->charToIndexMap));

	for (unsigned int i = 0; i < this->patternLength; i++)
		charToIndexMap[(unsigned __int8)this->pattern[i]] = i;

	this->bCharToIndexMapInitialized = true;
}

// Finds index of character.
inline unsigned __int8 CPermutationProcessor::FindIndexOfCharacter(char c)
{	
	return this->charToIndexMap[(unsigned __int8)c];
}

// Returns character by index
inline unsigned __int8 CPermutationProcessor::GetCharacterByIndex(unsigned int index)
{
	return this->pattern[index];
}


// Permutates string and executes function per thread
void CPermutationProcessor::ProcessRequestBruteForcePerThread(tHashFindRequest* pRequest, int handlerID, int threadNum)
{
	CPermutationProcessor* pInstance = this;
	tHashFindRequestThreadInfo* pThreadInfo = pRequest->threadInfo[threadNum];
	tPermutationRequestData* pPermutationData = (tPermutationRequestData*)pRequest->handlers[handlerID].pAdditionalData;

	int patternMaxIndex = pInstance->GetPatternLength() - 1;
	unsigned __int8* charToIndexMap = pInstance->charToIndexMap;
	char* pattern = pInstance->pattern;
	
	if (pThreadInfo->firstPermutationInt == 0)
	{
		pInstance->GetPermutationStringByOrdinalNum(pThreadInfo->firstPermutationInt, pThreadInfo->curPermutation);

		if (pPermutationData->func(pThreadInfo->curPermutation, pRequest->pUserData))
		{
			pRequest->hashFindResultState = HASH_FIND_RESULT_STATE_FOUND;
			strcpy(pRequest->foundMatchStr, pThreadInfo->curPermutation);
			return;
		}

		pThreadInfo->firstPermutationInt++;
	}
	
	pInstance->GetPermutationStringByOrdinalNum(pThreadInfo->firstPermutationInt, pThreadInfo->curPermutation);
	int curPermutationMaxIndex = strlen(pThreadInfo->curPermutation) - 1;

	unsigned __int64 firstPermutationInt = pThreadInfo->firstPermutationInt;
	unsigned __int64 lastPermutationInt = pThreadInfo->lastPermutationInt;

	for (pThreadInfo->curPermutationInt = firstPermutationInt; pThreadInfo->curPermutationInt <= lastPermutationInt; pThreadInfo->curPermutationInt++)
	{
		if (pRequest->hashFindResultState != HASH_FIND_RESULT_STATE_NOT_FOUND)
			break;
				
		if (pPermutationData->func(pThreadInfo->curPermutation, pRequest->pUserData))
		{
			pRequest->hashFindResultState = HASH_FIND_RESULT_STATE_FOUND;
			strcpy(pRequest->foundMatchStr, pThreadInfo->curPermutation);
			break;
		}		
		
		for (int i = curPermutationMaxIndex;;)
		{
			int index = charToIndexMap[pThreadInfo->curPermutation[i]];

			if (index < patternMaxIndex)
			{
				pThreadInfo->curPermutation[i] = pattern[index + 1];
				break;
			}
			else
			{
				pThreadInfo->curPermutation[i] = pattern[0];

				if (i > 0)	// there will be next iteration
				{
					i--;
					continue;
				}
				else
				{
					pThreadInfo->curPermutation[++curPermutationMaxIndex] = pattern[0];
					pThreadInfo->curPermutation[curPermutationMaxIndex+1] = NULL;
					
					break;
				}
			}
		}
	}
	
	/*
	for (pThreadInfo->curPermutationInt = pThreadInfo->firstPermutationInt; pThreadInfo->curPermutationInt <= pThreadInfo->lastPermutationInt; pThreadInfo->curPermutationInt++)
	{
		if (pRequest->bFoundMatch)
			break;

		// 257 milion seconds
		pInstance->GetPermutationStringByOrdinalNum(pThreadInfo->curPermutationInt, pThreadInfo->curPermutation);
		
		
		if (pRequest->func(pThreadInfo->curPermutation, pRequest->pUserData))
		{
			pRequest->bFoundMatch = true;
			pRequest->foundMatchInt = pThreadInfo->curPermutationInt;
			strcpy(pRequest->foundMatchStr, pThreadInfo->curPermutation);
		}
	}
	*/
}

// Process request brute force
void CPermutationProcessor::ProcessRequestBruteForce(tHashFindRequest* pRequest, int handlerID)
{
	/*
	pRequest->foundMatchInt = 20;
	pRequest->amplitudeToLastFoundMatch = 100;

	pRequest->firstPermutationInt = 0;
	pRequest->lastPermutationInt = 470;
	*/	

	tPermutationRequestData* pPermutationData = (tPermutationRequestData*)pRequest->handlers[handlerID].pAdditionalData;

	unsigned __int64 firstCombination = pPermutationData->firstPermutationInt;

	unsigned __int64 lastCombination = pPermutationData->lastPermutationInt;

	unsigned __int64 amplitudeHalf;

	unsigned __int64 firstCombinationByAmplitude;
	unsigned __int64 lastCombinationByAmplitude;

	unsigned __int64 foundMatchInt = this->GetOrdinalNumOfPermutationString(pRequest->foundMatchStr);

	if (pPermutationData->amplitudeToLastFoundMatch)
	{
		if (pPermutationData->amplitudeToLastFoundMatch >= 2)
			amplitudeHalf = pPermutationData->amplitudeToLastFoundMatch / 2;
		else
			amplitudeHalf = 1;

		if (foundMatchInt >= amplitudeHalf)
			firstCombinationByAmplitude = foundMatchInt - amplitudeHalf;
		else
			firstCombinationByAmplitude = 0;

		if (lastCombination - foundMatchInt >= amplitudeHalf)
			lastCombinationByAmplitude = foundMatchInt + amplitudeHalf - 1;
		else
			lastCombinationByAmplitude = lastCombination;
	}

	// omp_set_num_threads(1);

	int expectedPriority = GetThreadPriority(GetCurrentThread());


#pragma omp parallel
	{
		int this_thread = omp_get_thread_num(), num_threads = omp_get_num_threads();

		tHashFindRequestThreadInfo threadInfo;

#pragma omp master
		{
			pRequest->numberOfThreadsActive = num_threads;
		}

		pRequest->threadInfo[this_thread] = &threadInfo;

		HANDLE curThreadHandle = GetCurrentThread();

		SetThreadPriority(curThreadHandle, expectedPriority);

#pragma omp barrier

		unsigned __int64 numberOfCombinations;

		tHashFindRequestThreadInfo* pThreadInfo = &threadInfo;

		if (pPermutationData->amplitudeToLastFoundMatch)
		{
			numberOfCombinations = (lastCombinationByAmplitude - firstCombinationByAmplitude) + 1;

			pThreadInfo->firstPermutationInt = firstCombinationByAmplitude + this_thread * numberOfCombinations / num_threads;
			pThreadInfo->lastPermutationInt = firstCombinationByAmplitude + (this_thread + 1) * numberOfCombinations / num_threads;

			if (pThreadInfo->lastPermutationInt)
			{
				pThreadInfo->lastPermutationInt--;
				this->ProcessRequestBruteForcePerThread(pRequest, handlerID, this_thread);
			}
		}

		if (!pRequest->hashFindResultState != HASH_FIND_RESULT_STATE_NOT_FOUND)
		{
			numberOfCombinations = (lastCombination - firstCombination) + 1;

			pThreadInfo->firstPermutationInt = firstCombination + this_thread * numberOfCombinations / num_threads;
			pThreadInfo->lastPermutationInt = firstCombination + (this_thread + 1) * numberOfCombinations / num_threads;

			if (pThreadInfo->lastPermutationInt)
			{
				pThreadInfo->lastPermutationInt--;
				this->ProcessRequestBruteForcePerThread(pRequest, handlerID, this_thread);
			}
		}

#pragma omp barrier

#pragma omp master
		{
			pRequest->numberOfThreadsActive = 0;
		}

		pRequest->threadInfo[this_thread] = 0;
	}
}

// Writes a string - last possible permutation for specified length
void CPermutationProcessor::GetLastPermutationStringForSpecifiedLength(int permutationLength, char* lastPermutation)
{
	char lastChar = this->pattern[this->patternLength - 1];

	for (int i = 0; i < permutationLength; i++)
		lastPermutation[i] = lastChar;

	lastPermutation[permutationLength] = NULL;
}

// Returns last permutation ordinal num for specified length
unsigned __int64 CPermutationProcessor::GetLastPermutationOrdinalNumForSpecifiedLength(int permutationLength)
{
	__int64 result = 0;
	__int64 multiplier = 1;
	
	while (permutationLength > 0)
	{
		result += (this->patternLength) * multiplier;

		multiplier *= this->patternLength;
		permutationLength--;
	}

	return result;
}

// Returns permutation string by an ordinal number
void CPermutationProcessor::GetPermutationStringByOrdinalNum(__int64 ordinalNum, char* outString)
{
	// char* CopyOutString = outString;

	__int64 Xoffset = ordinalNum;

	while (Xoffset > 0)
	{
		if (Xoffset % patternLength == 0)
			Xoffset = (Xoffset / this->patternLength) - 1;
		else
			Xoffset /= this->patternLength;

		outString++;
	}

	*outString-- = NULL;

	Xoffset = ordinalNum;

	while (Xoffset > 0)
	{
		__int64 offsetMod = Xoffset % this->patternLength;

		*(outString) = this->pattern[offsetMod == 0 ? patternLength - 1 : offsetMod - 1];

		if (offsetMod == 0)
			Xoffset = (Xoffset / this->patternLength) - 1;
		else
			Xoffset /= this->patternLength;

		outString--;
	}
}

// Returns permutation as integer, number of permutation
unsigned __int64 CPermutationProcessor::GetOrdinalNumOfPermutationString(const char* permutationString)
{
	const char* xPermutationString = permutationString;

	while (*xPermutationString)
		xPermutationString++;

	xPermutationString--;		// go to last character

	__int64 result = 0;
	__int64 multiplier = 1;

	while (xPermutationString >= permutationString)
	{
		if (unsigned __int8 index = this->FindIndexOfCharacter(*xPermutationString--))
			result += (index + 1) * multiplier;
		else
			return FALSE;

		multiplier *= this->patternLength;
	}

	return result;
}

// Returns number of possible permutations for specified permutation length
__int64 CPermutationProcessor::GetMaxNumberOfPermutations(int maxPermutationLength)
{
	__int64 multiplier = 1;

	__int64 result = 0;

	while (maxPermutationLength >= 0)
	{
		result += multiplier;

		multiplier *= this->patternLength;
		maxPermutationLength--;
	}
	return result;
}