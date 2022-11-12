/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <type_traits>
#include <stdint.h>
#include <stdio.h>

#define DYNAMIC_MEMBER_OFFSET_UNDEFINED UINT32_MAX
// #define ENABLE_SAVING_LAST_BASE_PTR

///////////////////////////////////////
//       Dynamic structure           //
// base structure for dynamic classes//
///////////////////////////////////////
class CDynamicStructure {};

///////////////////////////////////////
//       Dynamic struct size         //
///////////////////////////////////////

// Used for size fields
class tDynamicStructEnd {};

///////////////////////////////////////
//       Dynamic struct member       //
///////////////////////////////////////

// Has an offset inside, which would be accessed easily from ASM code.
class CDynamicStructMemberBase;

// Struct member
template<class DynamicStructure, typename T> class CDynamicStructMember;
template<class DynamicStructure, typename T> class CDynamicStructMember<DynamicStructure, T[]>;
template<class DynamicStructure, typename T, int N> class CDynamicStructMember<DynamicStructure, T[N]>;
template<class DynamicStructure> class CDynamicStructMember<DynamicStructure, tDynamicStructEnd>;

///////////////////////////////////////


//////////////////////////////////////////////////////
//       Dynamic struct member array accessor       //
/////////////////////////////////////////////////////

// Struct member array accessor
template <typename T> class CDynamicStructMemberArrayAccess;

//////////////////////////////////////////////
//       Dynamic structure allocator        //
//////////////////////////////////////////////
class CDynamicStructAllocator;

//////////////////////////////////////////////
//     Type details: size and alignment     //
//////////////////////////////////////////////
class TypeDetails;

//////////////////////////////////////////////

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

		static size_t Alignment()
		{
			return std::alignment_of<T>::value;
		}
	};

	// for types, which derive from CDynamicStructMemberBase, single element
	template <
		template <typename, typename> class Tmember,
		typename DynamicStructure, typename T
	>
		struct TypeDetails<
		Tmember<DynamicStructure, T>,
		typename std::enable_if<std::is_base_of<CDynamicStructMemberBase, Tmember<DynamicStructure, T>>::value>::type
		>
	{
		static size_t SizeOf()
		{
			return TypeDetails<T>::SizeOf();
		}

		static size_t Alignment()
		{
			return TypeDetails<T>::Alignment();
		}
	};

	// for types, which derive from CDynamicStructMemberBase, an array of unknown size
	template <
		template <typename, typename> class Tmember,
		typename DynamicStructure, typename T
	>
		struct TypeDetails<
		Tmember<DynamicStructure, T[]>,
		typename std::enable_if<std::is_base_of<CDynamicStructMemberBase, Tmember<DynamicStructure, T[]>>::value>::type
		>
	{
		static size_t SizeOf()
		{
			static_assert(
				sizeof(T) == 0,
				"CDynamicStructMember with an array needs a descriptor to get its size."
				);
		}

		static size_t Alignment()
		{
			return TypeDetails<T>::Alignment();
		}
	};

	// for types, which derive from CDynamicStructMemberBase, an array of known size
	template <
		template <typename, typename> class Tmember,
		typename DynamicStructure, typename T, int N
	>
		struct TypeDetails<
		Tmember<DynamicStructure, T[N]>,
		typename std::enable_if<std::is_base_of<CDynamicStructMemberBase, Tmember<DynamicStructure, T[N]>>::value>::type
		>
	{
		static size_t SizeOf()
		{
			return N * TypeDetails<T>::SizeOf();
		}

		static size_t Alignment()
		{
			return TypeDetails<T>::Alignment();
		}
	};

	// for types, which derive from CDynamicStructure
	template<class T>
	struct TypeDetails<
		T,
		typename std::enable_if<std::is_base_of<CDynamicStructure, T>::value>::type>
	{
		static size_t SizeOf()
		{
			return T::endOfStructure.GetOffset();
		}

		static size_t Alignment()
		{
			return T::endOfStructure.maxAlignmentUsed;
		}
	};
}

// to be used in code
class TypeDetails
{
public:
	// Size of type
	template<class T> static size_t SizeOf()
	{
		return details::TypeDetails<T>::SizeOf();
	}

	template<class T> static size_t SizeOf(T& object)
	{
		return details::TypeDetails<T>::SizeOf();
	}

	// for types, which derive from CDynamicStructMemberBase, an array of unknown size
	template <
		template <typename, typename> class Tmember,
		typename DynamicStructure, typename T
	>
		static typename std::enable_if<std::is_base_of<CDynamicStructMemberBase, Tmember<DynamicStructure, T[]>>::value, size_t>::type
		SizeOf(Tmember<DynamicStructure, T[]>& member)
	{
		return member.countOfElementsAllocated * details::TypeDetails<T>::SizeOf();
	};

	// Alignment of type
	template<class T> static size_t Alignment()
	{
		return details::TypeDetails<T>::Alignment();
	}

	template<class T> static size_t Alignment(T& object)
	{
		return details::TypeDetails<T>::Alignment();
	}
};

// Struct member base
class CDynamicStructMemberBase
{
public:
	uint32_t offset;

public:
	// Returns offset
	uint32_t GetOffset() const
	{
		return this->offset;
	}

	// Sets offset
	void SetOffset(uint32_t offset)
	{
		this->offset = offset;
	}

	// Returns the pointer
	void* GetPtr(void* pObject)
	{
		return const_cast<void*>(
			static_cast<const CDynamicStructMemberBase*>(this)->GetPtr(pObject)
			);
	}

	// Returns the pointer, const version
	const void* GetPtr(const void* pObject) const
	{
		if (this->offset != DYNAMIC_MEMBER_OFFSET_UNDEFINED)
			return (const void*)((char*)pObject + this->offset);
		else
			return 0;
	}
};

#ifdef ENABLE_SAVING_LAST_BASE_PTR
extern thread_local void* SuperAccessLastBasePtr;
#endif

namespace details
{
	// Simplest case
	// The data is simple
	template<class DynamicStructure, typename T> class CDynamicStructMemberSimplestCase : public CDynamicStructMemberBase
	{
	public:
		// Returns the pointer
		T* GetPtr(DynamicStructure* pObject)
		{
			return const_cast<T*>(
				static_cast<const CDynamicStructMemberSimplestCase*>(this)->GetPtr(pObject)
				);
		}

		// Returns the pointer, const version
		const T* GetPtr(const DynamicStructure* pObject) const
		{
			if (this->offset != DYNAMIC_MEMBER_OFFSET_UNDEFINED)
				return (const T*)((char*)pObject + this->offset);
			else
				return 0;
		}

		// Access
		T& Access(DynamicStructure* pObject) {
			T* memberPtr = this->GetPtr(pObject);

		#ifdef ENABLE_SAVING_LAST_BASE_PTR
			SuperAccessLastBasePtr = memberPtr;
		#endif

			return *memberPtr;
		}

		const T& Access(const DynamicStructure* pObject) const {
			const T* memberPtr = this->GetPtr(pObject);

		#ifdef ENABLE_SAVING_LAST_BASE_PTR
			SuperAccessLastBasePtr = (void*)memberPtr;
		#endif

			return *memberPtr;
		}

	#ifdef ENABLE_SAVING_LAST_BASE_PTR
		T& Access()
		{
			T* memberPtr = this->GetPtr((DynamicStructure*)SuperAccessLastBasePtr);
			SuperAccessLastBasePtr = (void*)memberPtr;
			return *memberPtr;
		}

		const T& Access() const {
			const T* memberPtr = this->GetPtr((const DynamicStructure*)SuperAccessLastBasePtr);
			SuperAccessLastBasePtr = (void*)memberPtr;
			return *memberPtr;
		}
	#endif

		// Call operators
	#ifdef ENABLE_SAVING_LAST_BASE_PTR
		T& operator()()
		{
			T* memberPtr = this->GetPtr((DynamicStructure*)SuperAccessLastBasePtr);
			SuperAccessLastBasePtr = (void*)memberPtr;
			return *memberPtr;
		}

		const T& operator()() const {
			const T* memberPtr = this->GetPtr((const DynamicStructure*)SuperAccessLastBasePtr);
			SuperAccessLastBasePtr = (void*)memberPtr;
			return *memberPtr;
		}
	#endif

		T& operator() (DynamicStructure* pObject) {
			return this->Access(pObject);
		}

		const T& operator() (const DynamicStructure* pObject) const {
			return this->Access(pObject);
		}
	};
}

// Struct member
template<class DynamicStructure, typename T> class CDynamicStructMember : public ::details::CDynamicStructMemberSimplestCase<DynamicStructure, T>
{
};

// Struct member array accessor
template <typename T> class CDynamicStructMemberArrayAccess
{
private:
	T* pArray;

public:
	// Constructor taking an array address
	CDynamicStructMemberArrayAccess()
	{
		this->pArray = nullptr;
	}

	// Constructor taking an array address
	CDynamicStructMemberArrayAccess(T* pArray)
	{
		this->pArray = pArray;
	}
	
	// Constructor taking an array address
	CDynamicStructMemberArrayAccess(const CDynamicStructMemberArrayAccess& other)
	{
		this->pArray = other.pArray;
	}

	// Returns array pointer
	inline T* GetArrayPointer()
	{
		return this->pArray;
	}

	// Sets array pointer
	void SetArrayPtr(T* pArray)
	{
		this->pArray = pArray;
	}

	// * operator, used well with &* to get the pointer to the first element
	T& operator*()
	{
		return *pArray;
	}

	// [] operator
	T& operator[] (int index) {
		return *((T*)((char*)pArray + index * TypeDetails::SizeOf<T>()));
	}
};

////////////////////////////
namespace details
{
	template <typename T> struct ArrayElementType;

	template <typename T> struct ArrayElementType<T[]>
	{
		typedef T type;
	};
	
	template <typename T, int N> struct ArrayElementType<T[N]>
	{
		typedef T type;
	};	

	// Dynamic struct member array base
	template<class DynamicStructure, typename arrayType, class base>
	class CDynamicStructMemberArrayBase
		: public base
	{
	public:
		typedef typename ArrayElementType<arrayType>::type elementType;
		typedef CDynamicStructMemberArrayAccess<elementType> TarrayAccessor;
		
	protected:
		// Returns the pointer
		arrayType* GetPtr(DynamicStructure* pObject)
		{
			return const_cast<arrayType*>(
				static_cast<const CDynamicStructMemberArrayBase*>(this)->GetPtr(pObject)
				);
		}

		// Returns the pointer, const version
		const arrayType* GetPtr(const DynamicStructure* pObject) const
		{
			if (this->offset != DYNAMIC_MEMBER_OFFSET_UNDEFINED)
				return (const arrayType*)((char*)pObject + this->offset);
			else
				return 0;
		}

	public:
		// At index
		elementType& AtIndex(DynamicStructure* pObject, unsigned int index)
		{
			return const_cast<elementType&>(
				static_cast<const CDynamicStructMemberArrayBase*>(this)->AtIndex(pObject, index)
				);
		}

		// At index
		const elementType& AtIndex(DynamicStructure* pObject, unsigned int index) const
		{
			const arrayType* memberPtr = this->GetPtr(pObject);
			
			return *((elementType*)
				(	(char*)memberPtr +
					index * ::TypeDetails::SizeOf<elementType>()
				)
				);
		}

		// At index one
		// At index
		elementType& AtIndexZero(DynamicStructure* pObject)
		{
			return const_cast<elementType&>(
				static_cast<const CDynamicStructMemberArrayBase*>(this)->AtIndexZero(pObject)
				);
		}

		// At index
		const elementType& AtIndexZero(DynamicStructure* pObject) const
		{
			return this->AtIndex(pObject, 0);
		}
	};

	// Dynamic struct member array, element not derived from CDynamicStructure
	template<class DynamicStructure, typename arrayType, typename Sfinae = void>
	class CDynamicStructMemberArray
		: public CDynamicStructMemberArrayBase<
		DynamicStructure,
		arrayType,
		CDynamicStructMemberSimplestCase<DynamicStructure, arrayType>> {};
	
	// Dynamic struct, element derived from CDynamicStructure
	template<class DynamicStructure, class arrayType>
	struct CDynamicStructMemberArray<
		DynamicStructure,
		arrayType,
		typename std::enable_if<std::is_base_of<CDynamicStructure, typename ArrayElementType<arrayType>::type>::value>::type>
		: public
		CDynamicStructMemberArrayBase<DynamicStructure,
		arrayType,
			CDynamicStructMemberBase>
	{
	public:
		using typename CDynamicStructMemberArrayBase<DynamicStructure,
			arrayType,
			CDynamicStructMemberBase>::TarrayAccessor;
		using typename CDynamicStructMemberArrayBase<DynamicStructure,
			arrayType,
			CDynamicStructMemberBase>::elementType;

		// Access
		TarrayAccessor Access(DynamicStructure* pObject) {
			elementType* memberPtr = *this->GetPtr(pObject);

		#ifdef ENABLE_SAVING_LAST_BASE_PTR
			SuperAccessLastBasePtr = memberPtr;
		#endif

			return TarrayAccessor(memberPtr);
		}

		const TarrayAccessor Access(const DynamicStructure* pObject) const {
			const elementType* memberPtr = *this->GetPtr(pObject);

		#ifdef ENABLE_SAVING_LAST_BASE_PTR
			SuperAccessLastBasePtr = memberPtr;
		#endif

			return TarrayAccessor(memberPtr);
		}

		// Call operators
		TarrayAccessor operator() (DynamicStructure* pObject) {
			return this->Access(pObject);
		}

		const TarrayAccessor operator() (const DynamicStructure* pObject) const {
			return this->Access(pObject);
		}
	};
}
///////////////////////////

// Struct member array, unknown size
template<class DynamicStructure, typename T> class CDynamicStructMember<DynamicStructure, T[]>
	: public details::CDynamicStructMemberArray<DynamicStructure, T[]>
{
public:
	unsigned int countOfElementsAllocated;

	/*
	// Constructor
	CDynamicStructMember()
	{
		this->countOfElementsAllocated = 0;
	}
	*/

	// Returns count of array
	unsigned int GetArrayCount() {
		return this->countOfElementsAllocated;
	}
};

// Struct member array, known size
template<class DynamicStructure, typename T, int N> class CDynamicStructMember<DynamicStructure, T[N]>
	: public details::CDynamicStructMemberArray<DynamicStructure, T[N]>
{};

// Struct member tDynamicStructSize
template<class DynamicStructure> class CDynamicStructMember<DynamicStructure, tDynamicStructEnd>
	: public CDynamicStructMemberBase {
public:
	uint32_t maxAlignmentUsed;
};

///////////////////////////////////////
//      Dynamic struct allocator     //
///////////////////////////////////////

// Dynamic structure allocator
class CDynamicStructAllocator
{
private:
	template<class Tmember, class T>
	void AllocateBasic(
		Tmember& member,
		unsigned int numberOfArrayElements)
	{
		member.SetOffset(this->AllocateUnknownData<T>(numberOfArrayElements));
	}

public:
	uint32_t m_position;
	uint8_t m_alignment;
	uint32_t maxAlignmentUsed;

	// Initializes
	CDynamicStructAllocator()
	{
		this->m_position = 0;
		this->m_alignment = 8;
		this->maxAlignmentUsed = 1;
	}

	// Sets alignment
	void InitPerStruct(uint8_t alignment = 8)
	{
		this->m_position = 0;
		this->m_alignment = alignment;
		this->maxAlignmentUsed = 1;
	}

	// Sets alignment
	void SetAlignment(uint8_t alignment)
	{
		this->m_alignment = alignment;
	}

	// Sets alignment
	void SetMaxAlignmentUsed(uint8_t maxAlignmentUsed)
	{
		this->maxAlignmentUsed = maxAlignmentUsed;
	}

	// Returns top position
	uint32_t GetTop()
	{
		return this->m_position;
	}

	// Sets top position
	void SetTop(uint32_t top)
	{
		this->m_position = top;
	}

	// Allocates a none member
	void SkipBytes(uint32_t value)
	{
		this->m_position += value;
	}

	// Simplest case
	template<template<class, class> class Tmember, class DynamicStructure, typename T>
	void Allocate(Tmember<DynamicStructure, T>& member)
	{	
		this->AllocateBasic<Tmember<DynamicStructure, T>, T>(member, 1);
	}

	// Allocates a member, array of known size
	template<template<class, class> class Tmember, class DynamicStructure, typename T, unsigned int N>
	void Allocate(Tmember<DynamicStructure, T[N]>& member)
	{
		this->AllocateBasic<Tmember<DynamicStructure, T[N]>, T>(member, N);
	}
	
	// Allocates a member, array of unknown size	
	template<template<class, class> class Tmember, class DynamicStructure, typename T>
	void Allocate(Tmember<DynamicStructure, T[]> &member,
		unsigned int numberOfElements
	)
	{
		this->AllocateBasic<Tmember<DynamicStructure, T[]>, T>(member, numberOfElements);

		member.countOfElementsAllocated = numberOfElements;
	}

	// Allocates a data
	template<template<class, class> class Tmember, class DynamicStructure, typename T, unsigned int N>
	void Allocate(Tmember<DynamicStructure, T>& member)
	{
		this->AllocateBasic<Tmember<DynamicStructure, T>, T>(member, N);
	}

	// Allocates the end of structure
	template<template<class, class> class Tmember, class DynamicStructure>
	void Allocate(Tmember<DynamicStructure, tDynamicStructEnd>& member)
	{
		unsigned int alignmentUsed = this->maxAlignmentUsed;

		if (alignmentUsed > this->m_alignment)
			alignmentUsed = this->m_alignment;

		uint32_t top = this->GetTop();
		uint32_t rest = top % alignmentUsed;

		if (rest != 0)
			top += (alignmentUsed - rest);

		member.SetOffset(top);
		this->SetTop(top);
		member.maxAlignmentUsed = this->maxAlignmentUsed;
	}
	
	// Allocates parent structure
	// Parent structure should have a member endOfStructure
	template<template<class, class> class Tmember, class DynamicStructure>
	void AllocateParentStructure(
		Tmember<DynamicStructure, tDynamicStructEnd> endOfParentStructure)
	{
		static_assert(std::is_base_of<CDynamicStructure, DynamicStructure>::value,
			"A parent structure should be derived from CDynamicStructure");

		if (endOfParentStructure.maxAlignmentUsed > this->maxAlignmentUsed)		
			this->maxAlignmentUsed = endOfParentStructure.maxAlignmentUsed;
		
		this->m_position += endOfParentStructure.GetOffset();
	}

	template<class T> unsigned int AllocateUnknownData(
		unsigned int numberOfArrayElements = 1)
	{
		unsigned int alignmentUsed = TypeDetails::Alignment<T>();

		if (alignmentUsed > this->m_alignment)
			alignmentUsed = this->m_alignment;

		if (alignmentUsed > this->maxAlignmentUsed)
			this->maxAlignmentUsed = alignmentUsed;

		uint32_t top = this->GetTop();
		uint32_t rest = top % alignmentUsed;

		if (rest != 0)
			top += alignmentUsed - rest;

		this->SetTop(top + numberOfArrayElements * TypeDetails::SizeOf<T>());

		return top;
	}
};

///////////////////////////////////////
//              Macroes              //
///////////////////////////////////////
/*
#define PUT_DYNAMIC_MEMBER_DECLARATION(xclass, type, name) CDynamicStructMember<xclass, type> name;

#define PUT_STATIC_DYNAMIC_MEMBER_DECLARATION(xclass, type, name) static CDynamicStructMember<xclass, type> name;
#define PUT_STATIC_DYNAMIC_MEMBER_DEFINITION(xclass, type, name) CDynamicStructMember<xclass, type> xclass::name;
*/

#define SINGLE_ARG(...) __VA_ARGS__

////// class //////
// static ones
#define STRUCTURE_STATIC_MEMBER_DECLARATION(structName, type, memberName) \
static type memberName;

#define STRUCTURE_STATIC_MEMBER_DEFINITION(structName, type, memberName) \
type structName::memberName;

////// offset variables //////
#define STRUCTURE_MEMBER_OFFSET_VARIABLE_DEFINITION(structName, type, memberName) \
uint32_t Offset_##structName##__##memberName = 0

#define STRUCTURE_MEMBER_OFFSET_VARIABLE_ASSIGNMENT(structName, type, memberName) \
Offset_##structName##__##memberName = structName::memberName.GetOffset()

////////////////////
// macro(structName, SINGLE_ARG(CDynamicStructMember<structName, tDynamicStructEnd>), endOfStructure)