#include <SFML/Graphics.hpp>
#include <iostream>
#include "RayCaster.h"
#include <math.h>

int main(){
    cst::RayCaster RC;
	RC.camPos.x=250; RC.camPos.y=450;
    RC.castRays();

    sf::RenderWindow window(sf::VideoMode(500, 500), "Ray caster 2D");
	sf::Clock clock1;
	while (window.isOpen()) {

        sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				std::cout << event.key.code << std::endl;
				
				if(event.key.code==71){
					RC.dir-=0.1f;
				}
				if(event.key.code==72){
					RC.dir+=0.1f;
				}
				if(event.key.code==73){
					sf::Vector2f mov(std::cos(RC.dir)*5.0f,std::sin(RC.dir)*5.0f);
					RC.camPos+=mov;
				}
				if(RC.dir<0.0f){
					RC.dir=6.2831f;
				}
				if(RC.dir>6.2831f){
					RC.dir=0.025f;
				}
				std::cout << "new Anlge = " << RC.dir << std::endl;
				break;
			default:
				break;
			}
				
		}
		
		window.clear();
		RC.castRays();
        RC.drawRays(window);
		//RC.draw3D(window);
		window.display();
		sf::Time elapsed1 = clock1.getElapsedTime();
		//std::cout << elapsed1.asMilliseconds() << std::endl;
		clock1.restart();
	}

    return 0;

}