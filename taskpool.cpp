#include <vector>

#include "task.h"
#include "taskpool.h"

// Task pool implementation
TaskPool::TaskPool(const std::vector<Task>& aTasks, int aProcessorsCount)
{
    const std::vector<Task>::iterator it = aTasks.begin();
    for(; it != aTasks.end(); it++)
       taskProcessors.push_back(TaskProcessor(*it));
}

void TaskPool::start()
{
    std::vector<TaskProcessor>::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it).start();
}

void TaskPool::waitForDone()
{
    std::vector<TaskProcessor>::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it).join();
}

TaskProcessor::TaskProcessor(std::shared_ptr<Task> aTask)
{
    assignTask(aTask);
}

// Task Processor implementation
void TaskProcessor::assignTask(std::shared_ptr<Task> aTask)
{
    task = aTask;
}

void TaskProcessor::run()
{
    task.executeTask();
}
