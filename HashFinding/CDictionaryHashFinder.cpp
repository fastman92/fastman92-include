/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CDictionaryHashFinder.h"
#include <iostream>

// Load dictionary
bool CDictionaryHashFinder::LoadKnownCombinations(const char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (!fp)
		return false;

	char line[1024];

	char str[1024];
	
	while (fgets(line, sizeof(line), fp))
	{
		sscanf(line, "%s", str);
		this->CombinationArray.push_back(str);
	}	

	fclose(fp);
	return true;
}

// Process request by dictionary
void CDictionaryHashFinder::ProcessRequestByDictionary(tHashFindRequest* pRequest, int handlerID)
{
	tDictionaryHashFindRequestData* pDictionaryData = (tDictionaryHashFindRequestData*)pRequest->handlers[handlerID].pAdditionalData;

	auto func = pDictionaryData->func;

	int countOfEntries = 0;
	
	for (auto it = this->CombinationArray.begin(); it != this->CombinationArray.end(); ++it)
	{
		if (pRequest->hashFindResultState != HASH_FIND_RESULT_STATE_NOT_FOUND)
			break;

		const char* curPermutation = it->c_str();

		if (func(curPermutation, pRequest->pUserData))
		{
			pRequest->hashFindResultState = HASH_FIND_RESULT_STATE_FOUND;
			strcpy(pRequest->foundMatchStr, curPermutation);
			break;
		}
	}
}