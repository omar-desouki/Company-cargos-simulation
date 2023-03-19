#pragma once
#include "Event.h"


class CancelEvent:public Event
{
private:
	int ID;

public:
	CancelEvent(int id, int eventday, int eventhour,  Company* compptr);

	~CancelEvent();

	void Execute();
};

