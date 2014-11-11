#include "Unit.h"

#include "../../input/GlobalMouse.h"
#include "../../math/Math.h"

using namespace sf;
using namespace math;

void Unit::Initialize( const sf::Vector2f& position ) {
	m_Position			= position;
	m_TargetPosition	= position;

	m_Sprite.setFillColor( sf::Color::Blue );
	m_Sprite.setRadius( UNIT_RADIUS );
}

void Unit::Update( float deltaTime ) {
	if ( g_Mouse.RightClick() ) {
		m_TargetPosition = Vector2f( g_Mouse.Position().x, g_Mouse.Position().y );
	}

	Vector2f distance = m_TargetPosition - m_Position;
	
	if ( distance.x != 0.0f || distance.y != 0.0f ) {
		m_Position += UNIT_MOVESPEED * deltaTime * vec2f::Normalize( distance );
	}
}

void Unit::Draw( sf::RenderWindow* window ) {
	m_Sprite.setPosition( m_Position );

	window->draw( m_Sprite );
}