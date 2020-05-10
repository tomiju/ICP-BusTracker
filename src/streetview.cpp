/** ICP Project 2019/2020: Bus Tracker
 * @file streetview.cpp
 * @brief Trida pro ulozeni graficke reprezentace ulice
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "streetview.h"

#include <QPen>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include "drawable.h"
#include <QDebug>

StreetView::StreetView(Drawable* d,Street* str,qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent):
    QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    QPen pen;
    pen.setWidth(2);
    setPen(pen);
    draw = d;
    street = str;
    setZValue(0);
}

void StreetView::highlight()
{

    QPen newPen = pen();
    newPen.setColor(Qt::red);
    setPen(newPen);
    setZValue(1);
}

void StreetView::highlight2()
{
    QPen newPen = pen();
    newPen.setColor(Qt::cyan);
    setPen(newPen);
}

void StreetView::unhighlight()
{
    QPen newPen = pen();
    newPen.setColor(Qt::black);
    setPen(newPen);
    setZValue(0);
}

void StreetView::close()
{
    QPen newPen = pen();
    newPen.setStyle(Qt::PenStyle::DotLine);
    setPen(newPen);
}

void StreetView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    draw->streetOnClick(street);

    QGraphicsLineItem::mousePressEvent(event);
}
