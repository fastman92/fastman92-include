#pragma once
#include "elf.h"
#include "CDyn.h"
#include "CHeader.h"
#include "CPhdr.h"
#include "CRel.h"
#include "CShdr.h"
#include "CSym.h"
#include <vector>
#include <ptr_vector.h>

#define GET_ALIGNED_SIZE(requested_size, block_size) ((requested_size) % (block_size) == 0 ? (requested_size) : (((requested_size) / (block_size))+1)*(block_size))

namespace ELF_format {
	unsigned long elf_hash(const char *name);

	class CHashTable
	{
	public:
		uint32_t nbucket;
		uint32_t nchain;
		uint32_t* bucket;
		uint32_t* chain;

		CHashTable();
		~CHashTable();

		// Computes total size of table
		size_t ComputeTotalSize();
	};

	typedef void(*tProcessFileOffset)(uint64_t* pAddress, uint64_t* pSize, void* pUserData);

	class CELFmanager
	{
		eValueEncoding valueEncoding;

	public:
		CHeader header;
		stdx::ptr_vector<CDyn> dynamic_table;
		stdx::ptr_vector<CPhdr> program_header_table;
		stdx::ptr_vector<CShdr> section_header_table;
		char* pStringSectionData;
		stdx::ptr_vector<CSym> dynamic_symbol_table;
		stdx::ptr_vector<CRel> rel_plt_table;

	public:
		// Constructor
		CELFmanager();

		// Deconstructor
		~CELFmanager();

		// Loads a file
		bool Load(const char* filename);

		// Saves a new file
		bool Save(const char* filename);

		// Updates file offsets
		void UpdateFileOffsets();

		// Returns value encoding
		eValueEncoding GetValueEncoding() { return this->valueEncoding; }

		// Returns offset to end of file
		uint64_t GetOffsetToEndOfFile();

		// Reads a part of memory from segment
		bool ReadPartOfMemoryFromSegment(uint64_t address, uint64_t size, void* pMemory);

		// Returns a pointer to memory from segment
		void* GetPointerToPartOfMemoryFromSegment(uint64_t address, uint64_t size);

		// Returns offset to end of memory
		uint64_t GetOffsetToEndOfMemory();

		// Returns the size of phdr entry
		uint32_t GetSizeOfShdr();

		// Returns the size of dyn entry
		uint32_t GetSizeOfDyn();

		// Returns iterator to section by address
		stdx::ptr_vector<CShdr>::iterator FindSectionByAddress(uint32_t address);

		// Returns iterator to first section with specified type 
		stdx::ptr_vector<CShdr>::iterator FindFirstSectionWithType(uint32_t sh_type);

		// Returns iterator to first section with specified type 
		stdx::ptr_vector<CShdr>::iterator FindFirstSectionWithName(const char* name);

		// Returns iterator to first program segment with specified type 
		stdx::ptr_vector<CPhdr>::iterator FindFirstProgramSegmentWithType(uint32_t p_type);

		// Returns iterator to first dynamic table entry with specified tpye
		stdx::ptr_vector<CDyn>::iterator FindFirstEntryInDynamicTableWithTag(int64_t d_tag);

		// Writes relative structure depending on class
		void WriteJumpSlotRelocationDependingOnClass(void* toBeModified, Elf64_Addr offset, Elf64_Word symbol)
		{
			eValueEncoding valueEncoding = this->GetValueEncoding();
			unsigned char Class = this->header.e_ident[EI_CLASS];

			uint16_t Machine = this->header.e_machine;

			unsigned int SlotType;

			if (Class == ELFCLASS32)
			{
				if (Machine == EM_ARM)
					SlotType = 22;	// R_ARM_JUMP_SLOT
				else if (Machine == EM_386)
					SlotType = 7;
				else
					throw;

				elf32_rel_variedEncoding* pToBeModified = (elf32_rel_variedEncoding*)toBeModified;
				pToBeModified->r_offset.SetValue(offset, valueEncoding);
				pToBeModified->r_info.SetValue(ELF32_R_INFO(symbol, SlotType), valueEncoding);
			}
			else if (Class == ELFCLASS64)
			{
				if (Machine == EM_AARCH64)
					SlotType = 1026; /* R_AARCH64_JUMP_SLOT */
				else if (Machine == EM_X86_64)
					SlotType = 7;
				else
					throw;

				elf32_rel_variedEncoding* pToBeModified = (elf32_rel_variedEncoding*)toBeModified;
				pToBeModified->r_offset.SetValue(offset, valueEncoding);
				pToBeModified->r_info.SetValue(ELF64_R_INFO(symbol, SlotType), valueEncoding);
			}
		}
		
		// Returns number of buckets for dynamic symbol hash table
		unsigned int GetNumberOfBucketsForDynamicSymbolHashTable(unsigned int numberOfSymbols);

		// Builds dynamic symbol hash table
		void BuildDynamicSymbolHashTable(
			CHashTable* pHashTable, 
			const char* strPtr
		);

		// Writes hash table to memory
		void WriteHashTableToMemory(CHashTable* pHashTable, const void* ptr);

		// Returns pointer size
		unsigned int GetPointerSize()
		{
			unsigned char Class = this->header.e_ident[EI_CLASS];

			if (Class == ELFCLASS32)
				return 4;
			else if (Class == ELFCLASS64)
				return 8;
			else
				return 0;
		}


	private:
		// Reads ELF headers
		template<class phdrType, class dynType> bool ReadProgramSegmentHeaders(FILE* fp);

		// Writes ELF program segments
		template<class phdrType, class dynType> bool WriteProgramSegmentHeaders(FILE* fp);

		// Reads section headers headers
		template<class T> bool ReadSectionHeaders(FILE* fp);

		// Writes section headers headers
		template<class T> bool WriteSectionHeaders(FILE* fp);

		// Reads dynamic symbols
		template<class T> bool ReadDynamicSymbols();

		// Writes dynamic symbols
		template<class T> bool WriteDynamicSymbols();

		// Reads .rel.pltr
		template<class T> bool ReadPltRelocations();

		// Write .rel.pltr
		template<class T> bool WritePltRelocations();

		// Processes file offsets
		void ProcessFileOffsets(tProcessFileOffset func, void* pUserData);

	public:
		// Removes file bytes from segment
		void RemoveFileBytesFromSegment(uint64_t address, uint64_t size);
	};
}