//
// Created by Christian Hunter on 10/21/18.
//

#ifndef PA_5_SCHEDULER_H
#define PA_5_SCHEDULER_H

#include "Task.h"
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::fstream;
using std::cin;

class Scheduler
{
public:
    Scheduler();
    Scheduler(int _p, int method);

    ~Scheduler();

    int createID();
    void printIDs();
    void insert(Task t);
    Task getTask();
    void moveToRunning();
    void decrementTimer();
    void printTicks();
    bool tick();
    void tick(Task task);
    bool checkValid(Task &task);
    bool checkAvailability();
    void releaseProcs();
    void printRunning();
    bool waitQueueEmpty();
    void clearToBeRemoved();
    void printDeleted();
    void printNewRunning();
    void clearNewRunning();
    bool runningQueueEmpty();

private:
    int usedP;
    int p;
    std::set<int> availIDs;
    std::list<Task> runningQueue;
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> waitQueue;
    std::vector<std::list<Task>::iterator> toBeRemoved;
    std::vector<Task> newRunning;
    fstream input_Fstr;
};
#endif //PA_5_SCHEDULER_H
