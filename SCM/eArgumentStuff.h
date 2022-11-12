// Author: fastman92

#pragma once

namespace SCM
{
	namespace ArgumentStuff
	{
		enum class eArgumentDataTypesFormat_GTA_III_VC_SA : unsigned char
		{
			UNDEFINED,
			END_OF_ARGUMENTS = UNDEFINED,

			STATIC_INT_32BITS,			// Static number: (Long) Integer  – 32 bits
			GLOBAL_NUMBER_VARIABLE,		// Global 4-byte integer  /float variable multiplied by 4: (Short) Integer  – 16 bits
			LOCAL_NUMBER_VARIABLE,		// Local variable:  (Short) Integer  – 16 bits
			STATIC_INT_8BITS,			// Static number: (Char) Integer  – 8 bits
			STATIC_INT_16BITS,			// Static number: (Short) Integer  – 16 bits
			STATIC_FLOAT,				// Float IEEE 754 – 32 bits

			// Types below are only available in GTA SA
			TYPES_INTRODUCED_IN_GTASA,

			// Number arrays
			GLOBAL_NUMBER_ARRAY = TYPES_INTRODUCED_IN_GTASA,
			LOCAL_NUMBER_ARRAY,

			STATIC_SHORT_STRING,
			GLOBAL_SHORT_STRING_VARIABLE,
			LOCAL_SHORT_STRING_VARIABLE,

			GLOBAL_SHORT_STRING_ARRAY,
			LOCAL_SHORT_STRING_ARRAY,

			STATIC_PASCAL_STRING,
			STATIC_LONG_STRING,
			GLOBAL_LONG_STRING_VARIABLE,
			LOCAL_LONG_STRING_VARIABLE,

			GLOBAL_LONG_STRING_ARRAY,
			LOCAL_LONG_STRING_ARRAY,	// ID 19

			// added by Sanny Builder and CLEO
			STATIC_INT_64BITS,			// 20, Static number: (Long) Integer  – 64 bits, for example 0x12345678912357
			LOCAL_INT64_VARIABLE¨,	// 21, Local variable:  (Short) Integer  – 16 bits, for example 4@int64 in Sanny Builder

		};

		enum class eArgumentDataTypesFormat_GTA_LCS_VCS : unsigned char
		{
			UNDEFINED,
			END_OF_ARGUMENTS = UNDEFINED,

			STATIC_INT_ZERO,
			STATIC_FLOAT_ZERO,

			STATIC_FLOAT_PACKED_POSITIVE_1_LAST_BYTE,
			STATIC_FLOAT_PACKED_POSITIVE_2_LAST_BYTES,
			STATIC_FLOAT_PACKED_POSITIVE_3_LAST_BYTES,

			STATIC_INT_32BITS,		// Static number: (Long) Integer  – 32 bits

			STATIC_INT_8BITS,			// Static number: (Char) Integer  – 8 bits

			STATIC_INT_16BITS,			// Static number: (Short) Integer  – 16 bits

			STATIC_FLOAT,				// Float IEEE 754 – 32 bits

			VCS_STATIC_C_STRING = 10,
			
			LCS_TIMER_RANGE_FIRST = 10,

			LCS_TIMER_RANGE_LAST,

			VCS_RANGE_FIRST = 11,

			VCS_RANGE_LAST = 12,

			// local variable
			LCS_LOCAL_VARIABLE_RANGE_FIRST = 12,	// local variable 0@			
			LCS_LOCAL_VARIABLE_RANGE_LAST = LCS_LOCAL_VARIABLE_RANGE_FIRST + 95,	// local variable 95@

			VCS_LOCAL_VARIABLE_RANGE_FIRST = 13,	// local variable 0@
			VCS_LOCAL_VARIABLE_RANGE_LAST = VCS_LOCAL_VARIABLE_RANGE_FIRST + 95,

			// local variable + index:local variable
			LCS_LOCAL_ARRAY_RANGE_FIRST = LCS_LOCAL_VARIABLE_RANGE_LAST + 1,		// local index with local index
			LCS_LOCAL_ARRAY_RANGE_LAST = LCS_LOCAL_ARRAY_RANGE_FIRST + 95,

			VCS_LOCAL_ARRAY_RANGE_FIRST = VCS_LOCAL_VARIABLE_RANGE_LAST + 1,		// local index with local index
			VCS_LOCAL_ARRAY_RANGE_LAST = VCS_LOCAL_ARRAY_RANGE_FIRST + 95,

			// global variable
			LCS_GLOBAL_VARIABLE_RANGE_FIRST = 204,		// array multiplier = 0
			LCS_GLOBAL_VARIABLE_RANGE_LAST = LCS_GLOBAL_VARIABLE_RANGE_FIRST + 25,		// array multiplier = 24

			VCS_GLOBAL_VARIABLE_RANGE_FIRST = 205,
			VCS_GLOBAL_VARIABLE_RANGE_LAST = VCS_GLOBAL_VARIABLE_RANGE_FIRST + 24,

			// global variable + index:local variable
			LCS_GLOBAL_ARRAY_RANGE_FIRST = 230,		// global index with local offset
			LCS_GLOBAL_ARRAY_RANGE_LAST = LCS_GLOBAL_ARRAY_RANGE_FIRST + 25,			// global index with local offset

			VCS_GLOBAL_ARRAY_RANGE_FIRST = VCS_GLOBAL_VARIABLE_RANGE_LAST + 1,		// global index with local offset
			VCS_GLOBAL_ARRAY_RANGE_LAST = VCS_GLOBAL_ARRAY_RANGE_FIRST + 24,			// global index with local offset
		};
		/*
		// Prefix increment
		inline eArgumentDataTypesFormat_GTA_LCS_VCS& operator+(eGameName& game)
		{
			game = static_cast<eGameName>(game + 1);
			return game;
		}*/

		/*

		enum class eArgumentDataTypesFormat_GTA_LCS_VCS : BYTE
		{
			UNDEFINED,
			END_OF_ARGUMENTS = UNDEFINED,

			STATIC_INT_ZERO,
			STATIC_FLOAT_ZERO,

			STATIC_FLOAT_PACKED_POSITIVE_1_LAST_BYTE,
			STATIC_FLOAT_PACKED_POSITIVE_2_LAST_BYTES,
			STATIC_FLOAT_PACKED_POSITIVE_3_LAST_BYTES,

			STATIC_INT_32BITS,		// Static number: (Long) Integer  – 32 bits

			STATIC_INT_8BITS,			// Static number: (Char) Integer  – 8 bits

			STATIC_INT_16BITS,			// Static number: (Short) Integer  – 16 bits

			STATIC_FLOAT,				// Float IEEE 754 – 32 bits

			STATIC_C_STRING,

			LOCAL_VARIABLE_TIMER_A,

			LOCAL_VARIABLE_RANGE_FIRST = LOCAL_VARIABLE_TIMER_A + 2,	// local variable 0@
			
			LOCAL_VARIABLE_RANGE_LAST = LOCAL_VARIABLE_RANGE_FIRST + 94,	// local variable 94@

			LOCAL_ARRAY_RANGE_FIRST,		// local index with local index
			LOCAL_ARRAY_RANGE_LAST = LOCAL_ARRAY_RANGE_FIRST + 94,

			UNKNOWN_TYPE_202,

			GLOBAL_VARIABLE_RANGE_FIRST = 205,		// array multiplier = 0

			GLOBAL_VARIABLE_RANGE_LAST = GLOBAL_VARIABLE_RANGE_FIRST + 24,		// array multiplier = 24

			UNKNOWN_VARIABLE_TYPE_0xE5,

			GLOBAL_ARRAY_RANGE_FIRST,		// global index with local offset

			GLOBAL_ARRAY_RANGE_LAST = GLOBAL_ARRAY_RANGE_FIRST + 24,			// global index with local offset

			// UNKNOWN_ARRAY_TYPE_0xFF
		};
		*/

		enum class eArgumentDataTypes_Universal
		{
			UNDEFINED,

			END_OF_ARGUMENTS,

			GLOBAL_NUMBER_VARIABLE,		// Global 4-byte integer  /float variable multiplied by 4: (Short) Integer  – 16 bits
			LOCAL_NUMBER_VARIABLE,		// Local variable:  (Short) Integer  – 16 bits

			STATIC_INT_8BITS,			// Static number: (Char) Integer  – 8 bits
			STATIC_INT_16BITS,			// Static number: (Short) Integer  – 16 bits
			STATIC_INT_32BITS,			// Static number: (Long) Integer  – 32 bits

			STATIC_INT_ZERO,

			STATIC_FLOAT,				// Float IEEE 754 – 32 bits						
			STATIC_FLOAT_POSITIVE_PACKED_1_LAST_BYTE,
			STATIC_FLOAT_POSITIVE_PACKED_2_LAST_BYTES,
			STATIC_FLOAT_POSITIVE_PACKED_3_LAST_BYTES,
			STATIC_FLOAT_ZERO,

			// Number arrays
			GLOBAL_NUMBER_ARRAY,
			LOCAL_NUMBER_ARRAY,

			// Types below are only available in GTA SA
			TYPES_INTRODUCED_IN_GTASA,

			STATIC_SHORT_STRING = TYPES_INTRODUCED_IN_GTASA,
			GLOBAL_SHORT_STRING_VARIABLE,
			LOCAL_SHORT_STRING_VARIABLE,

			GLOBAL_SHORT_STRING_ARRAY,
			LOCAL_SHORT_STRING_ARRAY,

			STATIC_PASCAL_STRING,
			STATIC_C_STRING,
			STATIC_LONG_STRING,
			GLOBAL_LONG_STRING_VARIABLE,
			LOCAL_LONG_STRING_VARIABLE,

			GLOBAL_LONG_STRING_ARRAY,
			LOCAL_LONG_STRING_ARRAY
		};
	}
}