/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ruben
 *
 * Created on 25 décembre 2017, 17:17
 */

#include <cstdlib>
#include <iostream>


#include "Corps.h"
#include "Constantes.h"
#include "Univers.h"
#include "Rendu.h"
#include "Horloge.h"

using namespace std;

/*
 * 
 */


//int Corps::nbrCorps = 0;
//std::shared_ptr<Univers> Univers::inst;// = nullptr;

int main(int argc, char** argv) {

    cout<<"Universe simulation"<<endl;
    
    
   
    Univers::instance()->creerUnivers();
    //Univers::instance()->etatUnivers();
    //Horloge::instance();
    Rendu::instance()->init();

    
    Univers::instance()->~Univers();
    //std::cout<<"test"<<std::endl;
    return 0;
}

