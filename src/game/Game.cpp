#include "Game.h"

using namespace sf;

void Game::Initialize( sf::RenderWindow* window ) {
	m_Window	= window;

	m_Unit.Initialize( Vector2f( 100.0f, 100.0f ) );
}

void Game::Update( float deltaTime ) {
	m_Unit.Update( deltaTime );
}

void Game::Draw() {
	m_Unit.Draw( m_Window );
}