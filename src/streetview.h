#ifndef STREETVIEW_H
#define STREETVIEW_H

class QGraphicsLineItem;
class QGraphicsTextItem;


class StreetView
{
public:
    StreetView(QGraphicsLineItem* line, QGraphicsTextItem* name);
    QGraphicsTextItem* getName();
    QGraphicsLineItem* getLine();




private:
    QGraphicsLineItem* line;
    QGraphicsTextItem* name;
};

#endif // STREETVIEW_H
