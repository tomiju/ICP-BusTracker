#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>
#include <QObject>
#include <QVariant>
#include <QPoint>

class QGraphicsEllipseItem;
class QGraphicsTextItem;
class QVariantAnimation;
class Line;
class Street;
class Stop;
class QPainterPath;

class Vehicle : public QObject
{
    Q_OBJECT

public:
   QPointF *getCoordinate();

   QString getId();

   Vehicle(QString id, QPointF* c,Line* line);

   QGraphicsEllipseItem* elipse;
   QGraphicsTextItem* txt;

   void setRoute(int timeNew);


private:
   QString id;
   QPointF* c;
   Line* line;

   int time;
   int routeTime;

   unsigned currentStreet;
   unsigned nextStop;

   QPainterPath* path;


public slots:

   void touch();

};

#endif // VEHICLE_H
