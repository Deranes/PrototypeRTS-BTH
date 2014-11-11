#include "Unit.h"

void Unit::Initialize( const sf::Vector2f& position ) {
	m_Position = position;

	m_Sprite.setFillColor( sf::Color::Blue );
	m_Sprite.setRadius( UNIT_RADIUS );
}

void Unit::Update( float deltaTime ) {

}

void Unit::Draw( sf::RenderWindow* window ) {
	m_Sprite.setPosition( m_Position );

	window->draw( m_Sprite );
}