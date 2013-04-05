#include <QThread>
#include <QTime>
#include <QtCore/QCoreApplication>

#include "Task.h"

int g_counter = 0;
QMutex g_counterMutex;

// add your implementation here...

static void delay(int milliseconds)
{
    QTime dieTime= QTime::currentTime().addMSecs(milliseconds);
    // Give execution time to the system
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void ConcreteTask::executeTask()
{
    // Use mutex to be thread safe
    g_counterMutex.lock();
    g_counter++;
    g_counterMutex.unlock();

    delay(_milliseconds);
}
