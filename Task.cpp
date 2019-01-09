//
// Created by Christian Hunter on 10/21/18.
//

#include "Task.h"

Task::Task()
{

}

// Constructor to initialize all values
Task::Task(int id, string desc, int procs, int ticks)
{
    this->job_id = id;
    this->job_description = desc;
    this->n_procs = procs;
    this->n_ticks = ticks;
    this->runTime = ticks;
}

Task::~Task()
{

}

int Task::getJob_id() const {
    return job_id;
}

void Task::setJob_id(int job_id) {
    this->job_id = job_id;
}

int Task::getN_procs() const {
    return n_procs;
}

void Task::setN_procs(int n_procs) {
    this->n_procs = n_procs;
}

int Task::getN_ticks() const {
    return n_ticks;
}

void Task::setN_ticks(int n_ticks) {
    this->n_ticks = n_ticks;
}

const string &Task::getJob_description() const {
    return job_description;
}

void Task::setJob_description(const string &job_description) {
    Task::job_description = job_description;
}

bool Task::operator<(const Task &rhs) const {
    return n_ticks < rhs.n_ticks;
}

bool Task::operator>(const Task &rhs) const {
    return rhs < *this;
}

bool Task::operator<=(const Task &rhs) const {
    return !(rhs < *this);
}

bool Task::operator>=(const Task &rhs) const {
    return !(*this < rhs);
}

// Function to decrease runTime by 1 for a task
void Task::decrementRunTime()
{
    this->runTime--;
}

int Task::getRunTime() const {
    return runTime;
}

void Task::setRunTime(int runTime) {
    this->runTime = runTime;
}

// Overloaded stream extraction operator to read a line from a file into a task
istream &operator>> (istream &lhs, Task &rhs)
{
    char tempStr[100] = " ";
    lhs.getline(tempStr, 100, ' ');
    rhs.setJob_description(string(tempStr));
    lhs.getline(tempStr, 100, ' ');
    rhs.setN_procs(atoi(tempStr));
    lhs.getline(tempStr, 100, '\n');
    rhs.setN_ticks(atoi(tempStr));
    rhs.setRunTime(atoi(tempStr));
    rhs.setJob_id(0);

    return lhs;
}

// Overloaded stream insertion operator to print a task
ostream &operator<< (ostream &lhs, Task &rhs)
{
    lhs << "Job ID: " << rhs.getJob_id() << endl;
    lhs << "Job description: " << rhs.getJob_description() << endl;
    lhs << "# of ticks: " << rhs.getN_ticks() << endl;
    lhs << "# of processors: " << rhs.getN_procs() << endl;
   // lhs << "Runtime: " << rhs.getRunTime() << endl;
    return lhs;
}
