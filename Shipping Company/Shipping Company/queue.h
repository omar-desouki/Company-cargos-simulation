#pragma once
#include "Node.h"
template<class t>
class queue
{
	Node<t>* frontPtr;
	Node<t>* backPtr;
	int counter;
public:
	queue()
	{
		frontPtr = nullptr;
		backPtr = nullptr;
		counter = 0;
	}
	bool isempty() const
	{
		if (frontPtr)
			return false;
		return true;
	}
	void enqueue(const t &item)
	{
		Node<t>* nptr = new Node<t>(item);
		if (isempty())
		{
			frontPtr = nptr;
			backPtr = nptr;
		}
		else
		{
			
			backPtr->setnext(nptr);
			backPtr = nptr;
		}
		counter++;
	}
	bool dequeue(t& it)
	{
		if (isempty())
			return false;
		counter--;
		if (frontPtr == backPtr)
		{
			it = frontPtr->getitem();
			delete frontPtr;
			frontPtr = nullptr;
			backPtr = nullptr;
			return true;
		}
		it = frontPtr->getitem();
		Node<t>* temp = frontPtr->getnext();
		delete frontPtr;
		frontPtr = temp;
		return true;
	}
	bool peek(t& it)
	{
		if (isempty())
			return false;
		it = frontPtr->getitem();
		return true;
	}
	int count()
	{
		return counter;
	}
	//copy constructor
	queue(const queue<t>& LQ)
	{
		Node<t>* NodePtr = LQ.frontPtr;
		if (!NodePtr) //LQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		Node<t>* ptr = new Node<t>(NodePtr->getitem());
		frontPtr = backPtr = ptr;
		NodePtr = NodePtr->getnext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<t>* ptr = new Node<t>(NodePtr->getitem());
			backPtr->setnext(ptr);
			backPtr = ptr;
			NodePtr = NodePtr->getnext();
		}
	}

	void print()
	{
		Node < t>*ptr = frontPtr;
		while (ptr)
		{
			if (ptr->getnext())
			{
				cout << ptr->getitem() << ", ";
			}
			else
			{
				cout << ptr->getitem();
			}
			ptr = ptr->getnext();
		}
	}

	
};