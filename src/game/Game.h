#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Unit.h"
#include "entities/HumanPlayer.h"
#include "entities/AIPlayer.h"

class Game {
public:
	void				Initialize	( sf::RenderWindow* window );
	void				Update		( float deltaTime );
	void				Draw		( );

private:
	sf::RenderWindow*	m_Window;
	HumanPlayer			m_Player;
	AIPlayer			m_AI;
	std::vector<Unit>	m_PlayerUnits;
	std::vector<Unit>	m_AIUnits;
};