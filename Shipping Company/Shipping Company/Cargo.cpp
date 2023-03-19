#include "Cargo.h"

Cargo::Cargo()
{
}



Cargo::Cargo(char typ, int id, int dist, int loadtim, int cst,int hours,int days)
{
	ID = id;
	distance = dist;
	cost = cst;
	loadtime = loadtim;
	hourprepare = hours;
	dayprepare = days;
	if (typ =='N')
		type = 1;
	if (typ == 'V')
		type = 3;
	if (typ == 'S')
		type = 2;

	daywaited=-1;
	hourwaited=-1;
	daydelivered=-1;
	hourdelivered=-1;
	truckID = -1;
}

float Cargo::promote(int extra)
{
	if (type == 1)
	{
		type = 3;
		cost += extra;
		return calcprio();     //will return the priority of the cargo after being vip to move it in the list
	}
}

int Cargo::getid()
{
	return ID;
}

int Cargo::gettype()
{
	return type;
}

int Cargo::gethourprepare()
{
	return hourprepare;
}

int Cargo::getdayprepare()
{
	return dayprepare;
}

int Cargo::gethourwaited()
{
	return hourwaited;
}

int Cargo::getdaywaited()
{
	return daywaited;
}

int Cargo::getdaydelivered()
{
	return daydelivered;
}

int Cargo::gethourdelivered()
{
	return hourdelivered;
}

int Cargo::gettruckID()
{
	return truckID;
}

float Cargo::calcprio()
{
	return (float)(1.0*cost/(distance*loadtime));
}



int Cargo::getdistance() const
{
	return distance;
}

int Cargo::getloadtime() const
{
	return loadtime;
}

int Cargo::timewaited(int hours, int days)
{
	return days * 24 + hours - hourprepare - dayprepare * 24;
}





ostream& operator<<(ostream& os, const Cargo* crgo)
{
	cout << crgo->ID;
	return os;
}



void Cargo::setdaywaited(int day)
{
	daywaited = day;
}



void Cargo::sethourwaited(int hour)
{
	hourwaited = hour;
}

void Cargo::setdaydelivered(int day)
{
	daydelivered = day;
}

void Cargo::sethourdelivered(int hour)
{
	hourdelivered = hour;
}

void Cargo::settruckID(int id)
{
	truckID = id;
}

int Cargo::calccargowait(int day, int hour)
{
	if ((hour - hourprepare)<0)
		return (day - dayprepare) * 24 + -(hour - hourprepare) + loadtime;
	return (day - dayprepare) * 24 + (hour - hourprepare) + loadtime;
}