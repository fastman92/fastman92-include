/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <windows.h>

struct tHashFindRequestThreadInfo
{
	char curPermutation[64];
	unsigned __int64 curPermutationInt;
	unsigned __int64 firstPermutationInt;
	unsigned __int64 lastPermutationInt;
};

typedef bool(*tPermutationFunc)(const char* permutation, void* pUserData);

struct tHashFindRequest;

typedef void(*tHashFindHandler)(tHashFindRequest* pRequest, int handlerID);

struct tHashFindHandlerDescriptor
{
	bool bEnable;
	tHashFindHandler func;
	void* pAdditionalData;
};

enum eHashFindOperationState
{
	HASH_FIND_OPERATION_STATE_IN_PROGRESS,
	HASH_FIND_OPERATION_STATE_FINISHED
};

enum eHashFindResultState
{
	HASH_FIND_RESULT_STATE_NOT_FOUND,
	HASH_FIND_RESULT_STATE_FOUND,
	HASH_FIND_RESULT_STATE_ABORTED
};

class CPermutationProcessor;

struct tPermutationRequestData
{
	// ARGUMENTS	
	unsigned __int64 firstPermutationInt;
	unsigned __int64 lastPermutationInt;
	tPermutationFunc func;
	
	unsigned __int64 amplitudeToLastFoundMatch;	// set it to 0 if you don't know any other value
	CPermutationProcessor* pInstance;
};

struct tHashFindRequest
{
	// ARGUMENTS, need to be initialized
	unsigned int numberOfHandlers;
	tHashFindHandlerDescriptor handlers[32];
	void* pUserData;
	bool bAsynchronous;	// is the request asynchronous?
	HANDLE hEventWhenComplete;	// event fired when the request is completed 

	// UPDATED
	eHashFindResultState hashFindResultState;
	eHashFindOperationState hashFindOperationState;
	char foundMatchStr[64];
	// unsigned __int64 foundMatchInt;	

	// INTERNAL
	DWORD startTimeInMiliseconds;

	DWORD numberOfThreadsActive;
	tHashFindRequestThreadInfo* threadInfo[32];
};

static DWORD __stdcall DoProcessHashFindRequest(void* ptr)
{
	tHashFindRequest* pRequest = (tHashFindRequest*)ptr;

	for (unsigned int handlerID = 0; handlerID < pRequest->numberOfHandlers; handlerID++)
	{
		if (pRequest->handlers[handlerID].bEnable)
		{
			pRequest->handlers[handlerID].func(pRequest, handlerID);

			if (pRequest->hashFindResultState != HASH_FIND_RESULT_STATE_NOT_FOUND)
				break;
		}
	}

	// Finish
	pRequest->hashFindOperationState = HASH_FIND_OPERATION_STATE_FINISHED;

	if (pRequest->hEventWhenComplete)
		SetEvent(pRequest->hEventWhenComplete);

	return 0;
}

// Processes hash find request
static void ProcessHashFindRequest(tHashFindRequest* pRequest)
{
	pRequest->startTimeInMiliseconds = GetTickCount();
	pRequest->hashFindResultState = HASH_FIND_RESULT_STATE_NOT_FOUND;
	pRequest->hashFindOperationState = HASH_FIND_OPERATION_STATE_IN_PROGRESS;
	pRequest->numberOfThreadsActive = 0;
	memset(pRequest->threadInfo, NULL, sizeof(pRequest->threadInfo));

	if (pRequest->hEventWhenComplete)
		ResetEvent(pRequest->hEventWhenComplete);

	if (pRequest->bAsynchronous)
	{
		HANDLE curThreadHandle = GetCurrentThread();

		HANDLE handle = CreateThread(NULL, NULL, &DoProcessHashFindRequest, pRequest, CREATE_SUSPENDED, NULL);

		HANDLE curThread = GetCurrentThread();
		int curThreadPriority = GetThreadPriority(curThread);
		SetThreadPriority(handle, curThreadPriority);

		ResumeThread(handle);
	}
	else
		DoProcessHashFindRequest(pRequest);
}