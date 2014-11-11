#include "GlobalMouse.h"

GlobalMouse& GlobalMouse::GetInstance() {
	static GlobalMouse instance;
	return instance;
}

GlobalMouse::GlobalMouse() {
	m_LeftPressedThisFrame		= false;
	m_LeftPressedPreviousFrame	= false;
	m_RightPressedThisFrame		= false;
	m_RightPressedPreviousFrame	= false;
}

void GlobalMouse::Update( const sf::RenderWindow& window ) {
	// Store previous frames state, and fetch current frames state.
	m_LeftPressedPreviousFrame	= m_LeftPressedThisFrame;
	m_RightPressedPreviousFrame	= m_RightPressedThisFrame;

	m_LeftPressedThisFrame		= Mouse::isButtonPressed( Mouse::Button::Left );
	m_RightPressedThisFrame		= Mouse::isButtonPressed( Mouse::Button::Right );

	m_Position					= Mouse::getPosition( window );
}

bool GlobalMouse::LeftClick() {
	return m_LeftPressedThisFrame && !m_LeftPressedPreviousFrame;
}

bool GlobalMouse::RightClick() {
	return m_RightPressedThisFrame && !m_RightPressedPreviousFrame;
}

const Vector2i& GlobalMouse::Position() {
	return m_Position;
}