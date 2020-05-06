#include "vehicle.h"
#include "mainwindow.h"
#include "line.h"
#include "stop.h"
#include "vehicleview.h"

#include <QDebug>
#include <QPoint>
#include <QLineF>
#include <QPainterPath>

Vehicle::Vehicle(QString id, QPointF *c,Line* line, std::vector<unsigned> t)
{
    this->id = id;
    this->c = new QPointF(c->x(),c->y());
    this->line = line;
    this->currentStreet = 0;
    this->nextStop = 0;
    this->times = t;
    this->dead = false;

}


QPointF *Vehicle::getCoordinate()
{
    return c;
}


QString Vehicle::getId()
{
    return id;
}


void Vehicle::setRoute()
{

    time = 0;
    nextStop += 1;
    unsigned streetN = this->currentStreet;

    auto stop = line->getStop(nextStop);

    if(stop == nullptr ){
        auto scene = elipse->scene();
        txt->hide();
        elipse->hide();
        dead = true;
        return;
    }

    routeTime = times.at(nextStop) - times.at(nextStop - 1);

    path = new QPainterPath(*this->c);

    while(1){
        Street* str = line->getStreet(streetN);
        if(stop->getStreet() == str){
            break;
        }

        auto point = line->getCommonPoint(streetN,streetN + 1);

        if(point == nullptr){
            qDebug() << "no common point";
            return;
        }

        path->lineTo(*point);
        streetN += 1;
    }

    path->lineTo(*stop->getCoordinate());
    currentStreet = streetN;
}

Line *Vehicle::getLine()
{
    return line;
}

std::vector<Stop *> Vehicle::getStops()
{
    return line->getStops();
}

unsigned Vehicle::getNextStopN()
{
    return nextStop;
}

std::vector<unsigned> Vehicle::getStopTimes()
{
    return times;
}

bool Vehicle::isDead()
{
    return dead;
}


void Vehicle::touch()
{
    if(dead){
        return;
    }


    if(this->time >= this->routeTime){
        setRoute();
        return;
    }

    this->time += 1;
    double progress = static_cast< double >( this->time) / this->routeTime;

    QPointF newPoint = path->pointAtPercent(progress);

    double newX = newPoint.x();
    double newY = newPoint.y();

    this->c->setX(newX);
    this->c->setY(newY);

    this->elipse->setX(newX - 5);
    this->elipse->setY(newY - 5);

    this->txt->setX(newX);
    this->txt->setY(newY + 15);

}
