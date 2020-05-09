#ifndef STREET_H
#define STREET_H


#include <QString>
#include <vector>
#include <QPointF>

class Stop;
class StreetView;

using namespace std;

class Street
{
public:
        Street(QString id, QPointF* c1, QPointF* c2);

        QString getId();

        vector<QPointF*> getCoordinates();

        vector<Stop*> getStops();

        void addStop(Stop* Stop);

        bool operator==(const Street& Street) const;

        void setStreetView(StreetView* v);

        StreetView* getStreetView();

        qreal getCongestionDegree();

        bool contains(QPointF* point);

        void setCongestionDegree(qreal d);

        bool isClosed();

        void close();

        bool isNeighbor(Street *str);

    private:
        QString id;
        vector<QPointF*> coordinates;
        vector<Stop*> stops;
        StreetView* view;
        qreal congestionDegree;
        bool closed;

};

#endif // STREET_H
