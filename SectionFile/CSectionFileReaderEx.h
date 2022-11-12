/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CSectionFileReader.h"
#include "CSectionFileElementBase.h"
#include "CSectionFileElementBaseEx.h"
#include "../eGame.h"

class CSectionFileReaderEx : public CSectionFileReader
{
protected:
	Game::tSimpleGameAndPlatform m_gameInfo;

public:
	// Decodes section and calls ProcessModelEntry
	template<typename T> void DecodeSection(tLineParsingInfo* pParsingInfo)
	{
		T object;

		object.SetReaderPointer(this);
		object.ImportEntry(this->m_gameInfo.gameSimple, pParsingInfo->pLine);

		this->ProcessEntry(&object);
	}

	// Decodes section and calls ProcessModelEntry
	template<typename T, int sectionType> void DecodeSectionUsingType(tLineParsingInfo* pParsingInfo)
	{
		T object(sectionType);

		object.SetReaderPointer(this);
		object.ImportEntry(this->m_gameInfo.gameSimple, pParsingInfo->pLine);

		this->ProcessEntry(&object);
	}

	// Processes comment
	virtual void ProcessComment(tLineParsingInfo* pParsingInfo);

	// Sets game version and registers sections.
	virtual void SetGameVersion(Game::eGameName game) {}

	// Process model info
	virtual void ProcessEntry(CSectionFileElementBase* pModelInfo) = 0;

	// Returns pointer to game info
	const Game::tSimpleGameAndPlatform* GetPointerToGameInfo();
};

template <class Treader> class CSectionFileReaderExLoader : public Treader
{
public:
	CSectionFileMap m_FileElementMap;

	CSectionFileElement_SectionOfData* m_pCurFileElementSection;

	// CLears loaded data
	virtual void ClearLoadedData()
	{
		this->m_pCurFileElementSection = NULL;

		this->m_FileElementMap.ClearLoadedData();
	}

	// Loads file
	virtual bool LoadFile(const char* filename)
	{
		this->m_pCurFileElementSection = NULL;
		if (this->CSectionFileReader::LoadFile(filename))
			return true;
		else
			return false;
	}

	// Process model info
	virtual void ProcessEntry(CSectionFileElementBase* pElement)
	{
		// this->CSectionFileReaderEx::ProcessEntry();

		CSectionFileElementBase* pCopy = pElement->clone();

		if (this->m_pCurFileElementSection)
			this->m_pCurFileElementSection->Data.push_back(pCopy);
		else
			this->m_FileElementMap.Data.push_back(pCopy);
	}

	// Function executed when section is started.
	virtual void BeginSection()
	{
		this->m_pCurFileElementSection = this->m_FileElementMap.AddSection(
			this->m_pCurSectionInfo->typeID
			);
	}

	// Function executed when section is ended up.
	virtual void EndSection()
	{
		this->m_pCurFileElementSection = NULL;
	}

	// Browses sections of specified type
	void ForeachSectionWithSpecifiedType(
		int typeID,
		bool(*func)(CSectionFileElement_SectionOfData* pSection, void* pUserData),		
		void* pUserData
		)
	{
		for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
		{
			CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData();

			if (!pSection || pSectionInfo->GetSectionType() != typeID)
				continue;

			if (func(pSection, pUserData))
				return;			
		}
	}

private:
	bool ForeachAllDataElementsHelper(
		bool(*func)(CSectionFileElementBaseEx* pElement, void* pUserData),
		void* pUserData,
		CSectionFileElementBase* pElement
		)
	{
		if (pElement->IsData())
			return func((CSectionFileElementBaseEx*)pElement, pUserData);
		else if (CSectionFileElement_SectionOfData* pSection = pElement->ToSectionOfData())
		{
			for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
			{
				if (ForeachAllDataElementsHelper(func, pUserData, &*secondIt))
					return true;
			}
		}

		return false;
	}

public:

	
	// Browses sections and elements of specified type
	void ForeachAllDataElements(
		bool(*func)(CSectionFileElementBaseEx* pElement, void* pUserData),
		void* pUserData
		)
	{
		for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
		{
			if (ForeachAllDataElementsHelper(func, pUserData, &*firstIt))
				return;			
		}
	}
	

	// Browses sections and elements of specified type
	void ForeachSectionsAndElementsWithSpecifiedType(
		int typeID,
		bool(*func)(CSectionFileElementBase_WithSectionInfo* pElement, void* pUserData),
		void* pUserData
		)
	{
		for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
		{
			CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData();
			
			if (!pSection || pSection->GetSectionType() != typeID)
				continue;

			for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
			{
				CSectionFileElementBase_WithSectionInfo* pElement = secondIt->ToElementBaseWithSectionInfo();

				
				if (!pElement || pElement->GetSectionType() != pSection->GetSectionType()
					)
					continue;
				/*

				if (!pElement)
					continue;



				if(pElement->GetSectionType() != pSection->GetSectionType())
				{
					printf("actual section: %d type\n", pElement->GetSectionType());
					continue;
				}
				*/


				if (func(pElement, pUserData))
					return;
			}
		}
	}

	// Counts data with specified section type
	unsigned int CountDataElementsWithSpecifiedSectionType(int sectionType)
	{
		unsigned int count = 0;

		ForeachSectionsAndElementsWithSpecifiedType(
			sectionType,

			[](CSectionFileElementBase_WithSectionInfo* pElement, void* pUserData)
			{
				(*(unsigned int*)(pUserData))++;
			
				return false;
			},

			&count
			);

		return count;
	}

	// Updates all hashes
	virtual void UpdateAllHashes()
	{
		this->ForeachAllDataElements(

			[](CSectionFileElementBaseEx* pElementEx, void* pUserData)
		{
			pElementEx->ForeachAllStrHashPairs(
				[](CHashStrPair* pHashStrPair, void* pUserData)
			{
				Game::tSimpleGameAndPlatform* pGameInfo = (Game::tSimpleGameAndPlatform*)pUserData;

				pHashStrPair->UpdateHash(pGameInfo->gameSimple);
			},
				pUserData
				);

			return false;
		}
		, &this->m_gameInfo);
	}

	// Updates all lines
	virtual void UpdateAllLines()
	{
		this->ForeachAllDataElements(

			[](CSectionFileElementBaseEx* pElementEx, void* pUserData)
		{
			Game::tSimpleGameAndPlatform* pGameInfo = (Game::tSimpleGameAndPlatform*)pUserData;
			pElementEx->UpdateLine(pGameInfo->gameSimple);

			pElementEx->ForeachAllStrHashPairs(
				[](CHashStrPair* pHashStrPair, void* pUserData)
			{
				Game::tSimpleGameAndPlatform* pGameInfo = (Game::tSimpleGameAndPlatform*)pUserData;				
				pHashStrPair->UpdateHash(pGameInfo->gameSimple);
			},
				pGameInfo
				);

			return false;
		}
			, &this->m_gameInfo);
	}

	// Saves a text file
	virtual bool SaveTextFile(const char* filename, bool bUpdateEntryLines = false)
	{		
		if (FILE* fp = fopen(filename, "w"))
		{
			bool bIsFirstLine = true;

			for (auto firstIt = this->m_FileElementMap.Data.begin(); firstIt != this->m_FileElementMap.Data.end(); ++firstIt)
			{
				if (CSectionFileElement_SectionOfData* pSection = firstIt->ToSectionOfData())
				{					
					const tSectionInfo* pSectionInfo = this->FindSectionInfoWithSpecifiedTypeID(pSection->GetSectionType());

					if (!pSectionInfo)
						continue;					

					if (!bIsFirstLine)
						fprintf(fp, "\n");

					bIsFirstLine = false;

					fprintf(fp, "%s", pSectionInfo->sectionName);

					for (auto secondIt = pSection->Data.begin(); secondIt != pSection->Data.end(); ++secondIt)
					{
						fprintf(fp, "\n");
						this->SaveElement(fp, &*secondIt, bUpdateEntryLines);
					}

					fprintf(fp, "\nend");
				}
				else
				{
					if (!bIsFirstLine)
						fprintf(fp, "\n");

					bIsFirstLine = false;

					this->SaveElement(fp, &*firstIt, bUpdateEntryLines);
				}
			}

			fclose(fp);

			return true;
		}

		return false;
	}

	// Saves element
	void SaveElement(FILE* fp, CSectionFileElementBase* pElement, bool bUpdateEntries)
	{
		char line[4096];

		if (CSectionFileComment* pComment = pElement->ToComment())
		{
			pComment->ExportEntry(line);
			fprintf(fp, "%s", line);
		}
		else if (pElement->IsData())
		{
			CSectionFileElementBaseEx* pElementEx = static_cast<CSectionFileElementBaseEx*>(pElement);

			if (bUpdateEntries)
				pElementEx->UpdateLine(this->m_gameInfo.gameSimple);

			fprintf(fp, "%s", pElementEx->GetImportedLine());
		}
	}
};


typedef CSectionFileReaderExLoader<CSectionFileReaderEx> CSectionFileReaderExLoader_generic;