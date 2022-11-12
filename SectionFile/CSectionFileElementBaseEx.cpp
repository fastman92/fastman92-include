/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CSectionFileElementBaseEx.h"
#include "../Hashing/Hashing.h"

// Initializes
void CHashStrPair::Initialize(const char* str, unsigned __int32 hash)
{
	this->str = str;
	this->hash = hash;
}

// Sets hash
void CHashStrPair::SetHashAndString(Game::eGameNameSimplified game, unsigned __int32 hash)
{
	char str[64];
	CreateStringWithHashLowerCase(str, hash);
	this->str = str;
	this->hash = hash;
}

// Sets name
void CHashStrPair::SetStringAndHash(Game::eGameNameSimplified game, const char* str, bool bCalculateHash)
{
	this->str = str;

	if (bCalculateHash)
		this->UpdateHash(game);
}

// Updates hash
void CHashStrPair::UpdateHash(Game::eGameNameSimplified game)
{
	this->hash = ExtractsOrCalculateHashUsingGameAlgorithm(game, this->str.c_str());
}

// Checks if real string is available
bool CHashStrPair::IsRealStringAvailable() const
{
	unsigned __int32 hash;

	return Extract32bitHashFromString(this->str.c_str(), &hash) == false;
}

///////////////////

// Returns pointer to imported line
const char* CSectionFileElementBaseEx::GetImportedLine()
{
	return this->ImportedLine.c_str();
}

// Updates line
void CSectionFileElementBaseEx::UpdateLine(Game::eGameNameSimplified game)
{
	char line[4096];
	this->ExportEntry(game, line);
	this->ImportedLine = line;
}

// Imports entry.
unsigned __int32 CSectionFileElementBaseEx::ImportEntry(Game::eGameNameSimplified game, const char* line)
{
	this->ImportedLine = line;
	return -1;
}

// Exports entry. Returns length of output string.
int CSectionFileElementBaseEx::ExportEntry(Game::eGameNameSimplified game, char* line)
{
	strcpy(line, this->ImportedLine.c_str());
	return strlen(this->ImportedLine.c_str());
}

// Executes a function for all string hash pairs
void CSectionFileElementBaseEx::ForeachAllStrHashPairs(tHashStrPairFunc func, void* pUserData)
{
	this->ForeachModelStrHashPairs(func, pUserData);
	this->ForeachOtherStrHashPairs(func, pUserData);
}

// Executes a function for all world position vectors as 2D
void CSectionFileElementBaseEx::ForeachAllWorldPositionsAs2D(tHashVector2DFunc func, void* pUserData)
{
	this->Foreach2DworldPositions(func, pUserData);
	this->Foreach3DworldPositions((tHashVector3DFunc)func, pUserData);
}