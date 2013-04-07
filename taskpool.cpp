#include <vector>
#include <iostream>

#include "task.h"
#include "taskpool.h"

// Task pool implementation
TaskPool::TaskPool(TTaskArray& aTasks, size_t aProcessorsCount)
{
    if (aTasks.size() == 0 || aProcessorsCount < 1)
		return;

    size_t processorsCount = aProcessorsCount;
    taskNextIt = aTasks.begin();
    taskNextEndIt = aTasks.end();

    if (aTasks.size() <=  aProcessorsCount)
	{
        processorsCount = aTasks.size();
	}

    for(size_t i = 0; i < processorsCount; i++)
	{
        taskProcessors.push_back(
                    QSharedPointer<TaskProcessor>(new TaskProcessor(*this)));
	}

    std::cout << "total tasks " << aTasks.size() << " and processors " << processorsCount << " created" << std::endl;
}

TaskPool::~TaskPool()
{
    waitForDone();
}

void TaskPool::start()
{
	waitForDone();

    TTaskProcessorArray::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
	{
        (*it)->start();
	}
}

void TaskPool::waitForDone()
{
    TTaskProcessorArray::iterator it = taskProcessors.begin();
    for(; it != taskProcessors.end(); it++)
        (*it)->wait();
}

QSharedPointer<Task> TaskPool::getNextTask()
{
    QSharedPointer<Task> ret;

    taskNextItMutex.lock();
    if (taskNextIt != taskNextEndIt)
    {
        ret = *(taskNextIt++);
    }
    taskNextItMutex.unlock();

    return ret;
}

TaskProcessor::TaskProcessor(TaskPool& aTaskPool):
    taskPool(aTaskPool)
{
}

// Task Processor implementation
void TaskProcessor::assignTask(QSharedPointer<Task> aTask)
{
    task = aTask;
}

void TaskProcessor::run()
{
    bool finished = false;

    QSharedPointer<Task> task;
    while(!finished)
    {
        task = taskPool.getNextTask();
        if (!task.isNull())
        {
            std::cout << "task no " << task->_no << " has acqured by thread " << currentThreadId() << std::endl;
            task->executeTask();
        }
        else
        {
            finished = true;
            std::cout << "thread " << currentThreadId() << " has finished" << std::endl;
        }
    }
}
