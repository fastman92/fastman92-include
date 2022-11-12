#pragma once
#include <map>
#include <string>
#include "../eGame.h"

class CHashListLoaderBase
{
public:
	std::map<unsigned __int32, std::string> m_hashStrMap;

	// Loads file
	bool LoadFile(const char* filename);

	// Clears loaded data
	void ClearData();

	// Finds string by hash
	std::string* FindStringByHash(unsigned __int32 hash);

	// Calculates hash
	virtual unsigned __int32 GetHashFromString(const char* str) = 0;
};

class CHashListLoaderForGame : public CHashListLoaderBase
{
protected:
	Game::tSimpleGameAndPlatform m_gameInfo;

protected:
	// Calculates hash
	virtual unsigned __int32 GetHashFromString(const char* str);

public:
	// Sets game version and registers sections.
	virtual void SetGameVersion(Game::eGameName game);
};