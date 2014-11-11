#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
	void				Initialize	( sf::RenderWindow* window );
	void				Update		( float deltaTime );
	void				Draw		( );

private:
	sf::RenderWindow*	m_Window;
};