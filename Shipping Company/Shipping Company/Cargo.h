#pragma once
#include <iostream>
using namespace std;
class Cargo
{
	int type;  //1 normal 2 special 3 vip
	int ID;
	int distance;
	int loadtime;
	int cost;
	int hourprepare;
	int dayprepare;
	int daywaited;
	int hourwaited;
	int daydelivered;
	int hourdelivered;
	int truckID;
public:
	Cargo();
	Cargo(char typ, int id, int dist, int loadtim,int cst,int hours,int days);
	float promote(int extra);
	int getid();
	int gettype();
	int gethourprepare();
	int getdayprepare();
	int gethourwaited();
	int getdaywaited();
	int getdaydelivered();
	int gethourdelivered();
	int gettruckID();
	float calcprio();
	int getdistance() const;
	int getloadtime() const;
	int timewaited(int hours, int days);
	void setdaywaited(int day);
	void sethourwaited(int hour);
	void setdaydelivered(int day);
	void sethourdelivered(int hour);
	void settruckID(int id);
	int calccargowait(int day, int hour);



	friend ostream& operator<<(ostream& os, const Cargo* crgo);
};