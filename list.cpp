#include "list.h"
#include <iostream>
#include <cstddef>

using namespace std;

list::list()
{
	dataPtr = NULL;
	currentPos = dataPtr;
	length = 0;
	lastPtr = NULL;
}

void list::printlist()
{
	NodeType * tmp = dataPtr;
	while (tmp != NULL)
	{
		if (tmp->component.getDisplay() == LETTER)
		{
			cout << tmp->component.getLetter();
		}
		else
		{
			cout << "_";
		}

		tmp = tmp->link;
	}
}

void list::Insert(itemType item)
{
	NodePtr newNodePtr = new NodeType;
	newNodePtr->component = item;
	newNodePtr->link = NULL;
	if (lastPtr == NULL)
	{
		dataPtr = newNodePtr;
	}

	else
	{
		lastPtr->link = newNodePtr;
	}
	lastPtr = newNodePtr;
	length++;
}

void list::Delete(itemType item)
{
	NodePtr prevPtr = NULL;
	NodePtr currPtr = dataPtr;
	while (currPtr != NULL && currPtr->component.getLetter() != item.getLetter())
	{
		prevPtr = currPtr;
		currPtr = currPtr->link;
	}
	if (currPtr != NULL)
	{
		if (currPtr == dataPtr)
		{
			dataPtr = currPtr->link;
		}
		else
		{
			prevPtr->link = currPtr->link;
		}
		if (currPtr == lastPtr)
		{
			lastPtr = prevPtr;
		}
		delete currPtr;
		length--;
	}
}

void list::ResetList()
{
	currentPos = dataPtr;
}

/*itemType* list::getNextItem()
{
	itemType* item = &currentPos->component;
	if (currentPos != NULL)
		currentPos = currentPos->link;

	return item;
}*/

itemType* list::giveCurrent()
{
	itemType* item = &currentPos->component;
	return item;
}

void list::shiftIndex()
{
	if (currentPos != NULL)
	{
		currentPos = currentPos->link;
	}
}

int list::getLength() const { return length; }
bool list::isEmpty() const { return (dataPtr == NULL); }
bool list::hasNext() const { return (currentPos != NULL); }
bool list::isFull() const { return false; }

bool list::isThere(itemType item) const
{
	NodePtr currPtr = dataPtr;

	while (currPtr != NULL && currPtr->component.getLetter() != item.getLetter())
	{
		currPtr = currPtr->link;
	}
	if (currPtr != NULL)
	{
		return true;
	}

	else
	{
		return false;
	}
}
