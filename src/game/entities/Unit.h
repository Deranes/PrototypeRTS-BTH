#pragma once

#include <SFML/Graphics.hpp>

#define UNIT_RADIUS		20.0f
#define UNIT_MOVESPEED	200.0f

class Unit {
public:
	void				Initialize	( const sf::Vector2f& position );
	void				Update		( float deltaTime );
	void				Draw		( sf::RenderWindow* window );

private:
	sf::CircleShape		m_Sprite;
	sf::Vector2f		m_Position;
	sf::Vector2f		m_TargetPosition;
};