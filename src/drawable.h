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
     * @param s scena pro vykresleni mapy
     * @param mw hlavni okno aplikace
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
     * @brief mainWindow hlavni okno aplikace
     */
    MainWindow* mainWindow;

    /**
     * @brief scene scena pro vykresleni mapy
     */
    QGraphicsScene* scene;

    /**
     * @brief vehicle vozidlo zvyrazne na mape
     */
    Vehicle* vehicle;

    /**
     * @brief line linka zvyraznena na mape
     */
    Line* line;

    /**
     * @brief street ulice zvyraznena na mape
     */
    Street* street;

    /**
     * @brief editMode znaci zda, je aplikace v editacnim modu
     */
    bool editMode;

    /**
     * @brief newStreets novy vytvareny seznam ulic (trasa) pro linku
     */
    std::vector<Street*> newStreets;

    /**
     * @brief effectedLines linky ovlivnene uzavrenim ulice
     */
    std::vector<Line*> effectedLines;

public slots:

    /**
     * @brief closeStreet uzvre zvyraznenou ulici
     */
    void closeStreet();

    /**
     * @brief update aktualizuje zobrazovane informace
     */
    void update();

    /**
     * @brief setRoute nastavi novou trasu pro danou linku
     */
    void setRoute();

    /**
     * @brief clearRoute smaze novou trasu
     */
    void clearRoute();

};

#endif // DRAWABLE_H
