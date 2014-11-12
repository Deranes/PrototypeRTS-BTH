#include "HumanPlayer.h"

#include "../../input/GlobalMouse.h"
#include "Unit.h"
#include "../../math/Math.h"

using namespace sf;

void HumanPlayer::Initialize( sf::Color color ) {
	Player::Initialize( color );

	m_WaitingForAttackPosition = false;
}

void HumanPlayer::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {
	m_WantsToClone = false;

	if ( Keyboard::isKeyPressed( Keyboard::Key::A ) ) {
		m_WaitingForAttackPosition = true;
	}

	if ( g_Mouse.RightClick() ) {
		m_WaitingForAttackPosition	= false;

		Vector2f	targetPosition	= Vector2f( g_Mouse.Position().x, g_Mouse.Position().y );
		Unit*		enemyTarget		= nullptr;

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

	if ( m_WaitingForAttackPosition && g_Mouse.LeftClick() ) {
		m_WaitingForAttackPosition = false;

		Vector2f targetPosition	= Vector2f( g_Mouse.Position().x, g_Mouse.Position().y );

		for ( auto& unit : unitsFriendly ) {
			unit.CommandAttackMove( targetPosition );
		}
	}

	static bool cloneKeyPressedPreviousFrame	= false;
	bool cloneKeyPressedThisFrame				= Keyboard::isKeyPressed( Keyboard::Key::C );
	m_WantsToClone								= cloneKeyPressedThisFrame && !cloneKeyPressedPreviousFrame;
	cloneKeyPressedPreviousFrame				= cloneKeyPressedThisFrame;
}