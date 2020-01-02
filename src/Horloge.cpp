/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Horloge.cpp
 * Author: ruben
 * 
 * Created on 1 janvier 2018, 23:50
 */

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Horloge.h"
#include "Rendu.h"
#include "Univers.h"

const std::shared_ptr<Horloge> Horloge::instance()
{
    static std::shared_ptr<Horloge> inst = std::make_shared<Horloge>();
    return inst;
}

Horloge::Horloge() {
}

Horloge::Horloge(const Horloge& orig) {
}

Horloge::~Horloge() {
}

void Horloge::threadCallerHorloge()
{
    std::thread threadHorloge(&Horloge::lancerHorloge,this);
    threadHorloge.detach();
}

void Horloge::lancerHorloge()
{
    sf::Time ecoule;
    sf::Clock horloge;
    
    std::shared_ptr<sf::RenderWindow> wind = Rendu::instance()->getWindow();
    
    while(wind->isOpen())
    {
        ecoule=horloge.restart();
        Univers::instance()->majEtats(ecoule);
    }
}