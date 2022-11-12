/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "HashFinder.h"
#include <list>

class CDictionaryHashFinder;

struct tDictionaryHashFindRequestData
{
	// ARGUMENTS	
	tPermutationFunc func;

	CDictionaryHashFinder* pInstance;
};

class CDictionaryHashFinder
{
	friend void ProcessRequestByDictionaryHandler(tHashFindRequest* pRequest, int handlerID);

public:
	std::list<std::string> CombinationArray;


	// Load dictionary
	bool LoadKnownCombinations(const char* filename);

	// Process request by dictionary
	void ProcessRequestByDictionary(tHashFindRequest* pRequest, int handlerID);
};

// ProcessRequestByDictionaryHandler
static void ProcessRequestByDictionaryHandler(tHashFindRequest* pRequest, int handlerID)
{
	tDictionaryHashFindRequestData* ptr = (tDictionaryHashFindRequestData*)pRequest->handlers[handlerID].pAdditionalData;
	ptr->pInstance->ProcessRequestByDictionary(pRequest, handlerID);
}