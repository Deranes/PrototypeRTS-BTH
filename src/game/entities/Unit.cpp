#include "Unit.h"

#include "../../math/Math.h"
#include "Player.h"
#include "Resource.h"
#include "../../graphics/TextPrinter.h"

using namespace sf;
using namespace math;

#define RANDF	( rand() / static_cast<float>(RAND_MAX) )

void Unit::Initialize( const sf::Vector2f& position, Player* owner ) {
	m_Position		= position;
	m_MoveTo		= position;
	m_Owner			= owner;

	m_HP			= UNIT_HP_MAX;
	m_UnitState		= UnitState::Idle;

	m_Sprite.setFillColor( owner->GetColor() );
	m_Sprite.setRadius( UNIT_RADIUS );
	m_Sprite.setOrigin( UNIT_RADIUS, UNIT_RADIUS );
}

void Unit::Initialize( const Unit& toClone ) {
	Initialize( toClone.GetPosition(), toClone.GetOwner() );
}

void Unit::Update( float deltaTime, std::vector<Unit>& unitsHostile ) {
	m_AttackCooldownLeft -= deltaTime;
	if ( m_AttackCooldownLeft > 0.0f ) {
		return;
	}

	switch ( m_UnitState ) {
		case UnitState::Idle : {
			for ( auto& enemy : unitsHostile ) {
				if ( math::vec2f::LengthSqrd( m_Position - enemy.GetPosition() ) <= UNIT_AGGRO_DISTANCE * UNIT_AGGRO_DISTANCE ) {
					CommandAttackTarget( &enemy );
					break;
				}
			}
		} break;

		case UnitState::Moving : {
			const Vector2f	distance	= m_MoveTo - m_Position;
			const float		distLeft	= vec2f::Length( distance );
			const float		maxDist		= UNIT_MOVESPEED * deltaTime;

			if ( distLeft <= maxDist ) {
				m_UnitState = UnitState::Idle;
			}

			if ( distance.x != 0.0f || distance.y != 0.0f ) {
				m_Position += ( fminf(distLeft, maxDist) / distLeft ) * distance;
			}
		} break;

		case UnitState::MovingToAttack : {
			const Vector2f	distance	= m_AttackTarget->GetPosition() - m_Position;
			const float		distLeft	= vec2f::Length( distance );
			const float		maxDist		= UNIT_MOVESPEED * deltaTime;

			if ( distLeft <= UNIT_MELEE_RANGE + UNIT_RADIUS ) {
				m_AttackTarget->Damage( UNIT_MELEE_DAMAGE );
				m_AttackCooldownLeft = UNIT_MELEE_COOLDOWN;
				//g_TextPrinter.PrintFloatingText( Vector2i( m_AttackTarget->GetPosition().x, m_AttackTarget->GetPosition().y ), UNIT_MELEE_DAMAGE, 3.0f );
			} else if ( distance.x != 0.0f || distance.y != 0.0f ) {
				m_Position += ( fminf(distLeft, maxDist) / distLeft ) * distance;
			}
		} break;

		case UnitState::AttackMoving : {
			if ( !m_AttackTarget ) {
				float closest = FLT_MAX;
				for ( auto& enemy : unitsHostile ) {
					float distSqrd = math::vec2f::LengthSqrd( enemy.GetPosition() - m_Position );
					if ( distSqrd < closest ) {
						closest = distSqrd;
						m_AttackTarget = &enemy;
					}
				}
			}

			if ( m_AttackTarget ) {
				const Vector2f	distance	= m_AttackTarget->GetPosition() - m_Position;
				const float		distLeft	= vec2f::Length( distance );
				const float		maxDist		= UNIT_MOVESPEED * deltaTime;

				if ( distLeft <= UNIT_MELEE_RANGE + UNIT_RADIUS ) {
					m_AttackTarget->Damage( UNIT_MELEE_DAMAGE );
					m_AttackCooldownLeft = UNIT_MELEE_COOLDOWN;
					//g_TextPrinter.PrintFloatingText( Vector2i( m_AttackTarget->GetPosition().x, m_AttackTarget->GetPosition().y ), UNIT_MELEE_DAMAGE, 3.0f );
				} else if ( distance.x != 0.0f || distance.y != 0.0f ) {
					m_Position += ( fminf(distLeft, maxDist) / distLeft ) * distance;
				}
			} else {
				const Vector2f	distance	= m_MoveTo - m_Position;
				const float		distLeft	= vec2f::Length( distance );
				const float		maxDist		= UNIT_MOVESPEED * deltaTime;

				if ( distance.x != 0.0f || distance.y != 0.0f ) {
					m_Position += ( fminf(distLeft, maxDist) / distLeft ) * distance;
				}
			}
		} break;
	}
}

void Unit::Draw( sf::RenderWindow* window ) {
	m_Sprite.setPosition( m_Position );

	window->draw( m_Sprite );
}

void Unit::CommandMove( const sf::Vector2f& targetPosition ) {
	m_MoveTo		= targetPosition;
	m_UnitState		= UnitState::Moving;
}

void Unit::CommandAttackMove( const sf::Vector2f& targetPosition ) {
	m_MoveTo		= targetPosition;
	m_UnitState		= UnitState::AttackMoving;
	m_AttackTarget	= nullptr;
}

void Unit::CommandAttackTarget( Unit* target ) {
	m_AttackTarget	= target;
	m_UnitState		= UnitState::MovingToAttack;
}

void Unit::CalcPenetrationResolve( Unit* other, sf::Vector2f* outAppendResult ) {
	Vector2f		distance		= m_Position != other->GetPosition() ? m_Position - other->GetPosition() : Vector2f( RANDF, RANDF );
	const float		distanceAsFloat	= vec2f::Length( distance );
	const float		penetration		= ( UNIT_RADIUS * 2 ) - distanceAsFloat;

	if ( penetration > 0.0f ) {
		*outAppendResult += distance * (penetration / distanceAsFloat);
	}
}

bool Unit::CalcPenetrationResolve( Resource* resource, sf::Vector2f* outAppendResult ) {
	Vector2f		distance		= m_Position != resource->Position ? m_Position - resource->Position : Vector2f( RANDF, RANDF );
	const float		distanceAsFloat	= vec2f::Length( distance );
	const float		penetration		= ( UNIT_RADIUS + resource->Radius ) - distanceAsFloat;

	if ( penetration >= 0.0f ) {
		*outAppendResult += distance * (penetration / distanceAsFloat);
		return true;
	} else {
		return false;
	}
}

void Unit::Damage( int damage ) {
	m_HP -= damage;
}

const sf::Vector2f& Unit::GetPosition() const {
	return m_Position;
}

const UnitState& Unit::GetUnitState() const {
	return m_UnitState;
}

int Unit::GetHP() const {
	return m_HP;
}

Player*	Unit::GetOwner ( ) const {
	return m_Owner;
}

void Unit::SetPosition( const sf::Vector2f& newPosition ) {
	m_Position = newPosition;
}