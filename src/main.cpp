/** ICP Project 2019/2020: Bus Tracker
 * @file main.cpp
 * @brief Hlavni spusteni celeho programu
 * @author Tomáš Julina (xjulin08)
 * @author Tomáš Kantor (xkanto14)
 */

#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setMapFileName(argv[1]);

    qDebug() << "name: " << argv;
    w.showMaximized();




    return a.exec();
}
