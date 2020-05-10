/** ICP Project 2019/2020: Bus Tracker
 * @file vehicleview.cpp
 * @brief Trida pro ulozeni graficke reprezentace vozidla
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "vehicleview.h"
#include "QBrush"
#include "drawable.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QDebug>


VehicleView::VehicleView(Drawable* d,Vehicle* v,qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) :
    QGraphicsEllipseItem(x,y,width,height,parent)
{
    this->drawable = d;
    this->vehicle = v;

}

void VehicleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    drawable->showVehicleRoute(vehicle);

}
