#include "vehicle.h"

#include "line.h"
#include "stop.h"

#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QPoint>
#include <QLineF>
#include <QPainterPath>

Vehicle::Vehicle(QString id, QPointF *c,Line* line)
{
    this->id = id;
    this->c = new QPointF(c->x(),c->y());
    this->line = line;
    this->currentStreet = 0;
    this->nextStop = 0;

}


QPointF *Vehicle::getCoordinate()
{
    return c;
}


QString Vehicle::getId()
{
    return id;
}


void Vehicle::setRoute(int timeNew)
{
    routeTime = timeNew;
    time = 0;
    nextStop += 1;
    unsigned streetN = this->currentStreet;

    auto stop = line->getStop(nextStop);

    if(stop == nullptr ){
        auto scene = elipse->scene();
        scene->removeItem(elipse);
        scene->removeItem(txt);
        delete elipse;
        delete txt;
        line->removeFirstVehicle();
        delete this;
        return;
    }

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


void Vehicle::touch()
{

    if(this->time >= this->routeTime){
        setRoute(100);
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
