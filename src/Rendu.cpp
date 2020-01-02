/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rendu.cpp
 * Author: ruben
 * 
 * Created on 1 janvier 2018, 15:51
 */

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

#include "Rendu.h"
#include "Univers.h"
#include "Constantes.h"
#include "Horloge.h"

const std::shared_ptr<Rendu> Rendu::instance()
{
    static std::shared_ptr<Rendu> inst = std::make_shared<Rendu>();
    return inst;
}

Rendu::Rendu() {
}

Rendu::Rendu(const Rendu& orig) {
}

Rendu::~Rendu() {
}

void Rendu::init(){
    
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(MAXUNIVERS_X, MAXUNIVERS_Y), "gravite", sf::Style::Titlebar | sf::Style::Close);
    Horloge::instance()->threadCallerHorloge();
    window->setVerticalSyncEnabled(true);
    
    sf::Time ecoule;
    sf::Clock horloge;
    
    while (window->isOpen())
    {
        
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed : window->close();
                break;
                case sf::Event::MouseButtonPressed : if(event.mouseButton.button == sf::Mouse::Left){Univers::instance()->resetUnivers();}
                break;
                default : break;
            }
        }
        
        ecoule=horloge.restart();
        Univers::instance()->majEtats(ecoule);
        
        window->clear(sf::Color::Black);
        
        for(const std::shared_ptr<Corps> &corps : Univers::instance()->getCorps())
        {
            
            if(corps == nullptr){continue;}
            //if(!corps->valide){continue;}
            float rayon = corps->getRayon();
            sf::CircleShape cercle(rayon);
            cercle.setPosition(corps->getPosX()-rayon, corps->getPosY()-rayon);
            cercle.setFillColor(sf::Color(255, 255-(255 * (rayon - RAYONINITIAL) / std::sqrt(NOMBRECORPSSIMULTATION * RAYONINITIAL * RAYONINITIAL)), 255-(255 * (rayon - RAYONINITIAL) / std::sqrt(NOMBRECORPSSIMULTATION * RAYONINITIAL * RAYONINITIAL))));
            window->draw(cercle);
        }
        
        window->display();
    }
}