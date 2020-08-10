#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <vector>
#include <SFML/Graphics.hpp>


namespace cst{

    

    class Line{
    private:

    public:
        Line(sf::Vector2f sp, sf::Vector2f ep);
        sf::Color color;
        sf::Vector2f startPos, endPos;
    };

    class KXM{
    /*
        En kalss som håller en y=kx+m linje
        och som kan utföra beräkningar med räta linjer
    */
    private:

    public:
        float k=0.0f;
        float m=0.0f;
        void setValues(cst::Line line); // INTE SKAPAD BÖRJA HÄR!
        sf::Vector2f getColPos(cst::KXM kxm); // get collition position
    };

    class RayCaster{
    private:
        //Vars
        std::vector<cst::Line> lines;
        std::vector<sf::Vector2f> rayDirs;
        std::vector<float> rayLengths;
        float FOV=1.5f;
        
        //Functions
        sf::Vector2f normalize(sf::Vector2f vector);
    public:
        //publiv vars:
        float dir = 6.2831f;
        sf::Vector2f camPos;
        //public functions
        std::vector<float> castRays();
        void drawRays(sf::RenderWindow &window); // 2d rendering of the scene
        void draw3D(sf::RenderWindow &window);
        float getAbsAngle(sf::Vector2f normVector);
        float isRayInBetween(float rayAngle, float sA, float eA, cst::Line relLine);
    };

}



#endif

