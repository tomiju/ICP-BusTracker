/** ICP Project 2019/2020: Bus Tracker
 * @file stop.cpp
 * @brief Trida reprezentujici zastavku
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include<iostream>
#include <vector>
#include <QPointF>

#include "stop.h"
#include "street.h"


QPointF* Stop::getCoordinate(){
    return c;
}

Street* Stop::getStreet(){
    return s;
}

QString Stop::getId(){
    return id;
}


void Stop::setStreet(Street *str){
    s = str;
}

Stop::Stop(QString id, QPointF* c)
{
    this->id = id;
    this->c = c;
}

bool Stop::operator==(const Stop& stop) const {
    return id.compare(stop.id) == 0 && c == stop.c;
}
