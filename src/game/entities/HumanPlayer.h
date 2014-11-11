#pragma once

#include "Player.h"

class HumanPlayer : public Player {
public:
	virtual void Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile );
};