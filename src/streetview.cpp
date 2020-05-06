#include "streetview.h"

#include <QPen>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>


StreetView::StreetView(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent):
    QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    QPen pen;
    pen.setWidth(2);
    setPen(pen);

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
