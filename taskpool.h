#ifndef TASKPOOL_H
#define TASKPOOL_H

#include <QThread>
#include <vector>
#include <QSharedPointer>

#include "task.h"

using namespace std;

const int TASK_PROCESSOR_THREADS = 10;

class Task;
class TaskProcessor;

typedef std::vector<QSharedPointer<Task> > TTaskArray;
typedef std::vector<QSharedPointer<TaskProcessor> > TTaskProcessorArray;

class TaskProcessor: public QThread
{
    Q_OBJECT
public:
    TaskProcessor(QSharedPointer<Task> aTask);

    void assignTask(QSharedPointer<Task> aTask);

protected:
    void run();

private:
    QSharedPointer<Task> task;
 };

class TaskPool
{
public:
    TaskPool(TTaskArray& aTasks, int aProcessorsCount = TASK_PROCESSOR_THREADS);
    ~TaskPool();

    void start();

    void waitForDone();

private:
    TTaskProcessorArray taskProcessors;
};

#endif // TASKPOOL_H
