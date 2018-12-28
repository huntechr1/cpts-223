#include "mSubSum.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "helperFunctions.h"

using std::vector;
using std::fstream;
using std::cout;
using std::endl;


int main(int argc, char *argv[])
{

	if(findStr(argv, "-a", argc))
	{
		cout << "found" << endl;
	}
	fstream inputFStr, outputFStr;

	// No filename was provided from the command line
	if(argc <= 1)
	{
			cout << "No file name specified" << endl;
	}

	// Possible file name plus modifier was provided
	// If -m is provided all files from 0 - 9 of the same name will
	// be opened, processed, and results outputed in .csv format to
	// the specified output file which must be the 3rd argument
	else if(findStr(argv, "-m", argc) && argc != 2)
	{
		cout << argv[0] << endl;
		cout << argv[1] << endl;
		cout << argv[2] << endl;
		cout << argv[3] << endl;
		if(findStr(argv, "-m", argc))
		{
			cout << "Why tho" << endl;
		}
		int fileNameIndex = findFileName(argv, "input", argc, 5);

		// If a valid file name is found
		if(fileNameIndex != 0)
		{
			char fileName[100] = "\0"; 
			char *extensions[9] = {"1.txt","2.txt","3.txt",
			"4.txt","5.txt","6.txt","7.txt","8.txt","9.txt"};
			int index = 0;

			// copy file name from argv to a temporary char array
			stringCpy(fileName, argv[fileNameIndex]);

			// Open output file
			outputFStr.open(argv[3]);
			
			// Loop for all 10 files
			do
			{
				cout << fileName << endl;
				inputFStr.open(fileName);
				if(inputFStr.is_open())
				{
				int subSum[4] = {0,0,0,0}, inputSize = 0;
				vector<int> list;
				inputSize = readFile(list, inputFStr);
				printList(list);

				// Perform all 4 algorithms on the data read from the file
				// Calculates the execution time and max subsequence sum 

				cout << std::fixed;
				cout << "Input size: " << inputSize << endl;
				cout << "mSubSum1" << endl;
				auto startTime = std::chrono::system_clock::now();
				subSum[0] = maxSubSum1(list);
				auto endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time1 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[0] << endl;
				cout << "mSubSum1 time: " << time1.count() * 1000000 << " microseconds" << endl;
			
				cout << "mSubSum2" << endl;
				startTime = std::chrono::system_clock::now();
				subSum[1] = maxSubSum2(list);
				endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time2 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[1] << endl;
				cout << "mSubSum2 time: " << time2.count() * 1000000 << " microseconds" << endl;
				
				cout << "mSubSum3" << endl;
				startTime = std::chrono::system_clock::now();
				subSum[2] = maxSubSum3(list);
				endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time3 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[2] << endl;
				cout << "mSubSum3 time: " << time3.count() * 1000000 << " microseconds" << endl;
			
				cout << "mSubSum4" << endl;
				startTime = std::chrono::system_clock::now();
				subSum[3] = maxSubSum4(list);
				endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time4 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[3] << endl;
				cout << "mSubSum4 time: " << time4.count() * 1000000 << " microseconds" << endl;
				
				// output subsequence sum and execution time to .csv file
				outputFStr << subSum[0] << "," << time1.count() * 1000000 << ",,";
				outputFStr << subSum[1] << "," << time2.count() * 1000000 << ",,";
				outputFStr << subSum[2] << "," << time3.count() * 1000000 << ",,";
				outputFStr << subSum[3] << "," << time4.count() * 1000000 << '\n';
				}

				if(index < 9)
				{
				changeFileName('_', 2, extensions[index], fileName);
				}

				inputFStr.close();
				index++;
			}while(index < 10);

		}
		else
		{
			cout << "File not found" << endl;
		}
	}

	else if(findStr(argv, "-a", argc) && argc != 2)
	{
		cout << "-a" << endl;
		int fileNameIndex = findFileName(argv, "input", argc, 5);

		// If a valid file name is found
		if(fileNameIndex != 0)
		{
			char fileName[100] = "\0"; 
			char *extensions[9] = {"1.txt","2.txt","3.txt",
			"4.txt","5.txt","6.txt","7.txt","8.txt","9.txt"};
			int index = 0;
			char *middle[11] = {"8", "16", "32", "64", "128",
		    "256", "512", "1024", "2048", "4096", "8192"};
		    int passes = 0;
			// copy file name from argv to a temporary char array
			stringCpy(fileName, argv[fileNameIndex]);

			// Open output file
			outputFStr.open(argv[3]);
			
			// Loop for all 10 files
			do
			{
				cout << fileName << endl;
				inputFStr.open(fileName);
				if(inputFStr.is_open())
				{
				int subSum[4] = {0,0,0,0}, inputSize = 0;
				vector<int> list;
				inputSize = readFile(list, inputFStr);
				printList(list);

				// Perform all 4 algorithms on the data read from the file
				// Calculates the execution time and max subsequence sum 

				cout << std::fixed;
				cout << "Input size: " << inputSize << endl;
				cout << "mSubSum1" << endl;
				auto startTime = std::chrono::system_clock::now();
				subSum[0] = maxSubSum1(list);
				auto endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time1 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[0] << endl;
				cout << "mSubSum1 time: " << time1.count() * 1000000 << " microseconds" << endl;
			
				cout << "mSubSum2" << endl;
				startTime = std::chrono::system_clock::now();
				subSum[1] = maxSubSum2(list);
				endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time2 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[1] << endl;
				cout << "mSubSum2 time: " << time2.count() * 1000000 << " microseconds" << endl;
				
				cout << "mSubSum3" << endl;
				startTime = std::chrono::system_clock::now();
				subSum[2] = maxSubSum3(list);
				endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time3 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[2] << endl;
				cout << "mSubSum3 time: " << time3.count() * 1000000 << " microseconds" << endl;
			
				cout << "mSubSum4" << endl;
				startTime = std::chrono::system_clock::now();
				subSum[3] = maxSubSum4(list);
				endTime = std::chrono::system_clock::now();
				std::chrono::duration<double> time4 = endTime - startTime;
				cout << "Maximum subsequence sum: " << subSum[3] << endl;
				cout << "mSubSum4 time: " << time4.count() * 1000000 << " microseconds" << endl;
				
				// output subsequence sum and execution time to .csv file
				outputFStr << subSum[0] << "," << time1.count() * 1000000 << ",,";
				outputFStr << subSum[1] << "," << time2.count() * 1000000 << ",,";
				outputFStr << subSum[2] << "," << time3.count() * 1000000 << ",,";
				outputFStr << subSum[3] << "," << time4.count() * 1000000 << '\n';
				}

				if(index < 9)
				{
				changeFileName('_', 2, extensions[index], fileName);
				}
				else if(index == 9)
				{
					changeFileName('_', 1, middle[passes], fileName);
					++passes;
					changeFileName('_', 2, extensions[0], fileName);
				}
				inputFStr.close();
				index++;
			}while(passes < 11);

		}
		else
		{
			cout << "File not found" << endl;
		}
	}
	// Only filename was provided
	else
	{
		// open file with command line supplied string
		inputFStr.open(argv[1]);
		if(inputFStr.is_open())
		{
			int subSum[4] = {0,0,0,0}, inputSize = 0;
			vector<int> list;
			inputSize = readFile(list, inputFStr);
			//printList(list);

			// Perform all 4 algorithms on the data read from the file
			// Calculates the execution time and max subsequence sum
			// Prints data to the screen 			
			cout << std::fixed;
			cout << "Input size: " << inputSize << endl;
			cout << "mSubSum1" << endl;
			auto startTime = std::chrono::system_clock::now();
			subSum[0] = maxSubSum1(list);
			auto endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> time1 = endTime - startTime;
			cout << "Maximum subsequence sum: " << subSum[0] << endl;
			cout << "mSubSum1 time: " << time1.count() * 1000000 << " microseconds" << endl;
			
			cout << "mSubSum2" << endl;
			startTime = std::chrono::system_clock::now();
			subSum[1] = maxSubSum2(list);
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> time2 = endTime - startTime;
			cout << "Maximum subsequence sum: " << subSum[1] << endl;
			cout << "mSubSum2 time: " << time2.count() * 1000000 << " microseconds" << endl;
			
			cout << "mSubSum3" << endl;
			startTime = std::chrono::system_clock::now();
			subSum[2] = maxSubSum3(list);
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> time3 = endTime - startTime;
			cout << "Maximum subsequence sum: " << subSum[2] << endl;
			cout << "mSubSum3 time: " << time3.count() * 1000000 << " microseconds" << endl;
			
			cout << "mSubSum4" << endl;
			startTime = std::chrono::system_clock::now();
			subSum[3] = maxSubSum4(list);
			endTime = std::chrono::system_clock::now();
			std::chrono::duration<double> time4 = endTime - startTime;
			cout << "Maximum subsequence sum: " << subSum[3] << endl;
			cout << "mSubSum4 time: " << time4.count() * 1000000 << " microseconds" << endl;
			inputFStr.close();
		}

	}
	

	return 0;
}

