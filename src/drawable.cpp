#include "drawable.h"
#include "street.h"
#include "stop.h"
#include "vehicle.h"

#include <QGraphicsScene>
#include <vector>
#include <QGraphicsTextItem>
#include<QGraphicsEllipseItem>
#include <QPainter>
#include<QGraphicsLineItem>

Drawable::Drawable()
{

}

void Drawable::drawStreet(Street* street, QGraphicsScene* scene)
{

    vector<QPointF*> coordinates =  street->getCoordinates();

    double x1 = coordinates.at(0)->x();
    double y1 = coordinates.at(0)->y();
    double x2 = coordinates.at(1)->x();
    double y2 = coordinates.at(1)->y();

    QGraphicsLineItem* line = scene->addLine(x1, y1, x2, y2);
    QPen pen;
    pen.setWidth(2);
    line->setPen(pen);

    QGraphicsTextItem* name = scene->addText(street->getId());
    name->setX((x1+x2)/2);
    name->setY((y1+y2)/2);

}

void Drawable::drawStop(Stop* stop, QGraphicsScene* scene)
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

void Drawable::drawVehicle(Vehicle *vehicle, QGraphicsScene *scene)
{



    QPointF* p = vehicle->getCoordinate();

    vehicle->elipse = scene->addEllipse(0, 0, 10, 10);
    vehicle->elipse->setFlag(QGraphicsItem::ItemIsSelectable);

    vehicle->elipse->setX(p->x() - 5);
    vehicle->elipse->setY(p->y() - 5);

    QBrush brush;
    QColor color;
    color.setRgb(255, 128, 128);
    brush.setColor(color);
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


