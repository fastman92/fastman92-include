/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "CPermutationProcessor.h"

#include <thread>
#include <windows.h>

class CRainbowTablePermutation : public CPermutationProcessor
{
	///// Rainbow table file
	__int64 lastPositionHashFound;

	// Rainbow table file handle
	FILE* RainbowTableHandle;

	// Size of buffer in ELEMENTS
	size_t RainbowTableBufferSizeInElements;

	// Buffer for reading of rainbow table file
	char* RainbowTableBuffer;

	// Amplitude from last position to search from.
	size_t RainbowTableAmplitude;

	unsigned int hashSize;

public:

	// Constructor
	CRainbowTablePermutation()
	{
		this -> lastPositionHashFound = 0;

		this -> RainbowTableHandle = NULL;

		this -> RainbowTableBuffer = NULL;		

		this -> RainbowTableBufferSizeInElements = 0;

		this -> RainbowTableAmplitude = 0;
	}	

	// Destructor
	~CRainbowTablePermutation()
	{
		this -> CloseRainbowTableFile();
	}

	// Sets hash size
	void SetHashSize(unsigned int hashSize)
	{
		this->hashSize = 0;
	}

	// Returns size of complete rainbow table
	__int64 GetSizeOfCompleteRainbowTable(int maxPermutationLength)
	{
		return this -> GetMaxNumberOfPermutations(maxPermutationLength) * this->hashSize;
	}

	// Opens rainbow table file
	bool OpenRainbowTableFile(const char* filename, size_t bufferSize, size_t amplitude)
	{
		this -> CloseRainbowTableFile();
		
		this -> RainbowTableBuffer = new char[bufferSize];

		this -> RainbowTableBufferSizeInElements = bufferSize;

		this -> RainbowTableAmplitude = amplitude;

		if(this -> RainbowTableHandle = fopen(filename, "rb"))
			return true;
		else
			return false;
	}

	// Closes rainbow table file
	void CloseRainbowTableFile()
	{
		delete[] this -> RainbowTableBuffer;
		
		if(this -> RainbowTableHandle)
		{
			fclose(this -> RainbowTableHandle);
			this -> RainbowTableHandle = NULL;
		}
	}

	// Returns permutation string by table offset
	void GetPermutationStringByTableOffset(__int64 offset, char* outString)
	{
		return this->GetPermutationStringByOrdinalNum(offset / this->hashSize, outString);
	}

	// Returns table offset by permutation string
	__int64 GetTableOffsetByPermutationString(const char* permutationString)
	{
		return this->GetOrdinalNumOfPermutationString(permutationString) * this->hashSize;
	}

	// Sets last position of hash
	void SetLastPositionOfSearchedHash(__int64 position)
	{
		this -> lastPositionHashFound = position;
	}

	/*
	// Find hash in rainbow table
	bool FindPermutationStringByHashInRainbowTableFile(T hashToFind, char* outString)
	{	
		if(this -> RainbowTableHandle)
		{			
			__int64 start = this -> lastPositionHashFound - this -> RainbowTableAmplitude;

			__int64 end = this -> lastPositionHashFound + this -> RainbowTableAmplitude;

			if(start < 0)
				start = 0;

			_fseeki64(this -> RainbowTableHandle, start, SEEK_SET);
			
			cout << endl;

			while(true)
			{
				__int64 basePosition = _ftelli64(this -> RainbowTableHandle);

				if(basePosition >= end || feof(this -> RainbowTableHandle))
					break;

				cout << "\rAmplitude search position: " << (basePosition / (1024*1024) ) << " MB";			

				size_t NumberOfHashesRead = fread(this -> RainbowTableBuffer, sizeof(T),
					(end - basePosition) / sizeof(T) > this -> RainbowTableBufferSizeInElements ?
						this -> RainbowTableBufferSizeInElements : (end - basePosition) / sizeof(T),
					this -> RainbowTableHandle);

				for(int i = 0; i < NumberOfHashesRead; i++)
				{				
					if(this -> RainbowTableBuffer[i] == hashToFind)
					{
						this -> lastPositionHashFound = basePosition + i * sizeof(T);

						this -> GetPermutationStringByTableOffset(this -> lastPositionHashFound, outString);
						return true;
					}
				}	
			}

			fseek(this -> RainbowTableHandle, 0, SEEK_SET);

			cout << endl;
			
			while(!feof(this -> RainbowTableHandle))
			{
				__int64 basePosition = _ftelli64(this -> RainbowTableHandle);

				cout << "\rNormal search position: " << (basePosition / (1024*1024) ) << " MB";
								
				size_t NumberOfHashesRead = fread(this -> RainbowTableBuffer, sizeof(T), this -> RainbowTableBufferSizeInElements, this -> RainbowTableHandle);	

				for(int i = 0; i < NumberOfHashesRead; i++)
				{
					if(this -> RainbowTableBuffer[i] == hashToFind)
					{
						this -> lastPositionHashFound = basePosition + i * sizeof(T);

						this -> GetPermutationStringByTableOffset(this -> lastPositionHashFound, outString);
						return true;
					}
				}
			}
		}

		return false;
	}
	*/
};