#pragma once
#include "Event.h"
#include "Cargo.h"

class PromoteEvent:public Event
{
private:
int ID;
int extramoney;


public:
	PromoteEvent(int id, int extra, int eventday, int eventhour, Company* compptr);
	void Execute();
	~PromoteEvent();
};

