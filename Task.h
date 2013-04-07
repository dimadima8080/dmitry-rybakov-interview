#ifndef __TASK_H
#define __TASK_H

// example stub header for Tasks, use this as a basis to complete the interview questions

#include <QtGlobal>
#include <QMutex>

/*
 * A Task represents a unique chunk of work, the milliseconds member variable provides 
 * the amount of time a task should wait in executeTask.
 */

struct Task
{
    virtual ~Task() {}
    virtual void executeTask() = 0;

    int _milliseconds;
    int _no;
};

struct ConcreteTask: public Task
{
    ~ConcreteTask() {}
    ConcreteTask(int spin_time, int no) { _milliseconds = spin_time; _no = no;}

    void executeTask();
};

extern QMutex g_counterMutex;
extern int g_counter;

#endif

