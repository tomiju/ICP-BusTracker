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
class VehicleView;

class Vehicle : public QObject
{
    Q_OBJECT

public:
   QPointF *getCoordinate();

   QString getId();

   Vehicle(QString id, QPointF* c,Line* line,std::vector<unsigned> t);

   VehicleView* elipse;
   QGraphicsTextItem* txt;

   void setRoute();

   Line* getLine();

   std::vector<Stop*> getStops();
   unsigned getNextStopN();

   std::vector<unsigned> getStopTimes();

   bool isDead();

private:
   QString id;
   QPointF* c;
   Line* line;

   unsigned time;
   unsigned routeTime;

   unsigned currentStreet;
   unsigned nextStop;

   QPainterPath* path;
   std::vector<unsigned> times;
   bool dead;


public slots:

   void touch();

};

#endif // VEHICLE_H
