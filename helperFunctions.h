#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::fstream;
using std::vector;

// Reads all integers from the given file and places them into 
// the vector a. Returns the number of items inserted
int readFile(vector<int> &a, fstream &str);

// overloaded stream extraction operator, reads a line from a 
// file and places it into a vector
fstream &operator>> (fstream &lhs, vector<int> &rhs);

// Prints every value in a vector to the screen
void printList(const vector<int> &list);

// Copies one string into another
void stringCpy(char * dest, char* src);

// searches for a specific string among an array of strings
// and returns true if found and false if not
// Must supply the number of strings as well
bool findStr(char *src[], char *comp, int size);

// Compares two strings until it reaches n or gets to the end of a string
// Returns true if they are the same, false if not
bool strNCmp(char *str1, char *str2, int n);

// Searches for a file name in an array of strings
// Returns the index which stores the file name
int findFileName(char *src[], char *comp, int size, int compareLen);

// Appends a different file name based on a delimiter and how 
// many delimiters there are 
void changeFileName(char delim, int occurences, char *replacement, char *dest);
