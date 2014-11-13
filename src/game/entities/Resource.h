#pragma once

#include <SFML/Graphics.hpp>

#define RESOURCE_WORTH	20
#define RESOURCE_RADIUS	15.0f
#define RESOURCE_COLOR	sf::Color::Cyan

class Resource {
public:
	void				Initialize	( const sf::Vector2f& position );
	void				Draw		( sf::RenderWindow* window );

	int					Worth;
	sf::Vector2f		Position;
	float				Radius;
	sf::CircleShape		Sprite;
};