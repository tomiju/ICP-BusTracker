/** ICP Project 2019/2020: Bus Tracker
 * @file mainwindow.cpp
 * @brief Trida, ktera ovlada hlavni okno programu, zapina jizdu, atd...
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "street.h"
#include "stop.h"
#include "drawable.h"
#include "vehicle.h"
#include "line.h"
#include "jsonfactory.h"

#include <cmath>
#include <iostream>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QAnimationGroup>
#include <QVariantAnimation>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ICP Bus Tracker");

    mainTime = 0;

    connect(ui->ZoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->ZoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(ui->changeTimeButton,&QPushButton::clicked,this,&MainWindow::setTimer);
    connect(ui->stopPlayButton,&QPushButton::clicked,this,&MainWindow::stopPlay);
    connect(ui->resetButton,&QPushButton::clicked,this,&MainWindow::resetTime);
    connect(ui->setTimeButton, &QPushButton::clicked,this,&MainWindow::setTime);
    connect(ui->congestionButton, &QPushButton::clicked, this, &MainWindow::setCongestionDegree);
    ui->timeEdit->setDisplayFormat("hh:mm:ss");
    ui->infoLabel->setText("");
    ui->setRouteButton->hide();



    ui->closeStreetButton->hide();
    ui->lineEditCongestion->hide();
    ui->congestionButton->hide();

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    Drawable* draw = new Drawable(scene,this);
    this->drawable = draw;

     QString name;

     name = QFileDialog::getOpenFileName(this,
            tr("Open map file"), "",
            tr("Json files (*.json)"));




    //name = QApplication::applicationDirPath() + "/../examples/map.json";

    JsonFactory* factory = new JsonFactory(name,draw);

    this->lines = factory->getLines();

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::updateLines);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatemainTime);
    connect(timer, &QTimer::timeout, draw, &Drawable::update);
    connect(ui->closeStreetButton, &QPushButton::clicked, draw,  &Drawable::closeStreet);
    connect(ui->setRouteButton, &QPushButton::clicked, draw,  &Drawable::setRoute);

    timer->setInterval(1000);
    timer->start();

}


MainWindow::~MainWindow()
{
    this->timer->stop();
    delete ui;

}


void MainWindow::zoomIn()
{
    ui->graphicsView->scale(1.25, 1.25);
}

void MainWindow::zoomOut()
{
    ui->graphicsView->scale(0.8, 0.8);
}


void MainWindow::restart()
{
    ui->graphicsView->scale(0.8, 0.8);
}

void MainWindow::showVehicleRoute(Vehicle *vehicle)
{

    ui->infoLabel->setText("");

    ui->closeStreetButton->hide();
    ui->lineEditCongestion->hide();
    ui->congestionButton->hide();

    if(vehicle->isDead()){
        return;
    }

    auto stops = vehicle->getStops();
    auto times = vehicle->getStopTimes();

    int delay = vehicle->getDelay();
    delay = delay / 5;
    delay = delay * 5;


    QString infoStr = "VEHICLE INFO\n\n";
    infoStr += "Line: " + vehicle->getLine()->getId() + "\n";
    infoStr += "Id: " + vehicle->getId() + "\n";
    infoStr += "Next Stop: " + vehicle->getStops().at(vehicle->getNextStopN())->getId() + "\n";
    infoStr += "Street: " + vehicle->getCurrentStreet()->getId() + "\n";
    auto delayTime = QTime();
    delayTime.setHMS(0,0,0);
    delayTime = delayTime.addSecs(delay);
    infoStr += "Delay: " + delayTime.toString() + "\n\n";
    infoStr += "Stops:\n";

    for(unsigned i = 0; i < stops.size(); i++){

        auto t =  times.at(i);
        QTime time;
        time.setHMS(0,0,0);
        time = time.addSecs(t);

        infoStr += stops.at(i)->getId() + " : "+ time.toString() + "\n";

    }

    ui->infoLabel->setText(infoStr);
}

void MainWindow::showStreet(Street *street)
{

    QString infoStr = "STREET INFO\n\n";
    infoStr += "Street Id: " +street->getId() + "\n";
    infoStr += "Congestion Degree: " + QString::number(street->getCongestionDegree()) + "\n";
    ui->infoLabel->setText(infoStr);

    ui->closeStreetButton->show();
    ui->lineEditCongestion->show();
    ui->congestionButton->show();

}

void MainWindow::setCongestionDegree()
{
    QString str = ui->lineEditCongestion->text();

    qreal degree = str.toDouble();
    if(degree < 1){
        ui->lineEditCongestion->setText("Must be number greater or equal to 1");
    }else{
        drawable->setCongestionDegree(degree);
    }

}

void MainWindow::stop()
{
    this->timer->stop();
    this->ui->stopPlayButton->setText("Play");
}

std::vector<Line *> MainWindow::getLines()
{
    return lines;
}

void MainWindow::showNewRoute(Line *line, std::vector<Street *> str)
{

    QString infoStr = "Line Id: " + line->getId() + "\n\n";

    for(auto s : str){
        infoStr += "Street Id: " + s->getId() + "\n";
    }

    ui->infoLabel->setText(infoStr);
}


void MainWindow::setTimer()
{

    int t[10] = {1000,500,200,100,50,20,10,5,2,1};

    static int speed = 0;
    speed += 1;

    if(speed > 9){
        speed = 0;
    }

    this->timer->setInterval(t[speed]);
    ui->changeTimeButton->setText("Speed 1:" + QString::number(1000/t[speed]) );
}


void MainWindow::stopPlay()
{
    if(drawable->isEditMode()){
        return;
    }

    if(this->timer->isActive()){
        this->timer->stop();
        ui->stopPlayButton->setText("Play");
    }else{
        this->timer->start();
        ui->stopPlayButton->setText("Stop");
    }
}


void MainWindow::updatemainTime()
{
    mainTime += 1;
    QTime time;
    time.setHMS(0,0,0);
    time = time.addSecs(mainTime);

    ui->TimeLabel->setText(time.toString());
}

void MainWindow::resetTime()
{
    if(drawable->isEditMode()){
        return;
    }

    mainTime = 0;
    for(auto l : lines){
        l->reset();
    }
     drawable->update();
}

void MainWindow::setTime()
{
    if(drawable->isEditMode()){
        return;
    }

    resetTime();

    auto time = ui->timeEdit->time();

    int t = time.hour()*3600 + time.minute()*60 + time.second();

    for(int i = 0; i < t; i++){
        for(auto l : lines){
            l->touch();
        }
        updatemainTime();
    }

    drawable->update();
}

void MainWindow::updateLines()
{
    for(auto l : lines){
        l->touch();
    }
}

void MainWindow::setMapFileName(QString name)
{
    this->mapFileName = name;
}

void MainWindow::setEditMode()
{
    ui->setRouteButton->show();

    ui->closeStreetButton->hide();
    ui->congestionButton->hide();
    ui->lineEditCongestion->hide();

}

void MainWindow::setNormalMode()
{
    ui->setRouteButton->hide();
    ui->infoLabel->setText("");
}
