# Interview Questions

## Problem 1: Multi-threaded producer / consumer.

In our system there are many small tasks to be performed within a single process, each of these tasks take a considerable amount of time to complete and requires a small computation as well as access to shared information.  

In order to make writing this easier, the minimum definition of a task is as follows:
```c++
     struct Task {
          int _milliseconds;
          virtual void executeTask() = 0;
     };
```

This program has one global int counter, which is defined as:
```c++
     int g_counter = 0;
```

Please write a console C++ application (use Qt if you wish), that demonstrates:
  1. a queue of 50 "tasks" that are waiting to be processed, the queue can be created in main.cpp at startup.
  2. a pool of "task processors".  each task processor can run a single task at once.
  3. the executeTask() method must increment a global counter value, and each task *must* sleep for a random time between 1 and 3 seconds.
  4. the main thread of the program must wait until all tasks have been processed.
  5. once all tasks have been processed, output the g_counter value to the console, along with the average time it took per task.

To complete this task, you should deliver the following:
 * A description of the build environment and platform tools you are using, e.g. Microsoft Visual Studio and Windows 7 (just so we know what to use here)
 * Build scripts that are self contained - you can use qmake, makefiles or any other self contained build system.  Your submission will be rejected if you rely on external include directories or other dependancies.  We expect to check out a copy of your repo, and build it easily.
 * A summary of how to build your solution.

It's important that you demonstrate how such a program should be designed and can discuss the tradeoffs between different approaches.  When you finish the console application and believe it works - please let us know.

Bonus Points:
  1. Outline what different approaches can be taken to build the task pool.

