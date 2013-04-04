#ifndef TASKPOOL_H
#define TASKPOOL_H

#include <QThread>
#include <vector>
#include <tr1/memory>

#include "task.h"

using namespace std;
using namespace std::tr1;

class TaskProcessor: public QThread
{
    Q_OBJECT
public:
    TaskProcessor(shared_ptr<Task> aTask);

    void assignTask(shared_ptr<Task> aTask);

protected:
    void run();

private:
    shared_ptr<Task> task;
 };

class TaskPool
{
public:
    TaskPool(vector<shared_ptr<Task> >& aTasks, int aProcessorsCount = 1);
    ~TaskPool();

    void start();

    void waitForDone();

private:
    vector<shared_ptr<TaskProcessor> > taskProcessors;
};

#endif // TASKPOOL_H
