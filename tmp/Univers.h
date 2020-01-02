/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Univers.h
 * Author: ruben
 *
 * Created on 27 décembre 2017, 15:28
 */

#ifndef UNIVERS_H
#define UNIVERS_H

#include <memory>
#include <vector>
#include <SFML/System/Time.hpp>

#include "Corps.h" 

class Univers {
public:
    
    
    
    //static std::shared_ptr<Univers> inst;
    
    static const std::shared_ptr<Univers> instance();
    Univers();
    Univers(const Univers& orig);
    virtual ~Univers();
    void creerUnivers();
    void resetUnivers();
    void etatUnivers();
    void majEtats(sf::Time ecoule);
    std::vector<std::shared_ptr<Corps>> getCorps() { return corps;}
    
private:
    std::vector<std::shared_ptr<Corps>> corps;
    
    
};

#endif /* UNIVERS_H */

