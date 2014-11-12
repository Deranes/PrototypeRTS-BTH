#pragma once

#include <SFML/Graphics.hpp>

#define UNIT_MOVESPEED		200.0f
#define UNIT_HP_MAX			10
#define UNIT_RADIUS			20.0f
#define UNIT_MELEE_RANGE	25.0f

class Player;

enum class UnitState {
	Idle,
	Moving,
	MovingToAttack,
};

class Unit {
public:
	void					Initialize				( const sf::Vector2f& position, Player* owner );
	void					Update					( float deltaTime );
	void					Draw					( sf::RenderWindow* window );

	void					CommandMove				( const sf::Vector2f& targetPosition );
	void					CommandAttackTarget		( Unit* target );
	void					CalcPenetrationResolve	( Unit* other, sf::Vector2f* outAppendResult );

	const sf::Vector2f&		GetPosition				( );
	const UnitState&		GetUnitState			( );
	int						GetHP					( );

	void					SetPosition				( const sf::Vector2f& newPosition );

private:
	Player*					m_Owner;
	sf::CircleShape			m_Sprite;
	sf::Vector2f			m_Position;
	sf::Vector2f			m_MoveTo;
	UnitState				m_UnitState;
	int						m_HP;
	Unit*					m_AttackTarget;
};