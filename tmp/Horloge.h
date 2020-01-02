/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Horloge.h
 * Author: ruben
 *
 * Created on 1 janvier 2018, 23:50
 */

#ifndef HORLOGE_H
#define HORLOGE_H

#include <memory>
#include <thread>

class Horloge {
public:
    static const std::shared_ptr<Horloge> instance();
    Horloge();
    Horloge(const Horloge& orig);
    virtual ~Horloge();
    void lancerHorloge();
    void threadCallerHorloge();
private:

};

#endif /* HORLOGE_H */

