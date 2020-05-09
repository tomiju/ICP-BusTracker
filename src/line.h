#ifndef LINE_H
#define LINE_H

#include <QString>
#include <vector>
#include <QObject>
#include <QGraphicsScene>

class QPointF;
#include <vector>

class Street;
class Vehicle;
class Stop;
class Drawable;

class Line : public QObject
{
    Q_OBJECT

public:
    Line(QString id);

    void addStreet(Street* str);

    void addStop(Stop* stop);

    Stop* getStop(unsigned n);

    Street* getStreet(unsigned n);

    QPointF* getCommonPoint(unsigned n1,unsigned n2);

    void addToTimeTable(std::vector<QString> times);

    std::vector<Stop *> getStops();

    std::vector<Street*> getAllStreets();

    void reset();

    void setDrawable(Drawable* d);

    bool containsStreet(Street* s);

    void setRoute(std::vector<Street*> str);

    QString getId();



public slots:
    void touch();

private:
    Drawable* draw;
    std::vector<Vehicle*> vehicle;
    std::vector<Street*> streets;
    std::vector<Stop*> stops;
    std::vector<std::vector<unsigned>> timetable;
    unsigned time;
    QString id;
    unsigned vehicleNum;


};

#endif // LINE_H
