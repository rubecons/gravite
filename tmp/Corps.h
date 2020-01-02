/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Corps.h
 * Author: ruben
 *
 * Created on 27 décembre 2017, 15:18
 */

#ifndef CORPS_H
#define CORPS_H

#include <cstdlib>
#include <SFML/System/Vector2.hpp>
#include <memory>

class Corps {
public:
    Corps();
    Corps(const Corps& orig);
    Corps(float x, float y, float r, float vx, float vy);
    virtual ~Corps();
    
    float getPosX(){return posi.x;}//posX;}
    float getPosY(){return posi.y;}//posY;}
    float getTmpPosX(){return tmpPosi.x;}//posX;}
    float getTmpPosY(){return tmpPosi.y;}//posY;}
    float getRayon(){return rayon;}
    float getVx(){return vX;}
    float getVy(){return vY;}
    float getTmpVx(){return tmpVX;}
    float getTmpVy(){return tmpVY;}
    
    void setPosi(float x, float y){ posi.x = x; posi.y = y;}
    void setTmpPosi(float x, float y){ tmpPosi.x = x; tmpPosi.y = y;}
    void setRayon(float r){rayon = r;}
    void setVitesse(sf::Vector2f vitesse){vX = vitesse.x; vY = vitesse.y;}
    void setTmpVitesse(float x, float y){tmpVX = x; tmpVY = y;}
    void setTmpVitesse(sf::Vector2f vitesse){tmpVX = vitesse.x; tmpVY = vitesse.y;}
    
    void print(int i);
    void majEtat(void);
    
    static sf::Vector2f conservQteMouvement(std::shared_ptr<Corps> c1, std::shared_ptr<Corps> c2);
    
    //static int nbrCorps;
    //bool valide;
    
    
private:
    /*uint posX;
    uint posY;*/
    sf::Vector2f posi;
    sf::Vector2f tmpPosi;
    float rayon;
    
    float vX;
    float vY;
    float tmpVX;
    float tmpVY;

    
};

#endif /* CORPS_H */

