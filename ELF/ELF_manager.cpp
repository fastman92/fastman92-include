#include <stdio.h>
#include "ELF_manager.h"
#include <string.h>

#pragma warning(disable:4244)

namespace ELF_format {
	unsigned long
		elf_hash(const char *name)
	{
		const unsigned char* nameUnsigned = (const unsigned char*)name;
		unsigned long h = 0, g;

		while (*nameUnsigned)
		{
			h = (h << 4) + *nameUnsigned++;
			if (g = h & 0xf0000000)
				h ^= g >> 24;
			h &= ~g;
		}
		return h;
	}

	CHashTable::CHashTable()
	{
		this->nbucket = 0;
		this->nchain = 0;
		this->bucket = 0;
		this->chain = 0;
	}
	CHashTable::~CHashTable()
	{
		if (this->bucket)
			delete[] this->bucket;

		if (this->chain)
			delete[] this->chain;
	}

	// Computes total size of table
	size_t CHashTable::ComputeTotalSize()
	{
		return (this->nbucket + this->nchain + 2) * sizeof(uint32_t);
	}

	// Reads ELF headers
	template<class phdrType, class dynType> bool CELFmanager::ReadProgramSegmentHeaders(FILE* fp)
	{
		fseek(fp, this->header.e_phoff, SEEK_SET);

		if (this->header.e_phentsize != sizeof(phdrType))
			return false;

		// read program headers
		phdrType program_segment;
		fseek(fp, this->header.e_phoff, SEEK_SET);

		for (unsigned int i = 0; i < this->header.e_phnum; i++)
		{
			fread(&program_segment, sizeof(program_segment), 1, fp);

			CPhdr* phr = new CPhdr();

			ReadProgramHeader(phr, program_segment, valueEncoding, fp);

			program_header_table.push_back(phr);
		}

		// interpret PT_DYNAMIC segment
		const dynType* pDyn_in_file;

		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			++it)
		{
			if (it->p_type != PT_DYNAMIC)
				continue;

			for (unsigned int i = 0; i < it->p_filesz / sizeof(dynType); i++)
			{
				CDyn* dyn = new CDyn();
				pDyn_in_file = (const dynType*)it->pFileData + i;

				ReadDynamicStruct(dyn, *pDyn_in_file, valueEncoding);
				this->dynamic_table.push_back(dyn);
			}

			delete[] it->pFileData;
			it->pFileData = NULL;

			break;
		}

		return true;
	}

	// Writes ELF program segments
	template<class phdrType, class dynType> bool CELFmanager::WriteProgramSegmentHeaders(FILE* fp)
	{
		if (this->header.e_phentsize != sizeof(phdrType))
			return false;

		// Write segment data
		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			it++)
		{
			if (!it->p_filesz || !it->pFileData)
				continue;

			fseek(fp, it->p_offset, SEEK_SET);
			fwrite(it->pFileData, it->p_filesz, 1, fp);
		}

		// Write section data, used by .comment section
		for (auto it = this->section_header_table.begin();
			it != this->section_header_table.end();
			it++)
		{
			if (!it->sh_size || !it->pFileData)
				continue;

			fseek(fp, it->sh_offset, SEEK_SET);
			fwrite(it->pFileData, it->sh_size, 1, fp);
		}

		// Write header structures
		phdrType program_segment;

		fseek(fp, this->header.e_phoff, SEEK_SET);

		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			it++)
		{
			WriteProgramHeader(program_segment, *it, valueEncoding);

			fwrite(&program_segment, sizeof(program_segment), 1, fp);
		}

		// Write DYNAMIC section
		auto it = this->FindFirstProgramSegmentWithType(PT_DYNAMIC);

		if (it != this->program_header_table.end())
		{
			fseek(fp, it->p_offset, SEEK_SET);

			dynType dynInFile;

			for (auto it = this->dynamic_table.begin(); it != this->dynamic_table.end(); it++)
			{
				WriteDynamicStruct(dynInFile, *it, valueEncoding);
				fwrite(&dynInFile, sizeof(dynInFile), 1, fp);
			}
		}

		return true;
	}

	// Reads section headers
	template<class T> bool CELFmanager::ReadSectionHeaders(FILE* fp)
	{
		fseek(fp, this->header.e_shoff, SEEK_SET);

		if (this->header.e_shentsize != sizeof(T))
			return false;

		T section_header;
		fseek(fp, this->header.e_shoff, SEEK_SET);

		for (unsigned int i = 0; i < this->header.e_shnum; i++)
		{
			fread(&section_header, sizeof(section_header), 1, fp);

			CShdr* shdr = new CShdr();

			ReadSectionHeader(shdr, section_header, valueEncoding, fp);
			section_header_table.push_back(shdr);
		}

		auto it = this->section_header_table.begin() + this->header.e_shstrndx;

		fseek(fp, it->sh_offset, SEEK_SET);
		this->pStringSectionData = new char[it->sh_size];
		fread(this->pStringSectionData, it->sh_size, 1, fp);

		return true;
	}

	// Writes section headers
	template<class T> bool CELFmanager::WriteSectionHeaders(FILE* fp)
	{
		fseek(fp, this->header.e_shoff, SEEK_SET);

		T section_header;

		for (auto it = this->section_header_table.begin();
			it != this->section_header_table.end();
			it++)
		{
			WriteSectionHeader(section_header, *it, valueEncoding);

			fwrite(&section_header, sizeof(section_header), 1, fp);
		}

		return true;
	}

	// Reads dynamic symbols
	template<class T> bool CELFmanager::ReadDynamicSymbols()
	{
		auto sectionDynsym = this->FindSectionByAddress(
			this->FindFirstEntryInDynamicTableWithTag(DT_SYMTAB)->d_un.d_ptr
		);

		void* pDynsymMemory = this->GetPointerToPartOfMemoryFromSegment(sectionDynsym->sh_addr, sectionDynsym->sh_size);		

		// auto sectionGnuVersion = this->FindFirstSectionWithType(SHT_GNU_versym);

		// this->FindFirstEntryInDynamicTableWithTag(DT_VERSYM)->d_un.d_ptr

		uint16_t* pGnuVersionMemory = GetPointerToGNUversionArray();
		
		unsigned int numberOfDynamicSymbols = sectionDynsym->sh_size / sectionDynsym->sh_entsize;
		
		////
		for (unsigned int symbolID = 0; symbolID < numberOfDynamicSymbols; symbolID++)
		{
			CSym* symbol = new CSym();
			symbol->gnu_version = 1;

			ReadDynamicSymbol(symbol,
				*(const T*)((char*)pDynsymMemory + symbolID * sectionDynsym->sh_entsize),
				valueEncoding
			);

			if(pGnuVersionMemory)
				symbol->gnu_version = pGnuVersionMemory[symbolID];

			this->dynamic_symbol_table.push_back(symbol);
		}

		return true;
	}

	// Returns pointer to GNU version array
	uint16_t* CELFmanager::GetPointerToGNUversionArray()
	{
		uint16_t* pGnuVersionMemory = nullptr;

		{
			auto verSymEntry = this->FindFirstEntryInDynamicTableWithTag(DT_VERSYM);

			if (verSymEntry != this->dynamic_table.end())
			{

				auto sectionGnuVersion = this->FindSectionByAddress(
					verSymEntry->d_un.d_ptr
				);

				pGnuVersionMemory = (uint16_t*)this->GetPointerToPartOfMemoryFromSegment(sectionGnuVersion->sh_addr, sectionGnuVersion->sh_size);
			}
		}

		return pGnuVersionMemory;
	}

	// Writes dynamic symbols
	template<class T> bool CELFmanager::WriteDynamicSymbols()
	{
#ifndef WRITE_DYNAMIC_SYMBOLS
		return true;
#endif

		auto sectionDynsym = this->FindSectionByAddress(
			this->FindFirstEntryInDynamicTableWithTag(DT_SYMTAB)->d_un.d_ptr
		);

		void* pDynsymMemory = this->GetPointerToPartOfMemoryFromSegment(sectionDynsym->sh_addr, sectionDynsym->sh_size);

		uint16_t* pGnuVersionMemory = GetPointerToGNUversionArray();
		
		unsigned int numberOfDynamicSymbols = this->dynamic_symbol_table.size();

		for (unsigned int symbolID = 0; symbolID < this->dynamic_symbol_table.size(); symbolID++)
		{
			auto& symbol = this->dynamic_symbol_table[symbolID];

			WriteDynamicSymbol(
				*(T*)((char*)pDynsymMemory + symbolID * sectionDynsym->sh_entsize),
				symbol,
				valueEncoding
			);

			if(pGnuVersionMemory)
				pGnuVersionMemory[symbolID] = symbol.gnu_version;
		}

		return true;
	}

	// Reads .rel.pltr
	template<class T> bool CELFmanager::ReadPltRelocations()
	{
		auto sectionPltRel = this->FindSectionByAddress(
			this->FindFirstEntryInDynamicTableWithTag(DT_JMPREL)->d_un.d_ptr
		);

		void* pltRelData = this->GetPointerToPartOfMemoryFromSegment(sectionPltRel->sh_addr, sectionPltRel->sh_size);

		unsigned int numberOfRelocations = sectionPltRel->sh_size / sectionPltRel->sh_entsize;

		////
		for (unsigned int ID = 0; ID < numberOfRelocations; ID++)
		{
			CRel* symbol = new CRel();

			ReadPltRelocation(symbol,
				*(const T*)((char*)pltRelData + ID * sectionPltRel->sh_entsize),
				valueEncoding
			);

			this->rel_plt_table.push_back(symbol);
		}

		return true;
	}

	// Write .rel.pltr
	template<class T> bool CELFmanager::WritePltRelocations()
	{
		auto sectionPltRel = this->FindSectionByAddress(
			this->FindFirstEntryInDynamicTableWithTag(DT_JMPREL)->d_un.d_ptr
		);

		void* pltRelData = this->GetPointerToPartOfMemoryFromSegment(sectionPltRel->sh_addr, sectionPltRel->sh_size);

		unsigned int numberOfRelocations = this->rel_plt_table.size();

		for (unsigned int ID = 0; ID < numberOfRelocations; ID++)
		{
			auto& reloc = this->rel_plt_table[ID];

			WritePltRelocation(
				*(T*)((char*)pltRelData + ID * sectionPltRel->sh_entsize),
				reloc,
				valueEncoding
			);
		}

		return true;
	}

	// Processes file offsets
	void CELFmanager::ProcessFileOffsets(tProcessFileOffset func, void* pUserData)
	{
		// uint64_t offset

		// uint64_t size = this->header.e_phentsize * this->header.e_phnum;

		// func(&this->header.e_phoff, NULL);

		// Program segments
		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			it++)
			func(&it->p_offset, &it->p_filesz, pUserData);

		// Sections
		for (auto it = this->section_header_table.begin();
			it != this->section_header_table.end();
			it++)
			func(&it->sh_offset, NULL, pUserData);
	}

	// Removes file bytes from segment
	void CELFmanager::RemoveFileBytesFromSegment(uint64_t address, uint64_t size)
	{
		struct tMyData
		{
			uint64_t address;
			uint64_t size;
		} myData;

		myData.address = address;
		myData.size = size;

		this->ProcessFileOffsets(
			[](uint64_t* pAddress, uint64_t* pSize, void* pUserData)
		{
			tMyData* pMyData = (tMyData*)pUserData;

			if (*pAddress > pMyData->address + pMyData->size)
			{
				*pAddress -= pMyData->size;
			}
		},
			&myData
			);
	}

	// Constructor
	CELFmanager::CELFmanager()
	{
		this->pStringSectionData = nullptr;
	}

	// Deconstructor
	CELFmanager::~CELFmanager()
	{
		delete[] this->pStringSectionData;
	}

	// Loads a file
	bool CELFmanager::Load(const char* filename)
	{
		unsigned char Class;
		unsigned char encodingInHeader;

		FILE* fp = fopen(filename, "rb");

		if (!fp)
			return false;

		if (!fread(this->header.e_ident, sizeof(this->header.e_ident), 1, fp))
			goto errorHappened;

		if (this->header.e_ident[EI_MAG0] != ELFMAG0
			|| this->header.e_ident[EI_MAG1] != ELFMAG1
			|| this->header.e_ident[EI_MAG2] != ELFMAG2
			|| this->header.e_ident[EI_MAG3] != ELFMAG3)
			goto errorHappened;

		encodingInHeader = this->header.e_ident[EI_DATA];

		if (encodingInHeader == ELFDATA2LSB)
			this->valueEncoding = VALUE_ENCODING_LITTLE_ENDIAN;
		else if (encodingInHeader == ELFDATA2MSB)
			this->valueEncoding = VALUE_ENCODING_BIG_ENDIAN;
		else
			goto errorHappened;

		fseek(fp, 0, SEEK_SET);

		Class = this->header.e_ident[EI_CLASS];

		if (Class == ELFCLASS32)
		{
			elf32_hdr_variedEncoding header;
			fread(&header, sizeof(header), 1, fp);

			ReadELFheader(this->header, header, valueEncoding);
		}
		else if (Class == ELFCLASS64)
		{
			elf64_hdr_variedEncoding header;
			fread(&header, sizeof(header), 1, fp);

			ReadELFheader(this->header, header, valueEncoding);
		}
		else
			goto errorHappened;

		// Program segment table
		if (this->header.e_phnum)
		{
			if (Class == ELFCLASS32)
			{
				if (!this->ReadProgramSegmentHeaders<
					elf32_phdr_variedEncoding,
					Elf32_Dyn_variedEncoding>(fp))
					goto errorHappened;
			}
			else if (Class == ELFCLASS64)
			{
				if (!this->ReadProgramSegmentHeaders<
					elf64_phdr_variedEncoding,
					Elf64_Dyn_variedEncoding>(fp))
					goto errorHappened;
			}
			else
				goto errorHappened;
		}

		// Section header table
		if (this->header.e_shnum)
		{
			if (Class == ELFCLASS32)
			{
				if (!this->ReadSectionHeaders<elf32_shdr_variedEncoding>(fp))
					goto errorHappened;
			}
			else if (Class == ELFCLASS64)
			{
				if (!this->ReadSectionHeaders<elf64_shdr_variedEncoding>(fp))
					goto errorHappened;
			}
			else
				goto errorHappened;
		}

		////////

		// Dynamic symbol table &  .rel.plt table
		if (Class == ELFCLASS32)
		{
			if (!this->ReadDynamicSymbols<elf32_sym_variedEncoding>()
				|| !this->ReadPltRelocations<elf32_rel_variedEncoding>())
				goto errorHappened;
		}
		else if (Class == ELFCLASS64)
		{
			if (!this->ReadDynamicSymbols<elf64_sym_variedEncoding>()
				|| !this->ReadPltRelocations<elf64_rel_variedEncoding>())
				goto errorHappened;
		}
		else
			goto errorHappened;

		fclose(fp);
		return true;

	errorHappened:
		fclose(fp);
		return false;
	}

	// Saves a new file
	bool CELFmanager::Save(const char* filename)
	{
		this->header.e_phnum = this->program_header_table.size();
		this->header.e_shnum = this->section_header_table.size();

		FILE* fp = fopen(filename, "wb");

		if (!fp)
			return false;

		unsigned char Class = this->header.e_ident[EI_CLASS];

		// Fixes dynamic symbol table
		if (Class == ELFCLASS32)
		{
			if (!this->WriteDynamicSymbols<elf32_sym_variedEncoding>()
				|| !this->WritePltRelocations<elf32_rel_variedEncoding>())
				goto errorHappened;
		}
		else if (Class == ELFCLASS64)
		{
			if (!this->WriteDynamicSymbols<elf64_sym_variedEncoding>()
				|| !this->WritePltRelocations<elf64_rel_variedEncoding>())
				goto errorHappened;
		}


		///////////////

		// Write program segments
		if (Class == ELFCLASS32)
		{
			if (!this->WriteProgramSegmentHeaders<elf32_phdr_variedEncoding, Elf32_Dyn_variedEncoding>(fp))
				goto errorHappened;
		}
		else if (Class == ELFCLASS64)
		{
			if (!this->WriteProgramSegmentHeaders<elf64_phdr_variedEncoding, Elf64_Dyn_variedEncoding>(fp))
				goto errorHappened;
		}

		// Write strings
		{
			auto it = this->section_header_table.begin() + this->header.e_shstrndx;

			fseek(fp, it->sh_offset, SEEK_SET);
			fwrite(this->pStringSectionData, it->sh_size, 1, fp);
		}

		// Write sections
		if (Class == ELFCLASS32)
		{
			if (!this->WriteSectionHeaders<elf32_shdr_variedEncoding>(fp))
				goto errorHappened;
		}
		else if (Class == ELFCLASS64)
		{
			if (!this->WriteSectionHeaders<elf64_shdr_variedEncoding>(fp))
				goto errorHappened;
		}

		// Write header
		fseek(fp, 0, SEEK_SET);

		if (Class == ELFCLASS32)
		{
			elf32_hdr_variedEncoding header;
			WriteELFheader(header, this->header, valueEncoding);
			fwrite(&header, sizeof(header), 1, fp);
		}
		else if (Class == ELFCLASS64)
		{
			elf64_hdr_variedEncoding header;
			WriteELFheader(header, this->header, valueEncoding);
			fwrite(&header, sizeof(header), 1, fp);
		}

		fclose(fp);
		return true;

	errorHappened:
		fclose(fp);
		return false;
	}

	// Updates file offsets
	void CELFmanager::UpdateFileOffsets()
	{
		// this->ProcessFileOffsets(NULL);
	}

	// Returns offset to end of file
	uint64_t CELFmanager::GetOffsetToEndOfFile()
	{
		uint64_t offset = this->header.e_ehsize;

		// Program segments
		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			it++)
		{
			if (!it->p_filesz)
				continue;

			if (it->p_offset + it->p_filesz > offset)
				offset = it->p_offset + it->p_filesz;
		}

		uint64_t sectionEnd = this->header.e_shoff + this->header.e_shnum * this->header.e_shentsize;

		if (sectionEnd > offset)
			offset = sectionEnd;

		// Sections
		auto it = this->section_header_table.begin() + this->header.e_shstrndx;

		if (it->sh_offset + it->sh_size > offset)
			offset = it->sh_offset + it->sh_size;

		return offset;
	}

	// Reads a part of memory from segment
	bool CELFmanager::ReadPartOfMemoryFromSegment(uint64_t address, uint64_t size, void* pMemory)
	{
		void* memoryFromFile = this->GetPointerToPartOfMemoryFromSegment(address, size);

		if (pMemory)
		{
			memcpy(pMemory, memoryFromFile, size);
			return true;
		}
		else
			return false;
	}

	// Returns a pointer to memory from segment
	void* CELFmanager::GetPointerToPartOfMemoryFromSegment(uint64_t address, uint64_t size)
	{
		int i = 0;

		void* result = nullptr;

		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			it++)
		{
			if (address >= it->p_vaddr && address < it->p_vaddr + it->p_filesz)
			{
				if (address + size <= it->p_vaddr + it->p_filesz)
					result = &it->pFileData[address - it->p_vaddr];
				else
					return 0;
			}

			i++;
		}

		return result;
	}

	// Returns offset to end of memory
	uint64_t CELFmanager::GetOffsetToEndOfMemory()
	{
		uint64_t offset = this->header.e_ehsize;

		// Program segments
		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			it++)
		{
			if (it->p_vaddr + it->p_memsz > offset)
				offset = it->p_vaddr + it->p_memsz;
		}

		return offset;
	}

	// Returns the size of phdr entry
	uint32_t CELFmanager::GetSizeOfShdr()
	{
		unsigned char Class = this->header.e_ident[EI_CLASS];

		if (Class == ELFCLASS32)
			return sizeof(elf32_shdr_variedEncoding);
		else if (Class == ELFCLASS64)
			return sizeof(elf64_shdr_variedEncoding);
		else
			return 0;
	}

	// Returns the size of dyn entry
	uint32_t CELFmanager::GetSizeOfDyn()
	{
		unsigned char Class = this->header.e_ident[EI_CLASS];

		if (Class == ELFCLASS32)
			return sizeof(Elf32_Dyn);
		else if (Class == ELFCLASS64)
			return sizeof(Elf64_Dyn);
		else
			return 0;
	}

	// Returns iterator to program header by address
	stdx::ptr_vector<CPhdr>::iterator CELFmanager::FindPhdrThatIncludesMemoryAddress(uint32_t address)
	{
		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			++it)
		{
			if (address >= it->p_vaddr && address <= it->p_vaddr + it->p_memsz)
				return it;
		}

		return this->program_header_table.end();
	}

	// Returns iterator to section by address
	stdx::ptr_vector<CShdr>::iterator CELFmanager::FindSectionByAddress(uint32_t address)
	{
		for (auto it = this->section_header_table.begin();
			it != this->section_header_table.end();
			++it)
		{
			if (it->sh_addr == address)
				return it;
		}

		return this->section_header_table.end();
	}

	// Returns iterator to first section with specified type 
	stdx::ptr_vector<CShdr>::iterator CELFmanager::FindFirstSectionWithType(uint32_t sh_type)
	{
		for (auto it = this->section_header_table.begin();
			it != this->section_header_table.end();
			++it)
		{
			if (it->sh_type == sh_type)
				return it;
		}

		return this->section_header_table.end();
	}

	// Returns iterator to first section with specified type 
	stdx::ptr_vector<CShdr>::iterator CELFmanager::FindFirstSectionWithName(const char* name)
	{
		for (auto it = this->section_header_table.begin();
			it != this->section_header_table.end();
			++it)
		{
			const char* testedSectionName = this->pStringSectionData + it->sh_name;

			if(!strcmp(name, testedSectionName))
				return it;
		}

		return this->section_header_table.end();
	}

	// Returns iterator to first program segment with specified type 
	stdx::ptr_vector<CPhdr>::iterator CELFmanager::FindFirstProgramSegmentWithType(uint32_t p_type)
	{
		for (auto it = this->program_header_table.begin();
			it != this->program_header_table.end();
			++it)
		{
			if (it->p_type == p_type)
				return it;
		}

		return this->program_header_table.end();
	}

	// Returns iterator to first dynamic table entry with specified tpye
	stdx::ptr_vector<CDyn>::iterator CELFmanager::FindFirstEntryInDynamicTableWithTag(int64_t d_tag)
	{
		for (auto it = this->dynamic_table.begin();
			it != this->dynamic_table.end();
			++it)
		{
			if (it->d_tag == d_tag)
				return it;
		}

		return this->dynamic_table.end();
	}

	/* Array used to determine the number of hash table buckets to use
   based on the number of symbols there are.  If there are fewer than
   3 symbols we use 1 bucket, fewer than 17 symbols we use 3 buckets,
   fewer than 37 we use 17 buckets, and so forth.  We never use more
   than 32771 buckets.  */
	static const size_t elf_buckets[] =
	{
	  1, 3, 17, 37, 67, 97, 131, 197, 263, 521, 1031, 2053, 4099, 8209,
	  16411, 32771, 0
	};

	// Returns number of buckets for dynamic symbol hash table
	unsigned int CELFmanager::GetNumberOfBucketsForDynamicSymbolHashTable(unsigned int numberOfSymbols)
	{
		unsigned int best_size = 0;

		for (int i = 0; elf_buckets[i] != 0; i++)
		{
			best_size = elf_buckets[i];
			if (numberOfSymbols < elf_buckets[i + 1])
				break;
		}

		return best_size;
	}

	// Builds dynamic symbol hash table
	void CELFmanager::BuildDynamicSymbolHashTable(
		CHashTable* pHashTable,
		const char* strPtr
	)
	{
		unsigned int dynsymArrayCount = this->dynamic_symbol_table.size();
		
		pHashTable->nchain = dynsymArrayCount;
		pHashTable->nbucket = GetNumberOfBucketsForDynamicSymbolHashTable(dynsymArrayCount);

		uint32_t* bucketLastWrittenPositionInChain = new uint32_t[pHashTable->nbucket];
		memset(bucketLastWrittenPositionInChain, 0, pHashTable->nbucket * sizeof(uint32_t));

		pHashTable->bucket = new uint32_t[pHashTable->nbucket];
		memset(pHashTable->bucket, 0, pHashTable->nbucket * sizeof(uint32_t));

		pHashTable->chain = new uint32_t[dynsymArrayCount];
		memset(pHashTable->chain, 0, dynsymArrayCount * sizeof(uint32_t));

		for (unsigned int i = 0; i < dynsymArrayCount; i++)
		{
			uint64_t symbolNameOffset = this->dynamic_symbol_table[i].st_name;

			if (!symbolNameOffset)
				continue;

			const char* pSymbolName = strPtr + symbolNameOffset;

			uint32_t symbolNameHash = elf_hash(pSymbolName);
			unsigned int bucketID = symbolNameHash % pHashTable->nbucket;

			// printf("symbolName: %s bucketID: %d\n", pSymbolName, bucketID);

			if (bucketLastWrittenPositionInChain[bucketID])	// already chain created?
			{
				pHashTable->chain[bucketLastWrittenPositionInChain[bucketID]] = i;

				bucketLastWrittenPositionInChain[bucketID] = i;
			}
			else
			{
				pHashTable->bucket[bucketID] = i;

				bucketLastWrittenPositionInChain[bucketID] = i;
			}
		}

		delete[] bucketLastWrittenPositionInChain;
	}

	// Writes hash table to memory
	void CELFmanager::WriteHashTableToMemory(CHashTable* pHashTable, const void* ptr)
	{
		tVariedEncoding<uint32_t>* nbucket = (tVariedEncoding<uint32_t>*)ptr;
		tVariedEncoding<uint32_t>* nchain = nbucket + 1;

		nbucket->SetValue(pHashTable->nbucket, valueEncoding);
		nchain->SetValue(pHashTable->nchain, valueEncoding);

		tVariedEncoding<uint32_t>* bucket = nchain + 1;
		tVariedEncoding<uint32_t>* chain = bucket + pHashTable->nbucket;

		for (unsigned int i = 0; i < pHashTable->nbucket; i++)
			bucket[i].SetValue(pHashTable->bucket[i], valueEncoding);

		for (unsigned int i = 0; i < pHashTable->nchain; i++)
			chain[i].SetValue(pHashTable->chain[i], valueEncoding);
	}
}