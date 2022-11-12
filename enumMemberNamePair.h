/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <algorithm>
#include <string>

#define PUT_ENUM_MEMBER_FROM_LIST(member, ...) member,
#define PUT_ENUM_MEMBER_NAME_FOR_PAIR(member, ...) { member, #member},

#define DECLARE_LIST_WITH_ENUM_MEMBER_AND_NAME(arrayName, eType, listMacro) \
	static const enumMemberNamePair<eType> arrayName[] = \
	{ \
		listMacro(PUT_ENUM_MEMBER_NAME_FOR_PAIR) \
	};

template <typename enumMemberType, typename nameType = const char*> struct enumMemberNamePair
{		
	typedef enumMemberType tEnumMember;
	typedef nameType tName;

	enumMemberType enumMember;
	nameType name;
	/*
	bool operator== (const nameType name) const
	{		
		return this -> name == name;
	}

	bool operator== (const enumMemberType enumMember) const
	{		
		return this -> enumMember == enumMember;
	}
	*/
};

// Returns enum member-name pair.
// Returns NULL if not found.
template <typename enumMemberNamePairType, size_t _Size, typename searchedValueType> enumMemberNamePairType* getEnumPairFromArrayByMember(enumMemberNamePairType (&enumMemberNameArray)[_Size], searchedValueType searchedEnumMember)
{
	const enumMemberNamePairType* pair = std::find_if(
		enumMemberNameArray,
		enumMemberNameArray + _Size,
		[&](enumMemberNamePairType& pair)
		{
			return pair.enumMember == searchedEnumMember;
		}
	);

	return pair != enumMemberNameArray + _Size ? pair : nullptr;
}

// Returns enum member-name pair.
// Returns NULL if not found.
// template <typename enumMemberNamePairType, size_t _Size, typename searchedValueType> enumMemberNamePairType* getEnumPairFromArrayByName(enumMemberNamePairType (&enumMemberNameArray)[_Size], searchedValueType searchedName);
	/*
{
	const enumMemberNamePairType* pair = std::find_if(
		enumMemberNameArray,
		enumMemberNameArray + _Size,
		[&](enumMemberNamePairType& pair)
		{
			return pair.name == searchedName;
		}
	);

	return pair != enumMemberNameArray + _Size ? pair : nullptr;
}
*/

// Returns enum member-name pair.
// Returns NULL if not found.
template <typename enumMemberNamePairType, size_t _Size, typename tSearchedName, typename tCmpFunc> enumMemberNamePairType* _getEnumPairFromArrayByNameHelper(enumMemberNamePairType (&enumMemberNameArray)[_Size], tSearchedName* searchedName, tCmpFunc cmpFunc)
{
	const enumMemberNamePairType* pair = std::find_if(
		enumMemberNameArray,
		enumMemberNameArray + _Size,
		[&](enumMemberNamePairType& pair)
		{
			return pair.name == searchedName || !cmpFunc(pair.name, searchedName);
		}
	);

	return pair != enumMemberNameArray + _Size ? pair : nullptr;
}

// Returns enum member-name pair.
// Returns NULL if not found.
template <typename enumMemberNamePairType, size_t _Size> enumMemberNamePairType* getEnumPairFromArrayByName(enumMemberNamePairType (&enumMemberNameArray)[_Size], const char* searchedName)
{
	return _getEnumPairFromArrayByNameHelper(enumMemberNameArray, searchedName, strcmp);
}

// Returns enum member-name pair.
// Returns NULL if not found.
template <typename enumMemberNamePairType, size_t _Size> enumMemberNamePairType* getEnumPairFromArrayByName(enumMemberNamePairType (&enumMemberNameArray)[_Size], const wchar_t* searchedName)
{
	return _getEnumPairFromArrayByNameHelper(enumMemberNameArray, searchedName, wcscmp);
}

// Returns name by enum member.
// Returns NULL if not found.
template <typename enumMemberNamePairType, size_t _Size, typename enumMemberType>
 typename enumMemberNamePairType::tName getNameByEnumMemberFromArray(enumMemberNamePairType (&enumMemberNameArray)[_Size], enumMemberType searchedEnumMember)
{
	const enumMemberNamePairType* pair = getEnumPairFromArrayByMember(enumMemberNameArray, searchedEnumMember);

	return pair !=NULL ? pair -> name : NULL;
}

////////////////////////////////
// template tEnumMemberNameManager
// //DECLARE_LIST_WITH_ENUM_MEMBER_AND_NAME(pairArray, enumMemberType, listMacro); 

#define GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName) __##managerTypeName##_pairArray

#define DECLARE_ENUM_MEMBER_NAME_MANAGER_TYPE(managerTypeName, enumMemberType, undefinedMember, listMacro) \
	DECLARE_LIST_WITH_ENUM_MEMBER_AND_NAME(GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName), enumMemberType, listMacro) \
	class managerTypeName \
	{ \
	public: \
		\
		/* Finds enum member by name */ \
		static enumMemberType GetEnumMemberByName(const char* name) \
		{ \
			const enumMemberNamePair<enumMemberType>* pair = getEnumPairFromArrayByName(GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName), name); \
			\
			return pair != NULL ? pair->enumMember : undefinedMember; \
		} \
		\
		/* Finds name by enum member */ \
		static const char* GetEnumNameByMember(enumMemberType game) \
		{ \
			return getNameByEnumMemberFromArray(GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName), game); \
		} \
		\
	};

class CEnumMemberNameManagerBase
{
public:
	/* Finds enum member by name */
	virtual int GetEnumMemberByName(const char* name) const = 0;

	/* Finds name by enum member */
	virtual const char* GetEnumNameByMember(int member) const = 0;
};

#define DECLARE_ENUM_MEMBER_NAME_MANAGER_TYPE_CLASS(managerTypeName, enumMemberType, undefinedMember, listMacro) \
	DECLARE_LIST_WITH_ENUM_MEMBER_AND_NAME(GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName), enumMemberType, listMacro) \
	class managerTypeName : public CEnumMemberNameManagerBase\
	{ \
	public: \
		\
		/* Finds enum member by name */ \
		virtual int GetEnumMemberByName(const char* name) const \
		{ \
			const enumMemberNamePair<enumMemberType>* pair = getEnumPairFromArrayByName(GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName), name); \
			\
			return pair != NULL ? pair->enumMember : undefinedMember; \
		} \
		\
		/* Finds name by enum member */ \
		virtual const char* GetEnumNameByMember(int member) const \
		{ \
			return getNameByEnumMemberFromArray(GET_NAME_OF_PAIR_ARRAY_FOR_TYPE(managerTypeName), member); \
		} \
		\
	};