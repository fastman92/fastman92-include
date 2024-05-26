/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

/* Useful links:
	https://stackoverflow.com/questions/28109826/arm64-using-gas-on-ios
*/


// Stringify
#if !defined(STRINGIFY) || defined(TOSTRING)
#define STRINGIFY(str) #str
#define TOSTRING(x) STRINGIFY(x)
#endif

#define EXPAND_MACRO_HELPER(x) x
#define EXPAND_MACRO(x) EXPAND_MACRO_HELPER(x)

// Aligned address
#define GET_ALIGNED_ADDRESS(requested_size, block_size) (requested_size % block_size == 0 ? requested_size : ((requested_size / block_size)+1)*block_size)

// Deference
#define ACCESS_DEF(arg) (*arg)

// Author of macro: fastman92
#define MAKE_DEAD_IF() if(0)92

// ASM code macros
#ifdef __GNUC__
#define BALIGN(balignment) ".balign " #balignment"\n"
#define P2ALIGN(p2alignment) ".p2align " #p2alignment"\n"

#define PUT_LABEL_ID(label_id) #label_id":\n"

#define ASM_PUT_CONSTANT_VALUE(label_id, value, type, balignment) BALIGN(balignment) \
PUT_LABEL_ID(label_id) \
"." #type " " #value "\n"

#define ASM_PUT_CONSTANT_INT8_NO_LABEL(value) ".1byte " #value "\n"

#define ASM_PUT_CONSTANT_FLOAT(label_id, value) ASM_PUT_CONSTANT_VALUE(label_id, value, float, 4)
#define ASM_PUT_CONSTANT_DOUBLE(value) ASM_PUT_CONSTANT_VALUE(label_id, value, double, 8)
#define ASM_PUT_CONSTANT_INT8(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 1byte, 1)
#define ASM_PUT_CONSTANT_INT16(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 2byte, 2)
#define ASM_PUT_CONSTANT_INT32(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 4byte, 4)
#define ASM_PUT_CONSTANT_INT64(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 8byte, 8)
#define ASM_PUT_CONSTANT_INT128(value) ASM_PUT_CONSTANT_VALUE(label_id, value, octa, 16)
#elif defined(IS_PLATFORM_WIN)
#define BALIGN(balignment) align #balignment
#endif

#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_WIN_X64)
#define ASM_JMP_STATIC_ADDRESS(address) __asm push address __asm retn

#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) jmp [symbol]
#endif

// Load address of symbol
#ifdef IS_PLATFORM_ANDROID_ARM32
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "ldr " TOSTRING(reg) ", =("#symbol" - 100001f - 2*(100002f-100001f))\n" \
"100001:\n" \
"add " TOSTRING(reg) ", pc\n" \
"100002:\n"
#endif

#ifdef IS_PLATFORM_WIN_X86
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) lea reg, [symbol]
#endif

#ifdef IS_PLATFORM_WIN_X64
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) lea reg, [rip + symbol]
#endif

#ifdef IS_PLATFORM_ANDROID_X86
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "lea "#reg", ["#symbol"]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_X64
// GAS syntax for RIP - relative addressing looks like symbol + RIP, but it actually means symbol with respect to RIP.
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "lea "#reg", [rip + "#symbol"]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "adrp " TOSTRING(reg) ", "#symbol"\n" \
"add " TOSTRING(reg) ", " TOSTRING(reg) ", #:lo12:"#symbol"\n"

#define __ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol)
#endif

#ifdef IS_PLATFORM_IOS_ARM64
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "adrp " #reg ", "#symbol"@PAGE\n"  \
"add "#reg", "#reg", #"#symbol"@PAGEOFF\n"
#endif

///////////////
#ifdef IS_ARCHITECTURE_ARM64
#define FULL_REG_X0 X0
#define FULL_REG_X1 X1
#define FULL_REG_X2 X2
#define FULL_REG_X3 X3
#define FULL_REG_X4 X4
#define FULL_REG_X5 X5
#define FULL_REG_X6 X6
#define FULL_REG_X7 X7
#define FULL_REG_X8 X8
#define FULL_REG_X9 X9
#define FULL_REG_X10 X10
#define FULL_REG_X11 X11
#define FULL_REG_X12 X12
#define FULL_REG_X13 X13
#define FULL_REG_X14 X14
#define FULL_REG_X15 X15
#define FULL_REG_X16 X16
#define FULL_REG_X17 X17
#define FULL_REG_X18 X18
#define FULL_REG_X19 X19
#define FULL_REG_X20 X20
#define FULL_REG_X21 X21
#define FULL_REG_X22 X22
#define FULL_REG_X23 X23
#define FULL_REG_X24 X24
#define FULL_REG_X25 X25
#define FULL_REG_X26 X26
#define FULL_REG_X27 X27
#define FULL_REG_X28 X28
#define FULL_REG_X29 X29
#define FULL_REG_X30 X30

#define FULL_REG_W0 X0
#define FULL_REG_W1 X1
#define FULL_REG_W2 X2
#define FULL_REG_W3 X3
#define FULL_REG_W4 X4
#define FULL_REG_W5 X5
#define FULL_REG_W6 X6
#define FULL_REG_W7 X7
#define FULL_REG_W8 X8
#define FULL_REG_W9 X9
#define FULL_REG_W10 X10
#define FULL_REG_W11 X11
#define FULL_REG_W12 X12
#define FULL_REG_W13 X13
#define FULL_REG_W14 X14
#define FULL_REG_W15 X15
#define FULL_REG_W16 X16
#define FULL_REG_W17 X17
#define FULL_REG_W18 X18
#define FULL_REG_W19 X19
#define FULL_REG_W20 X20
#define FULL_REG_W21 X21
#define FULL_REG_W22 X22
#define FULL_REG_W23 X23
#define FULL_REG_W24 X24
#define FULL_REG_W25 X25
#define FULL_REG_W26 X26
#define FULL_REG_W27 X27
#define FULL_REG_W28 X28
#define FULL_REG_W29 X29
#define FULL_REG_W30 X30

#define REG_WORD_X0 W0
#define REG_WORD_X1 W1
#define REG_WORD_X2 W2
#define REG_WORD_X3 W3
#define REG_WORD_X4 W4
#define REG_WORD_X5 W5
#define REG_WORD_X6 W6
#define REG_WORD_X7 W7
#define REG_WORD_X8 W8
#define REG_WORD_X9 W9
#define REG_WORD_X10 W10
#define REG_WORD_X11 W11
#define REG_WORD_X12 W12
#define REG_WORD_X13 W13
#define REG_WORD_X14 W14
#define REG_WORD_X15 W15
#define REG_WORD_X16 W16
#define REG_WORD_X17 W17
#define REG_WORD_X18 W18
#define REG_WORD_X19 W19
#define REG_WORD_X20 W20
#define REG_WORD_X21 W21
#define REG_WORD_X22 W22
#define REG_WORD_X23 W23
#define REG_WORD_X24 W24
#define REG_WORD_X25 W25
#define REG_WORD_X26 W26
#define REG_WORD_X27 W27
#define REG_WORD_X28 W28
#define REG_WORD_X29 W29
#define REG_WORD_X30 W30

#define REG_WORD_W0 W0
#define REG_WORD_W1 W1
#define REG_WORD_W2 W2
#define REG_WORD_W3 W3
#define REG_WORD_W4 W4
#define REG_WORD_W5 W5
#define REG_WORD_W6 W6
#define REG_WORD_W7 W7
#define REG_WORD_W8 W8
#define REG_WORD_W9 W9
#define REG_WORD_W10 W10
#define REG_WORD_W11 W11
#define REG_WORD_W12 W12
#define REG_WORD_W13 W13
#define REG_WORD_W14 W14
#define REG_WORD_W15 W15
#define REG_WORD_W16 W16
#define REG_WORD_W17 W17
#define REG_WORD_W18 W18
#define REG_WORD_W19 W19
#define REG_WORD_W20 W20
#define REG_WORD_W21 W21
#define REG_WORD_W22 W22
#define REG_WORD_W23 W23
#define REG_WORD_W24 W24
#define REG_WORD_W25 W25
#define REG_WORD_W26 W26
#define REG_WORD_W27 W27
#define REG_WORD_W28 W28
#define REG_WORD_W29 W29
#define REG_WORD_W30 W30

#define SIZEOF_REG_X0 8
#define SIZEOF_REG_X1 8
#define SIZEOF_REG_X2 8
#define SIZEOF_REG_X3 8
#define SIZEOF_REG_X4 8
#define SIZEOF_REG_X5 8
#define SIZEOF_REG_X6 8
#define SIZEOF_REG_X7 8
#define SIZEOF_REG_X8 8
#define SIZEOF_REG_X9 8
#define SIZEOF_REG_X10 8
#define SIZEOF_REG_X11 8
#define SIZEOF_REG_X12 8
#define SIZEOF_REG_X13 8
#define SIZEOF_REG_X14 8
#define SIZEOF_REG_X15 8
#define SIZEOF_REG_X16 8
#define SIZEOF_REG_X17 8
#define SIZEOF_REG_X18 8
#define SIZEOF_REG_X19 8
#define SIZEOF_REG_X20 8
#define SIZEOF_REG_X21 8
#define SIZEOF_REG_X22 8
#define SIZEOF_REG_X23 8
#define SIZEOF_REG_X24 8
#define SIZEOF_REG_X25 8
#define SIZEOF_REG_X26 8
#define SIZEOF_REG_X27 8
#define SIZEOF_REG_X28 8
#define SIZEOF_REG_X29 8
#define SIZEOF_REG_X30 8

#define SIZEOF_REG_W0 4
#define SIZEOF_REG_W1 4
#define SIZEOF_REG_W2 4
#define SIZEOF_REG_W3 4
#define SIZEOF_REG_W4 4
#define SIZEOF_REG_W5 4
#define SIZEOF_REG_W6 4
#define SIZEOF_REG_W7 4
#define SIZEOF_REG_W8 4
#define SIZEOF_REG_W9 4
#define SIZEOF_REG_W10 4
#define SIZEOF_REG_W11 4
#define SIZEOF_REG_W12 4
#define SIZEOF_REG_W13 4
#define SIZEOF_REG_W14 4
#define SIZEOF_REG_W15 4
#define SIZEOF_REG_W16 4
#define SIZEOF_REG_W17 4
#define SIZEOF_REG_W18 4
#define SIZEOF_REG_W19 4
#define SIZEOF_REG_W20 4
#define SIZEOF_REG_W21 4
#define SIZEOF_REG_W22 4
#define SIZEOF_REG_W23 4
#define SIZEOF_REG_W24 4
#define SIZEOF_REG_W25 4
#define SIZEOF_REG_W26 4
#define SIZEOF_REG_W27 4
#define SIZEOF_REG_W28 4
#define SIZEOF_REG_W29 4
#define SIZEOF_REG_W30 4

#define __SIZEOF_REG__(reg) SIZEOF_REG_##reg

#define __FULL_REG__(reg) FULL_REG_##reg
#define __REG_WORD__(reg) REG_WORD_##reg
#else
#define __FULL_REG__(reg) reg
#define __REG_WORD__(reg) reg
#endif

#define FULL_REG(reg)  __FULL_REG__(reg)
#define REG_WORD(reg)  __REG_WORD__(reg)
#define SIZEOF_REG(reg) __SIZEOF_REG__(reg)

//////////////

#ifdef IS_ARCHITECTURE_ARM32
// Different register
#define DIFF_REG_R0 R1
#define DIFF_REG_R1 R0
#define DIFF_REG_R2 R0
#define DIFF_REG_R3 R0
#define DIFF_REG_R4 R0
#define DIFF_REG_R5 R0
#define DIFF_REG_R6 R0
#define DIFF_REG_R7 R0
#define DIFF_REG_R8 R0
#define DIFF_REG_R9 R0
#define DIFF_REG_R10 R0
#define DIFF_REG_R11 R0
#define DIFF_REG_R12 R0
#define DIFF_REG_SP R0
#define DIFF_REG_LR R0
#define DIFF_REG_PC R0
#define __DIFF_REG__(reg) DIFF_REG_##reg
#elif defined(IS_ARCHITECTURE_ARM64)
#define DIFF_REG_X0 X1
#define DIFF_REG_X1 X0
#define DIFF_REG_X2 X0
#define DIFF_REG_X3 X0
#define DIFF_REG_X4 X0
#define DIFF_REG_X5 X0
#define DIFF_REG_X6 X0
#define DIFF_REG_X7 X0
#define DIFF_REG_X8 X0
#define DIFF_REG_X9 X0
#define DIFF_REG_X10 X0
#define DIFF_REG_X11 X0
#define DIFF_REG_X12 X0
#define DIFF_REG_X13 X0
#define DIFF_REG_X14 X0
#define DIFF_REG_X15 X0
#define DIFF_REG_X16 X0
#define DIFF_REG_X17 X0
#define DIFF_REG_X18 X0
#define DIFF_REG_X19 X0
#define DIFF_REG_X20 X0
#define DIFF_REG_X21 X0
#define DIFF_REG_X22 X0
#define DIFF_REG_X23 X0
#define DIFF_REG_X24 X0
#define DIFF_REG_X25 X0
#define DIFF_REG_X26 X0
#define DIFF_REG_X27 X0
#define DIFF_REG_X28 X0
#define DIFF_REG_X29 X0
#define DIFF_REG_X30 X0

#define DIFF_REG_W0 W1
#define DIFF_REG_W1 W0
#define DIFF_REG_W2 W0
#define DIFF_REG_W3 W0
#define DIFF_REG_W4 W0
#define DIFF_REG_W5 W0
#define DIFF_REG_W6 W0
#define DIFF_REG_W7 W0
#define DIFF_REG_W8 W0
#define DIFF_REG_W9 W0
#define DIFF_REG_W10 W0
#define DIFF_REG_W11 W0
#define DIFF_REG_W12 W0
#define DIFF_REG_W13 W0
#define DIFF_REG_W14 W0
#define DIFF_REG_W15 W0
#define DIFF_REG_W16 W0
#define DIFF_REG_W17 W0
#define DIFF_REG_W18 W0
#define DIFF_REG_W19 W0
#define DIFF_REG_W20 W0
#define DIFF_REG_W21 W0
#define DIFF_REG_W22 W0
#define DIFF_REG_W23 W0
#define DIFF_REG_W24 W0
#define DIFF_REG_W25 W0
#define DIFF_REG_W26 W0
#define DIFF_REG_W27 W0
#define DIFF_REG_W28 W0
#define DIFF_REG_W29 W0
#define DIFF_REG_W30 W0
#define __DIFF_REG__(reg) DIFF_REG_##reg
#endif

#define DIFF_REG(reg) __DIFF_REG__(reg)

//////////////

#if defined(IS_PLATFORM_ANDROID_ARM32) || defined(IS_PLATFORM_ANDROID_ARM64)
#define ASM_LOAD_BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(FULL_REG(reg), symbol) \
"LDRB " TOSTRING(reg) ", [" TOSTRING(FULL_REG(reg)) "]\n"
#define ASM_LOAD_2BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(FULL_REG(reg), symbol) \
"LDRH " TOSTRING(reg) ", [" TOSTRING(FULL_REG(reg)) "]\n"

// use 32-bit reg like W0, W1...
#define ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(FULL_REG(reg), symbol) \
"LDR " TOSTRING(REG_WORD(reg)) ", [" TOSTRING(FULL_REG(reg)) "]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
// use 64-bit reg like X0, X1...
#define ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) \
"SXTW " TOSTRING(FULL_REG(reg)) ", " TOSTRING(reg) "\n"
#else
#define ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol)
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
#define ASM_LOAD_8BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) \
"LDR "#reg", ["#reg"]\n"
#endif
//////////////

#ifdef IS_ARCHITECTURE_ARM32
#define GET_CODE_START(address) ((uintptr_t)(address) & (~1))
#define GET_INSTRUCTION_SET_FROM_ADDRESS(address) (address & 1 ? INSTRUCTION_SET_THUMB : INSTRUCTION_SET_ARM)

#define ASM_GET_ARM_ADDRESS_FOR_JUMP(address) address
#define ASM_GET_THUMB_ADDRESS_FOR_JUMP(address) (address | 1)
#else
#define GET_CODE_START(address) ((uintptr_t)(address))
#define GET_INSTRUCTION_SET_FROM_ADDRESS(address) CURRENT_PROCESSOR_INSTRUCTION_SET
#endif

#ifdef IS_PLATFORM_ANDROID_ARM32
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol)

#define ASM_JUMP_TO_ADDRESS_OF_SYMBOL(symbol) "PUSH            {R0,R1}\n" \
ASM_LOAD_ADDRESS_OF_SYMBOL(R0, symbol) \
"STR R0, [SP, #4]\n" \
"POP            {R0,PC}\n"

#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "PUSH            {R0,R1}\n" \
ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, symbol) \
"STR R0, [SP, #4]\n" \
"POP            {R0,PC}\n"

#define ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "PUSH            {R0,R1}\n" \
"ADR LR, 100015f + ((4 - (100011f - 100010f)) / 2)\n" /* + 0 if ARM, + 1 if Thumb to set up the address */ \
ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, symbol) \
"100010:\n" \
"STR R0, [SP, #4]\n" \
"100011:\n" \
"POP            {R0,PC}\n" \
"100015:\n"

// Make instruction with register and symbol
#define ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(instruction, reg, symbol) "PUSH            {" TOSTRING(DIFF_REG(reg)) "}\n" \
ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(DIFF_REG_##reg, symbol) \
#instruction " " TOSTRING(reg) ", " TOSTRING(DIFF_REG(reg)) "\n" \
"POP            {" TOSTRING(DIFF_REG(reg)) "}\n"

// ADD register, value on symbol
#define ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(ADD, reg, symbol)
#define ASM_ADD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol)

#define ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(SUB, reg, symbol)

#define ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(CMP, reg, symbol)
#define ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(MUL, reg, symbol)

#define ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(reg, symbol) "PUSH            {R0,R1}\n" \
ASM_LOAD_ADDRESS_OF_SYMBOL(R0, symbol) \
"VLDR            "#reg", [R0]\n" \
"POP            {R0,R1}\n"
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
#define SAVE_REGISTER(reg) "STR " TOSTRING(reg) ", [SP, #-16]!\n"
#define RESTORE_REGISTER(reg) "LDR   " TOSTRING(reg) ", [sp], #16\n"

#define TRAMPOLINE_REGISTER X16
#define SAVE_TRAMPOLINE_REGISTER() "STR " TOSTRING(TRAMPOLINE_REGISTER) ", [SP, #-16]!\n"
#define RESTORE_TRAMPOLINE_REGISTER() "LDR   " TOSTRING(TRAMPOLINE_REGISTER) ", [sp], #16\n"

#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_8BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol)

#define ASM_JUMP_TO_ADDRESS_OF_SYMBOL(symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(TRAMPOLINE_REGISTER, symbol) \
"BR X0\n"

#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(TRAMPOLINE_REGISTER, symbol) \
"BR " TOSTRING(TRAMPOLINE_REGISTER) "\n"

// Remember, X0 gets pushed to stack, needs to be restored.
#define ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "ADR LR, 100015f\n" \
ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) \
"100015:\n"

////

// register like W0, no need to extend
#define LOAD_4BYTE_VALUE_INTO_REGISTER_SIZE_OF_4 ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL

// register like X0, need to extend
#define LOAD_4BYTE_VALUE_INTO_REGISTER_SIZE_OF_8 ASM_LOAD_4BYTE_SIGNED_VALUE_STORED_ON_SYMBOL

#define LOAD_VALUE_INTO_REGISTER_SIZE_OF_ARGUMENT_HELPER_1(size) LOAD_4BYTE_VALUE_INTO_REGISTER_SIZE_OF_ ## size
#define LOAD_VALUE_INTO_REGISTER_SIZE_OF_ARGUMENT_HELPER_2(size) LOAD_VALUE_INTO_REGISTER_SIZE_OF_ARGUMENT_HELPER_1(size)
#define LOAD_VALUE_INTO_REGISTER_SIZE_OF_ARGUMENT(size) LOAD_VALUE_INTO_REGISTER_SIZE_OF_ARGUMENT_HELPER_2(size)

#define LOAD_VALUE_INTO_REGISTER_SIGNED_HELPER_1(reg) LOAD_VALUE_INTO_REGISTER_SIZE_OF_ARGUMENT(SIZEOF_REG(reg))
#define LOAD_VALUE_INTO_REGISTER_SIGNED_HELPER_2(reg, symbol, macroName) macroName(reg, symbol)
#define LOAD_VALUE_INTO_REGISTER_SIGNED(reg, symbol) LOAD_VALUE_INTO_REGISTER_SIGNED_HELPER_2(reg, symbol, LOAD_VALUE_INTO_REGISTER_SIGNED_HELPER_1(reg))

// Make instruction with register and symbol
#define ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(instruction, reg, symbol) "STR " TOSTRING(DIFF_REG(FULL_REG(reg))) ", [SP, #-16]!\n" \
LOAD_VALUE_INTO_REGISTER_SIGNED(DIFF_REG(reg), symbol) \
#instruction " " TOSTRING(reg) ", " TOSTRING(DIFF_REG(reg)) "\n" \
"LDR   " TOSTRING(DIFF_REG(FULL_REG(reg))) ", [sp], #16\n"

// ADD register, value on symbol
#define ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(ADD, reg, symbol)
#define ASM_ADD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol)

#define ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(SUB, reg, symbol)

#define ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(CMP, reg, symbol)
#define ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(MUL, reg, symbol)
#endif

#ifdef IS_PLATFORM_WIN_X86
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) mov reg, [symbol]
#endif

#ifdef IS_PLATFORM_WIN_X64
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) mov reg, [rip + symbol]
#endif

#ifdef IS_PLATFORM_ANDROID_X86
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) "mov "#reg", ["#symbol"]\n"
#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "jmp ["#symbol"]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_X64
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) "mov "#reg", [rip + "#symbol"]\n"
#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "jmp [rip + "#symbol"]\n"
#endif

// JNI
#define break_on_jni_exception(jniEnv) if (jniEnv->ExceptionCheck()) break;

// Returns void pointer to method
template<typename T> void* GetMethodAsVoidPointer(T method)
{
	return *reinterpret_cast<void**>(&method);
}

static inline uintptr_t untag_address(uintptr_t p) {
#if defined(__aarch64__)
	return p & ((1ULL << 56) - 1);
#else
	return p;
#endif
}

#ifdef IS_PLATFORM_ANDROID_ARM64
static inline uintptr_t GetPointerPage(void* ptr)
{
	return (uintptr_t)ptr & (~0xFFF);
}
#endif