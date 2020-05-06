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


void Line::removeFirstVehicle()
{
    this->vehicle.erase(this->vehicle.begin());
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
    if(streets.size() < n1 || streets.size() < n2 ){
        qDebug() << "Number of streets too high";
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
    vector<unsigned> v = {};

    for(auto t : times){
        QTime time = QTime::fromString(t, "hh:mm");
        v.push_back(60*time.minute()+3600*time.hour());
    }

    timetable.push_back(v);
}

std::vector<Stop *> Line::getStops()
{
    return stops;
}

std::vector<Street *> Line::getAllStreets()
{
    return streets;
}


void Line::touch()
{
    for(auto timeTablePart : timetable){
        if(time == timeTablePart.at(0) ){
            this->vehicleNum += 1;
            QString string = "Vehicle"  + QString::number(vehicleNum);

            auto startStop = this->stops.at(0);
            Vehicle* v = new Vehicle(string,startStop->getCoordinate(),this, timeTablePart);
            draw->drawVehicle(v);
            v->setRoute();
            this->vehicle.push_back(v);
        }
    }

    for (auto it = this->vehicle.begin() ; it != this->vehicle.end(); ++it){
        Vehicle* v = *it;
        v->touch();
    }

    time += 1;
}

