#pragma once

#include "AIPlayer.h"
#include "Unit.h"
#include "../../math/Math.h"

#define RANDF	( rand() / static_cast<float>(RAND_MAX) )

void AIPlayer::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {
	m_WantsToClone = true;

	for ( auto& unit : unitsFriendly ) {
		float closest = FLT_MAX;
		for ( auto& enemy : unitsHostile ) {
			float distSqrd = math::vec2f::LengthSqrd( unit.GetPosition() - enemy.GetPosition() );
			if ( distSqrd < closest ) {
				closest = distSqrd;
				unit.CommandAttackTarget( &enemy );
			}
		}
	}
}