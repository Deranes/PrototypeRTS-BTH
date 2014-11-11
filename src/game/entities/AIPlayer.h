#pragma once

#include "Player.h"

class AIPlayer : public Player {
public:
	virtual void Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile );
};