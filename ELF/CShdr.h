#pragma once
#include <stdint.h>
#include <vector>

namespace ELF_format {
	struct CShdr {
		uint32_t sh_name;		/* Section name, index in string tbl */
		uint32_t sh_type;		/* Type of section */
		uint64_t sh_flags;		/* Miscellaneous section attributes */
		uint64_t sh_addr;		/* Section virtual addr at execution */
		uint64_t sh_offset;		/* Section file offset */
		uint64_t sh_size;		/* Size of section in bytes */
		uint32_t sh_link;		/* Index of another section */
		uint32_t sh_info;		/* Additional section information */
		uint64_t sh_addralign;	/* Section alignment */
		uint64_t sh_entsize;	/* Entry size if section holds table */

		char* pFileData;

		// Constructor
		CShdr()
		{
			this->pFileData = nullptr;
		}

		~CShdr()
		{
			delete[] this->pFileData;
		}
	};

	struct tShdrForAdding
	{
		char str[32];
		int sectionID;

		uint32_t sh_type;		/* Type of section */
		uint64_t sh_flags;		/* Miscellaneous section attributes */
		uint64_t sh_addr;		/* Section virtual addr at execution */
		uint64_t sh_offset;		/* Section file offset */
		uint64_t sh_size;		/* Size of section in bytes */
		uint32_t sh_link;		/* Index of another section */
		uint32_t sh_info;		/* Additional section information */
		uint64_t sh_addralign;	/* Section alignment */
		uint64_t sh_entsize;	/* Entry size if section holds table */
	};

	template<class T> void ReadSectionHeader(CShdr* shdr, const T& shdrInFile, eValueEncoding valueEncoding, FILE* fp)
	{
		shdr->sh_name = shdrInFile.sh_name.GetValue(valueEncoding);
		shdr->sh_type = shdrInFile.sh_type.GetValue(valueEncoding);
		shdr->sh_flags = shdrInFile.sh_flags.GetValue(valueEncoding);
		shdr->sh_addr = shdrInFile.sh_addr.GetValue(valueEncoding);
		shdr->sh_offset = shdrInFile.sh_offset.GetValue(valueEncoding);
		shdr->sh_size = shdrInFile.sh_size.GetValue(valueEncoding);
		shdr->sh_link = shdrInFile.sh_link.GetValue(valueEncoding);
		shdr->sh_info = shdrInFile.sh_info.GetValue(valueEncoding);
		shdr->sh_addralign = shdrInFile.sh_addralign.GetValue(valueEncoding);
		shdr->sh_entsize = shdrInFile.sh_entsize.GetValue(valueEncoding);

		auto off = ftell(fp);

		if (shdr->sh_addr == 0 && shdr->sh_size != 0)
		{
			fseek(fp, shdr->sh_offset, SEEK_SET);
			shdr->pFileData = new char[shdr->sh_size];
			fread(shdr->pFileData, shdr->sh_size, 1, fp);
		}

		fseek(fp, off, SEEK_SET);
	}

	template<class T> void WriteSectionHeader(T& shdrInFile, const CShdr& shdr, eValueEncoding valueEncoding)
	{
		shdrInFile.sh_name.SetValue(shdr.sh_name, valueEncoding);
		shdrInFile.sh_type.SetValue(shdr.sh_type, valueEncoding);
		shdrInFile.sh_flags.SetValue(shdr.sh_flags, valueEncoding);
		shdrInFile.sh_addr.SetValue(shdr.sh_addr, valueEncoding);
		shdrInFile.sh_offset.SetValue(shdr.sh_offset, valueEncoding);
		shdrInFile.sh_size.SetValue(shdr.sh_size, valueEncoding);
		shdrInFile.sh_link.SetValue(shdr.sh_link, valueEncoding);
		shdrInFile.sh_info.SetValue(shdr.sh_info, valueEncoding);
		shdrInFile.sh_addralign.SetValue(shdr.sh_addralign, valueEncoding);
		shdrInFile.sh_entsize.SetValue(shdr.sh_entsize, valueEncoding);
	}
}