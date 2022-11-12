/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/
#pragma once
#include <stdint.h>

typedef unsigned char tByte[10];
typedef unsigned char tMMXvalue[10];

class CMachineContext_x86
{
public:
	

	/////////// General registers
	struct
	{
		// EAX
		union {
			int32_t eax;
			int16_t ax;

			struct {
				int8_t al;
				int8_t ah;
			};
		};

		// EBX
		union {
			int32_t ebx;
			int16_t bx;

			struct {
				int8_t bl;
				int8_t bh;
			};
		};

		// ECX
		union {
			int32_t ecx;
			int16_t cx;

			struct {
				int8_t cl;
				int8_t ch;
			};
		};

		// EDX
		union {
			int32_t edx;
			int16_t dcx;

			struct {
				int8_t dl;
				int8_t dh;
			};
		};

		// ESI
		union {
			int32_t esi;
			int16_t si;
		};

		// EDI
		union {
			int32_t edi;
			int16_t di;
		};

		// EBP
		union
		{
			int32_t EBP;
			int16_t bp;
		};	

		// ESP
		union
		{
			int32_t ESP;
			int16_t SP;
		};
	} registers;

	///////////
	// FLAGS
	union {
		uint32_t flags;

		struct
		{
			unsigned char CF : 1;	// Carry flag	Status
			unsigned char flag_1 : 1;	// Reserved, always 1 in EFLAGS[2]
			unsigned char PF : 1;	// Parity flag	Status
			unsigned char flag_3 : 1;	// Reserved
			unsigned char AF : 1;	// Adjust flag	Status
			unsigned char flag_5 : 1;	// Zero flag	Status
			unsigned char ZF : 1;	// Reserved
			unsigned char SF : 1;	// Sign flag	Status
			unsigned char TF : 1;	// Trap flag(single step)	Control
			unsigned char IF : 1;	// Interrupt enable flag	Control
			unsigned char DF : 1;	// Direction flag	Control
			unsigned char OF : 1;	// Overflow flag	Status
			unsigned char IOPL : 2;	// IOPL	I / O privilege level(286 + only), always 1 on 8086 and 186	System
			unsigned char NT : 1;	// Nested task flag(286 + only), always 1 on 8086 and 186	System
			unsigned char flag_15 : 1;	// Reserved

			unsigned char RF : 1;	// Resume flag(386 + only)	System
			unsigned char VM : 1;	// Virtual 8086 mode flag(386 + only)	System
			unsigned char AC : 1;	// Alignment check(486SX + only)	System
			unsigned char VIF : 1;	// Virtual interrupt flag(Pentium + )	System
			unsigned char VIP : 1;	// Virtual interrupt pending(Pentium + )	System
			unsigned char ID : 1;	// Able to use CPUID instruction(Pentium + )	System
			unsigned char flag_22 : 1;	// Reserved
			unsigned char flag_24: 1;	// Reserved
			unsigned char flag_25 : 1;	// Reserved
			unsigned char flag_26 : 1;	// Reserved
			unsigned char flag_27 : 1;	// Reserved
			unsigned char flag_28 : 1;	// Reserved
			unsigned char flag_29 : 1;	// Reserved
			unsigned char flag_30 : 1;	// Reserved
			unsigned char flag_31 : 1;	// Reserved
		};
	};

	/////////// FPU / MMX registers

	union
	{
		union {
			tByte array[8];

			tByte ST0;
			tByte ST1;
			tByte ST2;
			tByte ST3;
			tByte ST4;
			tByte ST5;
			tByte ST6;
			tByte ST7;
		} FPUregisters;

		union {
			tMMXvalue array[8];
			tMMXvalue MM0;
			tMMXvalue MM1;
			tMMXvalue MM2;
			tMMXvalue MM3;
			tMMXvalue MM4;
			tMMXvalue MM5;
			tMMXvalue MM6;
			tMMXvalue MM7;
		} MMXregisters;
	};

	union
	{
		uint16_t flags;

		struct
		{
			unsigned char IM : 1;
			unsigned char DM : 1;
			unsigned char ZM : 1;
			unsigned char OM : 1;
			unsigned char UM : 1;
			unsigned char PM : 1;
			unsigned char flag_6 : 1;
			unsigned char IEM : 1;
			unsigned char PC : 2;
			unsigned char RC : 2;
			unsigned char IC : 1;
			unsigned char flag_13 : 1;
			unsigned char flag_14 : 1;
			unsigned char flag_15 : 1;
		};
	} FPUcontrol;

	union
	{
		uint16_t flags;

		unsigned char I : 1;
		unsigned char D : 1;
		unsigned char Z : 1;
		unsigned char O : 1;
		unsigned char U : 1;
		unsigned char P : 1;
		unsigned char SF : 1;
		unsigned char IR : 1;
		unsigned char C0 : 1;
		unsigned char C1 : 1;
		unsigned char C2 : 1;
		unsigned char TOP : 3;
		unsigned char C3 : 1;
		unsigned char B : 1;
	} FPUstatus;

	union FPUtag
	{
		uint16_t flags;

		unsigned char tag_0 : 2;
		unsigned char tag_1 : 2;
		unsigned char tag_2 : 2;
		unsigned char tag_3 : 2;
		unsigned char tag_4 : 2;
		unsigned char tag_5 : 2;
		unsigned char tag_6 : 2;
		unsigned char tag_7 : 2;
	} FPU_tags;

	/////////// XMMX registers
};