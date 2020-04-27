#ifndef STOP_H
#define STOP_H

#include <QString>
#include <QPointF>


class Street;


class Stop
{
public:
   QPointF* getCoordinate();

   QString getId();
   Street* getStreet();
   void setStreet(Street *str);

   Stop(QString id, QPointF* c);


   bool operator==(const Stop& Stop) const;

private:
   QString id;
   QPointF* c;
   Street* s;

};

#endif // STOP_H
