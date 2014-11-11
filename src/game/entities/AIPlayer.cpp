#pragma once

#include "AIPlayer.h"
#include "Unit.h"

#define RANDF	( rand() / static_cast<float>(RAND_MAX) )

void AIPlayer::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {
	for ( auto& unit : unitsFriendly ) {
		if ( unit.GetUnitState() == UnitState::Idle ) {
			unit.CommandMove( sf::Vector2f( RANDF * 1600.0f, RANDF * 900.0f ) );
		}
	}
}