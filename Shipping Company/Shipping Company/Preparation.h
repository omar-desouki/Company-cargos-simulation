#pragma once
#include "Event.h"
#include "Cargo.h"
class Company;
class Preparation:public Event
{

private:
	Cargo*cargoptr;

public:

	Preparation(char type, int id, int dist, int loadtime, int cost, int eventday,int eventhour, Company* compptr);
	virtual void Execute();
	~Preparation();
};

