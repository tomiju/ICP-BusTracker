/** ICP Project 2019/2020: Bus Tracker
 * @file stop.h
 * @brief Trida reprezentujici zastavku (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#ifndef STOP_H
#define STOP_H

#include <QString>
#include <QPointF>


class Street;


class Stop
{
public:
    /**
    * @brief getCoordinate ziska souradnice zastavky
    * @return souradnice zastavky
    */
   QPointF* getCoordinate();

   /**
    * @brief getId ziska nazev zastavky
    * @return nazev zastavky
    */
   QString getId();

   /**
    * @brief getStreet ziska ulici, na ktere zastavka lezi
    * @return ulice na ktere zastavka lezi
    */
   Street* getStreet();

   /**
    * @brief setStreet nastavi zastavce ulici
    * @param str
    */
   void setStreet(Street *str);

   /**
    * @brief Stop konstruktor tridy
    * @param id identifikator
    * @param c souradnice ulice
    */
   Stop(QString id, QPointF* c);

   /**
    * @brief operator ==
    * @param Stop
    * @return
    */
   bool operator==(const Stop& Stop) const;

private:
   /**
    * @brief id identifikator
    */
   QString id;

   /**
    * @brief c souradnice
    */
   QPointF* c;

   /**
    * @brief s ulice
    */
   Street* s;

};

#endif // STOP_H
