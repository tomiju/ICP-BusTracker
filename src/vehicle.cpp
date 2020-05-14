/** ICP Project 2019/2020: Bus Tracker
 * @file vehicle.cpp
 * @brief Trida reprezentujici vozidlo
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "vehicle.h"
#include "mainwindow.h"
#include "line.h"
#include "stop.h"
#include "vehicleview.h"
#include "street.h"

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
    this->delay = 0;

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
    if(nextStop == 0){
        createSkippedStops();

        while(skippedStops.at(nextStop)){
            nextStop += 1;
            if(nextStop >= skippedStops.size()){
                activationTime = 100000; //nikdy
                return;
            }
        }

        QPointF* startingPos = line->getStop(nextStop)->getCoordinate();
        this->c->setX(startingPos->x());
        this->c->setY(startingPos->y());

        activationTime = this->times.at(nextStop);

    }

    time = 0;
    nextStop += 1;
    unsigned streetN = this->currentStreet;

    auto stop = line->getStop(nextStop);

    if(stop == nullptr ){
        reset();
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
            nextStop += 1;
            if(nextStop >= line->getStops().size()){
                this->kill();
                return;
            }
            path = new QPainterPath(*this->c);
            streetN = this->currentStreet;
            routeTime += times.at(nextStop) - times.at(nextStop - 1);
            stop = line->getStop(nextStop);
            continue;
        }

        path->lineTo(*point);
        streetN += 1;
    }

    path->lineTo(*stop->getCoordinate());
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

Street* Vehicle::getCurrentStreet()
{
    return line->getStreet(currentStreet);
}

std::vector<unsigned> Vehicle::getStopTimes()
{
    return times;
}

qreal Vehicle::getDelay()
{
    return delay;
}

void Vehicle::kill()
{
    txt->hide();
    elipse->hide();
    dead = true;
}

void Vehicle::activate()
{
    txt->show();
    elipse->show();
    dead = false;
}

bool Vehicle::isDead()
{
    return dead;
}

void Vehicle::reset()
{

    this->kill();
    this->currentStreet = 0;
    this->nextStop = 0;
    this->delay = 0;
    auto newPoint = line->getStop(0)->getCoordinate();

    double newX = newPoint->x();
    double newY = newPoint->y();

    this->c->setX(newX);
    this->c->setY(newY);

    this->elipse->setX(newX - 5);
    this->elipse->setY(newY - 5);

    this->txt->setX(newX);
    this->txt->setY(newY + 15);
}

std::vector<bool> Vehicle::getSkippedStops()
{
    return skippedStops;
}

unsigned Vehicle::getActivationTime()
{
    return activationTime;
}

void Vehicle::createSkippedStops()
{
    skippedStops = {};

    for(auto stop : this->getStops()){
        Street* str = stop->getStreet();

        if(line->containsStreet(str)){
            skippedStops.push_back(false);
        }else{
            skippedStops.push_back(true);
        }
    }
}


void Vehicle::touch()
{
    if(dead){
        return;
    }

    auto str = line->getStreet(currentStreet);

    this->time += 1/str->getCongestionDegree();

    if(this->time >= this->routeTime){
        setRoute();
        return;
    }

    this->delay += 1 - 1/str->getCongestionDegree();
    double progress = this->time / this->routeTime;

    QPointF newPoint = path->pointAtPercent(progress);

    double newX = newPoint.x();
    double newY = newPoint.y();

    this->c->setX(newX);
    this->c->setY(newY);

    this->elipse->setX(newX - 10);
    this->elipse->setY(newY - 10);

    this->txt->setX(newX);
    this->txt->setY(newY + 15);

    if(!str->contains(c)){
        currentStreet += 1;
    }

}
