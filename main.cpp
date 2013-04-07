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

private:

    TTaskArray createTaskArray(int count, int& totalTime)
    {
        TTaskArray tasks;
        for(int i = 0; i < count; i++)
        {
            int sleepTime = (qrand() % 3 + 1) * 1000;
            totalTime += sleepTime;
            tasks.push_back(QSharedPointer<Task>(new ConcreteTask(sleepTime, i)));
        }

        return tasks;
    }

    void printResult(int counter, int totalTime)
    {
        if (counter > 0)
            std::cout << "global count: ["<< counter << "]   avarage time is: ["<< totalTime / counter / 1000.0f << " seconds]" << std::endl;
    }

    void printTestResult(bool passed, int tasksCount)
    {
        std::cout << "test with tasks count " << tasksCount << " ";
        if (passed)
            std::cout << "passed" << std::endl;
        else
            std::cout << "failed" << std::endl;
    }

    bool unitTest1()
    {
        int totalTime = 0;
        int tasksCount = 0;
        TTaskArray tasks = createTaskArray(tasksCount, totalTime);

        {
            TaskPool pool(tasks);
            g_counter = 0;
            pool.start();
        }

        printResult(g_counter, totalTime);

        printTestResult(g_counter == tasksCount, tasksCount);

        return g_counter == tasksCount;
    }

    bool unitTest2()
    {
        int totalTime = 0;
        int tasksCount = 9;
        TTaskArray tasks = createTaskArray(tasksCount, totalTime);

        {
            TaskPool pool(tasks);
            g_counter = 0;
            pool.start();
        }

        printResult(g_counter, totalTime);

        printTestResult(g_counter == tasksCount, tasksCount);

        return g_counter == tasksCount;
    }

    bool unitTest3()
    {
        int totalTime = 0;
        int tasksCount = 10;
        TTaskArray tasks = createTaskArray(tasksCount, totalTime);

        {
            TaskPool pool(tasks);
            g_counter = 0;
            pool.start();
        }

        printResult(g_counter, totalTime);

        printTestResult(g_counter == tasksCount, tasksCount);

        return g_counter == tasksCount;
    }

    bool unitTest4()
    {
        int totalTime = 0;
        int tasksCount = 100;
        TTaskArray tasks = createTaskArray(tasksCount, totalTime);

        {
            TaskPool pool(tasks);
            g_counter = 0;
            pool.start();
        }

        printResult(g_counter, totalTime);

        printTestResult(g_counter == tasksCount, tasksCount);

        return g_counter == tasksCount;
    }

public slots:

    void run()
    {
        std::cout << "starting up..." << std::endl;

#ifdef UNIT_TEST_ENABLED
        unitTest1();
        unitTest2();
        unitTest3();
        unitTest4();
#endif

        int totalTime = 0;
        TTaskArray tasks = createTaskArray(TASKS_COUNT, totalTime);

        {
            TaskPool pool(tasks);
            g_counter = 0;
            pool.start();
        }

        printResult(g_counter, totalTime);

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
