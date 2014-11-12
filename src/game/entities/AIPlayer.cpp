#pragma once

#include "AIPlayer.h"
#include "Unit.h"

#define RANDF	( rand() / static_cast<float>(RAND_MAX) )

void AIPlayer::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {
	for ( auto& unit : unitsFriendly ) {
		for ( auto& enemy : unitsHostile ) {
			unit.CommandAttackTarget( &enemy );
		}
	}
}