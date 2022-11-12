/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CSectionFileElementBase.h"

struct tBinarySectionStandardUserData
{
	CSectionFileReader* pReader;
	FILE* fp;
};

struct tBinarySectionDescriptor
{
	int sectionType;
	unsigned __int32 typeIDinBinaryFile;
	CSectionFileElementBase_WithSectionInfo*(*LoadFunc)(void* pUserData);
	void(*SaveFunc)(void* pUserData, const CSectionFileElementBase_WithSectionInfo* ptr);
};

// Finds binary descriptor by section type
template<class T> static const T* FindBinaryDescriptorBySectionType(const T* pArray, int sectionType)
{
	while (pArray->sectionType)
	{
		if (pArray->sectionType == sectionType)
			return pArray;

		pArray++;
	}

	return NULL;
}

// Finds binary descriptor by section type
template<class T> const T* FindBinaryDescriptorByIdentifierInFile(const T* pArray, int identifierInFile)
{
	while (pArray->sectionType)
	{
		if (pArray->typeIDinBinaryFile == identifierInFile)
			return pArray;

		pArray++;
	}

	return NULL;
}