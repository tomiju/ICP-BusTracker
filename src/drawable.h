#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QObject>

class QGraphicsScene;
class Street;
class Stop;
class Vehicle;
class MainWindow;
class Line;

class Drawable : public QObject
{
    Q_OBJECT

public:
    Drawable(QGraphicsScene* s,MainWindow* mw);

    void drawStreet(Street* street);

    void drawStop(Stop* stop);

    void drawVehicle(Vehicle* vehicle);

    void showVehicleRoute(Vehicle *vehicle);

    void showStreet(Street *street);

    void setCongestionDegree(qreal d);

private:
    MainWindow* mainWindow;
    QGraphicsScene* scene;
    Vehicle* vehicle;
    Line* line;
    Street* street;

public slots:

    void update();
};

#endif // DRAWABLE_H
