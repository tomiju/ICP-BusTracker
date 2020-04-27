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

class Vehicle : public QObject
{
    Q_OBJECT

public:
   QPointF *getCoordinate();

   QString getId();


   Vehicle(QString id, QPointF* c,Line* line);

   QGraphicsEllipseItem* elipse;
   QGraphicsTextItem* txt;

   void setRoute(int time, QPointF* destination);



private:
   QString id;
   QPointF* c;
   int time;
   int routeTime;
   QPointF* start;
   QPointF* destination;
   QVariantAnimation* a;
   unsigned pointN;
   Line* line;

   void pointNIncrease();

public slots:


   void change( QVariant x);
   void update();
   void touch();

};

#endif // VEHICLE_H
