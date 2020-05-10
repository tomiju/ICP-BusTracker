/** ICP Project 2019/2020: Bus Tracker
 * @file jsonfactory.h
 * @brief Trida pro zpracovani vstupniho souboru s daty do interni reprezentace (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#ifndef JSONFACTORY_H
#define JSONFACTORY_H

#include <QString>
#include <vector>

class QJsonObject;
class Line;
class Street;
class Stop;
class Drawable;
class QJsonArray;

class JsonFactory
{
public:
    /**
     * @brief JsonFactory konstruktor tridy
     * @param name
     * @param d
     */
    JsonFactory(QString name, Drawable* d);

    /**
     * @brief getStreets ziska seznam ulic
     * @return
     */
    std::vector<Street*> getStreets();

    /**
     * @brief getStops ziska seznam zastavek
     * @return
     */
    std::vector<Stop*> getStops();

    /**
     * @brief getLines ziska seznam linek
     * @return
     */
    std::vector<Line*> getLines();


private:
    /**
     * @brief drawable
     */
    Drawable* drawable;

    /**
     * @brief lines
     */
    std::vector<Line*> lines;

    /**
     * @brief streets
     */
    std::vector<Street*> streets;

    /**
     * @brief stops
     */
    std::vector<Stop*> stops;

    /**
     * @brief createStreets vytvori ulice ze vstupnich dat
     * @param obj
     */
    void createStreets(QJsonObject* obj);

    /**
     * @brief createStops vytvori zastavky ze vstupnich dat
     * @param obj
     */
    void createStops(QJsonObject* obj);

    /**
     * @brief createLines vytvori linky ze vstupnich dat
     * @param obj
     */
    void createLines(QJsonObject* obj);

    /**
     * @brief createTimeTable vytvori jizdni rad ze vstupnich dat
     * @param arr
     * @return jizdni rad
     */
    std::vector<std::vector<QString>> createTimeTable(QJsonArray arr);
};

#endif // JSONFACTORY_H
