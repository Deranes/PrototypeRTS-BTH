#include "Vector2f.h"


float math::vec2f::Length( const sf::Vector2f& toMeasure ) {
	sqrtf( toMeasure.x * toMeasure.x + toMeasure.y * toMeasure.y );
}

float math::vec2f::LengthSqrd( const sf::Vector2f& toMeasure ) {
	return toMeasure.x * toMeasure.x + toMeasure.y * toMeasure.y;
}

sf::Vector2f& math::vec2f::Normalize( const sf::Vector2f& toNormalize ) {
	return toNormalize * (1.0f / sqrtf( toNormalize.x * toNormalize.x + toNormalize.y * toNormalize.y ));
}