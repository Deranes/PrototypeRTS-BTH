#include "Resource.h"

void Resource::Initialize( const sf::Vector2f& position ) {
	this->Position	= position;

	this->Worth		= RESOURCE_WORTH;
	this->Radius	= RESOURCE_RADIUS;
	
	this->Sprite.setPosition( position );
	this->Sprite.setFillColor( RESOURCE_COLOR );
	this->Sprite.setRadius( RESOURCE_RADIUS );
	this->Sprite.setOrigin( RESOURCE_RADIUS, RESOURCE_RADIUS );
}

void Resource::Draw( sf::RenderWindow* window ) {
	window->draw( this->Sprite );
}