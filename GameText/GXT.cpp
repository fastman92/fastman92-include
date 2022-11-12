/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** GXT.h
** Class to open/edit GTA GXT text files.
** Works with GXT files from following games:
** • GTA2
** • GTA III
** • GTA VC
** • GTA SA
** • GTA IV
**
** Author: fastman92
** Site: fastman92.com
** -------------------------------------------------------------------------*/

#include "GXT.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <io.h>
#include <string.h>
#include "../StrLexStuff.h"

#include "../GMemFile.h"

#include "../Hashing\Hashing.h"
#include "../fileIO.h"

using namespace std;

// Sets key name
void CGameText::GXT_entry::SetKeyName(const char* KeyName)
{
	strncpy_s(this -> KeyName, KeyName, _TRUNCATE);

	auto CRCfunction = this -> GXT_instance -> GXTformatProperties[this -> GXT_instance -> GameTextVersion].CRC32_function;

	if(CRCfunction)
		this -> KeyHash = CRCfunction(this -> KeyName);
}

// Sets original text
void CGameText::GXT_entry::SetOriginalText(const char* OriginalText)
{
	size_t l = strlen(OriginalText);
	this -> OriginalText = wstring(OriginalText, OriginalText + l);
};

// Constructor of GXT entry
CGameText::GXT_entry CGameText::GXT_tableInfo::ConstructGXT_entry()
{
	GXT_entry entry;

	entry.GXT_instance = this -> GXT_instance;	

	*entry.KeyName = NULL;
	entry.KeyHash = 0;

	return entry;
}

// Constructor with key name
CGameText::GXT_entry CGameText::GXT_tableInfo::ConstructGXT_entry(const char* KeyName)
{
	GXT_entry entry;
	entry.GXT_instance = this -> GXT_instance;

	if (Extract32bitHashFromString(KeyName, &entry.KeyHash))
		*entry.KeyName = NULL;
	else
		entry.SetKeyName(KeyName);

	return entry;
}

// Constructor with key hash
CGameText::GXT_entry CGameText::GXT_tableInfo::ConstructGXT_entry(unsigned long int KeyHash)
{
	GXT_entry entry;
	entry.GXT_instance = this -> GXT_instance;
	sprintf(entry.KeyName, "HASH_%08X", KeyHash);
	entry.KeyHash = KeyHash;
	return entry;
}

// Finds GXT entry by key name
CGameText::tEntriesContainer::iterator CGameText::GXT_tableInfo::FindGXTentryByKeyName(const char* keyName)
{
	auto CRCfunction = this -> GXT_instance -> GXTformatProperties[this -> GXT_instance -> GameTextVersion].CRC32_function;	

	if(CRCfunction)
	{
		unsigned long int hashToFind = CRCfunction(keyName);
		
		return find_if(this -> Entries.begin(), this -> Entries.end(),
			[hashToFind](CGameText::GXT_entry& entry)
		{
			return entry.KeyHash == hashToFind;
		});
	}
	else
	{
		
		return find_if(this -> Entries.begin(), this -> Entries.end(),
			[keyName](CGameText::GXT_entry& entry)
		{
			return strcmp(entry.KeyName, keyName) == 0;
		});
	}
}

// Find entry by key name
CGameText::tEntriesContainer::iterator CGameText::GXT_tableInfo::FindEntryByKeyHash(unsigned long int hash)
{
	return std::find_if(
		this -> Entries.begin(),
		this -> Entries.end(),
		[hash](GXT_entry& entry) -> bool
		{
			return entry.KeyHash == hash;
		}
	);
}

// Constructor
CGameText::CGameText()
{
	this->GXTformatProperties[GXT_VERSION_UNDEFINED].CRC32_function = NULL;

	GXTformatDescriptor* format;

	format = &this->GXTformatProperties[GXT_VERSION_GTA2_UTF16];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = NULL;
	format->IsUTF16used = true;
	format->SupportsTables = false;
	format->TKEY_version = 1;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_GTAIII_UTF16];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = NULL;
	format->IsUTF16used = true;
	format->SupportsTables = false;
	format->TKEY_version = 1;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_GTAVC_UTF16];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = NULL;
	format->IsUTF16used = true;
	format->SupportsTables = true;
	format->TKEY_version = 1;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_GTASA_ASCII];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = GTASA_CRC32_fromString;
	format->IsUTF16used = false;
	format->SupportsTables = true;
	format->TKEY_version = 2;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_GTASA_UTF16];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = GTASA_CRC32_fromString;
	format->IsUTF16used = true;
	format->SupportsTables = true;
	format->TKEY_version = 2;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_GTAIV_ASCII];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = GTAIV_CRC32_fromString;
	format->IsUTF16used = false;
	format->SupportsTables = true;
	format->TKEY_version = 2;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_GTAIV_UTF16];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_GXT;
	format->CRC32_function = GTAIV_CRC32_fromString;
	format->IsUTF16used = true;
	format->SupportsTables = true;
	format->TKEY_version = 2;
	format->bNeedsMAINtable = true;

	format = &this->GXTformatProperties[GXT_VERSION_BULLY_SCHOLARSCHIP_EDITION];
	format->BaseFormat = GAME_TEXT_BASE_FORMAT_IMG;
	format->CRC32_function = &BullyScholarschipEdition_hash_fromUpCaseString;
	format->IsUTF16used = false;
	format->SupportsTables = true;
	format->TKEY_version = 0;
	format->bNeedsMAINtable = false;

	this->GXT_handle = NULL;
	memset(this->GameTextLanguage, NULL, sizeof(this->GameTextLanguage));

	this->GameTextVersion = GXT_VERSION_UNDEFINED;
}

// Destructor
CGameText::~CGameText()
{
	this -> CloseGXTfile();
}

// Parses string with escape characters such as "\r\n test"
bool CGameText::ReadStringWithEscapeChars(wchar_t*& Line, std::wstring& str)
{	
	if(*Line++ != '"')
	{
		return false;
	}
	
	while(*Line)
	{
		const wchar_t c = *Line;

		if(c == '"')
		{
			Line++;
			return true;
		}
		else if(c == '\\')
		{
			const wchar_t n = *++Line;
			Line++;

			switch(n)
			{
			// Alert (bell)
			case 'a':
				str += '\a';
				break;
			// Backspace
			case 'b':				
				str += '\b';
				break;

			// Form feed
			case 'f':		
				str += '\f';
				break;
					
			// Newline (line feed)
			case 'n':
				str += '\n';
				break;

			// Carriage return
			case 'r':
				str += '\r';
				break;

			// Horizontal tab
			case 't':
				str += '\t';

				// Error probably here!
				Line += 2;
				break;

			// Vertical tab
			case 'v':
				str += '\v';
				break;

			// Character with hexadecimal value hh
			case 'x':
				str += (wchar_t)wcstol(Line, (wchar_t**)&Line, 16);			
				break;
			case '\\':
				str += '\\';
				break;

			case '"':
				str += '"';
				break;

			default:
				return true;
			}			
		}
		else
		{
			str += c;
			Line += 1;
		}
	}

	return false;
}

// Loads GXT pattern of letters from a file
bool CGameText::LoadGxtFontCharacterMap(const char* path)
{
	this->CharacterMap.clear();

	FILE* fp;

	if(fp = fopen(path, "r"))
	{
		wchar_t line[1024];

		while(fgetws(line, _countof(line), fp))
		{
			wchar_t* cLine = line;

			size_t lineLength = wcslen(line);

			auto SkipWhiteCharacters = [&]() -> bool
			{
				while(wchar_t c = *cLine)
				{
					if(c != '\t' && c != ' ')
						return true;
					else
						cLine++;
				}

				return false;
			};

			SkipWhiteCharacters();

			if(*cLine == '#')
				continue;

			wchar_t CharacterTo;

			if(iswdigit(*cLine))
				CharacterTo = (wchar_t)wcstol(cLine, &cLine, 10);
			else
				goto error; // error here
			
			SkipWhiteCharacters();			

			if(*cLine++ != L':')
				goto error;

			SkipWhiteCharacters();

			wstring CharactersFrom;
			
			if(!this -> ReadStringWithEscapeChars(cLine, CharactersFrom))
				goto error;

			this -> CharacterMap.push_back(CharacterReplacement(CharactersFrom, CharacterTo));

			// Sort by From
			// 1. Length
			// 2. Alphabet
			
			sort(this -> CharacterMap.begin(), this -> CharacterMap.end(),
				[](CharacterReplacement& a, CharacterReplacement& b) -> bool
			{									
					return
						a.From.length() > b.From.length() ? true :
						a.From.length() < b.From.length() ? false :

						wcscmp(a.From.c_str(), b.From.c_str()) < 0;
			}
			);
		}

		fclose(fp);
		return true;
	}
	else
		return false;

error:
	this -> CharacterMap.clear();
	fclose(fp);
	return false;
}

// Loads GXT keys text file containing possible GXT keys
bool CGameText::LoadGxtKeysTextFile(const char* path)
{
	FILE* fp;

	auto CRC32_function = this -> GXTformatProperties[this -> GameTextVersion].CRC32_function;

	if (!CRC32_function)
		return true;

	if(fp = fopen(path, "r"))
	{
		char line[1024];

		char GxtKeyName[GXT_keyName_size];
		
		getLine:
		while(fgets(line, sizeof(line), fp))
		{
			if(this -> isValidGXTkeyNameChar(line[0]))
			{
				GxtKeyName[0] = line[0];

				int i;
				
				for(i = 1; ; i++)
				{
					char c = line[i];
					
					if(c == NULL || c == '\r' || c == '\n' || c == '\t')
						break;
					else if(i >= GXT_keyName_size)
						goto getLine;
					else if(this -> isValidGXTkeyNameChar(c))
						GxtKeyName[i] = c;
					else
						goto getLine;

				}
				GxtKeyName[i] = NULL;

				this -> GXT_keyHashNames.push_back(CGameText::GXT_keyHashName(CRC32_function(GxtKeyName), GxtKeyName));
			}
		}

		fclose(fp);

		return true;
	}

	return false;
}

// Loads GXT keys binary file (TDC) containing possible GXT keys
bool CGameText::LoadGxtKeysBinaryFile(const char* path)
{
	FILE* fp;

	auto CRC32_function = this -> GXTformatProperties[this -> GameTextVersion].CRC32_function;

	if(!CRC32_function || !(fp = fopen(path, "rb")))
		return false;

	fseek(fp, 0, SEEK_END);
	unsigned long filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* pBuffer = new char[filesize];

	fread((void*)pBuffer, filesize, 1, fp);

	fclose(fp);

	GMemFile file;
	file.Open(pBuffer, filesize);

	unsigned int NumberOfTables;

	if(file.Read(&NumberOfTables, 4) != 4)
		goto ErrorAndCloseFile;

	for(unsigned int i = 0; i < NumberOfTables; i++)
	{
		unsigned char tableNameLength;

		if(file.Read(&tableNameLength, 1) != 1)
			goto ErrorAndCloseFile;

		char tableName[8];

		if(file.Read(tableName, tableNameLength) != tableNameLength)
			goto ErrorAndCloseFile;

		tableName[tableNameLength] = NULL;

		unsigned long int NumberOfTableEntries;

		if(file.Read(&NumberOfTableEntries, 4) != 4)
			goto ErrorAndCloseFile;

		for(unsigned int j = 0; j < NumberOfTableEntries; j++)
		{
			file.Seek(4, SEEK_CUR);

			unsigned char keyNameLength;

			if(file.Read(&keyNameLength, 1) != 1)
				goto ErrorAndCloseFile;

			char GxtKeyName[GXT_keyName_size];			

			if(file.Read(GxtKeyName, keyNameLength) != keyNameLength)
				goto ErrorAndCloseFile;

			GxtKeyName[keyNameLength] = NULL;

			this -> GXT_keyHashNames.push_back(GXT_keyHashName(CRC32_function(GxtKeyName), GxtKeyName));
		}
	}

	delete pBuffer;
	return true;

	ErrorAndCloseFile:
	delete pBuffer;
	return false;
}

// Assign GXT keys from list to GXT keys in tables
void CGameText::AssignGxtKeysFromListToGxtKeysOfEntries()
{
	// unsigned int NotFound = 0;
	// unsigned int Found = 0;

	for(auto& table = this -> GXT_tables.begin(); table < this -> GXT_tables.end(); table++)
	{
		for(auto& entry = table -> Entries.begin(); entry < table -> Entries.end(); entry++)
		{
			unsigned long int hashToFind = entry -> KeyHash;

			auto it = find_if(this -> GXT_keyHashNames.begin(), this -> GXT_keyHashNames.end(),
				[hashToFind](GXT_keyHashName& keyHashName)
			{
				return keyHashName.KeyHash == hashToFind;
			});

			if(it != this -> GXT_keyHashNames.end())
			{
				strncpy_s(entry -> KeyName, it -> KeyName, _TRUNCATE);
				// Found++;
			}
			// else NotFound++;
			/*
			else
				wcout << endl << hex << "error: " << table -> TableName << " " <<  entry -> KeyHash;
			*/
		}
	}
// 	cout << endl << "there are : " << this -> GXT_keyHashNames.size() << " Found: " << Found << " Not found: " << NotFound;
}

// Open GXT file
// Suggestion is used in case GTA SA / GTA IV format
bool CGameText::OpenGXTfile(const char* gxtFilePath, eGameTextSuggestionVersion gxtFormatSuggestion)
{
	this -> CloseGXTfile();
	this -> GXT_tables.clear();

	if (gxtFormatSuggestion == SUGGESTION_BULLY_SCHOLARSCHIP_EDITION)
	{
		if (!this->IMG_archive.OpenArchive(gxtFilePath))
			return false;

		if (this->IMG_archive.GetFileCount() == 0)
			return true;

		char* fileContent = new char[IMG_archive.GetOriginalSizeInBytesOfLargestFile()];

		for (auto file = IMG_archive.begin(); file != IMG_archive.end(); file++)
		{
			const char* fileName = file->GetFilename();
			
			const char* pDot = strchr(fileName, '.');

			if (!pDot)
				continue;
			
			const char* pExtension = pDot + 1;

			if (strlen(pExtension) < 3 || _memicmp(pExtension, "BIN", 3))
				continue;

			char tableName[IMG_FASTMAN92_GTASA_MAX_FILENAME_LENGTH];
			int tableNameLen = pDot - fileName;
			memcpy(tableName, fileName, tableNameLen);
			tableName[tableNameLen] = NULL;

			if (!file->ReadEntireFile(fileContent))
				goto errorBullyScholarchipEdition;

			tGXTbullyScholarschipEdition_tableHeader* pTableHeader = (tGXTbullyScholarschipEdition_tableHeader*)fileContent;

			if (pTableHeader->magicID != BullyScholarschipEdition_table_MAGIC_ID
				|| pTableHeader->version != 1
				|| pTableHeader->field_18 != 2
				|| pTableHeader->field_1C != 0
				|| pTableHeader->sizeOfTKEYsection != pTableHeader->numberOfKeys * sizeof(tGXTbullyScholarschipEdition_TKEY_item)
				)
				goto errorBullyScholarchipEdition;

			if (pTableHeader->bShouldBeBE)
			{
				if (pTableHeader->BEorBD != 'EB')
					goto errorBullyScholarchipEdition;
			}
			else if (pTableHeader->BEorBD != 'DB')
				goto errorBullyScholarchipEdition;

			this->GameTextVersion = GXT_VERSION_BULLY_SCHOLARSCHIP_EDITION;

			const char* pDAT = fileContent + sizeof(tGXTbullyScholarschipEdition_tableHeader);
			
			tGXTbullyScholarschipEdition_TKEY_item* pKeys =
				(tGXTbullyScholarschipEdition_TKEY_item*)(
					pDAT + pTableHeader->tDATsectionSize);

			this->GXT_tables.push_back(GXT_tableInfo(this));
			GXT_tableInfo& tableInfo = this->GXT_tables.back();

			strncpy_s(tableInfo.TableName, tableName, _TRUNCATE);

			/*
			sort(pKeys, pKeys + pTableHeader->numberOfKeys,
				[](const tGXTbullyScholarschipEdition_TKEY_item& a, const tGXTbullyScholarschipEdition_TKEY_item& b) { return a.Position < b.Position; });
				*/
			
			for (unsigned int i = 0; i < pTableHeader->numberOfKeys; i++)
			{
				const char* pText = pDAT + pKeys[i].Position - 1 + 2;

				tableInfo.Entries.push_back(tableInfo.ConstructGXT_entry(pKeys[i].KeyHash));
				tableInfo.Entries.back().SetOriginalTextByGxtText<char>((const char*)pText);
			}
			
		}

		delete[] fileContent;
		return true;

	errorBullyScholarchipEdition:
		delete[] fileContent;
		this->CloseGXTfile();
		return false;
	}
	else
	{
		if (!(this->GXT_handle = fopen(gxtFilePath, "rb+")))
			return false;

		unsigned long int header;
		unsigned long int identifier;

		unsigned int GXT_filesize;

		fseek(this->GXT_handle, 0, SEEK_END);
		GXT_filesize = ftell(this->GXT_handle);
		fseek(this->GXT_handle, 0, SEEK_SET);

		if (fread(&header, 4, 1, this->GXT_handle))
		{
			switch (header)
			{
			case HEADER_ASCII:
				if (gxtFormatSuggestion == SUGGESTION_GTAIV)
					this->GameTextVersion = GXT_VERSION_GTAIV_ASCII;
				else
					this->GameTextVersion = GXT_VERSION_GTASA_ASCII;

				break;

			case HEADER_UTF16:
				if (gxtFormatSuggestion == SUGGESTION_GTAIV)
					this->GameTextVersion = GXT_VERSION_GTAIV_UTF16;
				else
					this->GameTextVersion = GXT_VERSION_GTASA_UTF16;

				break;

			case 'LBAT': this->GameTextVersion = GXT_VERSION_GTAVC_UTF16; fseek(this->GXT_handle, 0, SEEK_SET); break;
			case 'YEKT': this->GameTextVersion = GXT_VERSION_GTAIII_UTF16; break;
			default:
			{
				fseek(this->GXT_handle, 0, SEEK_SET);

				char header10Bytes[10];

				if (!fread(header10Bytes, 10, 1, this->GXT_handle))
					goto error;

				if (memcmp(header10Bytes + 4, "\x64\x0TKEY", 5))
					goto error;

				this->GameTextVersion = GXT_VERSION_GTA2_UTF16;

				*(DWORD*)this->GameTextLanguage = *(DWORD*)header10Bytes;
			}
			}

			// required position: past the TKEY
			auto AddTable = [this](const char* tableName)
			{
				auto SetOriginalTextByGxtText = [this](GXT_entry* entry, const void* GxtText)
				{
					if (this->VersionIsUnicodeUsed(this->GameTextVersion))
						entry->SetOriginalTextByGxtText<wchar_t>((const wchar_t*)GxtText);
					else
						entry->SetOriginalTextByGxtText<char>((const char*)GxtText);
				};

				this->GXT_tables.push_back(GXT_tableInfo(this));

				GXT_tableInfo& tableInfo = this->GXT_tables.back();

				strncpy_s(tableInfo.TableName, tableName, _TRUNCATE);

				unsigned int NumberOfEntries;
				fread(&NumberOfEntries, 4, 1, this->GXT_handle);

				if (this->VersionGetTKEYversion(this->GameTextVersion) == 2)
				{
					NumberOfEntries /= sizeof(GXT_VERSION_2_TKEY_item);

					GXT_VERSION_2_TKEY_item* pKeys = new GXT_VERSION_2_TKEY_item[NumberOfEntries];

					fread(pKeys, sizeof(GXT_VERSION_2_TKEY_item), NumberOfEntries, this->GXT_handle);

					sort(pKeys, pKeys + NumberOfEntries,
						[](const GXT_VERSION_2_TKEY_item& a, const GXT_VERSION_2_TKEY_item& b) { return a.Position < b.Position; });

					fseek(this->GXT_handle, 4, SEEK_CUR);

					unsigned long int TDAT_size;
					fread(&TDAT_size, 4, 1, this->GXT_handle);

					char* pTDAT = new char[TDAT_size];
					fread(pTDAT, 1, TDAT_size, this->GXT_handle);

					for (unsigned int j = 0; j < NumberOfEntries; j++)
					{
						const char* Text = pTDAT + pKeys[j].Position;

						tableInfo.Entries.push_back(tableInfo.ConstructGXT_entry(pKeys[j].KeyHash));

						SetOriginalTextByGxtText(&tableInfo.Entries.back(), Text);
					}

					delete[] pKeys;
					delete[] pTDAT;
				}
				else
				{
					NumberOfEntries /= sizeof(GXT_VERSION_1_TKEY_item);

					GXT_VERSION_1_TKEY_item* pKeys = new GXT_VERSION_1_TKEY_item[NumberOfEntries];

					fread(pKeys, sizeof(GXT_VERSION_1_TKEY_item), NumberOfEntries, this->GXT_handle);

					sort(pKeys, pKeys + NumberOfEntries,
						[](GXT_VERSION_1_TKEY_item a, GXT_VERSION_1_TKEY_item b) { return a.Position < b.Position; });

					fseek(this->GXT_handle, 4, SEEK_CUR);

					unsigned long int TDAT_size;
					fread(&TDAT_size, 4, 1, this->GXT_handle);

					char* pTDAT = new char[TDAT_size];
					fread(pTDAT, 1, TDAT_size, this->GXT_handle);

					for (unsigned int j = 0; j < NumberOfEntries; j++)
					{
						const char* Text = pTDAT + pKeys[j].Position;

						tableInfo.Entries.push_back(tableInfo.ConstructGXT_entry(pKeys[j].KeyName));
						SetOriginalTextByGxtText(&tableInfo.Entries.back(), Text);
					}

					delete[] pKeys;
					delete[] pTDAT;
				}
			};


			if (!this->VersionSupportsMultipleTables(this->GameTextVersion))
				AddTable("MAIN");
			else
			{
				if (!fread(&identifier, 4, 1, this->GXT_handle) || identifier != 'LBAT')
					goto error;

				unsigned int NumberOfTables;

				fread(&NumberOfTables, 4, 1, this->GXT_handle);
				NumberOfTables /= sizeof(GXT_TABL_item);

				GXT_TABL_item* pTables = new GXT_TABL_item[NumberOfTables];

				if (!fread(pTables, NumberOfTables*sizeof(GXT_TABL_item), 1, this->GXT_handle))
				{
					delete[] pTables;
					goto error;
				}

				for (unsigned int i = 0; i < NumberOfTables; i++)
				{
					fseek(this->GXT_handle, i ? pTables[i].Position + 8 : pTables[i].Position, SEEK_SET);

					if (!fread(&identifier, 4, 1, this->GXT_handle) || identifier != 'YEKT')
					{
						delete[] pTables;
						goto error;
					}

					AddTable(pTables[i].TableName);
				}

				delete[] pTables;

				return true;
			}
		}

	error:
		this->CloseGXTfile();
		return false;
	}
}

// Creates new GXT file
bool CGameText::CreateGXTfile(const char* gxtFilePath, eGameTextVersion gameTextVersion)
{
	this -> CloseGXTfile();
	this -> GXT_tables.clear();

	eGameTextBaseFormat BaseFormat = this->GXTformatProperties[gameTextVersion].BaseFormat;

	if (BaseFormat == GAME_TEXT_BASE_FORMAT_GXT)
	{
		if (this->GXT_handle = fopen(gxtFilePath, "wb+"))
			return false;
	}
	else if (BaseFormat == GAME_TEXT_BASE_FORMAT_IMG)
	{
		if (!this->IMG_archive.CreateArchive(gxtFilePath, IMG_VERSION_1))
			return false;
	}
	else
		return false;

	this->GameTextVersion = gameTextVersion;

	if(this->GXTformatProperties[gameTextVersion].bNeedsMAINtable)
		this->CreateGxtTable("MAIN");

	return this->SaveGXTfile(NULL, 200);
}

// Closes handle of GXT file
void CGameText::CloseGXTfile()
{
	if(this -> GXT_handle)
		fclose(this -> GXT_handle);

	this->IMG_archive.CloseArchive();
}

// Returns GXT string by original string, replaced characters to GXT equivalents
std::wstring CGameText::GetGxtStringByOriginalString(const wchar_t* OriginalText)
{
	wstring GxtText;
	const wchar_t* OriginalTextEnd = OriginalText + wcslen(OriginalText);

	while(OriginalText < OriginalTextEnd)
	{
		auto CharacterTo = find_if(this -> CharacterMap.begin(), this -> CharacterMap.end(),
			[&](CharacterReplacement Replacement) -> bool {
				if((OriginalTextEnd - OriginalText) >= Replacement.From.length() && memcmp(OriginalText, Replacement.From.c_str(), Replacement.From.length()) == 0)
					return true;
				else
					return false;
		});

		if(CharacterTo != this -> CharacterMap.end())
		{
			GxtText += CharacterTo->To;
			OriginalText += CharacterTo->From.length();
		}
		else
			GxtText += *OriginalText++;
	}

	return GxtText;
}

// Exports GXT file
// gxtFilePath has to be NULL if no new file should be created
bool CGameText::SaveGXTfile(const char* gxtFilePath, size_t MemoryBufferSize)
{
	eGameTextVersion gameTextVersion = this->GameTextVersion;
	eGameTextBaseFormat BaseFormat = this->GXTformatProperties[gameTextVersion].BaseFormat;

	if (BaseFormat == GAME_TEXT_BASE_FORMAT_GXT)
	{
		FILE* fp;

		if (gxtFilePath)
		{
			fp = fopen(gxtFilePath, "wb");

			if (!fp)
				return false;
		}
		else
		{
			fp = this->GXT_handle;
			fseek(fp, 0, SEEK_SET);
			int filedes = _fileno(fp);
			int result = _chsize_s(filedes, 0);
		}

		char* newGXTbuffer = new char[MemoryBufferSize];

		GMemFile newGXTfile;
		newGXTfile.Open(newGXTbuffer, 0, MemoryBufferSize);

		switch (gameTextVersion)
		{
		case GXT_VERSION_GTA2_UTF16:
		{
			newGXTfile.Write(this->GameTextLanguage, 4);
			unsigned short int x = 100;
			newGXTfile.Write(&x, 2);
			break;
		}

		case GXT_VERSION_GTASA_ASCII:
		case GXT_VERSION_GTAIV_ASCII:
			newGXTfile.Write(&this->HEADER_ASCII, 4);
			break;
		case GXT_VERSION_GTASA_UTF16:
		case GXT_VERSION_GTAIV_UTF16:
			newGXTfile.Write(&this->HEADER_UTF16, 4);
			break;
		}

		// Writes table to outputted GXT file
		// Returned is offset of table
		auto AddTable = [&, this](std::deque<GXT_tableInfo>::iterator tableIterator, bool writeTableName, bool shouldTDATbeAlligned) -> unsigned long int
		{
			GXT_tableInfo& table = *tableIterator;

			size_t tableOffset = newGXTfile.Tell();

			if (writeTableName)
				newGXTfile.Write(table.TableName, sizeof(table.TableName));

			newGXTfile.Write("TKEY", 4);

			unsigned __int32 NumberOfEntries = table.Entries.size();

			unsigned __int32 TKEY_blockSize;

			unsigned long int TDAT_BlockOffset;

			size_t* TDAT_blockSize;

			DWORD zero = 0;

			const int TDAT_alignTo = 4;
			char TDAT_alignBuffer[TDAT_alignTo];
			memset(TDAT_alignBuffer, NULL, TDAT_alignTo);

			// Returns pointer to TKEY block
			auto ReserveSpacePastTheTKEY = [&]()
			{
				newGXTfile.Write(&TKEY_blockSize, 4);

				void* pTKEYblock = newGXTfile.GetCurPtr();
				newGXTfile.Write(pTKEYblock, TKEY_blockSize);

				newGXTfile.Write("TDAT", 4);
				return pTKEYblock;
			};

			// Writes TDAT item
			auto WriteTDATitem = [&](GXT_entry& entry)
			{
				unsigned long int Beginning = (unsigned long int)newGXTfile.Tell() - TDAT_BlockOffset;

				if (this->VersionIsUnicodeUsed(gameTextVersion))
				{
					wstring GxtTextUTF16 = entry.GetGxtStringByOriginalString();
					newGXTfile.Write(GxtTextUTF16.c_str(), (GxtTextUTF16.length() + 1) * sizeof(wchar_t));
				}
				else
				{
					wstring GxtTextUTF16 = entry.GetGxtStringByOriginalString();
					string GxtTextASCII(GxtTextUTF16.begin(), GxtTextUTF16.end());
					newGXTfile.Write(GxtTextASCII.c_str(), GxtTextASCII.length() + 1);
				}

				return Beginning;
			};

			if (this->VersionGetTKEYversion(gameTextVersion) == 2)
			{
				TKEY_blockSize = NumberOfEntries * sizeof(GXT_VERSION_2_TKEY_item);

				GXT_VERSION_2_TKEY_item* pTKEYblock = (GXT_VERSION_2_TKEY_item*)ReserveSpacePastTheTKEY();

				TDAT_blockSize = (size_t*)newGXTfile.GetCurPtr();

				newGXTfile.Write(&zero, 4);

				TDAT_BlockOffset = (unsigned long int)newGXTfile.Tell();

				for (unsigned int entry_i = 0; entry_i < table.Entries.size(); entry_i++)
				{
					pTKEYblock[entry_i].Position = WriteTDATitem(table.Entries.begin()[entry_i]);
					pTKEYblock[entry_i].KeyHash = table.Entries.begin()[entry_i].KeyHash;
				}

				sort(pTKEYblock, pTKEYblock + NumberOfEntries,
					[](GXT_VERSION_2_TKEY_item a, GXT_VERSION_2_TKEY_item b) { return a.KeyHash < b.KeyHash; });
			}
			else
			{
				TKEY_blockSize = NumberOfEntries * sizeof(GXT_VERSION_1_TKEY_item);

				GXT_VERSION_1_TKEY_item* pTKEYblock = (GXT_VERSION_1_TKEY_item*)ReserveSpacePastTheTKEY();

				TDAT_blockSize = (size_t*)newGXTfile.GetCurPtr();

				newGXTfile.Write(&zero, 4);

				TDAT_BlockOffset = (unsigned long int)newGXTfile.Tell();

				for (unsigned int entry_i = 0; entry_i < table.Entries.size(); entry_i++)
				{
					pTKEYblock[entry_i].Position = WriteTDATitem(table.Entries.begin()[entry_i]);

					memcpy(pTKEYblock[entry_i].KeyName, table.Entries.begin()[entry_i].KeyName, sizeof(pTKEYblock[entry_i].KeyName));
				}

				sort(pTKEYblock, pTKEYblock + NumberOfEntries,
					[](GXT_VERSION_1_TKEY_item a, GXT_VERSION_1_TKEY_item b) { return strcmp(a.KeyName, b.KeyName) < 0; });
			}

			if (tableIterator == this->GXT_tables.begin())
			{
				GXT_entry w = table.ConstructGXT_entry();
				w.SetOriginalText("C++ GXT class 1.1 by fastman92");

				WriteTDATitem(w);
			}

			size_t d = newGXTfile.Tell() - TDAT_BlockOffset;

			if (shouldTDATbeAlligned)
			{
				size_t e = GET_ALIGNED_SIZE(d, TDAT_alignTo) - d;

				newGXTfile.Write(TDAT_alignBuffer, e);
			}

			*TDAT_blockSize = d;

			return tableOffset;
		};

		if (this->VersionSupportsMultipleTables(gameTextVersion))	// with tables
		{
			newGXTfile.Write("TABL", 4);

			size_t NumberOfTables = this->GXT_tables.size();

			size_t TABL_BlockSize = NumberOfTables * sizeof(GXT_TABL_item);
			newGXTfile.Write(&TABL_BlockSize, 4);
			unsigned long int TABL_offset = (unsigned long int)newGXTfile.Tell();

			GXT_TABL_item* pTables = (GXT_TABL_item*)newGXTfile.GetCurPtr();

			newGXTfile.Write(pTables, TABL_BlockSize);

			for (unsigned int tableID = 0; tableID < NumberOfTables; tableID++)
			{
				memset(pTables[tableID].TableName, NULL, sizeof(pTables[tableID].TableName));
				strncpy_s(pTables[tableID].TableName, this->GXT_tables[tableID].TableName, _TRUNCATE);

				pTables[tableID].Position = AddTable(this->GXT_tables.begin() + tableID, tableID != 0, tableID < NumberOfTables - 1);
			}
		}
		else 	// Without tables
		{
			if (this->GXT_tables.size() > 0)
				AddTable(this->GXT_tables.begin(), false, false);
		}

		fwrite(newGXTbuffer, newGXTfile.GetSize(), 1, fp);
		delete newGXTbuffer;

		if (gxtFilePath)
			fclose(fp);

		return true;
	}
	else if (BaseFormat == GAME_TEXT_BASE_FORMAT_IMG)
	{
		IMG* pArchive;

		if (gxtFilePath)
		{
			pArchive = new IMG;

			if (!pArchive->CreateArchive(gxtFilePath, IMG_VERSION_1))
			{
				delete pArchive;
				return false;
			}
		}
		else
		{
			pArchive = &this->IMG_archive;
			pArchive->RemoveAllFiles();
		}

		/////////////////////////////

		size_t tableFileMaxSize = 3145728;
		char* pTableBuffer = new char[tableFileMaxSize];
		GMemFile tableFile;
		tableFile.Open(pTableBuffer, 0, MemoryBufferSize);

		std::string entryStr;

		for (auto tableIt = this->GXT_tables.begin(); tableIt != this->GXT_tables.end(); ++tableIt)
		{
			tableFile.SetSize(0);
			tableFile.Seek(0, SEEK_SET);			
			
			unsigned int numberOfEntries = tableIt->Entries.size();

			tGXTbullyScholarschipEdition_tableHeader* pHeader;


			{
				tGXTbullyScholarschipEdition_tableHeader header;
				header.magicID = BullyScholarschipEdition_table_MAGIC_ID;
				header.version = 1;
				header.field_C = 0;
				header.field_18 = 2;
				header.field_1C = 0;
				header.numberOfKeys = numberOfEntries;
				header.sizeOfTKEYsection = numberOfEntries * sizeof(tGXTbullyScholarschipEdition_TKEY_item);
				header.BEorBD = 'DB';
				header.bShouldBeBE = false;

				pHeader = (tGXTbullyScholarschipEdition_tableHeader*)tableFile.GetCurPtr();
				tableFile.Write(&header, sizeof(header));
			}

			tGXTbullyScholarschipEdition_TKEY_item* pKeys = new tGXTbullyScholarschipEdition_TKEY_item[numberOfEntries];		
			
			unsigned int TDAToffset = tableFile.Tell();

			unsigned int entryID = 0;

			for (auto entryIt = tableIt->Entries.begin(); entryIt != tableIt->Entries.end(); ++entryIt)
			{
				entryStr = "\xFF\xFF";

				pKeys[entryID].KeyHash = entryIt->KeyHash;
				pKeys[entryID].Position = tableFile.Tell() - TDAToffset + 1;

				wstring GxtTextUTF16 = entryIt->GetGxtStringByOriginalString();
				string GxtTextASCII(GxtTextUTF16.begin(), GxtTextUTF16.end());

				entryStr.append(GxtTextASCII);

				tableFile.Writes4byteAlignedNULLterminatedString(entryStr.c_str());

				if (strlen(GxtTextASCII.c_str()) % 4 == 1)
				{
					DWORD zero = 0;
					tableFile.Write(&zero, sizeof(zero));
				}

				entryID++;
			}

			unsigned int TKEYoffset = tableFile.Tell();

			pHeader->tDATsectionSize = TKEYoffset - TDAToffset;

			sort(pKeys, pKeys + numberOfEntries,
				[](tGXTbullyScholarschipEdition_TKEY_item a, tGXTbullyScholarschipEdition_TKEY_item b) { return a.KeyHash < b.KeyHash; });

			tableFile.Write(pKeys, numberOfEntries * sizeof(tGXTbullyScholarschipEdition_TKEY_item));

			char filename[64];
			sprintf(filename, "%s.bin", tableIt->GetTableName());

			pArchive->AddFile(filename, pTableBuffer, tableFile.GetSize());
			
			/*
			{
				

				FILE* fp = fopen("table.bin", "wb");
				fwrite(pTableBuffer, tableFile.GetSize(), 1, fp);
				fclose(fp);
			}
			*/

			
		}

		pArchive->RebuildArchive();

		delete[] pTableBuffer;

		/////////////////////////////

		if (gxtFilePath)
			delete pArchive;

		return true;
	}
	else
		return false;
}

// Create GXT table
// Returns iterator of created table
CGameText::tTablesContainer::iterator CGameText::CreateGxtTable(const char* tableName)
{
	if(strlen(tableName) < sizeof(((GXT_tableInfo*)NULL) -> TableName) && !this -> TableExists(tableName))
	{
		auto it = this -> GXT_tables.insert(this -> FindSuitablePlaceToInsertTable(tableName), GXT_tableInfo(this));
		strcpy(it -> TableName, tableName);

		return it;
	}

	return this -> GXT_tables.end();
}

// Removes GXT table
void CGameText::RemoveGxtTable(const char* tableName)
{
	auto it = find_if(this -> GXT_tables.begin(), this -> GXT_tables.end(),
		[tableName](GXT_tableInfo table){return !strncmp(table.TableName, tableName, 7);
	});

	if(it != this -> GXT_tables.end())
		this -> GXT_tables.erase(it);
}

// Renames existing GXT table
CGameText::tTablesContainer::iterator CGameText::RenameGxtTable(CGameText::tTablesContainer::iterator oldTable, const char* newName)
{
	if(strlen(newName) < sizeof(((GXT_tableInfo*)NULL) -> TableName) && !this -> TableExists(newName))
	{
		GXT_tableInfo copy = *oldTable;
		this -> GXT_tables.erase(oldTable);

		strcpy(copy.TableName, newName);
		return this -> GXT_tables.insert(this -> FindSuitablePlaceToInsertTable(newName), copy);
	}
	else
		return this -> GXT_tables.end();
}

// Renames existing GXT table
bool CGameText::RenameGxtTable(const char* oldName, const char* newName)
{
	auto it = this -> GetTableIteratorByName(oldName);

	if(it != this -> GXT_tables.end())
		return this -> RenameGxtTable(it, newName) != this -> GXT_tables.end();
	else
		return false;
}

// Checks if table exists
bool CGameText::TableExists(const char* tableName)
{
	return this -> GetTableIteratorByName(tableName) != this -> GXT_tables.end();
}

// Returns table iterator by name
CGameText::tTablesContainer::iterator CGameText::GetTableIteratorByName(const char* tableName)
{
	return find_if(this -> GXT_tables.begin(), this -> GXT_tables.end(),
		[tableName](GXT_tableInfo table) { return strcmp(table.TableName, tableName) == 0; });
}

// Returns table iterator to the first table
CGameText::tTablesContainer::iterator CGameText::GetFirstTableIterator()
{
	return this -> GXT_tables.begin();
}

// Returns table iterator to the first table
CGameText::tTablesContainer::const_iterator CGameText::GetFirstTableIterator() const
{
	return this -> GXT_tables.begin();
}

// Returns table iterator to the end of table
CGameText::tTablesContainer::iterator CGameText::GetEndOfTableIterator()
{
	return this -> GXT_tables.end();
}

// Returns table iterator to the end of table
CGameText::tTablesContainer::const_iterator CGameText::GetEndOfTableIterator() const
{
	return this -> GXT_tables.end();
}

bool CGameText__ReadNativeTextFile(const char* filename, void* pUserData)
{
	CGameText* pGameText = (CGameText*)pUserData;

	const char* pExtension = strrchr(filename, '.');

	if (!pExtension)
		return false;

	int tableNameLen = pExtension - filename;

	FILE* fp = fopen(filename, "r, ccs=UTF-16LE");

	if (!fp)
		return false;

	pGameText->GXT_tables.push_back(CGameText::GXT_tableInfo(pGameText));
	CGameText::GXT_tableInfo& tableInfo = pGameText->GXT_tables.back();

	memcpy(tableInfo.TableName, filename, tableNameLen);
	tableInfo.TableName[tableNameLen] = NULL;
	
	wchar_t line[1024];

	char keyName[64];

	while (fgetws(line, _countof(line), fp))
	{
		wchar_t* iLine = FindFirstNonWhiteCharacter(line);

		if (*iLine != L'[')
			continue;

		wchar_t* pKeyName = iLine + 1;

		wchar_t* pKeyNameEnd = wcschr(pKeyName, L']');

		if (!pKeyNameEnd)
			continue;

		int keyNameLen = pKeyNameEnd - pKeyName;

		for (int i = 0; i < keyNameLen; i++)
			keyName[i] = (char)pKeyName[i];

		keyName[keyNameLen] = NULL;

		if (!fgetws(line, _countof(line), fp))
			break;

		wchar_t* pText = line;

		TrimRight(pText);

		tableInfo.Entries.push_back(tableInfo.ConstructGXT_entry(keyName));
		tableInfo.Entries.back().SetOriginalText(pText);
	}

	return false;
}

// Reads native R* game text files
// Directory must exist
bool CGameText::ReadNativeTextFiles(const char* directoryPath)
{
	this->GXT_tables.clear();

	return BrowseDirectory(
		directoryPath,
		&CGameText__ReadNativeTextFile,
		this
		);
}

// Write native R* game text files
// Directory must exist
bool CGameText::WriteNativeTextFiles(const char* directoryPath)
{
	char oldPath[_MAX_PATH+1];
	GetCurrentDirectoryA(_countof(oldPath)-1, oldPath);
	

	if(SetCurrentDirectoryA(directoryPath))
	{
		wstring entryKeyName;

		for(auto table = this -> GXT_tables.begin(); table < this -> GXT_tables.end(); table++)
		{
			char Filename[sizeof(table -> TableName)+4];

			strncpy_s(Filename, table -> TableName, sizeof(table->TableName)-1);

			strcat(Filename, ".txt");

			if(FILE* outfile = fopen(Filename, "w, ccs=UTF-16LE"))
			{
				size_t l = strlen(table -> TableName);

				wstring TableNameUnicode = wstring(table -> TableName, table -> TableName + l);

				fwprintf(outfile, L"{%ls table, generated from GXT class created by fastman92 }", TableNameUnicode.c_str());

				for(auto entry = table -> Entries.begin(); entry < table -> Entries.end(); entry++)
				{
					fwprintf(outfile, L"\n\n[");
					
					size_t m = strlen(entry -> KeyName);

					entryKeyName = wstring(entry->KeyName, entry->KeyName + m);

					fwrite(entryKeyName.c_str(), sizeof(wchar_t), m, outfile);
					

					fwprintf(outfile, L"]\n");

					fwrite(entry -> OriginalText.c_str(), sizeof(wchar_t), entry -> OriginalText.length(), outfile);
					
				}

			}
		}

		SetCurrentDirectoryA(oldPath);
		return true;
	}
	
	return false;
}

// Outputs list of entries to TXT file
void CGameText::DebugEntries(const char* filename)
{
	ofstream outfile;
	outfile.open(filename);

	if(outfile.is_open())
	{
		outfile << "Debug file of GXT class" << endl

			<< "Table names (" << this -> GXT_tables.size() << ") and number of entries:" << endl;

		for(auto& table = this -> GXT_tables.begin(); table < this -> GXT_tables.end(); table++)
			outfile << endl << table -> TableName << " ( " << table -> Entries.size() << " )";

		outfile << endl << setiosflags(ios::fixed) << setprecision(2) << hex;

		for(auto& table = this -> GXT_tables.begin(); table < this -> GXT_tables.end(); table++)
		{
			outfile << endl << "[" << table -> TableName << "]";

			for(auto& entry = table -> Entries.begin(); entry < table -> Entries.end(); entry++)
			{
				string Text = string(entry -> OriginalText.begin(), entry -> OriginalText.end());
				outfile << endl << endl << entry -> KeyHash << endl << entry -> KeyName << endl << Text.c_str();
			}
		}

		outfile.close();
	}

	cout << endl << "Character map count: " << this -> CharacterMap.size();

	for(auto it = this -> CharacterMap.begin(); it < this -> CharacterMap.end(); it++)
		wcout << endl << it - this -> CharacterMap.begin() << ". To: " << (int) it -> To << " From: " << it -> From.c_str();
}

// Returns iterator where new table name may be inserted alphabetically
std::deque<CGameText::GXT_tableInfo>::iterator CGameText::FindSuitablePlaceToInsertTable(const char* tableName)
{
	if(!strcmp(tableName, "MAIN"))
		return this -> GXT_tables.begin();
	else
	{
		std::deque<GXT_tableInfo>::iterator beginningOfSearch;

		if(this -> GXT_tables.size() > 0 && !strcmp(this -> GXT_tables.front().TableName, "MAIN"))
			beginningOfSearch = this -> GXT_tables.begin() + 1;
		else
			beginningOfSearch = this -> GXT_tables.begin();

		return find_if(
			beginningOfSearch,
			this -> GXT_tables.end(),
			[tableName](GXT_tableInfo& table) { return strcmp(table.TableName, tableName) > 0; }
		);
	}
}

// Returns true/false depending on whether an argument value is valid character for GXT key name.
bool CGameText::isValidGXTkeyNameChar(char KeyNameChar)
{
	return		KeyNameChar == '_' 
			||	KeyNameChar == '@'
			||	(KeyNameChar >= '0' && KeyNameChar <= '9')
			||	(KeyNameChar >= 'A' && KeyNameChar <= 'Z')
			||	(KeyNameChar >= 'a' && KeyNameChar <= 'z');
}

// Returns boolean depending on whether current version supports tables
bool CGameText::VersionSupportsMultipleTables(eGameTextVersion version)
{
	return this -> GXTformatProperties[version].SupportsTables;
}

// Returns boolean depending on whether unicode is used for current game text version.
bool CGameText::VersionIsUnicodeUsed(eGameTextVersion version)
{
	return this -> GXTformatProperties[version].IsUTF16used;
}

// Gets version (1 or 2) of TKEY
int CGameText::VersionGetTKEYversion(eGameTextVersion version)
{
	return this -> GXTformatProperties[version].TKEY_version;
}