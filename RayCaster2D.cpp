#include <SFML/Graphics.hpp>
#include <iostream>
#include "RayCaster.h"


int main(){
    cst::RayCaster RC;
    RC.castRays();
    std::cout << "Test" << std::endl;

    sf::RenderWindow window(sf::VideoMode(500, 500), "Ray caster 2D");

	while (window.isOpen()) {

        sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
				
		}

		window.clear();
        RC.drawRays(window);
		window.display();

	}

    return 0;

}