
#include "App.h"

// Contructor, no data to set in class App
App::App()
{
}
// Deconstructor, no data to handle upon leaving scope
App::~App()
{

}

// Attempts to open a file with the given file name argument
void App::openFile(char * const filename)
{
if(this->inputFstr.is_open())
{
this->inputFstr.close();
}

this->inputFstr.open(filename);
}

// Asks the user for the file name they wish to open, updates the array
void App::getFileName(char name[]) 
{
    cout << "Enter the filename: " << endl;
    cin >> name;
}

// Checks if the file was opened
// return true if open and false if closed
bool App::isOpen() const
{
    if(this->inputFstr.is_open())
    {
	cout << "File open" << endl;
        return true;
    }

    else
    {
	cout << "Failed to open file, try again" << endl;
        return false;
    }
}

// Reads the file until all data is retrieved
// Prints a message every 10000 nodes inserted into the list
void App::readFile()
{
    char str[100] = "\0";
    char const *dot[4] = {".", "..", "...", "...."};
    int i = 0, j = 0;
    while(this->inputFstr >> str)
    {
	if(i % 10000 == 0)
	{
	cout << "Nodes: " << this->inputList.getNodes() << " | Reading File" << dot[j] << endl;
	j++;
	if(j > 3)
	{
	j = 0;
	}
	}
	// Converts the string read from the file into an integer, then inserts
	// in order
        this->inputList.insertInOrder(atoi(str));
	i++;
    }
}

// overloaded stream extraction operator which grabs a line from a file
fstream &operator >> (fstream &lhs, char rhs[])
{
    lhs.getline(rhs, 100);
    return lhs;
}

// Returns a pointer to the list found in the App class
List *App::getList() 
{
    return &(this->inputList);
}

// Prints a start menu for the user
void App::menu() const
{
cout << "Options:" << endl;
cout << "1. Analyze file" << endl << "2. Exit" << endl;
}

// Reads in an integer value from the user, will produce an error message if the incorrect data type is entered and then ask for a new number
int App::getOption() const
{
int choice = 0;
while(!(cin >> choice))
{
cin.clear();
cin.ignore(1000, '\n');
cout << "Invalid: Enter an integer: " << endl;
}
return choice;
}

// Executes the main goal of the program
void App::runApp()
{
int cont = 1;
char name[1000] = "\0";
while(cont == 1)
{
this->menu();
cont = this->getOption();

if(cont == 1)
{

if(this->inputList.getHeadPtr() != nullptr)
{
this->inputList.destroyList();
cout << "Previous list destroyed" << endl;
}

do{
this->getFileName(name);
this->openFile(name);
}while(!this->isOpen());
auto startTot = std::chrono::system_clock::now();
this->readFile();
auto endTot = std::chrono::system_clock::now();
// this->getList()->printList();
int max = 0, min = 0, median = 0;

auto start = std::chrono::system_clock::now();
max = this->getList()->getMax();
auto end = std::chrono::system_clock::now();

auto start1 = std::chrono::system_clock::now();
min = this->getList()->getMin();
auto end1 = std::chrono::system_clock::now();

auto start2 = std::chrono::system_clock::now();
median = this->getList()->getMedian();
auto end2 = std::chrono::system_clock::now();

std::chrono::duration<double> time = end - start;
std::chrono::duration<double> time1 = end1 - start1;
std::chrono::duration<double> time2 = end2 - start2;
std::chrono::duration<double> timeTot = endTot - startTot;

//std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
//max = this->getList()->getMax();
//auto duration = now.time_since_epoch();
//auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
//cout << millis << endl;
cout << std::fixed;
cout << "-------------------------------------" << endl;
cout << "Nodes: " << this->inputList.getNodes() << endl;
cout << "Time_insert: " << timeTot.count() << " seconds"  << endl;
cout << "Max: " << max << " |";
cout << " Time_max: " << time.count() * 1000 << " milliseconds"  << endl;
cout << "Min: " << min << " |";
cout << " Time_min: " << time1.count() * 1000 << " milliseconds" << endl;
cout << "Median: " << median << " |";
cout << " Time_med: " << time2.count() * 1000 << " milliseconds"  << endl;
cout << "-------------------------------------" << endl << endl;
}
}
}



