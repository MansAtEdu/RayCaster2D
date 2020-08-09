#include "RayCaster.h"
#include <iostream>
#include <math.h>


std::vector<float> cst::RayCaster::castRays(){
    rayDirs.clear();
    camPos.x=250; camPos.y=250;
    int resolution = 10;

    for(int i = 0; i<resolution; i++){
        sf::Vector2f rayDir(0,0);
        float dirDiff = (i-(resolution/2.0f))/(float)resolution * (float)FOV;
        rayDir.x = std::cos(dirDiff+dir);
        rayDir.y = std::sin(dirDiff+dir);
        rayDirs.push_back(rayDir);
        std::cout << "Dir = (" << rayDir.x << ", " << rayDir.y << ")" << std::endl;
    }

    std::vector<float> tmp;
    return tmp;
}

void cst::RayCaster::drawRays(sf::RenderWindow &window){

    for(int i=0; i<rayDirs.size(); i++){
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = camPos;
        line[0].color = sf::Color::White;
        sf::Vector2f rayEnd(0,0);
        rayEnd.x =camPos.x + rayDirs[i].x*100;
        rayEnd.x =camPos.y + rayDirs[i].y*100;
        line[1].position = rayEnd;
        line[1].color = sf::Color::White;
        window.draw(line);
    }

}
