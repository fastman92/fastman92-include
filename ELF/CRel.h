#pragma once
#include "elf.h"

namespace ELF_format {
	class CRel
	{
	public:
		Elf64_Addr r_offset;	/* Location at which to apply the action */
		Elf64_Word r_index;	/* index and type of relocation */
		Elf64_Word r_type;	/* index and type of relocation */
	};


	void ReadPltRelocation(CRel* rel, const elf32_rel_variedEncoding& relInFile, eValueEncoding valueEncoding);
	void ReadPltRelocation(CRel* rel, const elf64_rel_variedEncoding& relInFile, eValueEncoding valueEncoding);

	void WritePltRelocation(elf32_rel_variedEncoding& relInFile, const CRel& rel, eValueEncoding valueEncoding);
	void WritePltRelocation(elf64_rel_variedEncoding& relInFile, const CRel& rel, eValueEncoding valueEncoding);
}