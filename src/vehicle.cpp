#include "vehicle.h"

#include "line.h"

#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QPoint>

Vehicle::Vehicle(QString id, QPointF *c,Line* line)
{
    this->id = id;
    this->c = new QPointF(c->x(),c->y());
    this->start = new QPointF(c->x(),c->y());
    this->destination = new QPointF;
    this->line = line;
    this->pointN = 1;
}

QPointF *Vehicle::getCoordinate()
{
    return c;
}

QString Vehicle::getId()
{
    return id;
}

void Vehicle::setRoute(int time, QPointF* destination)
{
    this->routeTime = time;
    this->time = 0;
    *this->start = *this->c;
    *this->destination = *destination;


    qDebug() << this->getId()<< "destination:" << *destination << this->routeTime;
}

void Vehicle::pointNIncrease()
{
    this->pointN += 1;
}

void Vehicle::change(const QVariant x)
{
    QPoint p = x.toPoint();

    this->elipse->setX(p.x());
    this->elipse->setY(p.y());

    this->elipse->update();

    this->txt->setX(p.x() - 10);
    this->txt->setY(p.y() + 15);

    this->txt->update();

}

void Vehicle::update()
{
    this->elipse->update();
    this->txt->update();
}

void Vehicle::touch()
{

    if(this->time >= this->routeTime){
        qDebug() <<id <<"had point point nr: " << pointN;

        this->pointNIncrease();

        qDebug() <<id <<"asked for point nr: " << pointN;
        QPointF* d = this->line->getPoint(pointN);

        if(d == nullptr){
            this->elipse->scene()->removeItem(this->txt);
            this->elipse->scene()->removeItem(this->elipse);
            delete this->elipse;
            delete this->txt;
            this->line->removeFirstVehicle();
            delete this;

        }else{

            setRoute(100,d);
        }

    }




    this->time += 1;

    QPointF* start =  this->start;
    QPointF* end =  this->destination;

    //qDebug() <<"start: " << *start<<"end: " << *end;

    double deltaX = end->x() - start->x();
    double deltaY = end->y() - start->y();


    double progress = static_cast< double >( this->time) / this->routeTime;
    //qDebug() << progress;

    double newX = start->x() + deltaX*progress;
    double newY = start->y() + deltaY*progress;

    this->c->setX(newX);
    this->c->setY(newY);

    this->elipse->setX(newX - 5);
    this->elipse->setY(newY - 5);

    this->txt->setX(newX);
    this->txt->setY(newY + 15);

}
