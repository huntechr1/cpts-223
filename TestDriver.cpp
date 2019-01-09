//
// Created by Christian Hunter on 10/26/18.
//

/*
 * should it read the file all at once?
 *
 */
#include "scheduler.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(void)
{
    int processors = 0;
    int inputMethod = 0;

    cout << "(1) Manually enter jobs" << endl;
    cout << "(2) Read jobs from file" << endl;
    while(!(cin >> inputMethod))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid: Enter an integer" << endl;
    }

    cout << "Enter available processors: " << endl;
    while(!(cin >> processors))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid: Enter an integer" << endl;
    }

    int i = 0;

    // User inputs jobs
    if(inputMethod == 1)
    {
        Scheduler s(processors, 0);
        string jobDesc = " ";
        Task tempTask;
        int ticks = 0;
        int procs = 0;

        cout << "Enter exit as job description to stop process\nOR\nNULL to not enter a job this tick" << endl << endl;

        do
        {
            cout << "Enter Job description" << endl;
            cin >> jobDesc;

            // If jobDesc == exit leave program
            if(jobDesc != "exit")
            {
                // If jobDesc == NULL don't enter a job
                if(jobDesc != "NULL")
                {
                    cout << "Enter # of ticks: ";
                    cin >> ticks;
                    cout << "Enter # of processors ";
                    cin >> procs;
                    tempTask.setN_ticks(ticks);
                    tempTask.setN_procs(procs);
                    tempTask.setRunTime(ticks);
                }

                else
                {
                    tempTask.setJob_id(0);
                    tempTask.setN_ticks(0);
                    tempTask.setN_procs(0);
                }

                tempTask.setJob_description(jobDesc);
                cout << "<------------------------------------>" << endl << endl;
                cout << endl << "Tick # " << i + 1 << endl;

                // Complete a tick with the new job
                s.tick(tempTask);
                // Print any jobs deleted this tick
                //s.printDeleted();
                // Print any jobs moved to the running queue
                s.printNewRunning();
                // Clear all newly added and deleted from their respective vectors
                s.clearNewRunning();
                s.clearToBeRemoved();
                i++;
                cout << "<------------------------------------>" << endl << endl;
            }
        // Loop as long as jobDesc != exit
        }while(jobDesc != "exit");

        cout << "Exit" << endl;
    }

    // Read all jobs from a file
    else if(inputMethod == 2)
    {
        bool readingFile = true;
        Scheduler s(processors, 1);

        // continue to loop as long as file isn't empty or one of the queues isn't empty
        while(readingFile || !s.waitQueueEmpty() || !s.runningQueueEmpty())
        {
            cout << "Tick # " << i + 1 << endl;
            cout << "<------------------------------------>" << endl << endl;
            readingFile = s.tick();
            // Print any jobs deleted this tick
            //s.printDeleted();
            // Print any jobs moved to the running queue
            s.printNewRunning();
            // Clear all newly added and deleted from their respective vectors
            s.clearNewRunning();
            s.clearToBeRemoved();
            i++;
            cout << "<------------------------------------>" << endl << endl;
        }
    }

    // 1 or 2 was not inputed from run method
    else
    {
        cout << "Invalid input method" << endl;
    }


    return 0;
}
