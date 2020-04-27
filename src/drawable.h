#ifndef DRAWABLE_H
#define DRAWABLE_H

class QGraphicsScene;
class Street;
class Stop;
class Vehicle;

class Drawable
{
public:
    Drawable();

    void drawStreet(Street* street, QGraphicsScene* scene);

    void drawStop(Stop* stop, QGraphicsScene* scene);

    void drawVehicle(Vehicle* vehicle, QGraphicsScene* scene);


};

#endif // DRAWABLE_H
