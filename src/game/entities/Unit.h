#pragma once

#include <SFML/Graphics.hpp>

#define UNIT_RADIUS		20.0f
#define UNIT_MOVESPEED	200.0f

class Player;

enum class UnitState {
	Idle,
	Moving
};

class Unit {
public:
	void				Initialize	( const sf::Vector2f& position, Player* owner );
	void				Update		( float deltaTime );
	void				Draw		( sf::RenderWindow* window );

	void				CommandMove	( const sf::Vector2f& targetPosition );

	const UnitState&	GetUnitState();

private:
	Player*				m_Owner;
	sf::CircleShape		m_Sprite;
	sf::Vector2f		m_Position;
	sf::Vector2f		m_TargetPosition;
	UnitState			m_UnitState;
};