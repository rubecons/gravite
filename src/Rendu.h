/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rendu.h
 * Author: ruben
 *
 * Created on 1 janvier 2018, 15:51
 */

#ifndef RENDU_H
#define RENDU_H

#include "SFML/Graphics/RenderWindow.hpp"

class Rendu {
public:
    static const std::shared_ptr<Rendu> instance();
    Rendu();
    Rendu(const Rendu& orig);
    virtual ~Rendu();
    void init();
    std::shared_ptr<sf::RenderWindow> getWindow() {return window;}
private:
    std::shared_ptr<sf::RenderWindow> window;
};

#endif /* RENDU_H */

