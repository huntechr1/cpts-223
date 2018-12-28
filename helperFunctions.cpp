
#include "helperFunctions.h"

int readFile(vector<int> &a, fstream &str)
{
	int items = 0;
	while(str >> a)
	{
		++items;
		//cout << "reading file" << endl;
	}
	return items;
}

fstream &operator>> (fstream &lhs, vector<int> &rhs)
{
	char temp[100] = "\0";
	lhs.getline(temp, 100);

	if(temp[0] != '\0')
	rhs.push_back(atoi(temp));

	return lhs;
}

void printList(const vector<int> &list)
{
	for(int i = 0; i < list.size(); ++i)
	{
		cout << list[i] << endl;
	}
}

void stringCpy(char * dest, char* src)
{
	int i = 0;
	for(; src[i] != '\0'; ++i)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

bool findStr(char *src[], char *comp, int size)
{
	bool found = false;
	for(int i = 0; i < size; ++i)
	{
		cout << src[i] << endl;
		if(strcmp(src[i], comp))
		{
			cout << "true" << endl;
			found = true;
		}
	}
	return found;
}

bool strNCmp(char *str1, char *str2, int n)
{
	bool same = true;
	int i = 0;
	for(; i < n && same == true && str1[i] != '\0' && str2[i] != '\0'; ++i)
	{
		if(str1[i] != str2[i])
		{
			same = false;
		}
	}

	return same;
}

int findFileName(char *src[], char *comp, int size, int compareLen)
{
	int found = 0;
	for(int i = 0; i < size && found == 0; ++i)
	{
		if(strNCmp(src[i], comp, compareLen))
		{
			found = i;
		}
	}
	return found;
}

void changeFileName(char delim, int occurences, char *replacement, char *dest)
{
	int i = 0;
	for(; dest[i] != '\0' && occurences != 0; ++i)
	{
		if(dest[i] == delim)
		{
			occurences--;
		}
	}
	stringCpy(&(dest[i]), replacement);
}

