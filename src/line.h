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

class Line : public QObject
{
    Q_OBJECT

public:
    Line(QString id,QGraphicsScene* scene);

    void addStreet(Street* str);
    void setStartPoint(QPointF* p);
    void addStop(Stop* stop);

    QPointF* getPoint(unsigned p);
    void removeFirstVehicle();
    Stop* getStop(unsigned n);
    Street* getStreet(unsigned n);
    QPointF* getCommonPoint(unsigned n1,unsigned n2);
    void addToTimeTable(std::vector<QString> times);

public slots:
    void touch();
    void pass();

private:
    std::vector<Vehicle*> vehicle;
    std::vector<Street*> streets;
    std::vector<Stop*> stops;
    std::vector<std::vector<unsigned>> timetable;
    unsigned time;
    QString id;
    QGraphicsScene* scene;
    unsigned vehicleNum;

};

#endif // LINE_H
