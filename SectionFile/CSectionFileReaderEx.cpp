/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CSectionFileReaderEx.h"

/*
// Decodes section and calls ProcessModelInfo
template<typename T> void CSectionFileReaderEx::DecodeSection(tLineParsingInfo* pParsingInfo)
{
	T object;

	object.ImportEntry(this->m_gameInfo.gameSimple, pParsingInfo->pLine);

	this->ProcessEntry(&object);
}
*/

// Processes comment
void CSectionFileReaderEx::ProcessComment(tLineParsingInfo* pParsingInfo)
{
	CSectionFileComment object;

	object.ImportEntry(pParsingInfo->pLine);

	this->ProcessEntry(&object);
}

// Returns pointer to game info
const Game::tSimpleGameAndPlatform* CSectionFileReaderEx::GetPointerToGameInfo()
{
	return &this->m_gameInfo;
}