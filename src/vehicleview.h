/** ICP Project 2019/2020: Bus Tracker
 * @file vehicleview.h
 * @brief Trida pro ulozeni graficke reprezentace vozidla (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>

class Vehicle;
class Drawable;


class VehicleView : public QGraphicsEllipseItem
{
public:
    /**
     * @brief VehicleView konstruktor tridy
     * @param d
     * @param v vozidlo
     * @param x souradnice x
     * @param y souradnice y
     * @param width sirka
     * @param height vyska
     * @param parent
     */
    VehicleView(Drawable* d,Vehicle* v,qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);

protected:
    /**
     * @brief mousePressEvent ovlada reakci na kliknuti na vozidlo
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)override;


private:
    /**
     * @brief drawable
     */
    Drawable* drawable;

    /**
     * @brief vehicle
     */
    Vehicle* vehicle;


};

#endif // VEHICLEVIEW_H
