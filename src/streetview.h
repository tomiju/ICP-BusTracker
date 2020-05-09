#ifndef STREETVIEW_H
#define STREETVIEW_H

class QGraphicsLineItem;
class QGraphicsTextItem;
class Drawable;
class Street;

#include <QGraphicsLineItem>

class StreetView : public QGraphicsLineItem
{
public:

    StreetView(Drawable* d,Street* str,qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = nullptr);

    void highlight();

    void  highlight2();

    void unhighlight();

    void close();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)override;

private:
    Drawable* draw;
    Street* street;

};

#endif // STREETVIEW_H
