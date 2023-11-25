#pragma once

#include "ITimerCallBack.h"


// When reading instrument data from a test file intead of collecting measurements,
// the Model classes reading data need a way to notify the Controllers that there is no more
// data left to read. QtCmdAdpater is a base class for CommandMgr, so CommandMgr can connect
// and receive signals.
//
// A QTimer can also be created by this class when the start command is received.

// Since our application works with the Qt framework, QTimer is
// the best choice for a timer since it does not create a new thread
// and integrates with the Qt event loop.

class QTimer;
class CustomTimer
{
private:
    class Impl;               // Forward declare the implementation class
    Impl* pimpl;              // Pointer to the implementation

public:
    CustomTimer(ITimerCallBack& tc);
    ~CustomTimer();
    void startTimer();
    void stopTimer();
};