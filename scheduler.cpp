//
// Created by Christian Hunter on 10/21/18.
//

#include "scheduler.h"


// Constructor which doesn't initialize number of processors
// Not used
Scheduler::Scheduler()
{
    this->p = 0;

    this->input_Fstr.open("input.txt");
    if(!this->input_Fstr.is_open())
    {
        do{
            std::string temp;
            cout << "Enter a valid file name" << endl;
            cin >> temp;
            this->input_Fstr.open(temp);
        }while(!this->input_Fstr.is_open());
    }

    srand((unsigned int)time(nullptr));
}

// Constructor which initializes with a number of processors and whether or not to open a file
// If method == 1 then attempt to open a file else don't use a file
// Also seeds a random number generator
Scheduler::Scheduler(int _p, int method)
{
    this->p = _p;
    this->usedP = 0;

    if(method == 1)
    {
    std::string temp;

    this->input_Fstr.open("input.txt");

    // Loop until a valid file name is entered and a file is opened
    if(!this->input_Fstr.is_open())
    {
        do{
            cout << "Enter a valid file name" << endl;
            cin >> temp;
            this->input_Fstr.open(temp);
        }while(!this->input_Fstr.is_open());
    }
    }

    // seed random number generator
    srand((unsigned int)time(nullptr));
}

// Deconstructor which closes the file if opened
Scheduler::~Scheduler()
{
    this->input_Fstr.close();
}

// Function to create a random ID number which isn't currently being used
// returns the new ID number
int Scheduler::createID()
{
    std::pair<std::set<int>::iterator, bool> pair;
    int tempID = 0;

    do {
        tempID = rand();
        //cout << temp << endl;
        pair = this->availIDs.emplace(tempID);

        // pair.second is a bool which represents whether tempID was inserted or no
        // Loop until an ID was inserted
    } while (!pair.second);

    cout << "------------------------------------" << endl;
    cout << "New unique ID: " << tempID << endl;

    // return new ID
    return tempID;
}

// Prints every ID being used in the ID set
void Scheduler::printIDs()
{
    std::set<int>::iterator it;
    int i = 1;
    for(it = this->availIDs.begin(); it != this->availIDs.end(); it++)
    {
        cout << "Number: " << i << " ID: ";
        cout << *it << endl;
        i++;
    }
}


// Inserts a task into the waitQueue priority_queue
void Scheduler::insert(Task t)
{
    this->waitQueue.push(t);
}

// Removes the top task from the waitQueue priority_queue
// returns the removed task
Task Scheduler::getTask()
{
    Task temp;
    temp.setJob_description(waitQueue.top().getJob_description());
    temp.setJob_id(waitQueue.top().getJob_id());
    temp.setN_procs(waitQueue.top().getN_procs());
    temp.setN_ticks(waitQueue.top().getN_ticks());
    temp.setRunTime(waitQueue.top().getRunTime());

    this->waitQueue.pop();

    return temp;
}

// Transfers a task from the waitQueue to the runningQueue
// Updates number of processors being used
void Scheduler::moveToRunning()
{
    Task temp = this->getTask();
    this->usedP += temp.getN_procs();
    this->runningQueue.push_back(temp);
    this->newRunning.emplace_back(temp);
}

// Decrements the run time for all tasks in the runningQueue
// If a tasks runtime becomes zero an iterator to that task is placed in the
// toBeRemoved vector
void Scheduler::decrementTimer()
{
    for(std::list<Task>::iterator it = runningQueue.begin(); it != runningQueue.end(); it++)
    {
        it->decrementRunTime();
        if(it->getRunTime() <= 0)
        {
            toBeRemoved.emplace_back(it);
        }
    }
}

// Prints the number of ticks for all tasks in the runningQueue
void Scheduler::printTicks()
{
    for(std::list<Task>::iterator it = runningQueue.begin(); it != runningQueue.end(); it++)
    {
        cout << "# of ticks: " << it->getN_ticks() << endl;
    }
}

// Function which handles all main scheduler functionality
// inputs new job if valid
// decrements runtimes
// removes finished jobs
// transfers jobs from waitQueue to runningQueue if allowed
// Returns true if still reading jobs from a file, false if not
bool Scheduler::tick()
{
    bool reading = false;

    Task tempTask;

    // If a new task can be read from a file then enter if statement
    if (this->input_Fstr >> tempTask)
    {
        reading = true;

        // If task is valid then create ID and insert into waitQueue
        if (this->checkValid(tempTask))
        {
            tempTask.setJob_id(this->createID());
            this->insert(tempTask);
        }
    }

    // If the runningQueue isn't empty then decrement runtimes and release any finished jobs
    if(!this->runningQueue.empty())
    {
        this->decrementTimer();
        this->releaseProcs();
    }

    // Loop until either waitQueue is empty or there is no more processors available
    // if succesful moves the next job in the waitQueue into the runningQueue
    while(!this->waitQueue.empty() && this->checkAvailability())
    {
        this->moveToRunning();
    }

    return reading;

}

// Function which handles all main scheduler functionality
// creates new ID's
// inputs new job if valid
// decrements runtimes
// removes finished jobs
// transfers jobs from waitQueue to runningQueue if allowed
void Scheduler::tick(Task task)
{
    // If task is valid then create ID and insert into waitQueue
    if (this->checkValid(task))
    {
        task.setJob_id(this->createID());
        this->insert(task);
    }

    // If the runningQueue isn't empty then decrement runtimes and release any finished jobs
    if(!this->runningQueue.empty())
    {
        this->decrementTimer();
        this->releaseProcs();
    }

    // Loop until either waitQueue is empty or there is no more processors available
    // if succesful moves the next job in the waitQueue into the runningQueue
    while(!this->waitQueue.empty() && this->checkAvailability())
    {
        this->moveToRunning();
    }
}

// Checks whether or not a task is valid and can be inserted into the waitQueue
// return true if valid, false if not
bool Scheduler::checkValid(Task &task)
{
    if(task.getJob_description() == "NULL" || task.getN_procs() > this->p
       || task.getN_procs() <= 0 || task.getN_ticks() <= 0)
    {
        cout << "------------------------------------" << endl;
        cout << "Invalid!" << endl;
        cout << task;
        cout << "------------------------------------" << endl;
        return false;
    }

    else
    {
        return true;
    }
}

// Checks whether their is enough processors available to run the next job in the waitQueue
bool Scheduler::checkAvailability()
{
    bool available = true;
    if(waitQueue.top().getN_procs() > (p - usedP))
    {
        available = false;
        cout << "------------------------------------" << endl;
        cout << "Waiting for more processors" << endl;
    }

    return available;
}

// Removes any jobs found in the toBeRemoved vector from the runningQueue
// Removes eaech jobs ID from the availIDs set
// Does not clear toBeRemoved vector
void Scheduler::releaseProcs()
{
    if(!toBeRemoved.empty())
    {
        cout << "------------------------------------" << endl;
        cout << "Deleted Tasks:" << endl << endl;
        for (unsigned int i = 0; i < toBeRemoved.size(); i++)
        {
            this->usedP -= toBeRemoved[i]->getN_procs();
            cout << *toBeRemoved[i] << endl;
            availIDs.erase(toBeRemoved.at(i)->getJob_id());
            runningQueue.erase(toBeRemoved.at(i));
        }
        cout << "------------------------------------" << endl;
    }

    else
    {
        cout << "------------------------------------" << endl;
        cout << "No items removed" << endl;
        cout << "------------------------------------" << endl;
    }
}

// Prints all tasks found in the runningQueue
void Scheduler::printRunning()
{
    cout << endl << "Printing running jobs....." << endl << endl;
    for(std::list<Task>::iterator it = runningQueue.begin(); it != runningQueue.end(); it++)
    {
        cout << *it << endl;
    }

    cout << endl;
}

// function to determine if waitQueue is empty
// returns true if empty, false if not
bool Scheduler::waitQueueEmpty()
{
    return this->waitQueue.empty();
}

// function to remove every element from toBeRemoved vector
void Scheduler::clearToBeRemoved()
{
    this->toBeRemoved.clear();
}

// Prints all tasks found in toBeRemoved vector
void Scheduler::printDeleted()
{


    cout << "------------------------------------" << endl;
    cout << "Deleted Tasks:" << endl << endl;

    if(!toBeRemoved.empty())
    {
        for (int i = 0; i < toBeRemoved.size(); i++)
        {
            cout << *toBeRemoved[i] << endl;
        }
    }

    else
    {
        cout << "No deletions" << endl;
    }

    cout << "------------------------------------" << endl;
}

// Prints all tasks found in the newRunning vector
void Scheduler::printNewRunning()
{
    cout << "------------------------------------" << endl;
    cout << "Newly Running Tasks:" << endl << endl;

    if(!newRunning.empty())
    {
        for(int i = 0; i < newRunning.size(); i++)
        {
            cout << newRunning[i] << endl;
        }
    }

    else
    {
        cout << "No new running tasks" << endl;
    }

    cout << "------------------------------------" << endl;

}

// Erases all elements from newRunning vector
void Scheduler::clearNewRunning()
{
    this->newRunning.clear();
}

// function to determine whether the runningQueue is empty or not
// return true if empty, false if not
bool Scheduler::runningQueueEmpty()
{
    return this->runningQueue.empty();
}