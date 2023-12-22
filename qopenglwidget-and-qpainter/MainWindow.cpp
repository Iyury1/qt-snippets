#include "MainWindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle(tr("QOpenGLWidget and QPainter Example"));

    subWidget = new SubOGLWidget(spiralEnd, this); 
    
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);
    layout->addWidget(subWidget, 0, 0);

    setCentralWidget(centralWidget);
    initSprial();

    spiralTimer = new QTimer(this);
    connect(spiralTimer, &QTimer::timeout, this, &MainWindow::timerCallback);
    spiralTimer->start(40);
}

MainWindow::~MainWindow() {}

void MainWindow::timerCallback() {
    if(direction == FORWARD) {
        spiralEnd += 1;
        if(spiralEnd > 100) {
            direction = BACK;
        }
    }
    else {
        spiralEnd -= 1;
        if(spiralEnd < 0) {
            direction = FORWARD;
        }
    }
    subWidget->update();
}