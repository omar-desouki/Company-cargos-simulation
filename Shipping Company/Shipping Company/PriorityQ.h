#pragma once
#include "Node.h"
template<class t>
class priorityqueue
{
	Node<t>* frontPtr;
	Node<t>* backPtr;
	int counter;
public:
	priorityqueue()
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
	
	void enqueue(const t& item,float priority)
	{
		Node<t>* nptr = new Node<t>(item,priority);
		if (isempty())
		{
			frontPtr = nptr;
			backPtr = nptr;
		}
		else
		{
			if (nptr->getpriority() > frontPtr->getpriority())
			{
				nptr->setnext(frontPtr);
				frontPtr = nptr;
			}
			else 
			{
				Node<t>* p = frontPtr;
				Node<t>* prev;
				while (p->getpriority() >= nptr->getpriority())
				{
					prev = p;
					p = p->getnext();
					if (p == nullptr)
						break;
				}
				prev->setnext(nptr);
				nptr->setnext(p);
				if (p == nullptr)
					backPtr = nptr;
			}
			
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
	priorityqueue(const priorityqueue<t>& LQ)
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
	void print() const
	{
		Node < t >*ptr= frontPtr;
		while (ptr)
		{
			if (ptr->getnext())
			{
				cout << ptr->getitem()<< ", ";
			}
			else
			{
				cout << ptr->getitem();
			}
			ptr = ptr->getnext();
		}
	}
};