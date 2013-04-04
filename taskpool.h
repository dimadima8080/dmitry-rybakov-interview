#ifndef TASKPOOL_H
#define TASKPOOL_H

#include <QThread>
#include <vector>
#include <memory>

struct Task;

class TaskProcessor: public QThread
{
    Q_OBJECT
public:
    TaskProcessor(std::shared_ptr<Task> aTask);

    void assignTask(std::shared_ptr<Task> aTask);

protected:
    void run();

private:
    std::shared_ptr<Task> task;
 };

class TaskPool
{
public:
    TaskPool(const std::vector<Task>& aTasks, int aProcessorsCount = 1);

    void start();

    void waitForDone();

private:
    std::vector<TaskProcessor> taskProcessors;
};

#endif // TASKPOOL_H
