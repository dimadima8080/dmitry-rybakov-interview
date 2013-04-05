#include <vector>
#include <iostream>

#include <QtCore/QCoreApplication>
#include <QTimer>

#include "Task.h"
#include "taskpool.h"

const int TASKS_COUNT = 50;

class TaskFinish : public QObject
{
    Q_OBJECT

public:
    TaskFinish(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run()
    {
        std::cout << "starting up..." << std::endl;

        int total_time = 0;
        TTaskArray tasks;

        for(int i = 0; i < TASKS_COUNT; i++)
        {
            int sleep_time = (qrand() % 3 + 1) * 1000;
            total_time += sleep_time;
            tasks.push_back(QSharedPointer<Task>(new ConcreteTask(sleep_time)));
        }

        {
            TaskPool pool(tasks);
            pool.start();
        }

        std::cout << "global count: ["<< g_counter << "]   avarage time is: ["<< total_time / g_counter / 1000.0f << " seconds]" << std::endl;

        emit finished();
    }

signals:
    void finished();
};

#include "main.moc"

int main(int argc, char *argv[]) {

    // add your implementation here...

    QCoreApplication a(argc, argv);

    TaskFinish *taskFinish = new TaskFinish(&a);

    QObject::connect(taskFinish, SIGNAL(finished()), &a, SLOT(quit()));

    QTimer::singleShot(0, taskFinish, SLOT(run()));

    return a.exec();
}
