#include <vector>
#include <tr1/memory>
#include <iostream>

#include <QApplication>

#include "Task.h"
#include "taskpool.h"

const int TASK_PROCESSOR_THREADS = 10;
const int TASKS_COUNT = 50;

int main(int argc, char *argv[]) {

    // add your implementation here...

    QCoreApplication a(argc, argv);

    std::cout << "starting up...";

    int total_time = 0;
    std::vector<shared_ptr<Task> > tasks;

    for(int i = 0; i < TASKS_COUNT; i++)
    {
        int sleep_time = (qrand() % 3 + 1) * 1000;
        total_time += sleep_time;
        tasks.push_back(shared_ptr<Task>(new ConcreteTask(sleep_time)));
    }

    {
        TaskPool pool(tasks, TASK_PROCESSOR_THREADS);
        pool.start();
    }

    std::cout << g_counter << total_time / g_counter;

    return a.exec();
}
