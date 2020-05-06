#ifndef STREETVIEW_H
#define STREETVIEW_H

class QGraphicsLineItem;
class QGraphicsTextItem;

#include <QGraphicsLineItem>

class StreetView : public QGraphicsLineItem
{
public:

    StreetView(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = nullptr);

    void highlight();
    void unhighlight();



};

#endif // STREETVIEW_H
