/** ICP Project 2019/2020: Bus Tracker
 * @file vehicle.h
 * @brief Trida reprezentujici vozidlo (header)
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>
#include <QObject>
#include <QVariant>
#include <QPoint>

class QGraphicsEllipseItem;
class QGraphicsTextItem;
class QVariantAnimation;
class Line;
class Street;
class Stop;
class QPainterPath;
class VehicleView;

class Vehicle : public QObject
{
    Q_OBJECT

public:
    /**
    * @brief getCoordinate ziska souradnice vozidla
    * @return souradnice vozidla
    */
   QPointF *getCoordinate();

   /**
    * @brief getId ziska nazev vozidla
    * @return nazev vozidla
    */
   QString getId();

   /**
    * @brief Vehicle konstruktor tridy
    * @param id
    * @param c
    * @param line
    * @param t
    */
   Vehicle(QString id, QPointF* c,Line* line,std::vector<unsigned> t);

   /**
    * @brief elipse
    */
   VehicleView* elipse;

   /**
    * @brief txt
    */
   QGraphicsTextItem* txt;

   /**
    * @brief setRoute nastavi trasu vozidla
    */
   void setRoute();

   /**
    * @brief getLine ziska linku, ke ktere vozidlo patri
    * @return linka, ke ktere vozidlo patri
    */
   Line* getLine();

   /**
    * @brief getStops ziska zastavky daneho vozidla
    * @return seznam zastavek vozidla
    */
   std::vector<Stop*> getStops();

   /**
    * @brief getNextStopN ziska index nasledujici ulice
    */
   unsigned getNextStopN();

   /**
    * @brief getCurrentStreet ziska soucasnou ulici
    * @return soucasna ulice
    */
   Street* getCurrentStreet();

   /**
    * @brief getStopTimes ziska casy prijezdu na zastavky
    * @return seznam casu s prijezdy na zastavky
    */
   std::vector<unsigned> getStopTimes();

   /**
    * @brief getDelay ziska zpozdeni vozidla
    * @return zpozdeni vozidla
    */
   qreal getDelay();

   /**
    * @brief kill skryje vozidlo
    */
   void kill();

   /**
    * @brief activate zobrazi vozidlo
    */
   void activate();

   /**
    * @brief isDead zjisti, zda je vozidlo skryte
    * @return true/false
    */
   bool isDead();

   /**
    * @brief reset restartuje stav vozidla
    */
   void reset();

   /**
    * @brief getSkippedStops
    * @return vraci vektor, true = preskocena zastavka
    */
   std::vector<bool> getSkippedStops();

   /**
    * @brief getActivationTime vraci cas vyjezdu
    */
   unsigned getActivationTime();

private:
   /**
    * @brief id
    */
   QString id;

   /**
    * @brief c
    */
   QPointF* c;

   /**
    * @brief line
    */
   Line* line;

   /**
    * @brief dead
    */
   bool dead;

   /**
    * @brief time
    */
   qreal time;

   /**
    * @brief routeTime
    */
   unsigned routeTime;

   /**
    * @brief delay
    */
   qreal delay;

   /**
    * @brief currentStreet
    */
   unsigned currentStreet;

   /**
    * @brief nextStop
    */
   unsigned nextStop;

   /**
    * @brief path
    */
   QPainterPath* path;

   /**
    * @brief times
    */
   std::vector<unsigned> times;

   /**
    * @brief skippedStops
    */
   std::vector<bool> skippedStops;

   /**
    * @brief createSkippedStops nalezne zastavky, ktere nelezi na trase
    */
   void createSkippedStops();

   /**
    * @brief activationTime
    */
   unsigned activationTime;



public slots:

   /**
    * @brief touch vypocita polohu vozidla a aktualizuje ji v mape
    */
   void touch();

};

#endif // VEHICLE_H
