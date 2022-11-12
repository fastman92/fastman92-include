/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#include "eGame.h"

#include "Array/countof.h"

namespace Game {

	namespace GameExact
	{
		static const char GameExactPrefix[] = "GAME_EXACT_";
		static const int GameExactPrefixLen = sizeof(GameExactPrefix) - 1;

		#define STR_EXPAND(str) #str

		#define DEFINE_GAME_MEMBER_NAME(gameExact, gameSimple, gamePlatform) { GAME_EXACT_##gameExact, STR_EXPAND(GAME_EXACT_##gameExact)},

		static const enumMemberNamePair<eGameName> GameEnumMemberNames[] =
		{
			DEFINE_GAME_MEMBER_NAME(UNDEFINED, GAME_SIMPLE_UNDEFINED, GAME_PLATFORM_UNDEFINED)

			DEFINE_GAME_MEMBER_NAME(COMMON, GAME_SIMPLE_UNDEFINED, GAME_PLATFORM_UNDEFINED)

			MAKE_GAME_EXACT_ALL_ERAS_LIST(DEFINE_GAME_MEMBER_NAME)
			/*
			MAKE_GAME_EXACT_III_ERA_LIST(DEFINE_GAME_MEMBER_NAME)
			MAKE_GAME_EXACT_IV_ERA_LIST(DEFINE_GAME_MEMBER_NAME)
			*/
		};

		// Finds game by string
		eGameName GetGameEnumMemberByName(const char* gameStr)
		{
			const enumMemberNamePair<eGameName>* pair = getEnumPairFromArrayByName(GameEnumMemberNames, gameStr);

			return pair != NULL ? pair->enumMember : GAME_EXACT_UNDEFINED;
		}

		// Finds name by game enum member
		const char* GetGameEnumNameByMember(eGameName game)
		{
			return getNameByEnumMemberFromArray(GameEnumMemberNames, game);
		}

		// Returns true if given game belongs to GTA III era
		// Returns true if given game belongs to GTA III era
		bool IsGTAIIIeraGame(eGameName game)
		{
			return game >= GAME_GTAIII_ERA_FIRST && game <= GAME_GTAIII_ERA_LAST;
		}

		// Returns true if given game belongs to GTA IV era
		bool IsGTAIVeraGame(eGameName game)
		{
			return game >= GAME_GTAIV_ERA_FIRST && game <= GAME_GTAIV_ERA_LAST;
		}

		// Returns true if given game belongs to Non-Stories
		bool IsNonStoriesIIIeraGame(eGameName game)
		{
			return game >= GAME_GTAIII_ERA_NONSTORIES_FIRST && game <= GAME_GTAIII_ERA_NONSTORIES_LAST;
		}

		// Returns true if given game belongs to Stories
		bool IsStoriesIIIeraGame(eGameName game)
		{
			return game >= GAME_GTAIII_ERA_STORIES_FIRST && game <= GAME_GTAIII_ERA_STORIES_LAST;
		}

		// Returns game era
		eGameEra GetGTAGameEra(eGameName game)
		{
			if (IsGTAIIIeraGame(game))
				return GAME_ERA_GTA_III;
			else if (IsGTAIVeraGame(game))
				return GAME_ERA_GTA_IV;
			else
				return GAME_ERA_UNDEFINED;		// error
		}
	}

	namespace GameSimple
	{
		#define PUT_GAME_SIMPLIFIED_ENUM_MEMBER_FOR_PAIR(gameSimple, era, shortName) { gameSimple, #gameSimple},

		static const enumMemberNamePair<eGameNameSimplified> GameEnumMemberNames[] =
		{
			MAKE_GAME_SIMPLE_LIST(PUT_GAME_SIMPLIFIED_ENUM_MEMBER_FOR_PAIR)
		};

		// Finds game by string
		eGameNameSimplified GetGameEnumMemberByName(const char* gameStr)
		{
			const enumMemberNamePair<eGameNameSimplified>* pair = getEnumPairFromArrayByName(GameEnumMemberNames, gameStr);

			return pair != NULL ? pair->enumMember : GAME_SIMPLE_UNDEFINED;
		}

		// Finds name by game enum member
		const char* GetGameEnumNameByMember(eGameNameSimplified game)
		{
			return getNameByEnumMemberFromArray(GameEnumMemberNames, game);
		}

		// Returns game era
		eGameEra GetGTAGameEra(eGameNameSimplified game)
		{
			#define MAKE_SWITCH_CASE_FOR_GET_GTA_GAME_ERA_SIMPLIFIED(gameSimple, era, shortName) case gameSimple: return era;

			switch(game)
			{
				MAKE_GAME_SIMPLE_LIST(MAKE_SWITCH_CASE_FOR_GET_GTA_GAME_ERA_SIMPLIFIED)
			default:
				return GAME_ERA_UNDEFINED;
			}
		}

		// Returns game era
		const char* GetShortNameOfGame(eGameNameSimplified game)
		{
#define MAKE_SWITCH_CASE_FOR_GET_SHORT_NAME_OF_GAME(gameSimple, era, shortName) case gameSimple: return #shortName;

			switch (game)
			{
				MAKE_GAME_SIMPLE_LIST(MAKE_SWITCH_CASE_FOR_GET_SHORT_NAME_OF_GAME)
			default:
				return "NONE";
			}
		}

		// Returns true if given game belongs to GTA III era
		bool IsGTAIIIeraGame(eGameNameSimplified game)
		{
			return GetGTAGameEra(game) == GAME_ERA_GTA_III;
		}

		// Returns true if given game belongs to GTA IV era
		bool IsGTAIVeraGame(eGameNameSimplified game)
		{
			return GetGTAGameEra(game) == GAME_ERA_GTA_IV;
		}
	}


	namespace GamePlatform
	{
#define PUT_PLATFORM_SIMPLIFIED_ENUM_MEMBER_FOR_PAIR(platform, bIsBigEndian) { platform, #platform},

		const enumMemberNamePair<eGamePlatform> PlatformEnumMemberNames[] =
		{
			MAKE_GAME_PLATFORM_LIST(PUT_PLATFORM_SIMPLIFIED_ENUM_MEMBER_FOR_PAIR)
		};

		// Finds name by platform enum member
		const char* GetGameEnumNameByMember(eGamePlatform platform)
		{
			return getNameByEnumMemberFromArray(PlatformEnumMemberNames, platform);
		}

		// Returns true if platform uses big endian byte order
		eValueEncoding IsPlatformBigEndian(eGamePlatform platform)
		{
#define MAKE_SWITCH_CASE_FOR_PLATFORM_ENDIANNESS(platform, bIsBigEndian) case platform: return bIsBigEndian;

			switch (platform)
			{
				MAKE_GAME_PLATFORM_LIST(MAKE_SWITCH_CASE_FOR_PLATFORM_ENDIANNESS)
			}

			return VALUE_ENCODING_UNDEFINED;
		}

		// Returns true if platform is any of Windows
		bool IsPlatformWindows(eGamePlatform platform)
		{
			return platform == GAME_PLATFORM_WIN_X86 || platform == GAME_PLATFORM_WIN_X64;
		}

		// Returns true if platform is any of Android
		bool IsPlatformAndroid(eGamePlatform platform)
		{
			return platform == GAME_PLATFORM_ANDROID_ARMEABI_V7A || platform == GAME_PLATFORM_ANDROID_ARM64_V8A
				|| platform == GAME_PLATFORM_ANDROID_X86 || platform == GAME_PLATFORM_ANDROID_X64;
		}
	}

	// Returns GameExactAndSimpleIDarrayEntry
	std::pair <eGameName, tSimpleGameAndPlatform> GetGameExactAndSimpleIDarrayEntry(eGameName game, eGameNameSimplified gameSimple, eGamePlatform platform)
	{
		tSimpleGameAndPlatform gameInfo;
		gameInfo.gameSimple = gameSimple;
		gameInfo.platform = platform;

		std::pair <eGameName, tSimpleGameAndPlatform> pair(game, gameInfo);
		return pair;
	}

	#define MakeGameExactAndSimpleIDarrayEntry(gameExact, gameSimple, gamePlatform) GetGameExactAndSimpleIDarrayEntry(GAME_EXACT_##gameExact, gameSimple, gamePlatform),

	// Information about game exact IDs and game simple IDs + platform IDs
	const std::pair <eGameName, tSimpleGameAndPlatform> GameExactAndSimpleIDarray[] =
	{
		MAKE_GAME_EXACT_ALL_ERAS_LIST(MakeGameExactAndSimpleIDarrayEntry)
	};

	// Returns exact game member by simple game member.
	eGameName GetExactGameMemberBySimpleGameMemberAndPlatform(eGameNameSimplified gameSimple, eGamePlatform platform)
	{
		for (const std::pair <eGameName, tSimpleGameAndPlatform>* it = GameExactAndSimpleIDarray;
			it != GameExactAndSimpleIDarray + _countof(GameExactAndSimpleIDarray);
			it++)
			if (it->second.gameSimple == gameSimple && it->second.platform == platform)
				return it->first;

		return GAME_EXACT_UNDEFINED;
	}

#define Make_GetSimpleGameAndPlatformByExactMember_switch_case(gameExact, arg2_gameSimple, arg3_gamePlatform) case GAME_EXACT_##gameExact: \
result.gameSimple = arg2_gameSimple; \
result.platform = arg3_gamePlatform; \
break;

	// Returns a struct with simple game and platform.
	tSimpleGameAndPlatform GetSimpleGameAndPlatformByExactMember(eGameName gameExact)
	{
		tSimpleGameAndPlatform result;

		switch (gameExact)
		{
			MAKE_GAME_EXACT_ALL_ERAS_LIST(Make_GetSimpleGameAndPlatformByExactMember_switch_case)
		default:
			result.gameSimple = GAME_SIMPLE_UNDEFINED;
			result.platform = GAME_PLATFORM_UNDEFINED;
		}

		return result;
	}
}