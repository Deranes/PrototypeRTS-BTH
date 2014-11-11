#pragma once

#include <SFML/Graphics.hpp>

#define UNIT_RADIUS	20.0f

class Unit {
public:
	void				Initialize	( const sf::Vector2f& position );
	void				Update		( float deltaTime );
	void				Draw		( sf::RenderWindow* window );

private:
	sf::Vector2f		m_Position;
	sf::CircleShape		m_Sprite;
};