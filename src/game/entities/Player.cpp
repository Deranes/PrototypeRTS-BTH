#include "Player.h"

void Player::Initialize( sf::Color color ) {
	m_Color = color;
}

void Player::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {

}

const sf::Color& Player::GetColor() {
	return m_Color;
}