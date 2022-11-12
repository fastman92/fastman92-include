#include "CRel.h"

namespace ELF_format {
	void ReadPltRelocation(CRel* rel, const elf32_rel_variedEncoding& relInFile, eValueEncoding valueEncoding)
	{
		rel->r_offset = relInFile.r_offset.GetValue(valueEncoding);

		auto info = relInFile.r_info.GetValue(valueEncoding);

		rel->r_index = ELF32_R_SYM(info);
		rel->r_type = ELF32_R_TYPE(info);
	}

	void ReadPltRelocation(CRel* rel, const elf64_rel_variedEncoding& relInFile, eValueEncoding valueEncoding)
	{
		rel->r_offset = relInFile.r_offset.GetValue(valueEncoding);

		auto info = relInFile.r_info.GetValue(valueEncoding);

		rel->r_index = ELF64_R_SYM(info);
		rel->r_type = ELF64_R_TYPE(info);
	}

	void WritePltRelocation(elf32_rel_variedEncoding& relInFile, const CRel& rel, eValueEncoding valueEncoding)
	{
		relInFile.r_offset.SetValue(rel.r_offset, valueEncoding);

		relInFile.r_info.SetValue(ELF32_R_INFO(rel.r_index, rel.r_type, valueEncoding), valueEncoding);
	}

	void WritePltRelocation(elf64_rel_variedEncoding& relInFile, const CRel& rel, eValueEncoding valueEncoding)
	{
		relInFile.r_offset.SetValue(rel.r_offset, valueEncoding);

		relInFile.r_info.SetValue(ELF64_R_INFO(rel.r_index, rel.r_type, valueEncoding), valueEncoding);
	}
}