#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Unit.h"

class Game {
public:
	void				Initialize	( sf::RenderWindow* window );
	void				Update		( float deltaTime );
	void				Draw		( );

private:
	sf::RenderWindow*	m_Window;
	Unit				m_Unit;
};