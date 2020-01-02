/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Univers.cpp
 * Author: ruben
 * 
 * Created on 27 décembre 2017, 15:28
 */

#include <future>
#include <iostream>
#include <valarray>
#include <cmath>

#include "Univers.h"
#include "Corps.h"
#include "Constantes.h"

#define FUSION
//#define CONTACT

const std::shared_ptr<Univers> Univers::instance()
{
    static std::shared_ptr<Univers> inst = std::make_shared<Univers>();
    return inst;
}

Univers::Univers() {
}

Univers::Univers(const Univers& orig) {
}

Univers::~Univers() {
    for(uint i = 0 ; i < NOMBRECORPSSIMULTATION ; i++)
    {
        corps[i]->~Corps();

        //delete corps[i].get();
        corps.pop_back();
    }
}

void Univers::creerUnivers()
{
    for(uint i = 0 ; i < NOMBRECORPSSIMULTATION ; i++)
    {
        corps.push_back(std::make_shared<Corps>());
    }
}

void Univers::resetUnivers()
{
    for(const std::shared_ptr<Corps> &corp : corps)
    {
        corp->~Corps();
        corps.pop_back();
    }
    for(uint i = 0 ; i < NOMBRECORPSSIMULTATION ; i++)
    {
        corps.push_back(std::make_shared<Corps>());
    }
}

void Univers::etatUnivers()
{
    //for(uint i = 0 ; i < corps.size() ; i++)
    //{   
    //    corps[i]->print(i);
    //}
    std::cout<<corps.size()<<" planetes"<<std::endl;
}

void Univers::majEtats(sf::Time ecoule)
{
    float sommeForcesExt_X = 0, sommeForcesExt_Y = 0;
    float distX, distY;
    std::shared_ptr<Corps> crps = nullptr, corp = nullptr;
    
    for(uint j= 0 ; j < corps.size() ; j++)
    {
        crps = corps[j];
        
        if(crps == nullptr)continue;
        
        /*if(!crps->valide)
        {
            continue;
        }*/
        
        sommeForcesExt_X = 0;
        sommeForcesExt_Y = 0;
        distX = 0;
        distY = 0;
        bool fusion = false;
        
        for(uint i = 0 ; i < corps.size() ; i++)//const std::shared_ptr<Corps> &corp : corps)
        {
            fusion=false;
            if(corps[i] == nullptr)
            {
                continue;
            }
            
            corp = corps[i];
            
            
            /*if(!corp->valide)
            {
                continue;
            }*/
            if(crps != corp)
            {
                
                distX = corp->getPosX() - crps->getPosX();
                distY = corp->getPosY() - crps->getPosY();
                
                float dist2corps = std::sqrt(               //c'est la tangente du triangle rectangle
                                                (
                                                    (distX)
                                                *
                                                    (distX)
                                                )
                                            +
                                                (  
                                                    (distY)
                                                *
                                                    (distY)
                                                )
                                            );
                
                if(dist2corps <= (corp->getRayon() + crps->getRayon())) //FUSION
                {
                    float rayonCorp = corp->getRayon(), rayonCrps = crps->getRayon();
                    
#ifdef FUSION
                    sf::Vector2f vitesse(Corps::conservQteMouvement(crps, corp));
                    if(rayonCrps >= rayonCorp)
                    {
                        crps->setPosi((float)(((corp->getPosX() * rayonCorp) + (crps->getPosX() * rayonCrps))/(rayonCorp + rayonCrps)), (float)(((corp->getPosY() * rayonCorp) + (crps->getPosY() * rayonCrps))/(rayonCorp + rayonCrps)));
                        crps->setRayon(std::sqrt((rayonCorp * rayonCorp) + (rayonCrps * rayonCrps)));
                        crps->setVitesse(vitesse);
                        //corp->valide = false;
                        corp->~Corps();
                        corp = nullptr;
                        corps.erase(corps.begin()+i);
                        i--;etatUnivers();
                        
                        continue;
                    }
                    if(rayonCorp > rayonCrps)
                    {
                        corp->setPosi((float)(((corp->getPosX() * rayonCorp) + (crps->getPosX() * rayonCrps))/(rayonCorp + rayonCrps)), (float)(((corp->getPosY() * rayonCorp) + (crps->getPosY() * rayonCrps))/(rayonCorp + rayonCrps)));
                        corp->setRayon(std::sqrt((rayonCorp * rayonCorp) + (rayonCrps * rayonCrps)));
                        corp->setVitesse(vitesse);
                        //crps->valide = false;
                        crps->~Corps();
                        crps = nullptr;
                        corps.erase(corps.begin()+j);
                        j--;etatUnivers();
                        break;
                    }
                    
                        
                    fusion = true; 

                    
                    //continue;
#endif
                    
#ifdef CONTACT
                    
#endif
                    
                }
                
                float force2corps = ((CONSTGRAVITATIONNELLE * corp->getRayon()) /(dist2corps * dist2corps));
                
                float forceX = force2corps * (distX / dist2corps);
                float forceY = force2corps * (distY / dist2corps);
                
                if(!fusion)
                {    
                    sommeForcesExt_X += forceX;
                    sommeForcesExt_Y += forceY;
                }    
            }
        }
//#ifdef FUSION
        if(crps)
        {
            crps->setPosi(crps->getPosX() + (crps->getVx() * ecoule.asSeconds()) + (sommeForcesExt_X * ecoule.asSeconds() * ecoule.asSeconds() / 2), crps->getPosY() + (crps->getVy() * ecoule.asSeconds()) + (sommeForcesExt_Y * ecoule.asSeconds() * ecoule.asSeconds() / 2));
            crps->setVitesse((sommeForcesExt_X * ecoule.asSeconds()) + crps->getVx(), (sommeForcesExt_Y * ecoule.asSeconds()) + crps->getVy());
        }
//#endif
    }
}