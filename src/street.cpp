/** ICP Project 2019/2020: Bus Tracker
 * @file street.cpp
 * @brief Trida reprezentujici ulici
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "street.h"

#include <string>
#include <iostream>
#include <QPointF>
#include <QGraphicsLineItem>

#include "stop.h"



using namespace std;

Street::Street(QString id, QPointF* c1, QPointF* c2){
    this->id = id;
    coordinates.push_back(c1);
    coordinates.push_back(c2);
    congestionDegree = 1;
    closed = false;
}

QString Street::getId(){
    return id;
}

vector<QPointF*> Street::getCoordinates(){
    return coordinates;
}

vector<Stop*> Street::getStops(){
    return stops;
}

void Street::addStop(Stop* stop){
    stops.push_back(stop);
    stop->setStreet(this);
}

bool Street::operator==(const Street& street) const {
    return id.compare(street.id) == 0 &&
        street.coordinates == coordinates &&
         street.stops == stops;

}

void Street::setStreetView(StreetView *v)
{
    this->view = v;
}


StreetView * Street::getStreetView()
{
    return view;
}

qreal Street::getCongestionDegree()
{
    return congestionDegree;
}

bool Street::contains(QPointF *point)
{
    return QGraphicsLineItem(coordinates.at(0)->x(),coordinates.at(0)->y(),coordinates.at(1)->x(),coordinates.at(1)->y()).contains(*point);
}

void Street::setCongestionDegree(qreal d)
{
    congestionDegree = d;
}

bool Street::isClosed()
{
    return closed;
}

void Street::close()
{
    closed = true;
}

bool Street::isNeighbor(Street *str)
{
    auto coords = str->getCoordinates();

    if(*coords[0] == *coordinates[0]){
        return true;
    }

    if(*coords[0] == *coordinates[1]){
        return true;
    }

    if(*coords[1] == *coordinates[0]){
        return true;
    }

    if(*coords[1] == *coordinates[1]){
        return true;
    }

    return false;
}
