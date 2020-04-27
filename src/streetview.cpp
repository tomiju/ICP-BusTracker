#include "streetview.h"

#include <QGraphicsLineItem>
#include <QGraphicsTextItem>


StreetView::StreetView(QGraphicsLineItem* line, QGraphicsTextItem* name)
{
    this->line = line;
    this->name = name;
}

QGraphicsTextItem *StreetView::getName()
{
    return this->name;
}

QGraphicsLineItem *StreetView::getLine()
{
    return this->line;
}






