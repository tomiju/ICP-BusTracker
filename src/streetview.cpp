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
    setZValue(-1);
}

void StreetView::highlight()
{

    QPen newPen = pen();
    newPen.setColor(Qt::red);
    setPen(newPen);

}

void StreetView::unhighlight()
{
    QPen newPen = pen();
    newPen.setColor(Qt::black);
    setPen(newPen);
}

void StreetView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    draw->showStreet(street);

    QGraphicsLineItem::mousePressEvent(event);

    qDebug() << "street press";


}
