#include "CustomTimer.h"
#include <iostream>
#include <QObject>
#include <QTimer>

class CustomTimer::Impl : public QObject
{
    Q_OBJECT
public:
    Impl(ITimerCallBack& tc) : callBackObject(tc), timer(nullptr) {
        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, this, &CustomTimer::Impl::timerExpired);
    }

    ITimerCallBack& callBackObject;
    QTimer *timer;

public slots:
    void timerExpired() {
        callBackObject.callBack();
    }
};

CustomTimer::CustomTimer(ITimerCallBack& tc) 
    : pimpl(new Impl(tc)) {}

CustomTimer::~CustomTimer() {
    delete pimpl;
}

void CustomTimer::startTimer() {

    pimpl->timer->start(40);
}

void CustomTimer::stopTimer(){
    pimpl->timer->stop();
    pimpl->callBackObject.callBack();
}

// Q_OBJECT macro placed in .cpp file instead of header file.
// For the Meta-Object Compiler to reference the CustomTimer class containing
// the Q_OBJECT macro, it needs to see the full class declaration.
// Source files are processed sequentially by the compiler, so we need to place the
// MOC generated code after the CustomTimer class declaration.
#include "CustomTimer.moc"