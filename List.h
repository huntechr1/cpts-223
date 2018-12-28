#include "ListNode.h"
#include <iostream>

using std::cout;
using std::endl;

class List
{
public:

List();
~List();
ListNode *getHeadPtr() const;
ListNode *getTailPtr() const;
void insertInOrder(const int newData);
void insertAtFront(const int newData);
void insertAtTail(const int newData);
ListNode *makeNode(const int newData);
void printList() const;
int getMax() const;
int getMin() const;
int getMedian() const;
int getNodes() const;
void destroyList();
private:

ListNode *pHead;
ListNode *pTail;
int nodes;

};
