#pragma once
#include "queue.h"
#include "PriorityQ.h"
#include "Cargo.h"
#include "LinkedList.h"
#include <fstream>
#include"UI.h"
#include"truck.h"


class UI;
class truck;
class Event;
class Company
{
private:
	UI* userinput;
	int autop;
	int maxw;
	//event list
	queue<Event*> Events;

	//waiting cargo list    
	priorityqueue<Cargo*> VIPCargos;
	queue<Cargo*> SpecialCargos;
	queue<Cargo*> NormalCargos;

	//delivered cargo lists
	queue<Cargo*>NormalDelivered;
	queue<Cargo*>SpecialDelivered;
	queue<Cargo*>VIPDelivered;

	//waiting truck lists
	queue<truck*>waitingnormaltrucks;
	queue<truck*>waitingspecialtrucks;
	queue<truck*>waitingviptrucks;

	//Loading Trucks
	truck* viploadingtruck;
	truck* specialloadingtruck;
	truck* normalloadingtruck;
	
	priorityqueue<truck*>movingtrucks;
	
	//InCheckup
	queue<truck*>Checkupnormal;
	queue<truck*>Checkupspecial;
	queue<truck*>Checkupvip;

	//hagat el statistics
	int ncargocont;
	int vcargocont;
	int scargocont;
	int ntruckcont;
	int ncargocontorg;
	int vtruckcont;
	int struckcont;
	int autopromotedcont;
	float truckstotalactivetime;
	int totaltruckjournies;
	float totalutilization;

	int finishedday;
	int finishedhour;

public:
	Company();
	~Company();
	void readinput(string s);
	void outputfile(string s);
	void simulate();
	void AddCargo(Cargo*ptr, float prio=0);
	void cancel(int id);
	void Promote(int id, int extra);
	bool isfinished();
	void movetodelivered(Cargo*ptr,int type);
	void truckschanging(int day,int hour);
	void assign(int day, int hour);
	void movingtruckscargo(int day, int hour);
	int getcountloading();
	void movingtrucksfail(int hour,int day);
	void autopromote(int day,int hour);
	void calculateTruckUtilization(int day, int hour);
	void movetowaitingcargo(Cargo* ptr, int type);


	truck* getviploadingtruck();
	truck* getspecialloadingtruck();
	truck* getnormalloadingtruck();
	queue<Cargo*>* getwaitingnormal();
	queue<Cargo*>* getdeliverednormal();
	queue<Cargo*>* getwaitingspecial();
	queue<Cargo*>* getdeliveredspecial();
	queue<Cargo*>* getdeliveredvip();
	priorityqueue<Cargo*>* getwaitingvip();

	queue<truck*>* getwaitingnormaltruck();
	queue<truck*>* getwaitingviptruck();
	queue<truck*>* getwaitingspecialtruck();

	queue<truck*>*getCheckupnormal();
	queue<truck*>*getCheckupspecial();
	queue<truck*>*getCheckupvip();

	priorityqueue<truck*>* getmovingtrucks();
};