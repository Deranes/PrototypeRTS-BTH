#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

#define g_Mouse GlobalMouse::GetInstance()

class GlobalMouse {
public:
	static GlobalMouse&	GetInstance();

	void				Update( const sf::RenderWindow& window );
	bool				LeftClick();
	bool				RightClick();
	const Vector2i&		Position();

private:
						GlobalMouse();

	Vector2i			m_Position;
	bool				m_LeftPressedThisFrame;
	bool				m_LeftPressedPreviousFrame;
	bool				m_RightPressedThisFrame;
	bool				m_RightPressedPreviousFrame;
};