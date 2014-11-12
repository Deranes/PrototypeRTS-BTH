#include "Player.h"

void Player::Initialize( sf::Color color ) {
	m_Color			= color;
	m_WantsToClone	= false;
	m_Resource		= PLAYER_START_RESOURCES;
}

void Player::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {

}

const sf::Color& Player::GetColor() const {
	return m_Color;
}

bool Player::GetWantsToClone( ) const {
	return m_WantsToClone;
}

int Player::GetResource() const {
	return m_Resource;
}

void Player::SetResource( int resource ) {
	m_Resource = resource;
}