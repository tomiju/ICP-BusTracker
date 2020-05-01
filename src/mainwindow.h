#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTimer;

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

public slots:
    void setTimer();
    void stopPlay();
    void updatemainTime();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    unsigned mainTime;

};
#endif // MAINWINDOW_H
