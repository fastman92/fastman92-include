#pragma once
#include "Endianness\Endianness.h"
#include "EnumOperators.h"
#include "enumMemberNamePair.h"

#define COMMA ,

namespace Game
{
	enum eGameEra
	{
		GAME_ERA_UNDEFINED,
		GAME_ERA_GTA_III,
		GAME_ERA_GTA_IV,
		GAME_ERA_BULLY
	};

#define PUT_PLATFORM_MEMBER_FROM_LIST(platform, bIsBigEndian) platform,

	// formatMacro is used as a formatting macro.
#define MAKE_GAME_PLATFORM_LIST(formatMacro) \
formatMacro(GAME_PLATFORM_UNDEFINED, VALUE_ENCODING_LITTLE_ENDIAN) \
/* formatMacro(GAME_PLATFORM_PC, VALUE_ENCODING_LITTLE_ENDIAN) \ */ \
formatMacro(GAME_PLATFORM_WIN_X86, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_WIN_X64, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_PS2, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_PS3, VALUE_ENCODING_BIG_ENDIAN) \
formatMacro(GAME_PLATFORM_PS4, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_PSP, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_XBOX, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_XBOX360, VALUE_ENCODING_BIG_ENDIAN) \
formatMacro(GAME_PLATFORM_ANDROID_X86, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_ANDROID_X64, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_ANDROID_ARMEABI, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_ANDROID_ARMEABI_V7A, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_ANDROID_ARM64_V8A, VALUE_ENCODING_LITTLE_ENDIAN) \
formatMacro(GAME_PLATFORM_IOS, VALUE_ENCODING_LITTLE_ENDIAN)

	enum eGamePlatform
	{
		MAKE_GAME_PLATFORM_LIST(PUT_PLATFORM_MEMBER_FROM_LIST)

		// last
		GAME_PLATFORM_LAST = GAME_PLATFORM_XBOX360
	};

#define MAKE_GAME_SIMPLE_LIST(formatMacro) \
		formatMacro(GAME_SIMPLE_UNDEFINED, GAME_ERA_UNDEFINED, NONE) \
		\
		/* III era */ \
		formatMacro(GAME_SIMPLE_NAME_GTA_III, GAME_ERA_GTA_III, III) \
		formatMacro(GAME_SIMPLE_NAME_GTA_VC, GAME_ERA_GTA_III, VC) \
		formatMacro(GAME_SIMPLE_NAME_GTA_SA, GAME_ERA_GTA_III, SA) \
		\
		formatMacro(GAME_SIMPLE_NAME_GTA_LCS, GAME_ERA_GTA_III, LCS) \
		formatMacro(GAME_SIMPLE_NAME_GTA_VCS, GAME_ERA_GTA_III, VCS) \
		\
		/* IV era */ \
		formatMacro(GAME_SIMPLE_NAME_GTA_IV, GAME_ERA_GTA_IV, IV) \
		formatMacro(GAME_SIMPLE_NAME_GTA_V, GAME_ERA_GTA_IV, V) \
		/* other */ \
		formatMacro(GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION, GAME_ERA_BULLY, SE)

	#define PUT_GAME_SIMPLIFIED_MEMBER_FROM_LIST(gameSimple, era, shortName) gameSimple,

	enum eGameNameSimplified
	{
		// make a list
		MAKE_GAME_SIMPLE_LIST(PUT_GAME_SIMPLIFIED_MEMBER_FROM_LIST)

		// other
		GAME_SIMPLE_FIRST = GAME_SIMPLE_NAME_GTA_III,
		GAME_SIMPLE_LAST = GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION
	};

	DEFINE_ENUM_OPERATORS(eGameNameSimplified);

// formatMacro is used as a formatting macro.
#define MAKE_GAME_EXACT_III_ERA_LIST(formatMacro) \
/* GTA III era */ \
formatMacro(GTAIII_PC, GAME_SIMPLE_NAME_GTA_III, GAME_PLATFORM_WIN_X86) \
formatMacro(GTAIII_PS2, GAME_SIMPLE_NAME_GTA_III, GAME_PLATFORM_PS2) \
formatMacro(GTAIII_XBOX, GAME_SIMPLE_NAME_GTA_III, GAME_PLATFORM_XBOX) \
formatMacro(GTAIII_ANDROID_ARM32, GAME_SIMPLE_NAME_GTA_III, GAME_PLATFORM_ANDROID_ARMEABI_V7A) \
\
formatMacro(GTAVC_PC, GAME_SIMPLE_NAME_GTA_VC, GAME_PLATFORM_WIN_X86) \
formatMacro(GTAVC_PS2, GAME_SIMPLE_NAME_GTA_VC, GAME_PLATFORM_PS2) \
formatMacro(GTAVC_XBOX, GAME_SIMPLE_NAME_GTA_VC, GAME_PLATFORM_XBOX) \
formatMacro(GTAVC_ANDROID, GAME_SIMPLE_NAME_GTA_VC, GAME_PLATFORM_ANDROID_ARMEABI_V7A) \
\
formatMacro(GTASA_PC, GAME_SIMPLE_NAME_GTA_SA, GAME_PLATFORM_WIN_X86) \
formatMacro(GTASA_PS2, GAME_SIMPLE_NAME_GTA_SA, GAME_PLATFORM_PS2) \
formatMacro(GTASA_XBOX, GAME_SIMPLE_NAME_GTA_SA, GAME_PLATFORM_XBOX) \
formatMacro(GTASA_ANDROID, GAME_SIMPLE_NAME_GTA_SA, GAME_PLATFORM_ANDROID_ARMEABI_V7A)\
\
formatMacro(GTALCS_PS2, GAME_SIMPLE_NAME_GTA_LCS, GAME_PLATFORM_PS2) \
formatMacro(GTAVCS_PS2, GAME_SIMPLE_NAME_GTA_VCS, GAME_PLATFORM_PS2)

#define MAKE_GAME_EXACT_IV_ERA_LIST(formatMacro) \
/* GTA IV IV era */ \
formatMacro(GTAIV_PC, GAME_SIMPLE_NAME_GTA_IV, GAME_PLATFORM_WIN_X86) \
formatMacro(GTAIV_PS3, GAME_SIMPLE_NAME_GTA_IV, GAME_PLATFORM_PS3) \
formatMacro(GTAIV_XBOX360, GAME_SIMPLE_NAME_GTA_IV, GAME_PLATFORM_XBOX360) \
formatMacro(GTAV_PC, GAME_SIMPLE_NAME_GTA_V, GAME_PLATFORM_WIN_X86)

#define MAKE_GAME_EXACT_BULLY_ERA_LIST(formatMacro) \
/* GTA IV IV era */ \
formatMacro(BULLY_SCHOLARSHIP_EDITION_PC, GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION, GAME_PLATFORM_WIN_X86)

// List of all games.
#define MAKE_GAME_EXACT_ALL_ERAS_LIST(formatMacro) \
MAKE_GAME_EXACT_III_ERA_LIST(formatMacro) \
MAKE_GAME_EXACT_IV_ERA_LIST(formatMacro) \
MAKE_GAME_EXACT_BULLY_ERA_LIST(formatMacro)

#define ENUM_GAME_MEMBER(gameExact, gameSimple, gamePlatform) GAME_EXACT_##gameExact,

	enum eGameName
	{
		GAME_EXACT_UNDEFINED,

		GAME_EXACT_COMMON,

		MAKE_GAME_EXACT_ALL_ERAS_LIST(ENUM_GAME_MEMBER)

		// Summary
		GAME_GTAIII_ERA_FIRST = GAME_EXACT_GTAIII_PC,
		GAME_GTAIII_ERA_LAST = GAME_EXACT_GTAVCS_PS2,
		GAME_GTAIII_ERA_NONSTORIES_FIRST = GAME_EXACT_GTAIII_PC,
		GAME_GTAIII_ERA_NONSTORIES_LAST = GAME_EXACT_GTASA_ANDROID,
		GAME_GTAIII_ERA_STORIES_FIRST = GAME_EXACT_GTALCS_PS2,
		GAME_GTAIII_ERA_STORIES_LAST = GAME_EXACT_GTAVCS_PS2,

		GAME_GTAIV_ERA_FIRST = GAME_EXACT_GTAIV_PC,
		GAME_GTAIV_ERA_LAST = GAME_EXACT_GTAV_PC,

		GAME_EXACT_GTA_FIRST = GAME_GTAIII_ERA_FIRST,
		GAME_EXACT_GTA_LAST = GAME_GTAIV_ERA_LAST,

		GAME_EXACT_FIRST = GAME_GTAIII_ERA_FIRST,
		GAME_EXACT_LAST = GAME_EXACT_BULLY_SCHOLARSHIP_EDITION_PC
	};

	DEFINE_ENUM_OPERATORS(eGameName);

	namespace GameExact
	{
		// Finds game exact by string
		eGameName GetGameEnumMemberByName(const char* gameStr);

		// Finds name by game enum member
		const char* GetPlatformEnumNameByMember(eGameName game);

		// Returns true if given game belongs to GTA III era
		bool IsGTAIIIeraGame(eGameName game);

		// Returns true if given game belongs to GTA IV era
		bool IsGTAIVeraGame(eGameName game);

		// Returns true if given game belongs to Non-Stories
		bool IsNonStoriesIIIeraGame(eGameName game);

		// Returns true if given game belongs to Stories
		bool IsStoriesIIIeraGame(eGameName game);

		// Returns game era
		eGameEra GetGTAGameEra(eGameName game);
	}

	namespace GameSimple
	{
		// Finds game exact by string
		eGameNameSimplified GetGameEnumMemberByName(const char* gameStr);

		// Finds name by game enum member
		const char* GetPlatformEnumNameByMember(eGameNameSimplified game);

		// Returns game era
		eGameEra GetGTAGameEra(eGameNameSimplified game);

		// Returns game era
		const char* GetShortNameOfGame(eGameNameSimplified game);

		// Returns true if given game belongs to GTA III era
		bool IsGTAIIIeraGame(eGameNameSimplified game);

		// Returns true if given game belongs to GTA IV era
		bool IsGTAIVeraGame(eGameNameSimplified game);
	}

	namespace GamePlatform
	{
		// Finds name by platform enum member
		const char* GetPlatformEnumNameByMember(eGamePlatform platform);

		// Returns true if platform uses big endian byte order
		eValueEncoding IsPlatformBigEndian(eGamePlatform platform);

		// Returns true if platform is any of Windows
		bool IsPlatformWindows(eGamePlatform platform);

		// Returns true if platform is any of Android
		bool IsPlatformAndroid(eGamePlatform platform);
	}
		
	struct tSimpleGameAndPlatform
	{
		eGameNameSimplified gameSimple;
		eGamePlatform platform;
	};

	// Information about game exact IDs and game simple IDs + platform IDs
	extern const std::pair <eGameName, tSimpleGameAndPlatform> GameExactAndSimpleIDarray[];

	// Returns exact game member by simple game member.
	eGameName GetExactGameMemberBySimpleGameMemberAndPlatform(eGameNameSimplified simpleGame, eGamePlatform platform);

	// Returns a struct with simple game and platform.
	tSimpleGameAndPlatform GetSimpleGameAndPlatformByExactMember(eGameName gameExact);
}