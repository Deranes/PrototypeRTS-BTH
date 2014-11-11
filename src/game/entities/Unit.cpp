#include "Unit.h"

#include "../../math/Math.h"
#include "Player.h"

using namespace sf;
using namespace math;

void Unit::Initialize( const sf::Vector2f& position, Player* owner ) {
	m_Position			= position;
	m_TargetPosition	= position;
	m_Owner				= owner;

	m_Sprite.setFillColor( owner->GetColor() );
	m_Sprite.setRadius( UNIT_RADIUS );
	m_Sprite.setOrigin( UNIT_RADIUS, UNIT_RADIUS );
}

void Unit::Update( float deltaTime ) {
	const Vector2f	distance	= m_TargetPosition - m_Position;
	const float		distLeft	= vec2f::Length( distance );
	const float		maxDist		= UNIT_MOVESPEED * deltaTime;
	
	if ( distLeft <= maxDist ) {
		m_UnitState = UnitState::Idle;
	}

	if ( distance.x != 0.0f || distance.y != 0.0f ) {
		m_Position += ( fminf(distLeft, maxDist) / distLeft ) * distance;
	}
}

void Unit::Draw( sf::RenderWindow* window ) {
	m_Sprite.setPosition( m_Position );

	window->draw( m_Sprite );
}

void Unit::CommandMove( const sf::Vector2f& targetPosition ) {
	m_TargetPosition	= targetPosition;
	m_UnitState			= UnitState::Moving;
}

const UnitState& Unit::GetUnitState() {
	return m_UnitState;
}