//
// Created by Christian Hunter on 10/21/18.
//

#ifndef PA_5_TASK_H
#define PA_5_TASK_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::cout;

class Task {

public:

    Task();
    Task(int id, string desc, int procs, int ticks);
    ~Task();
    int getJob_id() const;

    void setJob_id(int job_id);

    const string &getJob_description() const;

    void setJob_description(const string &job_description);

    int getN_procs() const;

    void setN_procs(int n_procs);

    int getN_ticks() const;

    void setN_ticks(int n_ticks);

    int getRunTime() const;

    void setRunTime(int runTime);

    bool operator<(const Task &rhs) const;

    bool operator>(const Task &rhs) const;

    bool operator<=(const Task &rhs) const;

    bool operator>=(const Task &rhs) const;

    void decrementRunTime();
private:
    int job_id;
    string job_description;
    int n_procs;
    int n_ticks;
    int runTime;

};

istream &operator>> (istream &lhs, Task &rhs);
ostream &operator<< (ostream &lhs, Task &rhs);
#endif //PA_5_TASK_H

