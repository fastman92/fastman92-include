/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "BullyScholarschipEdition_Hash.h"
#include "GTAIV_CRC32.h"
#include "GTASA_CRC32.h"
#include "../eGame.h"

using namespace Game;

// Calculates a hash using game algorithm
static unsigned __int32 CalculateHashUsingGameAlgorithm(
	Game::eGameNameSimplified game,
	const char* str
	)
{
	
	if (game == GAME_SIMPLE_NAME_BULLY_SCHOLARSHIP_EDITION)
		return BullyScholarschipEdition_hash_fromUpCaseString(str);
	else if (game == GAME_SIMPLE_NAME_GTA_SA)
		return GTASA_CRC32_fromUpCaseString(str);
	else if (game == GAME_SIMPLE_NAME_GTA_IV)
		return GTAIV_CRC32_fromString(str);
	else
		return 0;
}