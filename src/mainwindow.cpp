#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "street.h"
#include "stop.h"
#include "drawable.h"
#include "vehicle.h"
#include "line.h"

#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QAnimationGroup>
#include <QVariantAnimation>
#include <QDebug>
#include <QPoint>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->ZoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->ZoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QPointF* c1 = new QPointF(0,0);
    QPointF* c2 = new QPointF(100,0);
    QPointF* c3 = new QPointF(200,100);
    QPointF* c4 = new QPointF(200,200);

    Street* str1 = new Street("str1",c1,c2);
    Street* str2 = new Street("str2",c2,c3);
    Street* str3 = new Street("str3",c3,c4);

    Stop s1 = Stop("s1",c2);

    Drawable draw =  Drawable();

    draw.drawStreet(str1, scene);
    draw.drawStreet(str2, scene);
    draw.drawStreet(str3, scene);

    //draw.drawStop(&s1,scene);



    Line* line = new Line("Line", scene );

    line->setStartPoint(c1);
    line->addStreet(str1);
    line->addStreet(str2);
    line->addStreet(str3);


    timer = new QTimer();
    connect(timer, &QTimer::timeout, line, &Line::touch);
    timer->setInterval(20);
    timer->start();

/*
    for(int i = 0 ; i < 5; i++ ){
        line->touch();
    }
    */
    connect(ui->touchButton,&QPushButton::clicked,line, &Line::touch);
    connect(ui->changeTimeButton,&QPushButton::clicked,this,&MainWindow::setTimer);
    connect(ui->stopPlayButton,&QPushButton::clicked,this,&MainWindow::stopPlay);
}




MainWindow::~MainWindow()
{
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

void MainWindow::setTimer()
{

    int t[5] = {50,30,20,15,10};

    static int speed = 0;

    if(speed > 4){
        speed = 0;
    }

    this->timer->setInterval(t[speed]);

    speed += 1;

}

void MainWindow::stopPlay()
{
    if(this->timer->isActive()){
        this->timer->stop();
    }else{
        this->timer->start();
    }


}



