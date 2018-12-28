#include "ListNode.h"

// Constructor which sets data members to a known value
ListNode::ListNode()
{
this->data = 0;
this->pNext = nullptr;
}

// Constructor which copies a different nodes data into a new node
ListNode::ListNode(const ListNode &newNode)
{
this->data = newNode.data;
this->pNext = newNode.pNext;
}

// constructor which sets new data but doesn't effect the next pointer
ListNode::ListNode(const int newData)
{
this->data = newData;
this->pNext = nullptr;
}

// deconstructor
ListNode::~ListNode()
{
}

// Sets the data within the node
void ListNode::setData(const int newData)
{
this->data = newData;
}

// Sets the next pointer within a node
void ListNode::setNextPtr(ListNode * const nextPtr)
{
this->pNext = nextPtr;
}

// Returns the data found within the node
int ListNode::getData() const
{
return this->data;
}

// Returns the next pointer within the node
ListNode *ListNode::getNextPtr() const
{
return this->pNext;
}

/*ListNode ListNode::operator= (const ListNode &rhs) const
{
*/
