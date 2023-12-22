#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {

    QSurfaceFormat fmt;
    // setDefaultFormat recommended by Qt docs:
    // https://doc.qt.io/qt-6/qsurfaceformat.html#setDefaultFormat
    // https://doc.qt.io/qt-6/qopenglwidget.html
    QSurfaceFormat::setDefaultFormat(fmt);
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    return app.exec();
}