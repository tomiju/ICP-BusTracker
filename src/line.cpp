#include "line.h"

#include "street.h"
#include "vehicle.h"
#include "drawable.h"

#include <vector>
#include <QPointF>
#include <QGraphicsScene>
#include <QDebug>

Line::Line(QString id,QGraphicsScene* scene)
{
    this->id = id;
    this->time = 0;
    this->scene = scene;
    this->vehicleNum = 1;

}

void Line::addStreet(Street* str)
{
    QPointF* p = points.back();
    QPointF* strp1 = str->getCoordinates()[0];
    QPointF* strp2 = str->getCoordinates()[1];

    if(*p == *strp1){
        points.push_back(strp2);
        qDebug() <<"Next point:"<< *strp2;
    }else if(*p == *strp2){
        points.push_back(strp1);
        qDebug() <<"Next point:"<< *strp1;
    }else{
        return;
    }

    this->streets.push_back(str);

}

void Line::setStartPoint(QPointF *p)
{
    points.push_back(p);
    qDebug() <<"Start point: "<< *p;
    qDebug() <<"Saved value: "<< *points.at(0);

}

QPointF *Line::getPoint( unsigned p)
{

    if(p >= points.size() ){
        return nullptr;
    }


    return points.at(static_cast<unsigned>(p));
}

void Line::removeFirstVehicle()
{
    this->vehicle.erase(this->vehicle.begin());
}

void Line::touch()
{

    time += 1;
    //qDebug() <<"Saved value: "<< *this->points.at(0)<< *points.at(1) << *points.at(2) << *points.at(3) <<this->id ;



    if(time % 100 == 0 ){
        QString string = "Vehicle"  + QString::number(vehicleNum);
        this->vehicleNum += 1;
        Drawable draw;


        Vehicle* v = new Vehicle(string,this->points.at(0),this);
        draw.drawVehicle(v, this->scene);
        //qDebug() << "Set route: " << *this->points.at(1);
        v->setRoute(100,this->points.at(1));
        this->vehicle.push_back(v);
    }

    for (auto it = this->vehicle.begin() ; it != this->vehicle.end(); ++it){
        Vehicle* v = *it;

        v->touch();
    }


}

void Line::pass()
{
    return;
}
