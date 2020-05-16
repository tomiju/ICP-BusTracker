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
    * @param id identifikator
    * @param c souradnice vozidla
    * @param line linka, do ktere vozidlo patri
    * @param t casy pro jednotlive zastavky
    */
   Vehicle(QString id, QPointF* c,Line* line,std::vector<unsigned> t);

   /**
    * @brief elipse graficka reprezentace vozidla
    */
   VehicleView* elipse;

   /**
    * @brief txt textova reprezentace prislusne linky
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
    * @brief kill skryje vozidlo, pozice se nyni neaktualizuje
    */
   void kill();

   /**
    * @brief activate zobrazi vozidlo, aktivuje aktualizaci vozdila
    */
   void activate();

   /**
    * @brief isDead zjisti, zda je vozidlo neaktivni
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
    * @brief getActivationTime vraci cas, kdz je vozidlo na prvni zastavce
    */
   unsigned getActivationTime();

private:
   /**
    * @brief id identifikator
    */
   QString id;

   /**
    * @brief c aktualni poloha
    */
   QPointF* c;

   /**
    * @brief line prislusna linka
    */
   Line* line;

   /**
    * @brief dead znaci zda je vozidlo neaktivni
    */
   bool dead;

   /**
    * @brief time cas straveny na aktualni trase
    */
   qreal time;

   /**
    * @brief routeTime ocekavany cas cesty mezi zastavkami
    */
   unsigned routeTime;

   /**
    * @brief delay zpozdeni vozidla
    */
   qreal delay;

   /**
    * @brief currentStreet soucasna ulice
    */
   unsigned currentStreet;

   /**
    * @brief nextStop poradi pristi zastaky
    */
   unsigned nextStop;

   /**
    * @brief path aktualni trasa vozidla mezi minulou a pristi zastavkou
    */
   QPainterPath* path;

   /**
    * @brief times casy pro jednotlive zastavky (jizdni rad)
    */
   std::vector<unsigned> times;

   /**
    * @brief skippedStops preskocene zastavky
    */
   std::vector<bool> skippedStops;

   /**
    * @brief createSkippedStops nalezne zastavky, ktere nelezi na trase
    */
   void createSkippedStops();

   /**
    * @brief activationTime cas prvni zastavky
    */
   unsigned activationTime;



public slots:

   /**
    * @brief touch vypocita polohu vozidla a aktualizuje ji v mape
    */
   void touch();

};

#endif // VEHICLE_H
