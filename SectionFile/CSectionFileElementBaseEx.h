/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../eGame.h"
#include "../CVector2D.h"
#include "../CVector.h"
#include "CSectionFileElementBase.h"

class CHashStrPair
{
	unsigned __int32 hash;
	std::string str;

public:
	// Initializes
	void Initialize(const char* str, unsigned __int32 hash = 0);

	// Sets hash
	void SetHashAndString(Game::eGameNameSimplified game, unsigned __int32 hash);

	// Sets name
	void SetStringAndHash(Game::eGameNameSimplified game, const char* name, bool bCalculateHash = true);

	// Updates hash
	void UpdateHash(Game::eGameNameSimplified game);

	// Checks if real string is available
	bool IsRealStringAvailable() const;

	// Returns reference to string
	const std::string& GetString() const { return this->str; }

	// Returns hash
	unsigned __int32 GetHash() const { return this->hash; }
};

typedef void(*tHashStrPairFunc)(CHashStrPair* pHashStrPair, void* pUserData);
typedef void(*tHashVector2DFunc)(CVector2D* pVector, void* pUserData);
typedef void(*tHashVector3DFunc)(CVector* pVector, void* pUserData);
typedef void(*tModelIDfunc)(unsigned __int32* modelID, void* pUserData);

class CSectionFileElementBaseEx : public CSectionFileElementBase_WithSectionInfo
{
public:
	// Constructor
	CSectionFileElementBaseEx(eSectionFileElementType type, int sectionType) : CSectionFileElementBase_WithSectionInfo(type, sectionType)
	{
	}

	// Imported line
	std::string ImportedLine;

	// Returns pointer to imported line
	const char* GetImportedLine();

	// Updates line
	void UpdateLine(Game::eGameNameSimplified game);

	//// Virtual functions ////

	// Sets default values
	virtual void InitValues() {}

	// Imports entry.
	virtual unsigned __int32 ImportEntry(Game::eGameNameSimplified game, const char* line);

	// Exports entry. Returns length of output string.
	virtual int ExportEntry(Game::eGameNameSimplified game, char* line);

	// Executes a function for all string hash pairs
	virtual void ForeachAllModelIDs(tHashStrPairFunc func, void* pUserData) {}

	// Executes a function for all string hash pairs
	void ForeachAllStrHashPairs(tHashStrPairFunc func, void* pUserData);

	// Executes a function for each model string hash pair
	virtual void ForeachModelStrHashPairs(tHashStrPairFunc func, void* pUserData) {}

	// Executes a function for each other string hash pair
	virtual void ForeachOtherStrHashPairs(tHashStrPairFunc func, void* pUserData) {}

	// Executes a function for 2D world position vectors
	virtual void Foreach2DworldPositions(tHashVector2DFunc func, void* pUserData) {}

	// Executes a function for 3D world position vectors
	virtual void Foreach3DworldPositions(tHashVector3DFunc func, void* pUserData) {}

	// Executes a function for all world position vectors as 2D
	void ForeachAllWorldPositionsAs2D(tHashVector2DFunc func, void* pUserData);
};