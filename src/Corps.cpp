/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Corps.cpp
 * Author: ruben
 * 
 * Created on 27 décembre 2017, 15:18
 */

#include <iostream>
#include <random>

#include "Corps.h"
#include "Univers.h"
#include "Constantes.h"

Corps::Corps() {
    //nbrCorps++;
    //srand(time(NULL));
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> distX(1,MAXUNIVERS_X);
    std::uniform_int_distribution<std::mt19937::result_type> distY(1,MAXUNIVERS_Y);
    //posi.x = (float)(std::rand()%MAXUNIVERS_X);
    //posi.y = (float)(std::rand()%MAXUNIVERS_Y);
    posi.x = distX(rng);
    posi.y = distY(rng);
    rayon = RAYONINITIAL;
    
    vX = 0;
    vY = 0;
    
    //valide = true;
}

Corps::Corps(const Corps& orig) {
}

Corps::Corps(float x, float y, float r, float vx, float vy): /*valide(true),*/ posi(x, y), rayon(r), vX(vx), vY(vy)
{
   
}

Corps::~Corps() {
    //std::cout<<"corps supprimé avec succes"<<std::endl;
}

void Corps::print(int i)
{
    //if(valide)
    //{
        std::cout<<"le corps "<<i <<" se trouve en : "<<posi.x<<", "<<posi.y<<std::endl;
    /*}
    else
    {
        std::cout<<"le corps "<<i <<" est invalide"<<std::endl;
    }*/
}

sf::Vector2f Corps::conservQteMouvement(std::shared_ptr<Corps> c1, std::shared_ptr<Corps> c2)
{
    
    float x = ((c1->getRayon() * c1->getVx()) + (c2->getRayon() * c2->getVx())) / (c1->getRayon() + c2->getRayon());
    float y = ((c1->getRayon() * c1->getVy()) + (c2->getRayon() * c2->getVy())) / (c1->getRayon() + c2->getRayon());
    
    return sf::Vector2f(x, y);
}