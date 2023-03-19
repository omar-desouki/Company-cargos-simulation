#pragma once
template<class t>
class Node
{
	t item;
	Node<t>* next;
	float priority;
public:
	Node()
	{
		next = nullptr;
		priority = -1;
	};
	Node(t it)
	{
		item = it;
		next = nullptr;
		priority = -1;
	}
	Node(t it, float prio)
	{
		item = it;
		next = nullptr;
		priority = prio;
	}
	Node<t>* getnext() const
	{
		return next;
	}
	t getitem() const
	{
		return item;
	}
	void setitem(t it)
	{
		item = it;
	}
	void setnext(Node<t>* nxt)
	{
		next = nxt;
	}
	float getpriority() const
	{
		return priority;
	}
};