// GMemFile by fastman92
#pragma once
#include <stddef.h>

class GMemFile
{
public:
	typedef size_t tPosition;

private:
	char* Ptr;
	tPosition Pos;
	tPosition RealSize;
	tPosition SizeLimit;

public:
	// Constructor
	GMemFile();

	// Opens file from memory.
	void Open(void *Ptr, tPosition RealSize, tPosition SizeLimit = -1);

	// Closes a file
	void Close();

	// Reads to memory
	tPosition Read(void* Ptr, size_t Size);

	// Reads NULL terminated string
	void ReadNULLterminatedString(char* str);

	// Reads 4 byte aligned NULL terminated string
	void Read4byteAlignedNULLterminatedString(char* str);

	// Reads one ANSI character
	char ReadC();

	/*
	// Reads one Unicode character
	wchar_t GMemFile::ReadWideChar();
	*/

	// Writes to memory file
	void Write(const void* Ptr, size_t Size);

	// Writes string to memory file
	void WriteString(const char* str);

	// Writes 4 byte aligned NULL terminated string
	bool Writes4byteAlignedNULLterminatedString(const char* str);

	// Seek to certain position
	bool Seek(size_t offset, int origin);

	// Check End-of-File indicator
	bool isEOF();

	// Returns current position
	tPosition Tell();

	// Gets pointer to file
	void* GetPtr();

	// Gets Ptr + current position
	void* GetCurPtr();

	// Gets filesize
	size_t GetSize();

	// Sets filesize
	bool SetSize(tPosition filesize);
};