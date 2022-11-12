#pragma once
#include "elf.h"

namespace ELF_format {
	class CSym : public elf64_sym
	{
	public:
		Elf64_Half gnu_version;
	};

	template<class T> void ReadDynamicSymbol(CSym* sym, const T& symInFile, eValueEncoding valueEncoding)
	{
		sym->st_name = symInFile.st_name.GetValue(valueEncoding);
		sym->st_info = symInFile.st_info.GetValue(valueEncoding);
		sym->st_other = symInFile.st_other.GetValue(valueEncoding);
		sym->st_shndx = symInFile.st_shndx.GetValue(valueEncoding);
		sym->st_value = symInFile.st_value.GetValue(valueEncoding);
		sym->st_size = symInFile.st_size.GetValue(valueEncoding);
	}

	template<class T> void WriteDynamicSymbol(T& symInFile, const CSym& sym, eValueEncoding valueEncoding)
	{
		symInFile.st_name.SetValue(sym.st_name, valueEncoding);
		symInFile.st_info.SetValue(sym.st_info, valueEncoding);
		symInFile.st_other.SetValue(sym.st_other, valueEncoding);
		symInFile.st_shndx.SetValue(sym.st_shndx, valueEncoding);
		symInFile.st_value.SetValue(sym.st_value, valueEncoding);
		symInFile.st_size.SetValue(sym.st_size, valueEncoding);
	}

	void CopyCSymWithoutName(CSym* pToBeModified, CSym* pSource);
}