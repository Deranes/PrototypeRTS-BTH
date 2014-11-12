#pragma once

#include <SFML/Graphics.hpp>

#define UNIT_HP_MAX			8
#define UNIT_RADIUS			20.0f
#define UNIT_MOVESPEED		200.0f

#define UNIT_MELEE_DAMAGE	2
#define UNIT_MELEE_RANGE	25.0f
#define UNIT_MELEE_COOLDOWN	0.5f

class Player;

enum class UnitState {
	Idle,
	Moving,
	MovingToAttack,
};

class Unit {
public:
	void					Initialize				( const sf::Vector2f& position, Player* owner );
	void					Initialize				( const Unit& toClone );
	void					Update					( float deltaTime );
	void					Draw					( sf::RenderWindow* window );

	void					CommandMove				( const sf::Vector2f& targetPosition );
	void					CommandAttackTarget		( Unit* target );
	void					CalcPenetrationResolve	( Unit* other, sf::Vector2f* outAppendResult );
	void					Damage					( int damage );

	const sf::Vector2f&		GetPosition				( ) const;
	const UnitState&		GetUnitState			( ) const;
	int						GetHP					( ) const;
	Player*					GetOwner				( ) const;

	void					SetPosition				( const sf::Vector2f& newPosition );

private:
	Player*					m_Owner;
	sf::CircleShape			m_Sprite;
	sf::Vector2f			m_Position;
	sf::Vector2f			m_MoveTo;
	UnitState				m_UnitState;
	int						m_HP;
	Unit*					m_AttackTarget;
	float					m_AttackCooldownLeft;
};