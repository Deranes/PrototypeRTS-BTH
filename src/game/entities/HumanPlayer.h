#pragma once

#include "Player.h"

class HumanPlayer : public Player {
public:
	virtual void	Initialize( sf::Color color );
	virtual void	Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile );

private:
	bool			m_WaitingForAttackPosition;
};