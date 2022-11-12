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

#include "../IMG/IMG.h"

#include <deque>
#include <Windows.h>

#define GET_ALIGNED_SIZE(requested_size, block_size) (requested_size % block_size == 0 ? requested_size : ((requested_size / block_size)+1)*block_size)
#define GET_ALIGNED_SIZE_IN_BLOCKS(requested_size, block_size) (requested_size % block_size == 0 ? requested_size / block_size : (requested_size / block_size) + 1)


#pragma pack(push, 1)
struct GXT_TABL_item
{
	char TableName[8];
	unsigned long int Position;		// absolute position
};
#pragma pack(pop)

#pragma pack(push, 1)
struct tGXTbullyScholarschipEdition_tableHeader
{
	DWORD magicID;	// always 0xABCD1234
	DWORD version;	// always 1
	DWORD field_C;	// seems to be always 0
	DWORD tDATsectionSize;
	DWORD sizeOfTKEYsection;
	DWORD numberOfKeys;
	DWORD field_18;	// seems to be always 2
	DWORD field_1C;	// seems to be always 0
	DWORD BEorBD;
	DWORD bShouldBeBE;
};

VALIDATE_SIZE(tGXTbullyScholarschipEdition_tableHeader, 0x28);

#pragma pack(push, 1)
struct tGXTbullyScholarschipEdition_TKEY_item
{
	unsigned long int KeyHash;
	unsigned long int Position;		// TDAT + 1 offset	
};
#pragma pack(pop)

VALIDATE_SIZE(tGXTbullyScholarschipEdition_TKEY_item, 8);

#pragma pack(push, 1)
struct GXT_VERSION_1_TKEY_item
{
	unsigned long int Position;		// TDAT + 8 offset
	char KeyName[8];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct GXT_VERSION_2_TKEY_item
{
	unsigned long int Position;		// TDAT + 8 offset
	unsigned long int KeyHash;
};
#pragma pack(pop)

enum eGameTextBaseFormat
{
	GAME_TEXT_BASE_FORMAT_GXT,
	GAME_TEXT_BASE_FORMAT_IMG,
	GAME_TEXT_BASE_FORMAT_RPF
};

enum eGameTextSuggestionVersion
{
	SUGGESTION_UNDEFINED,
	SUGGESTION_GTASA = 0,
	SUGGESTION_GTAIV,
	SUGGESTION_BULLY_SCHOLARSCHIP_EDITION
};

enum eGameTextVersion
{
	GXT_VERSION_UNDEFINED,

	GXT_VERSION_GTA2_UTF16,
	GXT_VERSION_GTAIII_UTF16,
	GXT_VERSION_GTAVC_UTF16,

	GXT_VERSION_GTASA_ASCII,
	GXT_VERSION_GTASA_UTF16,

	GXT_VERSION_GTAIV_ASCII,
	GXT_VERSION_GTAIV_UTF16,

	// GXT_VERSION_GTAV_ASCII,

	GXT_VERSION_BULLY_SCHOLARSCHIP_EDITION,

	GXT_VERSION_MAX
};

class CGameText
{
	friend bool CGameText__ReadNativeTextFile(const char* filename, void* pUserData);

private:
	static const int GXT_keyName_size = 32;

	static const unsigned int BullyScholarschipEdition_table_MAGIC_ID = 0xABCD1234;

public:
	class GXT_entry
	{
		friend CGameText;

	private:
		// Make inaccessible constructor, you should always use GXT::GXT_tableInfo::ConstructGXT_entry instead!
		GXT_entry() {};

		CGameText* GXT_instance;

		char KeyName[GXT_keyName_size];
		unsigned __int32 KeyHash;

	public:
		std::wstring OriginalText;

		// Gets key name
		const char* GetKeyName() { return this->KeyName; }

		// Gets key hash
		unsigned long int GetKeyHash() { return this->KeyHash; }

		// Sets key name
		void SetKeyName(const char* KeyName);

		// Returns GXT string by original string, replaced characters to GXT equivalents
		std::wstring GetGxtStringByOriginalString() {
			return this->GXT_instance->GetGxtStringByOriginalString(this->OriginalText.c_str());
		};

		// Sets original text
		void SetOriginalText(const char* OriginalText);

		// Sets original text
		void SetOriginalText(const wchar_t* OriginalText) { this->OriginalText = OriginalText; };

		// Sets original text by GXT text
		template <typename typeChar>void SetOriginalTextByGxtText(const typeChar* GxtText)
		{
			this->OriginalText.clear();

			auto& CharacterMap = this->GXT_instance->CharacterMap;

			while (typeChar c = *GxtText)
			{
				auto CharacterFrom = find_if(CharacterMap.begin(), CharacterMap.end(),
					[c](CharacterReplacement& replacement) { return replacement.To == c; });

				if (CharacterFrom != CharacterMap.end())
					this->OriginalText += CharacterFrom->From;
				else
					this->OriginalText += c;

				GxtText++;
			}
		}
	};

	// Typed definition of entries container
	typedef std::deque<GXT_entry> tEntriesContainer;

	class GXT_tableInfo
	{
		friend CGameText;
		friend bool CGameText__ReadNativeTextFile(const char* filename, void* pUserData);

	private:
		CGameText* GXT_instance;

		// Name of table
		char TableName[32];

		GXT_tableInfo(CGameText* GXT_instance)
		{
			this->GXT_instance = GXT_instance;

			memset(this->TableName, NULL, sizeof(this->TableName));
		}

	public:
		// GXT entries
		tEntriesContainer Entries;

		const char* GetTableName()
		{
			return this->TableName;
		}

		// Constructor of GXT entry
		GXT_entry ConstructGXT_entry();

		// Constructor with key name
		GXT_entry ConstructGXT_entry(const char* KeyName);

		// Constructor with key hash
		GXT_entry ConstructGXT_entry(unsigned long int KeyHash);

		// Finds GXT entry by key name
		tEntriesContainer::iterator FindGXTentryByKeyName(const char* keyName);

		// Find entry by key name
		tEntriesContainer::iterator FindEntryByKeyHash(unsigned long int hash);

	};

	// Type definition of tables container
	typedef std::deque<GXT_tableInfo> tTablesContainer;

	static const unsigned int HEADER_ASCII = 0x080004;
	static const unsigned int HEADER_UTF16 = 0x100004;

	eGameTextVersion GameTextVersion;

	char GameTextLanguage[5];	// only available if GTA2 GXT is loaded.

	// Constructor
	CGameText();

	// Destructor
	~CGameText();

	// Parses string with escape characters such as "\r\n test"
	bool ReadStringWithEscapeChars(wchar_t*& Line, std::wstring& str);

	// Loads GXT pattern of letters from a file
	bool LoadGxtFontCharacterMap(const char* path);

	// Loads GXT keys text file containing possible GXT keys
	bool LoadGxtKeysTextFile(const char* path);

	// Loads GXT keys binary file (TDC) containing possible GXT keys
	bool LoadGxtKeysBinaryFile(const char* path);

	// Assign GXT keys from list to GXT keys in tables
	void AssignGxtKeysFromListToGxtKeysOfEntries();

	// Open GXT file
	// Suggestion is used in case GTA SA / GTA IV format
	bool OpenGXTfile(const char* gxtFilePath, eGameTextSuggestionVersion gxtFormatSuggestion);

	// Creates new GXT file
	bool CreateGXTfile(const char* gxtFilePath, eGameTextVersion gameTextVersion);

	/*
	// Open GXT file
	// Suggestion is used in case of creating GTA SA / GTA IV format
	bool OpenOrCreateGXTfile(const wchar_t* gxtFilePath, GXT::GXT_version gameTextVersion);
	*/
	// Closes handle of GXT file
	void CloseGXTfile();

	// Returns GXT string by original string, replaced characters to GXT equivalents
	std::wstring GetGxtStringByOriginalString(const wchar_t* OriginalText);

	// Exports GXT file
	// gxtFilePath has to be NULL if no new file should be created
	// gameTextVersion has to be GXT_VERSION_UNDEFINED if no new version should be used
	bool SaveGXTfile(const char* gxtFilePath = NULL, size_t MemoryBufferSize = 10485760 /* 10 MB */);

	// Create GXT table
	// Returns iterator of created table
	tTablesContainer::iterator CreateGxtTable(const char* tableName);

	// Removes GXT table
	void RemoveGxtTable(const char* tableName);

	// Renames existing GXT table
	tTablesContainer::iterator RenameGxtTable(tTablesContainer::iterator oldTable, const char* newName);

	// Renames existing GXT table
	bool RenameGxtTable(const char* oldName, const char* newName);

	// Checks if table exists
	bool TableExists(const char* tableName);

	// Returns number of tables
	tTablesContainer::size_type GetNumberOfTables() { return this->GXT_tables.size(); }

	// Returns table iterator by name
	tTablesContainer::iterator GetTableIteratorByName(const char* tableName);

	// Returns table iterator to the first table
	tTablesContainer::iterator GetFirstTableIterator();

	// Returns table iterator to the first table
	tTablesContainer::const_iterator GetFirstTableIterator() const;

	// Returns table iterator to the end of table
	tTablesContainer::iterator GetEndOfTableIterator();

	// Returns table iterator to the end of table
	tTablesContainer::const_iterator GetEndOfTableIterator() const;

	// Reads native R* game text files
	// Directory must exist
	bool ReadNativeTextFiles(const char* directoryPath);

	// Write native R* game text files
	// Directory must exist
	bool WriteNativeTextFiles(const char* directoryPath);

	// Outputs list of entries to TXT file
	void DebugEntries(const char* filename);

	struct GXTformatDescriptor
	{
		eGameTextBaseFormat BaseFormat;

		unsigned long(__cdecl *CRC32_function)(const char* string);

		bool IsUTF16used;

		bool SupportsTables;	// has TABL and tables?

		int TKEY_version;	// 1 or 2

		bool bNeedsMAINtable;
	};

private:
	// File handle of GXT file
	FILE* GXT_handle;

	// IMG archive handle
	IMG IMG_archive;

	// GXT tables
	tTablesContainer GXT_tables;

	struct GXTformatDescriptor GXTformatProperties[GXT_VERSION_MAX];

	struct GXT_keyHashName
	{
		unsigned long int KeyHash;
		char KeyName[GXT_keyName_size];

		GXT_keyHashName(unsigned long int keyHash, const char* keyName)
		{
			memcpy(this->KeyName, keyName, GXT_keyName_size);
			this->KeyHash = keyHash;
		};
	};

	std::deque<GXT_keyHashName> GXT_keyHashNames;

	struct CharacterReplacement
	{
		std::wstring From;	// for GxtText
		wchar_t To;		// for OriginalText

		// Standard constructor
		CharacterReplacement(std::wstring From, wchar_t To)
		{
			this->From = From;
			this->To = To;
		}
	};

	// GXT Character map
	std::deque<CharacterReplacement> CharacterMap;

	// Returns iterator where new table name may be inserted alphabetically
	std::deque<GXT_tableInfo>::iterator FindSuitablePlaceToInsertTable(const char* tableName);

	// Returns true/false depending on whether an argument value is valid character for GXT key name.
	static bool isValidGXTkeyNameChar(char KeyNameChar);

	// Returns boolean depending on whether current version supports tables
	bool VersionSupportsMultipleTables(eGameTextVersion version);

	// Returns boolean depending on whether unicode is used for current game text version.
	bool VersionIsUnicodeUsed(eGameTextVersion version);

	// Gets version (1 or 2) of TKEY
	int VersionGetTKEYversion(eGameTextVersion version);
};