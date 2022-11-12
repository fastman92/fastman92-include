#pragma once
#include <stdint.h>
#include <stdio.h>

namespace ELF_format {
	class CPhdr
	{
	public:
		uint32_t p_type;
		uint32_t p_flags;
		uint64_t p_offset;		/* Segment file offset */
		uint64_t p_vaddr;		/* Segment virtual address */
		uint64_t p_paddr;		/* Segment physical address */
		uint64_t p_filesz;		/* Segment size in file */
		uint64_t p_memsz;		/* Segment size in memory */
		uint64_t p_align;		/* Segment alignment, file & memory */

		char* pFileData;

		// Constructor
		CPhdr()
		{
			this->pFileData = nullptr;
		}

		~CPhdr()
		{
			delete[] this->pFileData;
		}
	};

	template<class T> void ReadProgramHeader(CPhdr* cPhr, const T& phrInFile, eValueEncoding valueEncoding, FILE* fp)
	{
		cPhr->p_type = phrInFile.p_type.GetValue(valueEncoding);
		cPhr->p_flags = phrInFile.p_flags.GetValue(valueEncoding);
		cPhr->p_offset = phrInFile.p_offset.GetValue(valueEncoding);
		cPhr->p_vaddr = phrInFile.p_vaddr.GetValue(valueEncoding);
		cPhr->p_paddr = phrInFile.p_paddr.GetValue(valueEncoding);
		cPhr->p_filesz = phrInFile.p_filesz.GetValue(valueEncoding);
		cPhr->p_memsz = phrInFile.p_memsz.GetValue(valueEncoding);
		cPhr->p_align = phrInFile.p_align.GetValue(valueEncoding);

		auto off = ftell(fp);

		if (cPhr->p_filesz != 0)
		{
			fseek(fp, cPhr->p_offset, SEEK_SET);
			cPhr->pFileData = new char[cPhr->p_filesz];
			fread(cPhr->pFileData, cPhr->p_filesz, 1, fp);
		}

		fseek(fp, off, SEEK_SET);
	}

	template<class T> void WriteProgramHeader(T& headerInFile, const CPhdr& cHeader, eValueEncoding valueEncoding)
	{
		headerInFile.p_type.SetValue(cHeader.p_type, valueEncoding);
		headerInFile.p_flags.SetValue(cHeader.p_flags, valueEncoding);
		headerInFile.p_offset.SetValue(cHeader.p_offset, valueEncoding);
		headerInFile.p_vaddr.SetValue(cHeader.p_vaddr, valueEncoding);
		headerInFile.p_paddr.SetValue(cHeader.p_paddr, valueEncoding);
		headerInFile.p_filesz.SetValue(cHeader.p_filesz, valueEncoding);
		headerInFile.p_memsz.SetValue(cHeader.p_memsz, valueEncoding);
		headerInFile.p_align.SetValue(cHeader.p_align, valueEncoding);
	}
}