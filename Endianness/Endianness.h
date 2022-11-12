/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

template <typename T>
using NoWrapper = T;

// Enumeration of possible value encodings.
enum eValueEncoding
{
	VALUE_ENCODING_UNDEFINED,	// never pass it to GetValue or SetValue function

	///////////
	VALUE_ENCODING_LITTLE_ENDIAN,
	VALUE_ENCODING_BIG_ENDIAN
};

// Checks if currently running machine is little endian
inline bool IsCurrentMachineLittleEndian()
{
	unsigned short value = 0x0201;

	return *(unsigned char*)&value == 0x01;
}

// Checks if currently running machine is little endian
inline bool IsCurrentMachineBigEndian()
{
	unsigned short value = 0x0201;

	return *(unsigned char*)&value == 0x02;
}

// Returns current machine value encoding
static eValueEncoding GetCurrentMachineValueEncoding()
{
	unsigned short value = 0x0201;

	if (*(unsigned char*)&value == 0x01)
		return VALUE_ENCODING_LITTLE_ENDIAN;
	else if (*(unsigned char*)&value == 0x02)
		return VALUE_ENCODING_BIG_ENDIAN;
	else
		return VALUE_ENCODING_UNDEFINED;
}

// File specific code
namespace {
	// Endian base
	template<typename T, bool(*func)()> struct tEndianBase
	{
	private:
		T value;

	public:
		// Default constructor
		tEndianBase() {}

		// Copy constructor
		tEndianBase(const tEndianBase& other)
		{
			*this = other;
		}

		// Copy constructor
		tEndianBase(const T& other)
		{
			*this = other;
		}

		// Assignment
		tEndianBase& operator=(const tEndianBase& other)
		{
			this->value = other.value;

			return *this;
		}

		// Assignment
		tEndianBase& operator=(const T& other)
		{
			if (func())
				this->value = other;
			else
			{
				for (int i = 0; i < sizeof(T); i++)
					*((char*)&this->value + i) = *((char*)&other + sizeof(T) - i - 1);
			}

			return *this;
		}

		// Convert to base type
		operator T()
		{
			T result;

			for (int i = 0; i < sizeof(T); i++)
				*((char*)&result + i) = *((char*)&this->value + sizeof(T) - i - 1);

			return result;
		}
	};
}

// Little endian
template <class T>
using tLittleEndian = tEndianBase<T, IsCurrentMachineLittleEndian>;

// Big endian
template <typename T>
using tBigEndian = tEndianBase<T, IsCurrentMachineBigEndian>;

// Varied encoding
template <typename T> struct tVariedEncoding
{
	T value;

public:
	// Sets value
	void SetValue(const T value, eValueEncoding encoding)
	{
		if (encoding == VALUE_ENCODING_LITTLE_ENDIAN || encoding == VALUE_ENCODING_BIG_ENDIAN)
		{
			if (encoding == VALUE_ENCODING_LITTLE_ENDIAN && !IsCurrentMachineLittleEndian())
			{
				for (int i = 0; i < sizeof(T); i++)
					*((char*)&this->value + i) = *((char*)&value + sizeof(T) - i - 1);
			}
			else
				this->value = value;
		}
	}

	// Returns a value
	const T GetValue(eValueEncoding encoding) const
	{
		if (encoding == VALUE_ENCODING_LITTLE_ENDIAN || encoding == VALUE_ENCODING_BIG_ENDIAN)
		{
			if (encoding == VALUE_ENCODING_LITTLE_ENDIAN && !IsCurrentMachineLittleEndian())
			{
				T result;

				for (int i = 0; i < sizeof(T); i++)
					*((char*)&result + i) = *((char*)&this->value + sizeof(T) - i - 1);

				return result;
			}
			else
				return this->value;
		}
		else
			return this->value;
	}

	// Returns value as little endian
	const T GetValueAsLittleEndian() const
	{
		return GetValue(VALUE_ENCODING_LITTLE_ENDIAN);
	}

	// Returns value as big endian
	const T GetValueAsBigEndian() const
	{
		return GetValue(VALUE_ENCODING_BIG_ENDIAN);
	}
};

#define DEFINE_ENDIAN_STRUCTURE(normal_name, fields_name) \
typedef fields_name<NoWrapper> normal_name; \
typedef fields_name<tLittleEndian> normal_name##_littleEndian; \
typedef fields_name<tBigEndian> normal_name##_bigEndian; \
typedef fields_name<tVariedEncoding> normal_name##_variedEncoding;

#define DEFINE_ENDIAN_STRUCTURE_DEFAULT(normal_name) \
DEFINE_ENDIAN_STRUCTURE(normal_name, normal_name##_template)

#define DEFINE_ENDIAN_STRUCTURE_ALIAS(to, from, fields_name) \
template <template<class> class Wrapper> \
using to##_template = fields_name<Wrapper>; \
typedef from to; \
typedef from##_littleEndian to##_littleEndian; \
typedef from##_bigEndian to##_bigEndian; \
typedef from##_variedEncoding to##_variedEncoding;

#define DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(to, from) DEFINE_ENDIAN_STRUCTURE_ALIAS(to, from, from##_template)