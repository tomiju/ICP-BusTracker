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

    mainTime = 0;

    connect(ui->ZoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->ZoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(ui->changeTimeButton,&QPushButton::clicked,this,&MainWindow::setTimer);
    connect(ui->stopPlayButton,&QPushButton::clicked,this,&MainWindow::stopPlay);
    connect(ui->resetButton,&QPushButton::clicked,this,&MainWindow::resetTime);
    connect(ui->lineEdit, &QLineEdit::textEdited,this,&MainWindow::setTime);
    connect(ui->congestionButton, &QPushButton::clicked, this, &MainWindow::setCongestionDegree);

    ui->closeStreetButton->hide();
    ui->lineEditCongestion->hide();
    ui->congestionButton->hide();

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    Drawable* draw = new Drawable(scene,this);
    this->drawable = draw;

     QString name = QFileDialog::getOpenFileName(this,
            tr("Open map file"), "",
            tr("Json files (*.json)"));


    qDebug() << "name: " << name;

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
    ui->listWidget->clear();
    ui->closeStreetButton->hide();
    ui->lineEditCongestion->hide();
    ui->congestionButton->hide();

    if(vehicle->isDead()){
        return;
    }

    auto stops = vehicle->getStops();
    auto times = vehicle->getStopTimes();

    qreal delay = vehicle->getDelay();
    delay = delay / 5;
    delay = std::floor(delay);
    delay = delay * 5;


    QString str = vehicle->getId() + " " + vehicle->getCurrentStreet()->getId() + " delay: " + QString::number(delay) + "s";

    ui->listWidget->addItem(str);

    for(unsigned i = 0; i < stops.size(); i++){

        auto t =  times.at(i);
        QTime time;
        time.setHMS(0,0,0);
        time = time.addSecs(t);

        str = time.toString() + "\t" + stops.at(i)->getId();

        ui->listWidget->addItem(str);

    }

    int nextStop = 1 + static_cast<int>(vehicle->getNextStopN());

    if(nextStop < ui->listWidget->count()){
        ui->listWidget->item(nextStop)->setBackgroundColor(Qt::red);
    }

}

void MainWindow::showStreet(Street *street)
{
    ui->listWidget->clear();

    QString str = street->getId() + " congestion degree: " + QString::number(street->getCongestionDegree());

    ui->listWidget->addItem(str);
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
    ui->listWidget->clear();
    ui->listWidget->addItem(line->getId());

    for(auto s : str){
        ui->listWidget->addItem(s->getId());
    }
}


void MainWindow::setTimer()
{

    int t[9] = {1000,500,200,100,50,20,10,5,2};

    static int speed = 0;
    speed += 1;

    if(speed > 8){
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

    QString str = ui->lineEdit->text();

    int t = str.toInt();

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



