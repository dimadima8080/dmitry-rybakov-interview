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

class TaskPool
{
public:
    TaskPool(TTaskArray& aTasks, size_t aProcessorsCount = TASK_PROCESSOR_THREADS);
    ~TaskPool();

    void start();

    void waitForDone();

    QSharedPointer<Task> getNextTask();

private:
    TTaskProcessorArray  taskProcessors;
    TTaskArray::iterator taskNextIt;
    TTaskArray::iterator taskNextEndIt;
    QMutex				 taskNextItMutex;
};

class TaskProcessor: public QThread
{
    Q_OBJECT
public:
    TaskProcessor(TaskPool& aTaskPool);

protected:
    void run();

private:
    void assignTask(QSharedPointer<Task> aTask);

private:
    QSharedPointer<Task>    task;
    TaskPool&               taskPool;
};

#endif // TASKPOOL_H
