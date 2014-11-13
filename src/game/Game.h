#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Unit.h"
#include "entities/HumanPlayer.h"
#include "entities/AIPlayer.h"
#include "entities/Resource.h"

#define UNIT_PENETRATION_RESOLVING	0.3f

class Game {
public:
	void					Initialize	( sf::RenderWindow* window );
	void					Update		( float deltaTime );
	void					Draw		( );

private:
	sf::RenderWindow*		m_Window;
	HumanPlayer				m_Player;
	AIPlayer				m_AI;
	std::vector<Unit>		m_PlayerUnits;
	std::vector<Unit>		m_AIUnits;
	std::vector<Resource>	m_Resources;
};