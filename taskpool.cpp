#include <vector>

#include "task.h"
#include "taskpool.h"

// Task pool implementation
TaskPool::TaskPool(TTaskArray& aTasks, int /*aProcessorsCount*/)
{
    TTaskArray::iterator it = aTasks.begin();
    for(; it != aTasks.end(); it++)
    {
        taskProcessors.push_back(QSharedPointer<TaskProcessor>(new TaskProcessor(*it)));
    }
}

TaskPool::~TaskPool()
{
    waitForDone();
}

void TaskPool::start()
{
    TTaskProcessorArray::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it)->start();
}

void TaskPool::waitForDone()
{
    TTaskProcessorArray::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it)->wait();
}

TaskProcessor::TaskProcessor(QSharedPointer<Task> aTask)
{
    assignTask(aTask);
}

// Task Processor implementation
void TaskProcessor::assignTask(QSharedPointer<Task> aTask)
{
    task = aTask;
}

void TaskProcessor::run()
{
    task->executeTask();
}
