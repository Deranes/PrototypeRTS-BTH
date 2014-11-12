#include <SFML/Graphics.hpp>
#include "game/Game.h"
#include "input/GlobalMouse.h"

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Large Game Project - RTS Prototype 0.3 - HP and melee attack", sf::Style::Default, settings );

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
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) ){
			window.close();
		}

		sf::Time deltaTime = deltaClock.restart();

		g_Mouse.Update( window );

		game.Update( deltaTime.asSeconds() );

		window.clear( sf::Color::White );
		game.Draw();
		window.display();
    }

    return 0;	// EXIT_SUCCESS
}