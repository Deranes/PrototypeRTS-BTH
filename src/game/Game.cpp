#include "Game.h"

using namespace sf;

void Game::Initialize( sf::RenderWindow* window ) {
	m_Window = window;
}

void Game::Update( float deltaTime ) {

}

void Game::Draw() {
	m_Window->clear();
	m_Window->display();
}