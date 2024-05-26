/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

/*
	Author: fastman92

	Description: Bitwise operations.
*/

#pragma once

namespace BitwiseOperation
{
	// Changes n bits on specified position to new value.
	inline unsigned int ChangeMultipleBits(unsigned int num, char position, char numberOfBits, unsigned int newValue)
	{
		unsigned int mask = (1 << numberOfBits)-1;
		return num & ~(mask << position) | ((newValue & mask) << position);
	}

	// Clears multiple bits
	inline unsigned int SetMultipleBits(unsigned int num, char position, char numberOfBits)
	{
		unsigned int mask = (1 << numberOfBits)-1;
		return num | (mask << position);
	}

	// Clears multiple bits
	inline unsigned int ClearMultipleBits(unsigned int num, char position, char numberOfBits)
	{
		unsigned int mask = (1 << numberOfBits)-1;
		return num & ~(mask << position);
	}

	// Reads value from bits
	inline unsigned int ReadValueFromBits(unsigned int num, char position, char numberOfBits)
	{
		unsigned int mask = (1 << numberOfBits)-1;
		return (num >> position) & mask;
	}

	// Sets one bit
	inline unsigned int SetOneBit(unsigned int num, char position)
	{
		return num | (1 << position);
	}

	// Clears one bit
	inline unsigned int ClearOneBit(unsigned int num, char position)
	{
		return num & ~(1 << position);
	}

	// Changes one bit
	inline unsigned int ChangeOneBit(unsigned int num, char position, bool newValue)
	{
		return num & ~(1 << position) | (newValue << position);
	}

	// Returns one bit
	inline bool TestBit(unsigned int num, char position)
	{
		return (num & (1 << position)) != 0;
	}

	// Returns shift from value, for example
	inline int GetShiftFromValue(unsigned int num)
	{
		const int numberOfBits = sizeof(unsigned int) * 8;

		unsigned int mask = 1;

		for (int i = 0; i < numberOfBits; i++)
		{
			if (num & mask)
			{
				if (num & (~mask))
					return -1;
				else
					return i;
			}

			mask <<= 1;
		}

		return -1;
	}

	// Replaces bit positions
	template<class tNum> inline
		tNum ReplaceBitPositions(char* PositionArray, tNum num)
	{
		char i = sizeof(num) * 8 - 1;

		tNum newNum = 0;

		do
		{
			newNum |= (num & (1 << (i))) << (PositionArray[i] - i);
			newNum |= (num & (1 << (i - 1))) << (PositionArray[i - 1] - i + 1);
			newNum |= (num & (1 << (i - 2))) << (PositionArray[i - 2] - i + 2);
			newNum |= (num & (1 << (i - 3))) << (PositionArray[i - 3] - i + 3);
			newNum |= (num & (1 << (i - 4))) << (PositionArray[i - 4] - i + 4);
			newNum |= (num & (1 << (i - 5))) << (PositionArray[i - 5] - i + 5);
			newNum |= (num & (1 << (i - 6))) << (PositionArray[i - 6] - i + 6);
			newNum |= (num & (1 << (i - 7))) << (PositionArray[i - 7] - i + 7);
			i -= 8;
		} while (i >= 0);

		return newNum;
	}
}