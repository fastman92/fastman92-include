// GMemFile by fastman92

#include "GMemFile.h"
#include <string>

// Constructor
GMemFile::GMemFile()
{
	this -> Ptr = NULL;
	this -> RealSize = 0;
	this -> SizeLimit = 0;
	this -> Pos = NULL;
}

// Opens file from memory.
void GMemFile::Open(void *Ptr, tPosition RealSize, tPosition SizeLimit)
{
	this -> Ptr = (char*)Ptr;
	this -> RealSize = RealSize;
	this -> SizeLimit = SizeLimit;
	this -> Pos = NULL;
}

// Closes a file
void GMemFile::Close()
{

}

// Reads NULL terminated string
void GMemFile::ReadNULLterminatedString(char* str)
{
	while (GMemFile::Read(str, 1))
	{
		if (!*str)
			break;

		str++;
	}
}

// Reads Bully aligned string
void GMemFile::Read4byteAlignedNULLterminatedString(char* str)
{
	char data[4];

	while (this->Read(data, 4))
	{
		if (data[3])
			*(__int32*)str = *(__int32*)data;
		else
		{
			for (int i = 0; i < 4; i++)
			{
				str[i] = data[i];

				if (!str[i])
					break;
			}

			break;
		}

		str += 4;
	}
}

// Reads to memory
GMemFile::tPosition GMemFile::Read(void* Ptr, size_t Size)
{
	if(this -> Ptr && this -> Pos < this -> RealSize)
	{
		tPosition SizeToRead = Size;

		if((this -> Pos + Size) > this -> RealSize)
			SizeToRead = this -> RealSize - this -> Pos;
		
		memcpy(Ptr, this -> Ptr + this -> Pos, SizeToRead);

		this -> Pos += SizeToRead;

		return SizeToRead;
	}
	else 
		return false;
}

// Reads one ANSI character
char GMemFile::ReadC()
{
	if(Ptr)
		return this -> Ptr[this -> Pos++];
	else
		return -1;
}
/*
// Reads one Unicode character
wchar_t GMemFile::ReadWideChar()
{
	if(Ptr)
		return this -> Ptr[this -> Pos];
	else
		return -1;
}
*/

// Writes to memory file
void GMemFile::Write(const void* Ptr, size_t Size)
{
	tPosition SizeToCopy = this -> Pos + Size > this -> SizeLimit ? this -> SizeLimit - this -> Pos : Size;
	
	memcpy(this -> Ptr + this -> Pos, Ptr, SizeToCopy);
	this -> Pos += SizeToCopy;

	if(this -> Pos > this -> RealSize)
		this -> RealSize = this -> Pos;
}

// Writes string to memory file
void GMemFile::WriteString(const char* str)
{
	this->Write(str, strlen(str) + 1);
}

// Writes 4 byte aligned NULL terminated string
bool GMemFile::Writes4byteAlignedNULLterminatedString(const char* str)
{
	while (true)
	{
		char data[4] = { 0 };
		
		for (int i = 0; i < 4; i++)
		{
			if (str[i])
				data[i] = str[i];
			else
				break;
		}

		this->Write(data, sizeof(data));

		if (!data[3])
			break;

		str += 4;
	}

	return true;
}

// Seek to certain position
bool GMemFile::Seek(size_t offset, int origin)
{
	bool result = false;

	if(origin == SEEK_SET)
	{
		if(offset >= 0 && offset <= this -> RealSize)
		{
			this -> Pos = offset;
			result = true;
		}
	}
	else if(origin == SEEK_CUR)
	{
		if(Pos + offset >= 0 && Pos + offset <= this -> RealSize)
		{
			this -> Pos += offset;
			result = true;
		}
	}
	else if(origin == SEEK_END)
	{
		if(Pos + RealSize + offset >= 0 && Pos + RealSize + offset <= RealSize)
		{
			this -> Pos += RealSize + offset;
			result = true;
		}
	}

	return result;
}

// Check End-of-File indicator
bool GMemFile::isEOF()
{
	return this -> Pos >= this -> RealSize;
}

// Returns current position
GMemFile::tPosition GMemFile::Tell()
{
	return this -> Pos;
}

// Gets pointer to file
void* GMemFile::GetPtr()
{
	return this -> Ptr;
}

// Gets Ptr + current position
void* GMemFile::GetCurPtr()
{
	return this -> Ptr + Pos;
}

// Gets filesize
size_t GMemFile::GetSize()
{
	return this -> RealSize;
}

// Sets filesize
bool GMemFile::SetSize(tPosition filesize)
{
	if (filesize <= this->SizeLimit)
	{
		this->RealSize = filesize;
		return true;
	}
	else
		return false;
}