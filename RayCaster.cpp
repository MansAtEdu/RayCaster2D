#include "RayCaster.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

void cst::KXM::setValues(cst::Line line){
    int leftPoint=0;
    if(line.startPos.x < line.endPos.x){leftPoint=0;} else{leftPoint=1;}
    float yDiff = line.endPos.y-line.startPos.y;
    float xDiff = line.endPos.x - line.startPos.x;
    k = yDiff/xDiff;
    if(leftPoint==0){  
        //Startpoint is on lines startpoint
        m = line.startPos.y - k * line.startPos.x;
    }
    else{
        //Startpoint is on lines endpoint
        m = line.endPos.y - k * line.endPos.x;
    }
    //std::cout << "KXM vals: k = " << k << " m= " << m << std::endl;
}

sf::Vector2f cst::KXM::getColPos(cst::KXM kxm){
    //gets the pos of collision between the two lines
    sf::Vector2f colPoint(0,0);
    colPoint.x = (kxm.m - m) / (k - kxm.k);
    colPoint.y = k*colPoint.x + m;
    return colPoint;
}

cst::Line::Line(sf::Vector2f sp, sf::Vector2f ep){

    startPos=sp; endPos = ep;

}


sf::Vector2f cst::RayCaster::normalize(sf::Vector2f vector){
    float length=0.0f;
    length = std::sqrt(std::pow(vector.x,2) + std::pow(vector.y,2));
    return sf::Vector2f(vector.x/length, vector.y / length);
}

float cst::RayCaster::getAbsAngle(sf::Vector2f normVector){
    //Ger resultat i radianer
    float angle=0.0f;
    if(normVector.y>=0.0f){
        angle = std::acos(normVector.x);
    }
    else{
        float diff = 3.14159265358979f - std::acos(normVector.x);
        angle = diff+3.14159265358979f;
    }
    return angle;
}

float cst::RayCaster::isRayInBetween(float rayAngle, float sA, float eA, cst::Line relLine){
    
    float TWO_PI = 2.0f * 3.14159265358979f;
    // DEBUG PRINT std::cout << "INFO: ray anlge = " << rayAngle << " | sA = " << sA << " | eA = " << eA << std::endl;
    if(rayAngle<0 || rayAngle>TWO_PI){
        rayAngle-=TWO_PI;
    }
    bool crossZero=false;
    float max=0, min=0;
    if(sA > eA){max=sA; min=eA;} else{max = eA; min = sA;}
    if(max-min > TWO_PI/2.0f){
        crossZero=true;
    }
    bool inside = (rayAngle < max && rayAngle > min);
    if(!crossZero && inside){
        return true;
    } else if(crossZero && !inside){
        return true;
    }
    return false;
}

std::vector<float> cst::RayCaster::castRays(){
    rayDirs.clear();
    rayLengths.clear();
    lines.clear();
    
    lines.push_back(cst::Line(sf::Vector2f(150,100), sf::Vector2f(400,100)));
    lines.push_back(cst::Line(sf::Vector2f(400,100), sf::Vector2f(450,400)));
    lines.push_back(cst::Line(sf::Vector2f(450,400), sf::Vector2f(100,450)));
    lines.push_back(cst::Line(sf::Vector2f(100,450), sf::Vector2f(150, 100)));
    //lines.push_back(cst::Line(sf::Vector2f(0,450), sf::Vector2f(350, 385)));
    /*for(int i=0; i< 5; i++){
        lines.push_back(cst::Line(sf::Vector2f(rand() % 500 + 0, rand() % 500 + 0), 
        sf::Vector2f(rand() % 500 + 0, rand() % 500 + 0)));
    }
    */ 
    int resolution = 100;
    
    for(int i = 0; i<resolution; i++){
        sf::Vector2f rayDir(0,0);
        float dirDiff = (i-(resolution/2.0f))/(float)resolution * (float)FOV;
        float angle = dirDiff + dir;
        rayDir.x = std::cos(angle);
        rayDir.y = std::sin(angle);

        //Line ray intersection
        float closestHit = INFINITY;
        float maxDist=1000;
        float minDist=10000;
        for(int j=0; j<lines.size(); j++){
            bool didHit=false;
            //Line pos relative to camera:
            cst::Line relLine (lines[j].startPos-camPos, lines[j].endPos-camPos);
            
            sf::Vector2f spNorm = normalize(sf::Vector2f(relLine.startPos.x, relLine.startPos.y));
      
            sf::Vector2f epNorm = normalize(sf::Vector2f(relLine.endPos.x, relLine.endPos.y));
            
            float sA = getAbsAngle(spNorm);
            float eA = getAbsAngle(epNorm);

            didHit = isRayInBetween(angle, sA, eA, relLine);
            if(didHit){
                // skaffa codrenaterna:
                cst::Line rayLine(camPos, rayDir*maxDist + camPos);
                cst::KXM lineKXM; lineKXM.setValues(lines[j]);
                cst::KXM rayKXM; rayKXM.setValues(rayLine);
                sf::Vector2f pointOfCollision = lineKXM.getColPos(rayKXM);
                pointOfCollision-=camPos;
                float thisDist = std::sqrt(std::pow(pointOfCollision.x,2) + std::pow(pointOfCollision.y,2));
                if(minDist > thisDist) {
                    minDist=thisDist;
                } 
            } 
        }
        //Projection correction of dist (avoid fisheye):
        float projectedDist=std::cos(dirDiff) * minDist;
        rayLengths.push_back(projectedDist);
        rayDirs.push_back(rayDir);
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
        rayEnd.x = camPos.x + rayDirs[i].x*rayLengths[i];
        rayEnd.y = camPos.y + rayDirs[i].y*rayLengths[i];
        line[1].position = rayEnd;
        line[1].color = sf::Color::White;
        window.draw(line);
    }
    //Draw lines:
    for(int i=0; i<lines.size(); i++){
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = lines[i].startPos;
        line[0].color = sf::Color::Red;
        line[1].position = lines[i].endPos;
        line[1].color = sf::Color::Red;
        window.draw(line);


    }

}

void cst::RayCaster::draw3D(sf::RenderWindow &window){
    int scaleFactor=5;
    sf::RectangleShape sp;
    int col=0;
    sp.setFillColor(sf::Color(255,255,255,255));
    sp.setSize(sf::Vector2f(scaleFactor, 500));
    for(int i=0; i<100;i++){
        float height=1.0f / rayLengths[i] * 5000;
        float fac = (500-rayLengths[i])/500.0f; 
        if(fac>1.0f){col=1.0f;} else if(fac<0.0f){fac=0.0f;}
        col = fac*255;;
        //float height = 500*fac;
        sp.setSize(sf::Vector2f(scaleFactor, height));
        sp.setFillColor(sf::Color(col,col,col,255));
        sp.setPosition(i*scaleFactor, (500-height)/2.0f);
        window.draw(sp);
    }
}
