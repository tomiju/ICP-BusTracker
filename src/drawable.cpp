/** ICP Project 2019/2020: Bus Tracker
 * @file drawable.cpp
 * @brief Trida pro vykreslovane objekty na mape
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

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
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QDebug>


Drawable::Drawable(QGraphicsScene* s,MainWindow* mw)
{
    scene = s;
    mainWindow = mw;
    this->vehicle = nullptr;
    this->line = nullptr;
    this->street = nullptr;
    editMode = false;
    newStreets = {};
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
    name->hide();

}

void Drawable::drawStop(Stop* stop)
{

    QPointF* coordinate = stop->getCoordinate();

    double x = coordinate->x();
    double y = coordinate->y();

    auto ellipse = scene->addEllipse(x - 10, y - 10 , 20, 20);

    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    QPen pen;
    pen.setWidth(4);

    ellipse->setBrush(brush);
    ellipse->setPen(pen);
    ellipse->setZValue(2);

    QGraphicsTextItem* name = scene->addText(stop->getId());
    name->setX(x);
    name->setY(y);
    auto font  = QFont();
    font.setPointSize(2);
    name->setFont(font);
    name->setDefaultTextColor(Qt::black);
}

void Drawable::drawVehicle(Vehicle *vehicle)
{

    QPointF* p = vehicle->getCoordinate();
    auto e = new VehicleView(this,vehicle,0, 0, 20, 20);

    vehicle->elipse = e;
    scene->addItem(e);
    e->setZValue(3);

    vehicle->elipse->setX(p->x() - 10);
    vehicle->elipse->setY(p->y() - 10);

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    QPen pen;
    pen.setWidth(4);

    vehicle->elipse->setPen(pen);
    vehicle->elipse->setBrush(brush);

    vehicle->elipse->update();

    QGraphicsTextItem* name = scene->addText(vehicle->getLine()->getId());
    name->setX(p->x());
    name->setY(p->y() + 10);
    name->setDefaultTextColor(Qt::blue);

    vehicle->txt = name;

}

void Drawable::showVehicleRoute(Vehicle *vehicle)
{

    if(editMode){
        return;
    }

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);

    if(this->street){
        this->street->getStreetView()->unhighlight();
    }

    this->street = nullptr;

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

void Drawable::streetOnClick(Street *str)
{

    if(!editMode){
        showStreet(str);
        return;
    }

     if(str->isClosed()){
        return;
     }

     for(auto s : newStreets){
         if(s->getId() == str->getId()){
             return;
         }
     }

     if(newStreets.empty()){
         qDebug() << "added str: " + str->getId();
         str->getStreetView()->highlight2();
         newStreets.push_back(str);
         mainWindow->showNewRoute(effectedLines.at(0),newStreets);

         return;
     }

     if(newStreets.back()->isNeighbor(str)){
         qDebug() << "added str: " + str->getId();
         str->getStreetView()->highlight2();
         newStreets.push_back(str);
         mainWindow->showNewRoute(effectedLines.at(0),newStreets);
         return;
     }

}

bool Drawable::isEditMode()
{
    return editMode;
}

void Drawable::closeStreet()
{
    if(editMode){
        return;
    }

    effectedLines = {};
    auto lines = mainWindow->getLines();

    for(auto l : lines){
        if(l->containsStreet(this->street)){
            effectedLines.push_back(l);
        }
    }

    if(effectedLines.empty()){
        street->getStreetView()->close();
        street->close();
        return;
    }

    mainWindow->stop();
    mainWindow->resetTime();
    mainWindow->showNewRoute(effectedLines.at(0),newStreets);

    if(this->street){
        street->getStreetView()->close();
        this->editMode = true;
        street->close();
        mainWindow->setEditMode();
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

void Drawable::setRoute()
{
    if(effectedLines.empty()){
        return;
    }

    effectedLines.at(0)->setRoute(this->newStreets);
    effectedLines.erase(effectedLines.begin());
    for(auto s : newStreets){
        s->getStreetView()->unhighlight();
    }
    newStreets = {};

    if(effectedLines.empty()){
        this->editMode = false;
        mainWindow->setNormalMode();
    }

}
