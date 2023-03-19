#pragma once
#include <iostream>
#include "PriorityQ.h"
#include "Cargo.h"
#include "Company.h"
#include <cstdlib>

using namespace std;
class Company;  //loll lets check this later
class truck
{
	int timespentunloading;
	int speed;
	int id;
	int capacity;
	static int numberofjournies;
	int checkupduration;
	int type;  // 1 for normal 2 for special 3 for vip
	priorityqueue<Cargo*> carriedcargo;
	int beingloaded;
	int cargotype;
	float maxdistance;
	int numberofjourniesdone;
	int dayofstartloading;
	int hourofstartloading;
	int dayofdepart;
	int hourofdepart;
	int dayofchkup;
	int hourofchkup;
	bool maxw;
	int totalloadingtime;
	int totalcargodelivered;
	float totaltruckactivetime;

public:
	truck(int sped, int cap, int checkup, int typ, int idd);
	static void setjournies(int x);
	int getid();
	friend ostream& operator<<(ostream& os, const truck* trck);
	bool loadcargo(Cargo* crgoptr);
	bool isfull();
	float prioritywhilemoving();
	bool gotocheckup(int hour,int day);
	void departed(int hour, int day);
	bool finishedtrip(int hour, int day);
	bool hasurgentcargo();
	int gettype();
	bool finishedcheckup(int hour, int day);
	void cargodelievery(int hour, int day,Company*cmpnyptr);
	bool failed(Company* cmpnyptr,int hour,int day);
	priorityqueue<Cargo*>* getcargoqueue();
	bool startedloading();
	bool isenoughcargo(int availablecargos, bool waitedmaxw);
	void decrementeloadtime();
	float calculateactivetime();
	float calculateUtilization(int day, int hour);
	float gettotalactivetime();
	int gettotaljournies();
	bool finishedloading();
	bool CarriesCargo() const;
	void PrintCarriedCargo() const;
	void StartofLoading(int hour, int day);
};