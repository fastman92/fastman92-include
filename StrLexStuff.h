#pragma once
#include <ctype.h>
#include <string>
#include <stdlib.h>

#ifdef IS_PLATFORM_WIN
#include <Windows.h>
#endif

// Checks if given character may be beginning of identifier
static bool IsValidIdentifierBeginningChar(int c)
{
	return c == '_'  || iswalpha(c);
};

// Checks if given character may be part of identfifier
static bool IsValidIdentifierContinuation(int c)
{
	return c == L'_' || iswalnum(c);
}

// Checks if given character may be beginning or terminator of string
static bool IsCharacterAValidStringPreceeder(int c)
{
	return c == '\'' || c == '"';
}

// Checks if given array of characters may be valid identifier name
template<typename T> bool IsValidIdentifierName(const T* str)
{
	if(*str && IsValidIdentifierBeginningChar(*str))
	{
		str++;

		while(*str)
		{
			if(!IsValidIdentifierContinuation(*str))
				return false;

			str++;
		}

		return true;
	}

	return false;
}

// Checks if given array of characters may be valid identifier name
template<typename T> bool IsValidHexNumberWithoutPreceding(const T* str)
{
	bool validHexNumber = true;

	while(*str)
	{
		if(!isxdigit(*str))
		{
			validHexNumber = false;
			break;
		}
		str++;
	}

	return validHexNumber;
}

// Returns true if given string contains only white characters or doesn't contain any characters at all
template<typename T> bool AreWhiteOrNoneCharactersInString(const T* str)
{
	return *FindFirstNonWhiteCharacter(str) == NULL;
}

// Trims right
template<typename T> void TrimRight(T* str)
{
	int i = 0;

	while (str[i])
		i++;
	
	if (i > 0)
	{
		i--;

		while (i >= 0 && (str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == ' '))
			str[i--] = NULL;
	}	
}

// Trims right
template<typename T> void TrimRightOnlyNewLineCharacters(T* str)
{
	int i = 0;

	while (str[i])
		i++;

	if (i > 0)
	{
		i--;

		while (i >= 0 && (str[i] == '\n' || str[i] == '\r'))
			str[i--] = NULL;
	}
}

// Checks if given character is new line char.
template<typename T> bool IsNewLineCharacter(T c)
{
	return c == L'\r' || c == L'\n';
}

// Checks if given character appears white in single line
template<typename T> bool IsSingleLineWhiteCharacter(T c)
{
	return c == L'\t' || c == L' ';
}

// Checks if given character is invisible
template<typename T> bool IsAnyWhiteCharacter(T c)
{
	return IsNewLineCharacter(c) || IsSingleLineWhiteCharacter(c);
};

typedef bool (*tFuncIsValidCharacter)(int c);

/*
// Reads identifier
static std::string ReadIdentifierPlaceholderAllowed(const char* line, const char** pIdentifierEnd)
{
	return ReadIdentifierPlaceholderAllowed<char, std::string> (line, pIdentifierEnd, "-");
}

// Reads identifier
static std::wstring ReadIdentifierPlaceholderAllowed(const wchar_t* line, const wchar_t** pIdentifierEnd)
{
	return ReadIdentifierPlaceholderAllowed<wchar_t, std::wstring> (line, pIdentifierEnd, L"-");
}*/

// Finds first not white character in text
template<typename T> const T* FindFirstWhiteOrNULLcharacter(const T* str)
{
	while (*str != NULL && !IsAnyWhiteCharacter(*str))
		str++;

	return str;
}

// Finds first not white character in text
template<typename T> T* FindFirstNonWhiteCharacter(const T* str)
{
	while (IsAnyWhiteCharacter(*str))
		str++;

	return (T*)str;
}

// Finds next not white character in text
template<typename T> T* FindNextWhiteCharacter(const T* str)
{
	while (*str && !IsAnyWhiteCharacter(*str))
		str++;

	return (T*)str;
}


// Skips specified character and returns incremented pointer
template <typename T> T* SkipSpecifiedCharacter(T* line, T c)
{
	T* iLine = FindFirstNonWhiteCharacter<T>(line);

	if(*iLine == c)
		iLine++;

	return iLine;
}

// Skips comma
template <typename T> T* SkipComma(T* line)
{
	return SkipSpecifiedCharacter(line, ',');
};

template<typename inputT, typename outputT> outputT ReadAnyValue(const inputT* line, inputT** pValueEnd)
{
	inputT* iLine = FindFirstNonWhiteCharacter<inputT>(line);

	outputT Value;
	
	
	if(IsCharacterAValidStringPreceeder(*iLine))
	{
		inputT starter = *iLine;

		iLine++;

		while(inputT c = *iLine++)
		{
			if(c == starter)
				break;
			else
				Value += c;
		}		
	}
	else
	{
		if(!IsAnyWhiteCharacter(*iLine))
		{
			do
				Value += *iLine;
			while(!IsAnyWhiteCharacter(*++iLine));
		}
	}

	if(pValueEnd)
		*pValueEnd = iLine;

	return Value;
}

// Reads string
template<typename inputT, typename outputT> bool ReadString(const inputT* line, outputT& outStr, inputT** pValueEnd = NULL)
{
	outStr.clear();

	inputT* iLine = FindFirstNonWhiteCharacter<inputT>(line);	
	
	inputT starter = *iLine++;

	if(!IsCharacterAValidStringPreceeder(starter))
		return false;

	while(const inputT c = *iLine)
	{
		if(c == (inputT)'"')
		{
			if(pValueEnd)
				*pValueEnd = iLine + 1;

			return true;
		}

		if(c == '\\')
		{
			const char n = *++iLine;
			iLine++;

			switch(n)
			{
			// Alert (bell)
			case 'a':
				outStr += '\a';
				break;
			// Backspace
			case 'b':				
				outStr += '\b';
				break;

			// Form feed
			case 'f':		
				outStr += '\f';
				break;
					
			// Newline (line feed)
			case 'n':
				outStr += '\n';
				break;

			// Carriage return
			case 'r':
				outStr += '\r';
				break;

			// Horizontal tab
			case 't':
				outStr += '\t';
				iLine += 2;
				break;

			// Vertical tab
			case 'v':
				outStr += '\v';
				break;

			// Character with hexadecimal value hh
			case 'x':
				char Character;
				Character = (char)strtol(iLine, (char**)&iLine, 16);
				outStr += Character;			
				break;
			case '\\':
				outStr += '\\';
				break;
			}			
		}
		else
		{
			outStr += c;
			iLine += 1;
		}
	}

	return false;
}

static int ReadAnyValue(char* lpReturnedString, size_t returnedStringSize, const char* line, char** pIdentifierEnd)
{
	std::string result = ReadAnyValue<char, std::string>(line, pIdentifierEnd);

	if(returnedStringSize != -1)
		strncpy(lpReturnedString, result.c_str(), returnedStringSize);
	else
		strcpy(lpReturnedString, result.c_str());

	return strlen(lpReturnedString);
}

static int ReadAnyValue(wchar_t* lpReturnedString, size_t returnedStringSize, const wchar_t* line, wchar_t** pIdentifierEnd)
{
	std::wstring result = ReadAnyValue<wchar_t, std::wstring>(line, pIdentifierEnd);

	if(returnedStringSize != -1)
		wcsncpy(lpReturnedString, result.c_str(), returnedStringSize);
	else
		wcscpy(lpReturnedString, result.c_str());

	return result.length();
}

// Reads identifier
template<typename inputT, typename outputT> outputT ReadIdentifier(const inputT* line, inputT** pIdentifierEnd, tFuncIsValidCharacter beginningCharVerifier, tFuncIsValidCharacter continuationCharVerifier)
{
	inputT* iLine = FindFirstNonWhiteCharacter<inputT>(line);

	outputT Identifier;

	if(beginningCharVerifier(*iLine))
	{
		do
			Identifier += *iLine;
		while(continuationCharVerifier(*++iLine));
	}

	if(pIdentifierEnd)
		*pIdentifierEnd = iLine;

	return Identifier;
}

template<typename inputT, typename outputT> outputT ReadIdentifier(const inputT* line, inputT** pIdentifierEnd)
{
	return ReadIdentifier<inputT, outputT>(line, pIdentifierEnd, IsValidIdentifierBeginningChar, IsValidIdentifierContinuation);
}

static int ReadIdentifier(char* lpReturnedString, size_t returnedStringSize, char* line, char** pIdentifierEnd)
{
	std::string result = ReadIdentifier<char, std::string>(line, pIdentifierEnd);

	if(returnedStringSize != -1)
		strncpy(lpReturnedString, result.c_str(), returnedStringSize);
	else
		strcpy(lpReturnedString, result.c_str());

	return result.length();
}

// Returns length of identifier
static int ReadIdentifier(wchar_t* lpReturnedString, size_t returnedStringSize, const wchar_t* line, wchar_t** pIdentifierEnd)
{
	std::wstring result = ReadIdentifier<wchar_t, std::wstring>(line, pIdentifierEnd);

	if(returnedStringSize != -1)
		wcsncpy(lpReturnedString, result.c_str(), returnedStringSize);
	else
		wcscpy(lpReturnedString, result.c_str());

	return result.length();
}

// Reads identifier
template<typename inputT, typename outputT> outputT ReadIdentifierPlaceholderAllowed(const inputT* line, inputT** pIdentifierEnd, const inputT* placeholder)
{
	outputT result = ReadIdentifier<inputT, outputT>(line, pIdentifierEnd,
		[](int c) {return c == '-' || IsValidIdentifierBeginningChar(c); },
		IsValidIdentifierContinuation);

	if (result == placeholder)
		result.clear();

	return result;
}

// Reads identifier
static std::string ReadIdentifierPlaceholderAllowed(const char* line, char** pIdentifierEnd)
{
	return ReadIdentifierPlaceholderAllowed<char, std::string>(line, pIdentifierEnd, "-");
}

// Reads identifier
static std::wstring ReadIdentifierPlaceholderAllowed(const wchar_t* line, wchar_t** pIdentifierEnd)
{
	return ReadIdentifierPlaceholderAllowed<wchar_t, std::wstring>(line, pIdentifierEnd, L"-");
}

// Reads integer number
static int64_t ReadIntegerNum(const char* line, char** pNumberEnd)
{

#ifdef IS_PLATFORM_WIN
	char* iLine = FindFirstNonWhiteCharacter(line);

	int64_t result;
		
	if(*iLine == '0' && *(iLine+1) == 'x')	// 0x hex numbers
	{
		iLine += 2;
		result = _strtoi64(iLine, &iLine, 16);
	}
	else if(*iLine == '0' && *(iLine+1) == 'b')	// 0b hex numbers
	{
		iLine += 2;
			
		result = _strtoi64(iLine, &iLine, 2);
	}
	else
		result = _strtoi64(iLine, &iLine, 10);

	if(pNumberEnd)
		*pNumberEnd = iLine;

	return result;
#else
	return 0;
#endif
}


template<typename inputT, typename outputT> outputT ReadFunctionArgumentType(const inputT* line, inputT** pIdentifierEnd)
{
	return ReadIdentifier<inputT, outputT>(line, pIdentifierEnd,
		[](int c) { return c == '.' || IsValidIdentifierBeginningChar(c); },
		[](int c) { return c == '.' || IsValidIdentifierContinuation(c); });
}

// Returns true if string contains a valid integer.
template<typename T> bool IsStringAValidInteger(const T* str)
{
	if(*str == '0' && *(str+1) == 'x')	// 0x hex numbers
	{
		str += 2;

		while(*str)
			if(!isxdigit(*str++))
				return false;
	}
	else
		while(*str)
			if(!isdigit(*str++))
				return false;

	return true;
}

// Checks if string delimiter is double "
template<typename T> bool IsCharAstringDelimiterDoubleQuotation(T character)
{
	return character == '"';
}

// Checks if string delimiter is single '
template<typename T> bool IsCharAstringDelimiterSingleQuotation(T character)
{
	return character == '\'';
}

// Checks if string delimiter is single '
template<typename T> bool IsDigitOrIdentifierChar(T character)
{
	return IsValidIdentifierContinuation(character);
}

// Returns string if not empty, otherwise a placeholder
static const char* GetStrOrPlaceHolderIfEmpty(const char* str, const char* placeHolder)
{
	if (str[0])
		return str;
	else
		return placeHolder;
}

#ifdef IS_PLATFORM_WIN
static std::string ToUtf8(std::string ansiText)
{
    int ansiRequiredSize = MultiByteToWideChar(1250, 0, ansiText.c_str(), ansiText.size(), NULL, 0);
    wchar_t * wideText = new wchar_t[ansiRequiredSize + 1];
    wideText[ansiRequiredSize] = NULL;
    MultiByteToWideChar(1250, 0, ansiText.c_str(), ansiText.size(), wideText, ansiRequiredSize);
    int utf8RequiredSize = WideCharToMultiByte(65001, 0, wideText, ansiRequiredSize, NULL, 0, NULL, NULL);
    char utf8Text[1024];
    utf8Text[utf8RequiredSize] = NULL;
    WideCharToMultiByte(65001, 0, wideText, ansiRequiredSize, utf8Text, utf8RequiredSize, NULL, NULL);
    delete [] wideText;
    return utf8Text;
}
#endif

// Returns a string with slashes
template<typename inputT, typename outputT> outputT addcslashes(const inputT* str, inputT escapeChar)
{
	outputT outStr;

	while (const inputT c = *str++)
	{
		if (c == escapeChar)
		{
			outStr += "\\";
			outStr += escapeChar;
		}
		else
		{
			switch (c)
			{
				// Alert (bell)
			case '\a':
				outStr += "\\a";
				break;
				// Backspace
			case '\b':
				outStr += "\\b";
				break;

				// Form feed
			case '\f':
				outStr += "\\f";
				break;

				// Newline (line feed)
			case '\n':
				outStr += "\\n";
				break;

				// Carriage return
			case '\r':
				outStr += "\\r";
				break;

				// Horizontal tab
			case '\t':
				outStr += "\\t";
				break;

				// Vertical tab
			case '\v':
				outStr += "\\v";
				break;
			case '\\':
				outStr += "\\\\";
				break;
			default:
				outStr += c;
			}
		}
	}

	return outStr;
}

// Returns a string with slashes
template<typename inputT, typename outputT> outputT duplicateQuoteMarks(const inputT* str, inputT escapeChar)
{
	outputT outStr;

	while (const inputT c = *str++)
	{
		if (c == escapeChar)
		{
			outStr += escapeChar;
			outStr += escapeChar;
		}
		else
			outStr += c;
	}

	return outStr;
}

static bool StrContainsNewLine(const char* str)
{
	while (char c = *str)
	{
		if (c == '\n')
			return true;

		str++;
	}

	return false;
}