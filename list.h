#pragma once
#include"slot.h"
typedef slot itemType;

struct NodeType;
typedef NodeType* NodePtr;

struct NodeType
{
	itemType component;
	NodePtr link;
};

class list
{
public:
	list();
	void Insert(itemType item);
	void Delete(itemType item);
	void ResetList();
	//itemType* getNextItem();
	itemType* giveCurrent();
	void shiftIndex();

	void printlist();

	int getLength() const;
	bool isEmpty() const;
	bool isFull() const;
	bool isThere(itemType item) const;
	bool hasNext() const;

private:
	NodePtr dataPtr;
	NodePtr currentPos;
	NodePtr lastPtr;
	int length;
};
