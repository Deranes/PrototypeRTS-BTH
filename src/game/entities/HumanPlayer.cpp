#include "HumanPlayer.h"

#include "../../input/GlobalMouse.h"
#include "Unit.h"
#include "../../math/Math.h"

using namespace sf;

void HumanPlayer::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {
	m_WantsToClone = false;

	if ( g_Mouse.RightClick() ) {
		Vector2f targetPosition = Vector2f( g_Mouse.Position().x, g_Mouse.Position().y );
		Unit* enemyTarget = nullptr;

		// Check if player clicked an enemy
		for ( auto& unit : unitsHostile ) {
			const Vector2f distance = unit.GetPosition() - targetPosition;

			if ( math::vec2f::LengthSqrd( distance ) <= UNIT_RADIUS * UNIT_RADIUS ) {
				enemyTarget = &unit;
			}
		}

		if ( enemyTarget ) {
			for ( auto& unit : unitsFriendly ) {
				unit.CommandAttackTarget( enemyTarget );
			}
		} else {
			for ( auto& unit : unitsFriendly ) {
				unit.CommandMove( targetPosition );
			}
		}
	}

	static bool cloneKeyPressedPreviousFrame	= false;
	bool cloneKeyPressedThisFrame				= Keyboard::isKeyPressed( Keyboard::Key::C );
	m_WantsToClone								= cloneKeyPressedThisFrame && !cloneKeyPressedPreviousFrame;
	cloneKeyPressedPreviousFrame				= cloneKeyPressedThisFrame;
}