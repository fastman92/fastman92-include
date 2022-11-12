// Author: fastman92
#include <Windows.h>

#ifdef DLL_TRICKS_EXPORT
#define DLL_TRICKS_API __declspec(dllexport)
#else
#define DLL_TRICKS_API __declspec(dllimport)
#endif

typedef bool (WINAPI *tDllMain)(  _In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved);

typedef bool (WINAPI *tCallDllMain)( tDllMain* pDllMain,
	_In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved);

// tSearchSequence
struct tSearchSequence
{
	unsigned int size;
	const char* data;
};

class DLL_TRICKS_API CTheDllTricks
{
public:
	// Search sequence array for CallDllMain
	static const tSearchSequence ms_callDllMainSearchSequenceArray[];

	// Search for CallDllMain in section
	static tCallDllMain SearchForCallDllMain(const void* SectionDataAddress,DWORD SectionDataSize);

	// Returns address to CallDllMain
	static tCallDllMain GetAddressToCallDllMain();
};