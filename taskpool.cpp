#include <vector>

#include "task.h"
#include "taskpool.h"

// Task pool implementation
TaskPool::TaskPool(std::vector<shared_ptr<Task> >& aTasks, int /*aProcessorsCount*/)
{
    std::vector<shared_ptr<Task> >::iterator it = aTasks.begin();
    for(; it != aTasks.end(); it++)
    {
        taskProcessors.push_back(shared_ptr<TaskProcessor>(new TaskProcessor(*it)));
    }
}

TaskPool::~TaskPool()
{
    waitForDone();
}

void TaskPool::start()
{
    std::vector<shared_ptr<TaskProcessor> >::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it)->start();
}

void TaskPool::waitForDone()
{
    std::vector<shared_ptr<TaskProcessor> >::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it)->wait();
}

TaskProcessor::TaskProcessor(shared_ptr<Task> aTask)
{
    assignTask(aTask);
}

// Task Processor implementation
void TaskProcessor::assignTask(shared_ptr<Task> aTask)
{
    task = aTask;
}

void TaskProcessor::run()
{
    task->executeTask();
}
