#ifndef __TASK_H
#define __TASK_H

// example stub header for Tasks, use this as a basis to complete the interview questions

/*
 * A Task represents a unique chunk of work, the milliseconds member variable provides 
 * the amount of time a task should wait in executeTask.
 */
struct Task {
        int _milliseconds;
        virtual void executeTask() = 0;
};

extern int g_counter;

#endif

