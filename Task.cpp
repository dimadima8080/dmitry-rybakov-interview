#include <QThread>
#include <QApplication>
#include <QTime>

#include "Task.h"

int g_counter = 0;
QMutex g_counterMutex;

// add your implementation here...

static void delay(int milliseconds)
{
    QTime dieTime= QTime::currentTime().addMSecs(milliseconds);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void ConcreteTask::executeTask()
{
    g_counterMutex.lock();
    g_counter++;
    g_counterMutex.unlock();

    delay(_milliseconds);
}
