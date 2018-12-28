#include "List.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using std::fstream;
using std::cout;
using std::cin;
using std::endl;

class App
{
public:
App();
~App();
void openFile(char* const filename);
void getFileName(char name[]);
List *getList();
void readFile();
bool isOpen() const;
void menu() const;
int getOption() const;
void runApp();

private:
fstream inputFstr;
List inputList;

};

fstream &operator >> (fstream &lhs, char rhs[]);



