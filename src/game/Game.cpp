#include "Game.h"

#include "../graphics/TextPrinter.h"

using namespace sf;

void Game::Initialize( sf::RenderWindow* window ) {
	m_Window	= window;

	m_Player.Initialize( sf::Color::Blue );
	m_AI.Initialize( sf::Color::Red );

	m_PlayerUnits.resize(1);
	m_AIUnits.resize(1);

	for ( auto& unit : m_PlayerUnits ) {
		unit.Initialize( Vector2f( 100.0f, window->getSize().y - 100.0f ), &m_Player );
	}

	for ( auto& unit : m_AIUnits ) {
		unit.Initialize( Vector2f( window->getSize().x - 100.0f, 100.0f ), &m_AI );
	}
}

void Game::Update( float deltaTime ) {
	m_Player.Update( m_PlayerUnits, m_AIUnits );
	m_AI.Update( m_AIUnits, m_PlayerUnits );

	for ( auto& unit : m_PlayerUnits ) {
		unit.Update( deltaTime );
	}
	for ( auto& unit : m_AIUnits ) {
		unit.Update( deltaTime );
	}

	// Check for deaths
	for ( int i = m_PlayerUnits.size() - 1; i >= 0; --i ) {
		if ( m_PlayerUnits[i].GetHP() <= 0 ) {
			m_PlayerUnits.erase( m_PlayerUnits.begin() + i );
		}
	}
	for ( int i = m_AIUnits.size() - 1; i >= 0; --i ) {
		if ( m_AIUnits[i].GetHP() <= 0 ) {
			m_AIUnits.erase( m_AIUnits.begin() + i );
		}
	}
	
	// Victory condition
	if ( m_PlayerUnits.size() == 0 ) {
		// AI Wins
		g_TextPrinter.PrintText( "DEFEAT", Vector2i( m_Window->getSize().x / 2, m_Window->getSize().y / 3 ), 200, Color::Red, Vector2f( 0.5f, 1.0f ) );
	} else if ( m_AIUnits.size() == 0 ) {
		// Human Wins
		g_TextPrinter.PrintText( "VICTORY", Vector2i( m_Window->getSize().x / 2, m_Window->getSize().y / 3 ), 200, Color::Blue, Vector2f( 0.5f, 1.0f ) );
	}

	// Cloning
	if ( m_Player.GetWantsToClone() ) {
		int cost = UNIT_RESOURCE_COST * m_PlayerUnits.size();
		if ( cost <= m_Player.GetResource() ) {
			m_Player.SetResource( m_Player.GetResource() - cost );
			m_PlayerUnits.insert( m_PlayerUnits.end(), m_PlayerUnits.begin(), m_PlayerUnits.end() );
		}
	}
	if ( m_AI.GetWantsToClone() && m_AI.GetResource() >= UNIT_RESOURCE_COST * m_AIUnits.size() ) {
		int cost = UNIT_RESOURCE_COST * m_AIUnits.size();
		if ( cost <= m_AI.GetResource() ) {
			m_AI.SetResource( m_AI.GetResource() - cost );
			m_AIUnits.insert( m_AIUnits.end(), m_AIUnits.begin(), m_AIUnits.end() );
		}
	}

	// Resolve collisions by pushing units away from each other.
	for ( auto& unit : m_PlayerUnits ) {
		Vector2f penetrationTotal( 0.0f, 0.0f);
		for ( auto& friendlyUnit : m_PlayerUnits ) {
			if ( &unit == &friendlyUnit ) {
				continue;
			}
			unit.CalcPenetrationResolve( &friendlyUnit, &penetrationTotal );
		}
		for ( auto& enemyUnit : m_AIUnits ) {
			unit.CalcPenetrationResolve( &enemyUnit, &penetrationTotal );
		}
		unit.SetPosition( unit.GetPosition() + UNIT_PENETRATION_RESOLVING * penetrationTotal );
	}

	for ( auto& unit : m_AIUnits ) {
		Vector2f penetrationTotal( 0.0f, 0.0f);
		for ( auto& friendlyUnit : m_AIUnits ) {
			if ( &unit == &friendlyUnit ) {
				continue;
			}
			unit.CalcPenetrationResolve( &friendlyUnit, &penetrationTotal );
		}
		for ( auto& enemyUnit : m_PlayerUnits ) {
			unit.CalcPenetrationResolve( &enemyUnit, &penetrationTotal );
		}
		unit.SetPosition( unit.GetPosition() + UNIT_PENETRATION_RESOLVING * penetrationTotal );
	}

	g_TextPrinter.Update( deltaTime );
}

void Game::Draw() {
	for ( auto& unit : m_PlayerUnits ) {
		unit.Draw( m_Window );
	}

	for ( auto& unit : m_AIUnits ) {
		unit.Draw( m_Window );
	}

	g_TextPrinter.PrintNumber( m_Player.GetResource(), Vector2i( 0, 0 ), 30, m_Player.GetColor(), Vector2f( 0.0f, 0.0f ) );

	g_TextPrinter.Draw( *m_Window );
}