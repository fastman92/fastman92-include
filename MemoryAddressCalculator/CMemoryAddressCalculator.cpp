/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "CMemoryAddressCalculator.h"

// Constructor
CMemoryAddressCalculator::CMemoryAddressCalculator()
{
	this->m_currentBaseVA = 0;
	this->m_preferedBaseVA = 0;
}

// Initializes
void CMemoryAddressCalculator::Initialize(uintptr_t preferedVA, uintptr_t currentVA)
{
	this->m_currentBaseVA = currentVA;
	this->m_preferedBaseVA = preferedVA;
}

// Sets prefered module base
void CMemoryAddressCalculator::SetPreferedModuleBase(uintptr_t virtualAddress)
{
	this->m_preferedBaseVA = virtualAddress;
}

// Sets current module base
void CMemoryAddressCalculator::SetCurrentModuleBase(uintptr_t virtualAddress)
{
	this->m_currentBaseVA = virtualAddress;
}

// Gets actual virtual address from virtual prefered address given.
uintptr_t CMemoryAddressCalculator::GetCurrentVAbyPreferedVA(uintptr_t virtualAddress)
{
	return virtualAddress - this->m_preferedBaseVA + this->m_currentBaseVA;
}

// Gets prefered virtual address from virtual current address given.
uintptr_t CMemoryAddressCalculator::GetPreferedVAbyCurrentVA(uintptr_t virtualAddress)
{
	return virtualAddress - this->m_currentBaseVA + this->m_preferedBaseVA;
}

// Returns prefered module base
uintptr_t CMemoryAddressCalculator::GetPreferedModuleBase()
{
	return this->m_preferedBaseVA;
}

// Returns current module base
uintptr_t CMemoryAddressCalculator::GetCurrentModuleBase()
{
	return this->m_currentBaseVA;
}