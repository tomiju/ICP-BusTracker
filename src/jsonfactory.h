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
     * @param name nazev souboru s mapovym podkladem a jizdnimi rady
     * @param d objekt drawable pro vytvareni graficke reprezentace objektu
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
     * @brief drawable objekt drawable pro vytvareni graficke reprezentace objektu
     */
    Drawable* drawable;

    /**
     * @brief lines seznam vytvorenych linek
     */
    std::vector<Line*> lines;

    /**
     * @brief streets seznam vytvorenych ulic
     */
    std::vector<Street*> streets;

    /**
     * @brief stops seznam vytvorenych zastavek
     */
    std::vector<Stop*> stops;

    /**
     * @brief createStreets vytvori ulice ze vstupnich dat
     * @param obj hlavni objekt souboru
     */
    void createStreets(QJsonObject* obj);

    /**
     * @brief createStops vytvori zastavky ze vstupnich dat
     * @param obj hlavni objekt souboru
     */
    void createStops(QJsonObject* obj);

    /**
     * @brief createLines vytvori linky ze vstupnich dat
     * @param obj hlavni objekt souboru
     */
    void createLines(QJsonObject* obj);

    /**
     * @brief createTimeTable vytvori jizdni rad ze vstupnich dat
     * @param arr 2d pole obsahujici jizdni rad
     * @return jizdni rad
     */
    std::vector<std::vector<QString>> createTimeTable(QJsonArray arr);
};

#endif // JSONFACTORY_H
