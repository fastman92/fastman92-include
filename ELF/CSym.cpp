#include "CSym.h"

namespace ELF_format {
	void CopyCSymWithoutName(CSym* pToBeModified, CSym* pSource)
	{
		auto name = pToBeModified->st_name;
		*pToBeModified = *pSource;
		pToBeModified->st_name = name;
	}
}