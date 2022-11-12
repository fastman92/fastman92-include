#include "CHashListLoader.h"
#include "CalculateHashUsingGameAlgorithm.h"
#include "../StrLexStuff.h"

// Loads file
bool CHashListLoaderBase::LoadFile(const char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (!fp)
		return false;

	char line[1024];
	char str[128];

	while (fgets(line, sizeof(line), fp))
	{
		char* iLine = FindFirstNonWhiteCharacter(line);

		if (!iLine[0] || iLine[0] == '#')
			continue;

		str[0] = NULL;
		sscanf(iLine, "%s", &str);

		auto hash = this->GetHashFromString(str);

		this->m_hashStrMap[hash] = str;
	}

	fclose(fp);

	return true;
}

// Clears loaded data
void CHashListLoaderBase::ClearData()
{
	this->m_hashStrMap.clear();
}

// Finds string by hash
std::string* CHashListLoaderBase::FindStringByHash(unsigned __int32 hash)
{
	auto it = this->m_hashStrMap.find(hash);

	if (it != this->m_hashStrMap.end())
		return &it->second;
	else
		return NULL;
}

// Calculates hash
unsigned __int32 CHashListLoaderForGame::GetHashFromString(const char* str)
{
	return CalculateHashUsingGameAlgorithm(this->m_gameInfo.gameSimple, str);
}

// Sets game version and registers sections.
void CHashListLoaderForGame::SetGameVersion(Game::eGameName game)
{
	this->ClearData();

	this->m_gameInfo = Game::GetSimpleGameAndPlatformByExactMember(game);
}