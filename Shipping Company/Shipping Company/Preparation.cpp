#include "Preparation.h"
Preparation:: Preparation(char type, int id, int dist, int loadtime, int cost, int eventday,int eventhour, Company* compptr) : Event(eventday,eventhour, compptr)
{
	cargoptr = new Cargo(type, id, dist, loadtime, cost,eventhour,eventday);
}


void Preparation:: Execute()
{
	if (cargoptr->gettype() == 3)
	{
		CompanyPtr->AddCargo(cargoptr, cargoptr->calcprio());
		return;

	}
	CompanyPtr->AddCargo(cargoptr);
}


Preparation::~Preparation()
{
}
