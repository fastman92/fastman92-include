#pragma once
#include <stdint.h>

namespace ELF_format {

	class CDyn
	{
	public:
		int64_t d_tag;		/* entry tag value */
		union {
			uint64_t d_val;
			uint64_t d_ptr;
		} d_un;
	};

	template<class T> void ReadDynamicStruct(CDyn* dyn, const T& dynInFile, eValueEncoding valueEncoding)
	{
		dyn->d_tag = dynInFile.d_tag.GetValue(valueEncoding);

		dyn->d_un.d_val = dynInFile.d_un.d_val.GetValue(valueEncoding);
		dyn->d_un.d_ptr = dynInFile.d_un.d_ptr.GetValue(valueEncoding);
	}

	template<class T> void WriteDynamicStruct(T& dynInFile, const CDyn& dyn, eValueEncoding valueEncoding)
	{
		dynInFile.d_tag.SetValue(dyn.d_tag, valueEncoding);

		dynInFile.d_un.d_val.SetValue(dyn.d_un.d_val, valueEncoding);
		dynInFile.d_un.d_ptr.SetValue(dyn.d_un.d_ptr, valueEncoding);
	}
}