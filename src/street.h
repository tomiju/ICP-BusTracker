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

    private:
        QString id;
        vector<QPointF*> coordinates;
        vector<Stop*> stops;
        StreetView* view;

};

#endif // STREET_H
