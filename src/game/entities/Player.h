#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Unit;

class Player {
public:
	virtual void		Initialize			( sf::Color color );
	virtual void		Update				( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile );

	const sf::Color&	GetColor			( );

private:
	sf::Color			m_Color;
};