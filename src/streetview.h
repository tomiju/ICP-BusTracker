/** ICP Project 2019/2020: Bus Tracker
 * @file streetview.h
 * @brief Trida pro ulozeni graficke reprezentace ulice
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

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
    /**
     * @brief StreetView konstruktor tridy
     * @param d
     * @param str
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @param parent
     */
    StreetView(Drawable* d,Street* str,qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = nullptr);

    /**
     * @brief highlight zvyrazni ulici
     */
    void highlight();

    /**
     * @brief highlight2 zvyrazni ulici
     */
    void  highlight2();

    /**
     * @brief unhighlight resetuje zvyrazneni ulice
     */
    void unhighlight();

    /**
     * @brief close nastavi vzhled uzavrene ulice
     */
    void close();

    /**
     * @brief mousePressEvent ovlada reakci na kliknuti na ulici
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)override;

private:
    /**
     * @brief draw
     */
    Drawable* draw;

    /**
     * @brief street
     */
    Street* street;

};

#endif // STREETVIEW_H
