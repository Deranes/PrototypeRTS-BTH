#include "Game.h"

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
}

void Game::Draw() {
	for ( auto& unit : m_PlayerUnits ) {
		unit.Draw( m_Window );
	}

	for ( auto& unit : m_AIUnits ) {
		unit.Draw( m_Window );
	}
}