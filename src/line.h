/** ICP Project 2019/2020: Bus Tracker
 * @file line.h
 * @brief Trida reprezentujici autobusovou linku (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

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
    /**
     * @brief Line konstruktor tridy
     * @param id
     */
    Line(QString id);

    /**
     * @brief addStreet prida ulici do linky
     * @param str
     */
    void addStreet(Street* str);

    /**
     * @brief addStop
     * @param stop
     */
    void addStop(Stop* stop);

    /**
     * @brief getStop ziska konkretni zastavku
     * @param n
     * @return ziskana zastavka (null kdyz je seznam prazdny)
     */
    Stop* getStop(unsigned n);

    /**
     * @brief getStreet ziska konkretni zastavku
     * @param n
     * @return ziskana ulice (null kdyz je seznam prazdny)
     */
    Street* getStreet(unsigned n);

    /**
     * @brief getCommonPoint zjisti spolecne souradnice ulic s indexem n1, n2
     * @param n1
     * @param n2
     * @return spolecne souradnice
     */
    QPointF* getCommonPoint(unsigned n1,unsigned n2);

    /**
     * @brief addToTimeTable prida polozku do jizdniho radu
     * @param times
     */
    void addToTimeTable(std::vector<QString> times);

    /**
     * @brief getStops ziska vsechny zastavky
     * @return seznam zastavek
     */
    std::vector<Stop *> getStops();

    /**
     * @brief getAllStreets ziska vsechny ulice
     * @return seznam ulic
     */
    std::vector<Street*> getAllStreets();

    /**
     * @brief reset restartuje simulaci
     */
    void reset();

    /**
     * @brief setDrawable
     * @param d
     */
    void setDrawable(Drawable* d);

    /**
     * @brief containsStreet zjisti, zda linka obsahuje danou ulici
     * @param s
     * @return
     */
    bool containsStreet(Street* s);

    /**
     * @brief setRoute nastavi upravenou trasu
     * @param str
     */
    void setRoute(std::vector<Street*> str);

    /**
     * @brief getId ziska id linky
     * @return
     */
    QString getId();

public slots:
    /**
     * @brief touch
     */
    void touch();

private:
    /**
     * @brief draw
     */
    Drawable* draw;

    /**
     * @brief vehicle
     */
    std::vector<Vehicle*> vehicle;

    /**
     * @brief streets
     */
    std::vector<Street*> streets;

    /**
     * @brief stops
     */
    std::vector<Stop*> stops;

    /**
     * @brief timetable
     */
    std::vector<std::vector<unsigned>> timetable;

    /**
     * @brief time
     */
    unsigned time;

    /**
     * @brief id
     */
    QString id;

    /**
     * @brief vehicleNum
     */
    unsigned vehicleNum;

};

#endif // LINE_H
