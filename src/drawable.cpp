#include "drawable.h"
#include "street.h"
#include "stop.h"
#include "vehicle.h"
#include "vehicleview.h"
#include "mainwindow.h"
#include "line.h"
#include "streetview.h"

#include <QGraphicsScene>
#include <vector>
#include <QGraphicsTextItem>
#include<QGraphicsEllipseItem>
#include <QPainter>
#include<QGraphicsLineItem>

Drawable::Drawable(QGraphicsScene* s,MainWindow* mw)
{
    scene = s;
    mainWindow = mw;
    this->vehicle = nullptr;
    this->line = nullptr;
    this->street = nullptr;
}

void Drawable::drawStreet(Street* street)
{

    vector<QPointF*> coordinates =  street->getCoordinates();

    double x1 = coordinates.at(0)->x();
    double y1 = coordinates.at(0)->y();
    double x2 = coordinates.at(1)->x();
    double y2 = coordinates.at(1)->y();

    auto* view = new StreetView(this,street,x1, y1, x2, y2);
    this->scene->addItem(view);

    street->setStreetView(view);

    QGraphicsTextItem* name = scene->addText(street->getId());
    name->setX((x1+x2)/2);
    name->setY((y1+y2)/2);

}

void Drawable::drawStop(Stop* stop)
{

    QPointF* coordinate = stop->getCoordinate();

    double x = coordinate->x();
    double y = coordinate->y();

    auto ellipse = scene->addEllipse(x - 10, y - 10 , 20, 20);

    QBrush brush;
    QColor color;
    color.setRgb(121, 236, 121);
    brush.setColor(color);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    QPen pen;
    pen.setWidth(2);

    ellipse->setBrush(brush);
    ellipse->setPen(pen);

    QGraphicsTextItem* name = scene->addText(stop->getId());
    name->setX(x);
    name->setY(y);
}

void Drawable::drawVehicle(Vehicle *vehicle)
{

    QPointF* p = vehicle->getCoordinate();
    auto e = new VehicleView(this,vehicle,0, 0, 10, 10);

    vehicle->elipse = e;
    scene->addItem(e);
    e->setZValue(2);

    vehicle->elipse->setX(p->x() - 5);
    vehicle->elipse->setY(p->y() - 5);

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    QPen pen;
    pen.setWidth(2);

    vehicle->elipse->setPen(pen);
    vehicle->elipse->setBrush(brush);

    vehicle->elipse->update();

    QGraphicsTextItem* name = scene->addText(vehicle->getId());
    name->setX(p->x());
    name->setY(p->y() + 10);

    vehicle->txt = name;


}

void Drawable::showVehicleRoute(Vehicle *vehicle)
{

    this->street = nullptr;
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    if(this->street){
        this->street->getStreetView()->unhighlight();
    }

    if(this->vehicle){
        this->vehicle->elipse->setBrush(brush);
        auto line = this->vehicle->getLine();

        auto streets = line->getAllStreets();

        for(auto str : streets){
            str->getStreetView()->unhighlight();
        }

    }

    this->vehicle = vehicle;

    brush.setColor(Qt::red);
    this->vehicle->elipse->setBrush(brush);

    auto line = this->vehicle->getLine();

    auto streets = line->getAllStreets();

    for(auto str : streets){
        str->getStreetView()->highlight();
    }


    mainWindow->showVehicleRoute(vehicle);
}

void Drawable::showStreet(Street *str)
{
    if(this->street){
        this->street->getStreetView()->unhighlight();
    }
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    if(this->vehicle){
        this->vehicle->elipse->setBrush(brush);
        auto line = this->vehicle->getLine();

        auto streets = line->getAllStreets();

        for(auto str : streets){
            str->getStreetView()->unhighlight();
        }

    }

    this->vehicle = nullptr;
    this->street = str;

    str->getStreetView()->highlight();

    mainWindow->showStreet(street);
}

void Drawable::setCongestionDegree(qreal d)
{
    if(this->street){
        street->setCongestionDegree(d);
    }
}


void Drawable::update()
{
    if(this->vehicle){
        mainWindow->showVehicleRoute(vehicle);
    }

    if(this->street){
        mainWindow->showStreet(street);
    }
}


