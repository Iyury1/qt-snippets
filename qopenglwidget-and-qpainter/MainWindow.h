#pragma once
#include <QMainWindow>
#include <QTimer>
#include "SubOGLWidget.h"

#define FORWARD 1
#define BACK 2

class MainWindow : public QMainWindow 
{
private:
    QTimer *spiralTimer;
    void timerCallback();
    int spiralEnd = 0;
    SubOGLWidget *subWidget;
    int direction = FORWARD;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
