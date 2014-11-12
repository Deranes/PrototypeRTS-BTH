#include "Player.h"

void Player::Initialize( sf::Color color ) {
	m_Color			= color;
	m_WantsToClone	= false;
}

void Player::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {

}

const sf::Color& Player::GetColor() {
	return m_Color;
}

bool Player::GetWantsToClone( ) {
	return m_WantsToClone;
}