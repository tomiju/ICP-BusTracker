/** ICP Project 2019/2020: Bus Tracker
 * @file line.cpp
 * @brief Trida reprezentujici autobusovou linku
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "line.h"

#include "street.h"
#include "stop.h"
#include "vehicle.h"
#include "drawable.h"

#include <vector>
#include <QPointF>
#include <QGraphicsScene>
#include <QDebug>
#include <QTime>


Line::Line(QString id)
{
    this->id = id;
    this->time = 0;
    this->vehicleNum = 0;
    this->timetable = {};

}


void Line::addStreet(Street* str)
{
    this->streets.push_back(str);
}


void Line::addStop(Stop *stop)
{
    stops.push_back(stop);
}


Stop* Line::getStop(unsigned n)
{
    if(stops.size() > n ){
        return stops.at(n);
    }else{
        return nullptr;
    }
}


Street *Line::getStreet(unsigned n)
{
    if(streets.size() > n ){
        return streets.at(n);
    }else{
        return nullptr;
    }
}


QPointF *Line::getCommonPoint(unsigned n1, unsigned n2)
{
    if(streets.size() <= n1 || streets.size() <= n2 ){
        return nullptr;
    }

    Street* str1 = streets.at(n1);
    Street* str2 = streets.at(n2);

    if(*str1->getCoordinates()[0] == *str2->getCoordinates()[0]){
        return str1->getCoordinates()[0];
    }

    if(*str1->getCoordinates()[1] == *str2->getCoordinates()[0]){
        return str1->getCoordinates()[1];
    }

    if(*str1->getCoordinates()[1] == *str2->getCoordinates()[1]){
        return str1->getCoordinates()[1];
    }

    if(*str1->getCoordinates()[0] == *str2->getCoordinates()[1]){
        return str1->getCoordinates()[0];
    }

    return nullptr;
}

void Line::addToTimeTable(std::vector<QString> times)
{
    vector<unsigned> vec = {};

    for(auto t : times){
        QTime time = QTime::fromString(t, "hh:mm");
        vec.push_back(60*time.minute()+3600*time.hour());
    }

    timetable.push_back(vec);
    this->vehicleNum += 1;
    QString string = this->id + "v"  + QString::number(vehicleNum);

    auto startStop = this->stops.at(0);
    Vehicle* v = new Vehicle(string,startStop->getCoordinate(),this, vec);
    draw->drawVehicle(v);
    v->setRoute();
    v->kill();
    this->vehicle.push_back(v);

}

std::vector<Stop *> Line::getStops()
{
    return stops;
}

std::vector<Street *> Line::getAllStreets()
{
    return streets;
}

void Line::reset()
{
    this->time = 0;
    for(auto v : vehicle){
        v->reset();
        v->setRoute();
    }
}

void Line::setDrawable(Drawable *d)
{
    draw = d;
}

bool Line::containsStreet(Street *s)
{
   for(auto str : streets){
        if(s->getId() == str->getId() ){
            return true;
        }
   }

   return false;
}

void Line::setRoute(std::vector<Street *> str)
{

    this->streets = str;
    this->reset();
}

QString Line::getId()
{
    return id;
}


void Line::touch()
{
    for(unsigned i = 0; i < timetable.size(); i++){
        if(time == timetable.at(i).at(0) ){
            vehicle.at(i)->activate();
        }
    }

    for (auto it = this->vehicle.begin() ; it != this->vehicle.end(); ++it){
        Vehicle* v = *it;
        v->touch();
    }

    time += 1;
}
