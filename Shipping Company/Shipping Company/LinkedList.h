#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	
	int itemCount;

public:
	LinkedList()
	{
		Head = nullptr;
		itemCount = 0;
	}

	bool isEmpty() const
	{
		return (Head == nullptr);
	}

	int getlength() const
	{
		return itemCount;
	}

	void Insert(const T& it)
	{
			Node<T>* newNodePtr = new Node<T>(it);
			if (!Head)
			{
				newNodePtr->setnext(Head);
				Head = newNodePtr;
				itemCount++;
				return;
			}
			Node<T>*temp = Head;
			while (temp->getnext())
			{
				temp->getnext();
			}
			temp->setnext(newNodePtr);
			itemCount++;
	}

	bool Remove(const T& it)
	{
		Node<T>*temp = Head;
		if (!Head)
			return false;

		if (Head->getitem() == it)
		{
			Head = Head->getnext();
			delete temp;
			return true;
		}
		while (temp->getnext())
		{
			if (temp->getnext() == it)
			{
				Node<T>*remove = temp->getnext();
				temp->setnext(temp->getnext()->getnext());
				delete remove;
			}
			temp = temp->getnext();
		}
	}

	T getEntry(const T&item) const
	{
		Node<T>*temp = Head;
		while (temp)
		{
			if (temp == item)
				return item;
		}
		return 0;
	}

	void Clear()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getnext();
			delete Head;
			Head = P;
		}
	}

	~LinkedList()
	{
		Clear();
	}
};