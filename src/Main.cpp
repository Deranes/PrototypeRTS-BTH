#include <SFML/Graphics.hpp>

#include "game/Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Large Game Project - RTS Prototype 0.1");

	Game game;
	game.Initialize( &window );

	sf::Clock deltaClock;

    while ( window.isOpen() ) {
        sf::Event event;
        while ( window.pollEvent( event ) ) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
			}
        }

		sf::Time deltaTime = deltaClock.restart();

		game.Update( deltaTime.asSeconds() );
		game.Draw();
    }

    return 0;	// EXIT_SUCCESS
}