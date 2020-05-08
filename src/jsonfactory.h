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
    JsonFactory(QString name, Drawable* d);

    std::vector<Street*> getStreets();
    std::vector<Stop*> getStops();
    std::vector<Line*> getLines();


private:
    Drawable* drawable;

    std::vector<Line*> lines;
    std::vector<Street*> streets;
    std::vector<Stop*> stops;

    void createStreets(QJsonObject* obj);
    void createStops(QJsonObject* obj);
    void createLines(QJsonObject* obj);

    std::vector<std::vector<QString>> createTimeTable(QJsonArray arr);
};

#endif // JSONFACTORY_H
