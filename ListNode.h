#pragma once

class ListNode
{
public:
ListNode();
ListNode(const ListNode &newNode);
ListNode(const int newData);
~ListNode();
void setData(const int newData);
void setNextPtr(ListNode * const nextPtr);
int getData() const;
ListNode *getNextPtr() const;
//ListNode operator= (const ListNode) const;
private:
int data;
ListNode *pNext;	
};
