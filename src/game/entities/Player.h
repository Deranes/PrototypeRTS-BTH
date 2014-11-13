#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Unit;

#define PLAYER_START_RESOURCES	0

class Player {
public:
	virtual void		Initialize			( sf::Color color );
	virtual void		Update				( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile );

	const sf::Color&	GetColor			( ) const;
	bool				GetWantsToClone		( ) const;
	int					GetResource			( ) const;

	void				SetResource			( int resource );

protected:
	bool				m_WantsToClone;
	int					m_Resource;

private:
	sf::Color			m_Color;
};