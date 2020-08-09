#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <vector>
#include <SFML/Graphics.hpp>


namespace cst{


    class RayCaster{
    private:
        sf::Vector2f camPos;
        std::vector<sf::Vector2f> rayDirs;
        float FOV=2.0f;
        float dir = 0.0f; 
    public:
        std::vector<float> castRays();
        void drawRays(sf::RenderWindow &window);
    };

}



#endif

