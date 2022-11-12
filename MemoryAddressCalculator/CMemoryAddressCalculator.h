/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <stdint.h>

class CMemoryAddressCalculator
{
private:
	uintptr_t m_preferedBaseVA;
	uintptr_t m_currentBaseVA;

public:
	// Constructor
	CMemoryAddressCalculator();

	// Initializes
	void Initialize(uintptr_t preferedVA, uintptr_t currentVA);

	// Sets prefered module base
	void SetPreferedModuleBase(uintptr_t virtualAddress);

	// Sets current module base
	void SetCurrentModuleBase(uintptr_t virtualAddress);

	// Gets actual virtual address from virtual prefered address given.
	uintptr_t GetCurrentVAbyPreferedVA(uintptr_t virtualAddress);

	// Gets prefered virtual address from virtual current address given.
	uintptr_t GetPreferedVAbyCurrentVA(uintptr_t virtualAddress);

	// Returns prefered module base
	uintptr_t GetPreferedModuleBase();

	// Returns current module base
	uintptr_t GetCurrentModuleBase();
};