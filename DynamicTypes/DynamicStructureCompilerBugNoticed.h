/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <type_traits>
#include <stdint.h>
#include <stdio.h>

///////////////////////////////////////
//       Dynamic structure           //
// base structure for dynamic classes//
///////////////////////////////////////
class CDynamicStructure {};

///////////////////////////////////////
//       Dynamic struct member       //
///////////////////////////////////////

// Has an offset inside, which would be accessed easily from ASM code.
class CDynamicStructMemberBase;

// Struct member
template<class DynamicStructure, typename T> class CDynamicStructMember;
template<class DynamicStructure, typename T> class CDynamicStructMember<DynamicStructure, T[]>;

///////////////////////////////////////


//////////////////////////////////////////////////////
//       Dynamic struct member array accessor       //
/////////////////////////////////////////////////////

//////////////////////////////////////////////
//     Type details: size and alignment     //
//////////////////////////////////////////////
class TypeDetails;

//////////////////////////////////////////////

// Struct member base
class CDynamicStructMemberBase {};

// Struct member array, unknown size
template<class DynamicStructure, typename T> class CDynamicStructMember<DynamicStructure, T[]>
	: public CDynamicStructMemberBase
{
public:
	unsigned int countOfElementsAllocated;
};

///////////////////////////////////////
//           Type details            //
///////////////////////////////////////
namespace details
{
	// for all other types
	template<class T, typename Sfinae = void>
	struct TypeDetails
	{
		static size_t SizeOf()
		{
			return sizeof(T);
		}
	};
}

// to be used in code
class TypeDetails
{
public:

	// bug, if using this function

	// for types, which derive from CDynamicStructMemberBase, an array of unknown size
	template <
		template <typename, typename> class Tmember,
		typename DynamicStructure, typename T
	>
		static typename std::enable_if<std::is_base_of<details::CDynamicStructMemberBase, Tmember<DynamicStructure, T[]>>::value, size_t>::type
		SizeOf(Tmember<DynamicStructure, T[]>& member)
	{
		return member.countOfElementsAllocated * details::TypeDetails<T>::SizeOf();
	};
};