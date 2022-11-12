#pragma once

// Calculates BullyScholarschip Edition hash from upcase string
unsigned long BullyScholarschipEdition_hash_fromUpCaseString(const char* string);

// Calculates BullyScholarschip Edition string from hash
const char* BullyScholarschipEdition_stringFromHash(unsigned __int32 hash, char* outString);