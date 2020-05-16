/** ICP Project 2019/2020: Bus Tracker
 * @file street.h
 * @brief Trida reprezentujici ulici (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#ifndef STREET_H
#define STREET_H


#include <QString>
#include <vector>
#include <QPointF>

class Stop;
class StreetView;

using namespace std;

class Street
{
public:
        /**
         * @brief Street konstruktor tridy
         * @param id identifikator
         * @param c1 souradnice zacatku ulice
         * @param c2 souradnice konce ulice
         */
        Street(QString id, QPointF* c1, QPointF* c2);

        /**
         * @brief getId ziska nazev ulice
         * @return nazev ulice
         */
        QString getId();

        /**
         * @brief getCoordinates ziska souradnice ulice
         * @return seznam obsahujici zacatek a konec ulice
         */
        vector<QPointF*> getCoordinates();

        /**
         * @brief getStops ziska zastavky, ktere patri k dane ulici
         * @return seznam zastavek
         */
        vector<Stop*> getStops();

        /**
         * @brief addStop prida zastavku k ulici
         * @param Stop
         */
        void addStop(Stop* Stop);

        /**
         * @brief operator ==
         * @param Street
         * @return
         */
        bool operator==(const Street& Street) const;

        /**
         * @brief setStreetView ulozi grafickou reprezentaci ulice do promenne
         * @param v
         */
        void setStreetView(StreetView* v);

        /**
         * @brief getStreetView ziska grafickou reprezentaci ulice
         * @return
         */
        StreetView* getStreetView();

        /**
         * @brief getCongestionDegree ziska informaci o "ucpanosti" ulice
         * @return
         */
        qreal getCongestionDegree();

        /**
         * @brief contains zjisti, zda dany bod lezi na ulici
         * @param point
         * @return
         */
        bool contains(QPointF* point);

        /**
         * @brief setCongestionDegree nastavi "ucpanost" ulice
         * @param d
         */
        void setCongestionDegree(qreal d);

        /**
         * @brief isClosed zjisti, zda je ulice uzavrena
         * @return true/false
         */
        bool isClosed();

        /**
         * @brief close uzavre ulici
         */
        void close();

        /**
         * @brief isNeighbor zjisti, zda dana ulice navazuje na tuto ulici
         * @param str ulice
         * @return true/false
         */
        bool isNeighbor(Street *str);

    private:
        /**
         * @brief id identifikator
         */
        QString id;

        /**
         * @brief coordinates souradnice zacatku a konce ulice
         */
        vector<QPointF*> coordinates;

        /**
         * @brief stops seznam zastavek
         */
        vector<Stop*> stops;

        /**
         * @brief view graficka reprezentace
         */
        StreetView* view;

        /**
         * @brief congestionDegree hodnota "ucpanosti" ulice
         */
        qreal congestionDegree;

        /**
         * @brief closed uavrenost ulice
         */
        bool closed;

};

#endif // STREET_H
