/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/


///////////////////////////////////////
//      Dynamic struct allocator     //
///////////////////////////////////////

// Dynamic structure allocator
template<typename T> class CDynamicEnumAllocator
{
private:
	T currentIndex;

public:
	// Constructor
	CDynamicEnumAllocator()
	{
		this->currentIndex = 0;
	}

	// Allocates a member of enumeration
	void Allocate(T& member)
	{
		member = this->currentIndex;
		this->currentIndex++;
	}

	// Sets current index
	void AllocateSpecificIndex(T& member, T member_value)
	{
		this->currentIndex = member_value;
		member = this->currentIndex;

		this->currentIndex++;;
	}

	// Adds a value to current index
	void Skip(T number)
	{
		this->currentIndex += number;
	}

};