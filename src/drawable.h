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

    void streetOnClick(Street* str);

    bool isEditMode();

private:
    MainWindow* mainWindow;
    QGraphicsScene* scene;
    Vehicle* vehicle;
    Line* line;
    Street* street;
    bool editMode;
    std::vector<Street*> newStreets;
    std::vector<Line*> effectedLines;

public slots:

    void closeStreet();

    void update();

    void setRoute();


};

#endif // DRAWABLE_H
