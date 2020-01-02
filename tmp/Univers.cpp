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
    for(uint i = 0 ; i < corps.size() ; i++)
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
        std::cout<<"corps["<<i<<"]  x = "<<corps[i]->getPosX()<<" y = "<<corps[i]->getPosY()<<std::endl;
    }
    etatUnivers();
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
    etatUnivers();
}

void Univers::etatUnivers()
{
    //for(uint i = 0 ; i < corps.size() ; i++)
    //{   
    //    corps[i]->print(i);
    //}
    std::cout<<corps.size()<<" planetes"<<std::endl;
}

#ifdef TMP
void Univers::majEtats(sf::Time ecoule)
{
    float sommeForcesExt_X = 0, sommeForcesExt_Y = 0;
    float distX, distY;
    std::shared_ptr<Corps> crps = nullptr, corp = nullptr;
    
    for(uint j= 0 ; j < corps.size() ; j++)
    {
        
        if(corps[j] == nullptr)
            continue;
        
        crps = corps[j];

        //crps->setTmpPosi(0,0);
        //crps->setTmpVitesse(0,0);
        sommeForcesExt_X = 0;
        sommeForcesExt_Y = 0;
        distX = 0;
        distY = 0;
        bool fusion = false;
        
        for(uint i = 0 ; i < corps.size() ; i++)//const std::shared_ptr<Corps> &corp : corps)
        {
            fusion=false;
            if(corps[i] == nullptr || corps[i] == crps || i==j)
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
         //   std::cout<<"   c1 = "<<j<<" c2 = "<<i<<"  distance = "<<dist2corps<<std::endl;
                
                if(dist2corps <= (corp->getRayon() + crps->getRayon())) //FUSION
                {
#ifdef FUSION
                    float rayonCorp = corp->getRayon(), rayonCrps = crps->getRayon();
                    if(j>i){std::cout<<"probleme j>i ordre effacer planete"<<std::endl;}
                    if(j==i){std::cout<<"probleme 2 ordre effacer planete"<<std::endl;}
                    sf::Vector2f vitesse(Corps::conservQteMouvement(crps, corp));
//                    if(rayonCrps >= rayonCorp)
//                    {
                        crps->setPosi(   (float)(((corp->getPosX() * rayonCorp) + (crps->getPosX() * rayonCrps))/(rayonCorp + rayonCrps)),
                                         (float)(((corp->getPosY() * rayonCorp) + (crps->getPosY() * rayonCrps))/(rayonCorp + rayonCrps))
                                        );
                        crps->setRayon(std::sqrt((rayonCorp * rayonCorp) + (rayonCrps * rayonCrps)));
                        crps->setVitesse(vitesse);
                        //crps->setVitesse(vitesse.x, vitesse.y);
                        //corp->valide = false;
                        corp->~Corps();
                        corps[i] = nullptr;
//                        corps.erase(corps.begin()+i);
//                        i--;
//                        etatUnivers();
                        
                        //continue;
//                    }
/*                    if(rayonCorp > rayonCrps)
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
                    }//*/
                    
                        
                    fusion = true; 

                    
                    continue;
#endif
                    
#ifdef CONTACT
                    
#endif
                    
                }
                
                if(!fusion)
                {    
                    float force2corps = ((CONSTGRAVITATIONNELLE * corp->getRayon()) /(dist2corps * dist2corps));

                    float forceX = force2corps * (distX / dist2corps);
                    float forceY = force2corps * (distY / dist2corps);
                
                    sommeForcesExt_X += forceX;
                    sommeForcesExt_Y += forceY;
                }
            }
        }
//#ifdef FUSION
        if(crps)
        {
            crps->setTmpVitesse(
                                (sommeForcesExt_X * ecoule.asSeconds()) + crps->getVx(),
                                (sommeForcesExt_Y * ecoule.asSeconds()) + crps->getVy()
                               );
            
            crps->setTmpPosi(
                                (sommeForcesExt_X * ecoule.asSeconds() * ecoule.asSeconds() / 2) + (crps->getVx() * ecoule.asSeconds()) + crps->getPosX(),
                                (sommeForcesExt_Y * ecoule.asSeconds() * ecoule.asSeconds() / 2) + (crps->getVy() * ecoule.asSeconds()) + crps->getPosY() 
                            );
            //std::cout<<"corps["<<j<<"]  x = "<<crps->getPosX()<<" tmpX = "<<crps->getTmpPosX()<<" y = "<<crps->getPosY()<<" tmpY = "<<crps->getTmpPosY()<<std::endl;
        }
//#endif
        
        
        
    }
    
    //int ite = corps.size()-1;
    for(uint ite=0;ite<corps.size(); ite++)
    {   
        if(corps[ite]==nullptr)
        {
            corps.erase(corps.begin()+ite);
            ite--;
            etatUnivers();
        }
        else
            corps[ite]->majEtat();
        
    }
}
#endif //TMP

void Univers::majEtats(sf::Time ecoule)
{
    float sommeForcesExt_X = 0, sommeForcesExt_Y = 0;
    float distX, distY;
    std::shared_ptr<Corps> crps = nullptr, corp = nullptr;
    
    for(uint j= 0 ; j < corps.size() ; j++)
    {
        if(corps[j] == nullptr)
            continue;
        
        crps = corps[j];

        sommeForcesExt_X = 0;
        sommeForcesExt_Y = 0;
        distX = 0;
        distY = 0;
        
        for(uint i = 0 ; i < corps.size() ; i++)
        {
            if(corps[i] == nullptr || corps[i] == crps || i==j)
            {
                continue;
            }
            
            corp = corps[i];
            
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
         //   std::cout<<"   c1 = "<<j<<" c2 = "<<i<<"  distance = "<<dist2corps<<std::endl;
                
                float force2corps = ((CONSTGRAVITATIONNELLE * corp->getRayon()) /(dist2corps * dist2corps));

                float forceX = force2corps * (distX / dist2corps);
                float forceY = force2corps * (distY / dist2corps);

                sommeForcesExt_X += forceX;
                sommeForcesExt_Y += forceY;
            }
        }

        if(crps)
        {
            crps->setTmpVitesse(
                                (sommeForcesExt_X * ecoule.asSeconds()) + crps->getVx(),
                                (sommeForcesExt_Y * ecoule.asSeconds()) + crps->getVy()
                               );
            
            crps->setTmpPosi(
                                (sommeForcesExt_X * ecoule.asSeconds() * ecoule.asSeconds() / 2) + (crps->getVx() * ecoule.asSeconds()) + crps->getPosX(),
                                (sommeForcesExt_Y * ecoule.asSeconds() * ecoule.asSeconds() / 2) + (crps->getVy() * ecoule.asSeconds()) + crps->getPosY() 
                            );
            //std::cout<<"corps["<<j<<"]  x = "<<crps->getPosX()<<" tmpX = "<<crps->getTmpPosX()<<" y = "<<crps->getPosY()<<" tmpY = "<<crps->getTmpPosY()<<std::endl;
        }
    }
    

    for(uint ite=0;ite<corps.size(); ite++)
    {   
            corps[ite]->majEtat();
    }
    
    //Boucle de test de fusion de planetes
    for(uint j= 0 ; j < corps.size() ; j++)
    {
        
        if(corps[j] == nullptr)
            continue;
        
        crps = corps[j];
        distX = 0;
        distY = 0;
        
        for(uint i = 0 ; i < corps.size() ; i++)//const std::shared_ptr<Corps> &corp : corps)
        {

            if(corps[i] == nullptr || corps[i] == crps || i==j)
            {
                continue;
            }
            
            corp = corps[i];
            
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
#ifdef FUSION
                    float rayonCorp = corp->getRayon(), rayonCrps = crps->getRayon();
                    if(j>i){std::cout<<"probleme j>i ordre effacer planete"<<std::endl;}
                    if(j==i){std::cout<<"probleme 2 ordre effacer planete"<<std::endl;}
                    sf::Vector2f vitesse(Corps::conservQteMouvement(crps, corp));
                    
                    crps->setPosi(   (float)(((corp->getPosX() * rayonCorp) + (crps->getPosX() * rayonCrps))/(rayonCorp + rayonCrps)),
                                     (float)(((corp->getPosY() * rayonCorp) + (crps->getPosY() * rayonCrps))/(rayonCorp + rayonCrps))
                                    );
                    crps->setRayon(std::sqrt((rayonCorp * rayonCorp) + (rayonCrps * rayonCrps)));
                    crps->setVitesse(vitesse);
                    //crps->setVitesse(vitesse.x, vitesse.y);
                    
                    corp->~Corps();
                    //corps.erase(corps.begin()+i);
                    //i--;
                    corps[i] = nullptr;
                    
                    //continue;
#endif 
                }
            }
        }
    }
    
//*
    for(uint ite=0;ite<corps.size(); ite++)
    {   
        if(corps[ite]==nullptr)
        {
            corps.erase(corps.begin()+ite);
            ite--;
            etatUnivers();
        }
    }//*/
}