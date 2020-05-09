#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class Vehicle;
class Street;
class QTimer;
class Line;
class Drawable;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void zoomIn();

    void zoomOut();
    void restart();
    void showVehicleRoute(Vehicle *vehicle);
    void showStreet(Street *street);
    void setCongestionDegree();

public slots:
    void setTimer();
    void stopPlay();
    void updatemainTime();
    void resetTime();
    void setTime();
    void updateLines();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    unsigned mainTime;
    Line* mainLine;
    Drawable* drawable;
    std::vector<Line*> lines;

};
#endif // MAINWINDOW_H
