#pragma once
#include <stdint.h>
#include <string.h>

#include "elf.h"

#pragma warning(disable:4244)

namespace ELF_format
{
	struct CHeader
	{
	public:
		unsigned char	e_ident[EI_NIDENT];
		uint16_t e_type;
		uint16_t e_machine;
		uint32_t e_version;
		uint64_t e_entry;		/* Entry point virtual address */
		uint64_t e_phoff;		/* Program header table file offset */
		uint64_t e_shoff;		/* Section header table file offset */
		uint32_t e_flags;
		uint16_t e_ehsize;
		uint16_t e_phentsize;
		uint16_t e_phnum;	// will be updated automatically when saving a new file
		uint16_t e_shentsize;
		uint16_t e_shnum;
		uint16_t e_shstrndx;
	};

	template<class T> void ReadELFheader(CHeader& cHeader, const T& headerInFile, eValueEncoding valueEncoding)
	{
		memcpy(cHeader.e_ident, headerInFile.e_ident, sizeof(headerInFile.e_ident));
		cHeader.e_type = headerInFile.e_type.GetValue(valueEncoding);
		cHeader.e_machine = headerInFile.e_machine.GetValue(valueEncoding);
		cHeader.e_version = headerInFile.e_version.GetValue(valueEncoding);
		cHeader.e_entry = headerInFile.e_entry.GetValue(valueEncoding);  /* Entry point */
		cHeader.e_phoff = headerInFile.e_phoff.GetValue(valueEncoding);
		cHeader.e_shoff = headerInFile.e_shoff.GetValue(valueEncoding);
		cHeader.e_flags = headerInFile.e_flags.GetValue(valueEncoding);
		cHeader.e_ehsize = headerInFile.e_ehsize.GetValue(valueEncoding);
		cHeader.e_phentsize = headerInFile.e_phentsize.GetValue(valueEncoding);
		cHeader.e_phnum = headerInFile.e_phnum.GetValue(valueEncoding);
		cHeader.e_shentsize = headerInFile.e_shentsize.GetValue(valueEncoding);
		cHeader.e_shnum = headerInFile.e_shnum.GetValue(valueEncoding);
		cHeader.e_shstrndx = headerInFile.e_shstrndx.GetValue(valueEncoding);
	}

	template<class T> void WriteELFheader(T& headerInFile, const CHeader& cHeader, eValueEncoding valueEncoding)
	{
		memcpy(headerInFile.e_ident, cHeader.e_ident, sizeof(cHeader.e_ident));

		headerInFile.e_type.SetValue(cHeader.e_type, valueEncoding);
		headerInFile.e_machine.SetValue(cHeader.e_machine, valueEncoding);
		headerInFile.e_version.SetValue(cHeader.e_version, valueEncoding);
		headerInFile.e_entry.SetValue(cHeader.e_entry, valueEncoding);
		headerInFile.e_phoff.SetValue(cHeader.e_phoff, valueEncoding);
		headerInFile.e_shoff.SetValue(cHeader.e_shoff, valueEncoding);
		headerInFile.e_flags.SetValue(cHeader.e_flags, valueEncoding);
		headerInFile.e_ehsize.SetValue(cHeader.e_ehsize, valueEncoding);
		headerInFile.e_phentsize.SetValue(cHeader.e_phentsize, valueEncoding);
		headerInFile.e_phnum.SetValue(cHeader.e_phnum, valueEncoding);
		headerInFile.e_shentsize.SetValue(cHeader.e_shentsize, valueEncoding);
		headerInFile.e_shnum.SetValue(cHeader.e_shnum, valueEncoding);
		headerInFile.e_shstrndx.SetValue(cHeader.e_shstrndx, valueEncoding);
	}
}