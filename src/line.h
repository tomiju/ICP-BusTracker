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
     * @param id identifikator linky
     */
    Line(QString id);

    /**
     * @brief addStreet prida ulici do linky
     * @param str ulice
     */
    void addStreet(Street* str);

    /**
     * @brief addStop prida zastavku do linky
     * @param stop zastavka
     */
    void addStop(Stop* stop);

    /**
     * @brief getStop ziska konkretni zastavku
     * @param n poradi zastavky
     * @return ziskana zastavka (null pokud je n mimo rozsah)
     */
    Stop* getStop(unsigned n);

    /**
     * @brief getStreet ziska konkretni zastavku
     * @param n poradi ulice
     * @return ziskana ulice (null pokud je n mimo rozsah)
     */
    Street* getStreet(unsigned n);

    /**
     * @brief getCommonPoint zjisti spolecne souradnice ulic s indexem n1, n2
     * @param n1 poradi ulice 1
     * @param n2 poradi ulice 2
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
     * @param d objekt Drawable
     */
    void setDrawable(Drawable* d);

    /**
     * @brief containsStreet zjisti, zda linka obsahuje danou ulici
     * @param s ulice
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
     * @brief touch aktualizuje linky a jeji vozidla
     */
    void touch();

private:
    /**
     * @brief draw objekt Drawable
     */
    Drawable* draw;

    /**
     * @brief vehicle seznam vozidel
     */
    std::vector<Vehicle*> vehicle;

    /**
     * @brief streets sezname ulic
     */
    std::vector<Street*> streets;

    /**
     * @brief stops seznam zastavek
     */
    std::vector<Stop*> stops;

    /**
     * @brief timetable jizdni rad linky
     */
    std::vector<std::vector<unsigned>> timetable;

    /**
     * @brief time aktualni cas v simulaci
     */
    unsigned time;

    /**
     * @brief id identifikator
     */
    QString id;

    /**
     * @brief vehicleNum poce vozidel linky
     */
    unsigned vehicleNum;

};

#endif // LINE_H
