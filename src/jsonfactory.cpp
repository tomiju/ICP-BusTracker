#include "jsonfactory.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QPointF>
#include <QString>

#include "street.h"
#include "stop.h"
#include "line.h"
#include "drawable.h"

JsonFactory::JsonFactory(QString name, Drawable* d)
{

    QFile* file = new QFile(name);
    drawable = d;

    if(file->exists() && file->open(QIODevice::ReadOnly | QIODevice::Text)){

        QJsonDocument doc = QJsonDocument::fromJson(file->readAll());
        QJsonObject obj =  doc.object();
        createStreets(&obj);
        createStops(&obj);
        createLines(&obj);

    }

}

std::vector<Street *> JsonFactory::getStreets()
{
    return  streets;
}

std::vector<Stop *> JsonFactory::getStops()
{
    return stops;
}

std::vector<Line *> JsonFactory::getLines()
{
    return lines;
}

void JsonFactory::createStreets(QJsonObject* obj)
{
    QJsonArray streetsArray = obj->value("streets").toArray();

    for(auto strObjValue :streetsArray ){
        auto strObj = strObjValue.toObject();
        QString id = strObj.value("id").toString();
        int x1 = strObj.value("x1").toInt();
        int x2 = strObj.value("x2").toInt();
        int y1 = strObj.value("y1").toInt();
        int y2 = strObj.value("y2").toInt();

        qDebug() << id << x1 << y1 << x2 << y2;


        Street* str = new Street(id,new QPointF(x1,y1),new QPointF(x2,y2));
        streets.push_back(str);

        drawable->drawStreet(str);
    }
}

void JsonFactory::createStops(QJsonObject *obj)
{
     QJsonArray stopsArray = obj->value("stops").toArray();

     for(auto stopObjValue :stopsArray ){
         auto stopObj = stopObjValue.toObject();
         QString id = stopObj.value("id").toString();
         int x = stopObj.value("x").toInt();
         int y = stopObj.value("y").toInt();
         QString strId = stopObj.value("street").toString();

         qDebug() << id << x << y << strId;


         Stop* stop = new Stop(id,new QPointF(x,y));
         stops.push_back(stop);

         for(auto str : streets){
             if(str->getId() == strId){
                 str->addStop(stop);
                 break;
             }
         }

         drawable->drawStop(stop);
     }
}

void JsonFactory::createLines(QJsonObject *obj)
{
    QJsonArray linesArray = obj->value("lines").toArray();

    for(auto lineObjValue : linesArray){
        auto lineObj = lineObjValue.toObject();
        QString id = lineObj.value("id").toString();

        Line* line = new Line(id);
        line->setDrawable(drawable);
        lines.push_back(line);



        QJsonArray stopsArray = lineObj.value("stops").toArray();

        for(auto stopObjValue : stopsArray){
            QString stopId = stopObjValue.toString();
            qDebug() << id << stopId;
            for(auto stop : stops){
                if(stop->getId() == stopId){
                    line->addStop(stop);
                }
            }
        }

        QJsonArray streetsArray = lineObj.value("streets").toArray();

        for(auto streetObjValue : streetsArray){
            QString streetId = streetObjValue.toString();
            qDebug() << id << streetId;
            for(auto street : streets){
                if(street->getId() == streetId){
                    line->addStreet(street);
                }
            }
        }

        auto timeTable = createTimeTable(lineObj.value("timetable").toArray());

        for(auto timePart : timeTable){
            line->addToTimeTable(timePart);
        }

    }
}

std::vector<std::vector<QString>> JsonFactory::createTimeTable(QJsonArray arr)
{
    std::vector<std::vector<QString>> vector;

    qDebug() << arr;

    for(auto arrPart : arr){
        std::vector<QString> vectorPart;

        for(auto timeValue : arrPart.toArray()){
            vectorPart.push_back(timeValue.toString());
        }

        vector.push_back(vectorPart);
    }

    qDebug() << vector;

    return vector;
}
