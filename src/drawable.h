/** ICP Project 2019/2020: Bus Tracker
 * @file drawable.h
 * @brief Trida pro vykreslovane objekty na mape (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

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
    /**
     * @brief Drawable konstruktor tridy
     * @param s
     * @param mw
     */
    Drawable(QGraphicsScene* s,MainWindow* mw);

    /**
     * @brief drawStreet vykresli ulici
     * @param street ulice
     */
    void drawStreet(Street* street);

    /**
     * @brief drawStop vykresli zastavky
     * @param stop zastavka
     */
    void drawStop(Stop* stop);

    /**
     * @brief drawVehicle vykresli vozidlo
     * @param vehicle vozidlo
     */
    void drawVehicle(Vehicle* vehicle);

    /**
     * @brief showVehicleRoute zvyrazni trasu vozidla
     * @param vehicle vozidlo
     */
    void showVehicleRoute(Vehicle *vehicle);

    /**
     * @brief showStreet zvyrazni ulici
     * @param street ulice
     */
    void showStreet(Street *street);

    /**
     * @brief setCongestionDegree nastavi stupen ucpanosti ulice
     * @param d hodnota ucpanosti ulice
     */
    void setCongestionDegree(qreal d);

    /**
     * @brief streetOnClick funkce pro naklikani nove trasy
     * @param str nakliknuta ulice
     */
    void streetOnClick(Street* str);

    /**
     * @brief isEditMode zjisti, zda je zapnuty editovaci mod
     * @return true/false
     */
    bool isEditMode();

private:
    /**
     * @brief mainWindow
     */
    MainWindow* mainWindow;

    /**
     * @brief scene
     */
    QGraphicsScene* scene;

    /**
     * @brief vehicle
     */
    Vehicle* vehicle;

    /**
     * @brief line
     */
    Line* line;

    /**
     * @brief street
     */
    Street* street;

    /**
     * @brief editMode
     */
    bool editMode;

    /**
     * @brief newStreets
     */
    std::vector<Street*> newStreets;

    /**
     * @brief effectedLines
     */
    std::vector<Line*> effectedLines;

public slots:

    /**
     * @brief closeStreet
     */
    void closeStreet();

    /**
     * @brief update
     */
    void update();

    /**
     * @brief setRoute
     */
    void setRoute();

};

#endif // DRAWABLE_H
