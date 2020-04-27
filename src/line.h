#ifndef LINE_H
#define LINE_H

#include <QString>
#include <vector>
#include <QObject>
#include <QGraphicsScene>

class QPointF;
class Street;
class Vehicle;

class Line : public QObject
{
    Q_OBJECT

public:
    Line(QString id,QGraphicsScene* scene);

    void addStreet(Street* str);
    void setStartPoint(QPointF* p);

    QPointF* getPoint(unsigned p);
    void removeFirstVehicle();

public slots:
    void touch();
    void pass();

private:
    std::vector<QPointF*> points;
    std::vector<Vehicle*> vehicle;
    std::vector<Street*> streets;
    int time;
    QString id;
    QGraphicsScene* scene;
    int vehicleNum;

};

#endif // LINE_H
