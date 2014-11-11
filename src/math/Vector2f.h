#pragma once

#include <SFML/Graphics.hpp>	// Overkill but whatever

namespace math {
	namespace vec2f {
		float			Length		( const sf::Vector2f& toMeasure );
		float			LengthSqrd	( const sf::Vector2f& toMeasure );
		sf::Vector2f	Normalize	( const sf::Vector2f& toNormalize );
	};
};