#include "truck.h"
#include<iostream>
#include<time.h>

int truck::numberofjournies = 0;
truck::truck(int sped, int cap, int checkup, int typ, int idd)
{
	speed = sped;
	capacity = cap;
	checkupduration = checkup;
	type = typ;
	id = idd;
	beingloaded = 0;
	cargotype = -1;
	maxdistance = -1;
	numberofjourniesdone = 0;
	maxw = false;
	totalloadingtime = 0;
	totalcargodelivered = 0;
	totaltruckactivetime = 0;
	timespentunloading = 0;
}

void truck::setjournies(int x)
{
	numberofjournies = x;
}

int truck::getid()
{
	return id;
}

bool truck::loadcargo(Cargo* crgoptr)
{
	if (beingloaded != 0)
	{
		return false;

	}
	if (maxw&&carriedcargo.count()!=0)
		return false;

	if (carriedcargo.count() >= capacity)
		return false;

	if (cargotype == -1)
	{
		cargotype = crgoptr->gettype();
	}
	else
	{
		if (cargotype != crgoptr->gettype())
			return false;
	}

	carriedcargo.enqueue(crgoptr, (1.0/crgoptr->getdistance()));
	beingloaded = crgoptr->getloadtime();
	totalloadingtime += beingloaded;
	if (crgoptr->getdistance() > maxdistance)
		maxdistance = crgoptr->getdistance();
	return true;
}

bool truck::isfull()
{

	return (capacity==carriedcargo.count())&&(beingloaded==0);
}

float truck::prioritywhilemoving()
{
	return 1.0/((maxdistance / speed)+hourofdepart+24*dayofdepart);
}


bool truck::gotocheckup(int hour, int day)
{
	bool chckup = ((numberofjourniesdone % numberofjournies)==0) && (numberofjourniesdone != 0);
	if (chckup)
	{
		hourofchkup = hour;
		dayofchkup = day;
	}

	return chckup ;
}

void truck::departed(int hour, int day)
{
	hourofdepart = hour;
	dayofdepart = day;
}

bool truck::finishedtrip(int hour, int day)
{
	bool finished = (totalloadingtime + hourofdepart + dayofdepart * 24 + 2*maxdistance / speed) <= (hour + day * 24);
	if (finished)
	{
		totaltruckactivetime += calculateactivetime();
		timespentunloading = 0;
		maxdistance = -1;
		cargotype = -1;
		hourofdepart = 0;
		dayofdepart = 0;
		beingloaded = 0;
		maxw = false;
		numberofjourniesdone++;
		totalloadingtime = 0;
	}
	return finished;
}

bool truck::hasurgentcargo()
{

	return maxw&&(beingloaded==0);
}

int truck::gettype()
{
	return type;
}

bool truck::finishedcheckup(int hour, int day)
{
	
	bool finishedcheckup = ((hour + day * 24) == (checkupduration + hourofchkup + dayofchkup * 24));
	if (finishedcheckup)
	{
		hourofchkup = 0;
		dayofchkup = 0;
	}
	return finishedcheckup;
	
}

void truck::cargodelievery(int hour, int day,Company*cmpnyptr)
{
	Cargo* crgoptr;
	while (carriedcargo.peek(crgoptr))
	{

		if (((1.0*crgoptr->getdistance() / speed )+ (dayofdepart * 24 )+ hourofdepart+timespentunloading+crgoptr->getloadtime()) <= (hour + day * 24))
		{
			carriedcargo.dequeue(crgoptr);
			totalcargodelivered++;
			timespentunloading += crgoptr->getloadtime();
			//ana ba7ot 7aget statistics hna
			crgoptr->setdaydelivered(day);
			crgoptr->sethourdelivered(hour);
			crgoptr->settruckID(id);
			cmpnyptr->movetodelivered(crgoptr,cargotype);
		}
		else
			break;

	}
}

bool truck::failed(Company* cmpnyptr,int hour,int day) //random gdan
{
	bool fail=false;
	if (rand() < 10)   //small chance of failier
		fail = true;
	if (fail)
	{
		Cargo* crgoptr;
		while (carriedcargo.dequeue(crgoptr))
		{
			cmpnyptr->movetowaitingcargo(crgoptr, cargotype);
		}

		totaltruckactivetime += calculateactivetime();
		timespentunloading = 0;
		maxdistance = -1;
		cargotype = -1;
		hourofdepart = 0;
		dayofdepart = 0;
		beingloaded = 0;
		maxw = false;
		numberofjourniesdone++;
		totalloadingtime = 0;
		hourofchkup = hour;
		dayofchkup = day;
		
		
	}

	
	return fail;
}

priorityqueue<Cargo*>* truck::getcargoqueue()
{
	return &carriedcargo;
}

bool truck::startedloading()
{
	return (beingloaded != 0);
}

bool truck::isenoughcargo(int availablecargos, bool waitedmaxw)
{
	if (!waitedmaxw)
	{
		if ((availablecargos + carriedcargo.count()) < capacity)
			return false;
	}
	else
		maxw = true;
	return true;
}

void truck::decrementeloadtime()
{
	if (beingloaded > 0)
		beingloaded--;
}


float truck::calculateactivetime()
{
	return (dayofdepart-dayofstartloading)*24 + (hourofdepart-hourofstartloading) + 1.0 * maxdistance / speed + totalloadingtime; //x2 for loading + unloading
}

float truck::calculateUtilization(int day, int hour)
{
	int totalsimulationtime = day * 24 + hour;
	if (numberofjourniesdone == 0)
		return 0;
	else
	{
		return (((1.0*totalcargodelivered) / (1.0*capacity * numberofjourniesdone)) * (1.0*totaltruckactivetime / totalsimulationtime));
	}
}

float truck::gettotalactivetime()
{
	return totaltruckactivetime;
}

int truck::gettotaljournies()
{
	return numberofjourniesdone;
}

bool truck::finishedloading()
{
	return beingloaded == 0;
}

bool truck::CarriesCargo() const
{
	return !carriedcargo.isempty();
}

void truck::PrintCarriedCargo() const
{
	carriedcargo.print();
}

void truck::StartofLoading(int hour, int day)
{
	if (carriedcargo.count() == 1)
	{
		dayofstartloading = day;
		hourofstartloading = hour;
	}
}

ostream& operator<<(ostream& os, const truck* trck)
{
	if (trck->CarriesCargo())
	{
		if (trck->cargotype == 1)
		{
			cout << trck->id;
			cout << "[";
			trck->PrintCarriedCargo();
			cout << "]";
		}
		else if (trck->cargotype == 2)
		{
			cout << trck->id;
			cout << "(";
			trck->PrintCarriedCargo();
			cout << ")";
		}
		else
		{
			cout << trck->id;
			cout << "{";
			trck->PrintCarriedCargo();
			cout << "}";
		}
	}
	else
		cout << trck->id;
	return os;
	
	
}
