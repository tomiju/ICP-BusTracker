#ifndef LINE_H
#define LINE_H

#include <QString>
#include <vector>
#include <QObject>
#include <QGraphicsScene>

class QPointF;
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

public slots:
    void touch();
    void pass();

private:
    std::vector<Vehicle*> vehicle;
    std::vector<Street*> streets;
    std::vector<Stop*> stops;
    std::vector<std::vector<unsigned>> timetable;
    int time;
    QString id;
    QGraphicsScene* scene;
    int vehicleNum;

};

#endif // LINE_H
