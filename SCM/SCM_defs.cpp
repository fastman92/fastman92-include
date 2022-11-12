#include "SCM_defs.h"
#include <algorithm>
#include <cctype>

namespace SCM { namespace Common {

	// Reads intermediate command hex represantation e.g 0001
	// endptr may be NULL
	bool ReadIntermediateCommandNumberinHexRepresentation(SCM::CompiledFormat::tCompiledCommandID* pID, const char* pStr, char** endptr)
	{
		bool validHexNumber = true;

		for(int i = 0; i < 4; i++)
		{
			if(!isxdigit(pStr[i]))
			{
				validHexNumber = false;
				break;
			}
		}						

		if(!validHexNumber)
			return false;

		char buffer[5];

		memcpy(buffer, pStr, 4);
		buffer[4] = NULL;
		
		*pID = (SCM::CompiledFormat::tCompiledCommandID)strtol (buffer, NULL, 16);

		if(endptr)
			*endptr = (char*)pStr + 4;
		
		return true;
	}

	// Reads intermediate command hex represantation e.g 0001 and skips equality operator
	// endptr may be NULL
	bool ReadIntermediateCommandNumberinHexRepresentationAndSkipEqualityOperator(SCM::CompiledFormat::tCompiledCommandID* pID, const char* pStr, char** endptr)
	{
		char* xEndPtr;

		if(!ReadIntermediateCommandNumberinHexRepresentation(pID, pStr, &xEndPtr))
			return false;

		if(*xEndPtr != '=')
			return false;

		if(endptr)
			*endptr = xEndPtr;

		return true;
	}
} }