#include "List.h"

// Constructor which sets data to a known value
List::List()
{
this->pHead = nullptr;
this->pTail = nullptr;
this->nodes = 0;
}

// Deconstructor which removes all nodes within the current list
List::~List()
{
ListNode *pCur = this->pHead, *pTemp = nullptr;

while(pCur != nullptr)
{
pTemp = pCur;
pCur = pCur->getNextPtr();
delete pTemp;
}
}

// Returns pointer to the head of the list
ListNode *List::getHeadPtr() const
{
return this->pHead;
}

// Returns pointer to the end of the list
ListNode *List::getTailPtr() const
{
return this->pTail;
}

// Inserts a node with integer data type in order into the list
void List::insertInOrder(const int newData)
{
ListNode *pMem = this->makeNode(newData);

// Check for valid allocation of memory
if(pMem != nullptr)
{
	// Check if the current list is empty
	if(this->pHead == nullptr)
	{
	// Only one node in list so pHead and pTail are the same
	this->pHead = pMem;
	this->pTail = pMem;
	}
	// Else list is not empty
	else
	{
	ListNode *pCur = pHead, *pPrev = this->pHead;
	bool found = false;

	// Continue to loop until either the end of the list is reached or
	//  node is inserted
	while(pHead != nullptr && !found)
	{
	// If data found in the new  node is less than the current node in the list and 
	// current node is the first node in the list then insert node at front
	// of the list
	if(pMem->getData() < pCur->getData() && pCur == pHead)
	{
		pMem->setNextPtr(pCur);
		pHead = pMem;
		found = true;
	}
	// else if the new data is less than the current nodes data but pCur is not
	// at the front of the list then insert in place before pCur
	else if(pMem->getData() < pCur->getData())
	{
		pPrev->setNextPtr(pMem);
		pMem->setNextPtr(pCur);
		found = true;
	}
	// insert at the end of the list
	else if(pCur->getNextPtr() == nullptr)
	{
		pCur->setNextPtr(pMem);
		pTail = pMem;
		found = true;
	}
	
	// if node is not inserted than pPrev becomes pCur and pCur advances to 
	// the next node
	else
	{
		pPrev = pCur;
		pCur = pCur->getNextPtr();
	}
	}
	}
}
}
// Inserts a new node at the front of the list
void List::insertAtFront(const int newData)
{
// Empty list
if(this->pHead == nullptr)
{
this->pHead = new ListNode(newData);
this->pTail = pHead;
}

// None empty list
else
{
ListNode *pMem = new ListNode(newData);
pMem->setNextPtr(this->pHead);
this->pHead = pMem;
}
}

// Inserts a node at the end of the list
void List::insertAtTail(const int newData)
{
this->pTail->setNextPtr(new ListNode(newData));
}

// Creates a new node and returns a pointer to it
// Also updates the number of nodes stored in the list class
ListNode *List::makeNode(const int newData)
{
this->nodes += 1;
//cout << "Nodes: " << this->nodes << endl;
ListNode *temp = new ListNode(newData);
return temp;
}

// Prints the entire current list
void List::printList() const
{
ListNode *pCur = this->pHead;

while(pCur != nullptr)
{
cout << pCur->getData() << endl;
pCur = pCur->getNextPtr();
}
}

// Finds the max value in the list
int List::getMax() const
{
    return this->pTail->getData();
}

// Finds the min value in the list
int List::getMin() const
{
    return this->pHead->getData();
}

// Finds the median value in the list
int List::getMedian() const
{
//	cout << "Nodes: " << this->nodes << endl;
    int location = this->nodes / 2;
//	cout << "location: " << location << endl;
    ListNode *pCur = pHead, *pPrev = pHead;
        for (int i = 0; i < location; ++i, pCur = pCur->getNextPtr()) {

        }

    return pCur->getData();
}

// returns the number of nodes found in the list
int List::getNodes() const
{
    return this->nodes;
}

// Destroys and deallocates the current list
void List::destroyList()
{
ListNode *pCur = this->pHead, *pTemp = nullptr;

while(pCur != nullptr)
{
pTemp = pCur;
pCur = pCur->getNextPtr();
delete pTemp;
}
this->pHead = nullptr;
this->pTail = nullptr;
this->nodes = 0;
}





