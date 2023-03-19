#include "Company.h"
#include <fstream>
#include"Preparation.h"
#include"PromoteEvent.h"
#include"CancelEvent.h"

//include the rest

Company::Company()
{
	userinput = new UI();
	viploadingtruck = nullptr;
	specialloadingtruck = nullptr;
	normalloadingtruck = nullptr;
	//hagat el statistics
	ncargocont=0;
	ncargocontorg = 0;
	vcargocont=0;
	scargocont=0;
	ntruckcont=0;
	vtruckcont=0;
	struckcont=0;
	autopromotedcont=0;
	truckstotalactivetime = 0;
	totaltruckjournies = 0;
	totalutilization = 0;
}


Company::~Company()
{
	delete userinput;
}

void Company::readinput(string s)
{
	ifstream file(s+".txt");
	int number[3];
	int speed[3];
	int capacity[3];
	int journy;
	int checkup[3];
	for (int i = 0; i < 3; i++)
	{
		file >> number[i];
	}

	for (int i = 0; i < 3; i++)
	{
		file >> speed[i];
	}
	for (int i = 0; i < 3; i++)
	{
		file >> capacity[i];
	}
	file >> journy;
	for (int i = 0; i < 3; i++)
	{
		file >> checkup[i];
	}
	truck* truckptr;
	for (int i = 0; i < number[0]; i++)
	{
		truckptr = new truck(speed[0], capacity[0], checkup[0], 1,i);
		waitingnormaltrucks.enqueue(truckptr);
		ntruckcont++;
	}
	for (int i = 0; i < number[1]; i++)
	{
		truckptr = new truck(speed[1], capacity[1], checkup[1], 2,number[0]+i);
		waitingspecialtrucks.enqueue(truckptr);
		struckcont++;
	}
	for (int i = 0; i < number[2]; i++)
	{
		truckptr = new truck(speed[2], capacity[2], checkup[2], 3,number[0]+number[1]+i);
		waitingviptrucks.enqueue(truckptr);
		vtruckcont++;
	}
	truck::setjournies(journy);

	int x;
	file >> x;
	autop = x;
	file >> x;
	maxw = x;
	file >> x;
	char eventtype;
	char cargotype;
	int days;
	int hours;
	int id;
	int distance;
	int timecargo;
	int cost;
	Preparation* prepptr;
	CancelEvent* canclptr;
	PromoteEvent* promtptr;
	for (int i = 0; i < x; i++)
	{
		file >> eventtype;
		if (eventtype == 'R')
		{
			file >> cargotype;
			file >> days;
			file >> eventtype;
			file >> hours;
			file >> id;
			file >> distance;
			file >> timecargo;
			file >> cost;
			if (cargotype == 'N')
				ncargocontorg++;
			prepptr = new Preparation(cargotype, id, distance, timecargo, cost, days,hours,this); 
			Events.enqueue(prepptr);
		}
		if (eventtype == 'X')
		{
			file >> days;
			file >> eventtype;
			file >> hours;
			file >> id;
			canclptr = new CancelEvent(id,days,hours, this);
			Events.enqueue(canclptr);
		}
		if (eventtype == 'P')
		{
			file >> days;
			file >> eventtype;
			file >> hours;
			file >> id;
			file >> cost;
			promtptr = new PromoteEvent(id, cost,days,hours, this);
			Events.enqueue(promtptr);

		}  
	}
}

void Company::outputfile(string s)
{
	Cargo* temp;
	Cargo* normal = nullptr;
	Cargo* special = nullptr;
	Cargo* vip = nullptr;
	int normaltime;
	int specialtime;
	int viptime;
	int totalcargowait=0;
	int b;
	ofstream file(s + ".txt", ios::out);
	file.close();
	file.open(s + ".txt", ios::app);
	file << "CDT		ID		PT		WT		TID" << endl;
	while (!NormalDelivered.isempty() || !SpecialDelivered.isempty() || !VIPDelivered.isempty())
	{
		temp = nullptr;
		NormalDelivered.peek(normal); SpecialDelivered.peek(special); VIPDelivered.peek(vip);
		if (normal)
			normaltime = normal->getdaydelivered() * 24 + normal->gethourdelivered(); //i think de lazem tb2a fn gowa cargo?
		else
			normaltime = 100000;
		if (special)
			specialtime = special->getdaydelivered() * 24 + special->gethourdelivered();
		else
			specialtime = 100000;
		if (vip)
			viptime = vip->getdaydelivered() * 24 + vip->gethourdelivered();
		else
			viptime = 100000;
		//kda lw = 100000 then its null
		if (normaltime <= specialtime && normaltime <= viptime && normaltime != 100000)
		{
			NormalDelivered.dequeue(temp);
			ncargocont++;
			normal = nullptr;
		}
		else if (viptime <= normaltime && viptime <= specialtime && viptime != 100000)
		{
			VIPDelivered.dequeue(temp);
			vcargocont++;
			vip = nullptr;
		}
		else if (specialtime != 100000)
		{
			SpecialDelivered.dequeue(temp);
			scargocont++;
			special = nullptr;
		}

		if (temp)
		{
			file << temp->getdaydelivered() << ":" << temp->gethourdelivered() << "		";
			file << temp->getid() << "		";
			file << temp->getdayprepare() << ":" << temp->gethourprepare() << "		";
			b = (temp->getdaywaited() - temp->getdayprepare()) * 24 + (temp->gethourwaited() - temp->gethourprepare());
			file << b/24 << ":" << b%24 << "		";
			file << temp->gettruckID() << endl;
			totalcargowait += (temp->getdaywaited() - temp->getdayprepare()) * 24 + (temp->gethourwaited() - temp->gethourprepare());
			delete temp;
		}
	}
	file << "----------------------------------------------------------"<<endl;
	file << "----------------------------------------------------------"<<endl;
	file << "Cargos: " << ncargocont + scargocont + vcargocont << " [N: " << ncargocont << ", S: " << scargocont << ", V:" << vcargocont << "]" << endl;
	file << "Cargo Avg Wait = " << (totalcargowait/(ncargocont + scargocont + vcargocont)/24) << ":" << totalcargowait / (ncargocont + scargocont + vcargocont)%24+1 << endl;
	file << "Auto-promoted Cargos: " << (1.0*autopromotedcont / ncargocontorg) * 100 << "%" << endl;
	file << "Trucks: " << ntruckcont + struckcont + vtruckcont << " [N: " << ntruckcont << ", S: " << struckcont << ", V:" << vtruckcont << "]" << endl;
	file << "Avg Active Time = " << (1.0*truckstotalactivetime/(ntruckcont + struckcont + vtruckcont)/(finishedday*24+finishedhour)*100) << "%"<<endl;
	file << "Avg Utilization =" << (1.0*totalutilization/(ntruckcont + struckcont + vtruckcont))*100 << "%" << endl;
	file.close();
}

void Company::simulate()
{
	readinput(userinput->askmode());
	int day=0;
	int finishedhoura = 0;
	Event* temp;
	srand(time(0));
	while (!isfinished())
	{
		Events.peek(temp);

		for (int i = 0; i < 24; i++)
		{
			while (temp->istime(i, day))
			{
				Events.dequeue(temp);
				temp->Execute();
				delete temp;
				if (!Events.peek(temp))
					break;
			}
			autopromote(day,i);
			if(i>=5 && i<=23)
				assign(day,i);
			movingtruckscargo(day, i);
			movingtrucksfail(i, day);
			truckschanging(day, i);
			userinput->modeffect(this,i,day);
			if (isfinished())
			{
				finishedhoura = i;
				break;
			}
		}
		day++;
	}
	finishedday = day - 1;
	finishedhour = finishedhoura;
	calculateTruckUtilization(finishedday, finishedhour);
	outputfile(userinput->getoutput());
}


void Company:: AddCargo (Cargo*ptr, float prio)
{
	if (ptr->gettype() == 1)
		NormalCargos.enqueue(ptr);
	else if (ptr->gettype() == 2)
		SpecialCargos.enqueue(ptr);
	else
		VIPCargos.enqueue(ptr,prio); //we need to figure the priority thing
}

void Company :: cancel(int id) 
{
	queue<Cargo*>tempq;
	Cargo*temp=nullptr;
	NormalCargos.peek(temp);
	if (!temp)
		return;

	if (temp->getid() == id)
	{
		NormalCargos.dequeue(temp);
		return;
	}

	while (temp->getid() != id && !NormalCargos.isempty()) //search for cargo with the id to be removed
	{
		tempq.enqueue(temp);
		NormalCargos.dequeue(temp);
		NormalCargos.peek(temp);
	}
	if (temp)
	{
		NormalCargos.dequeue(temp);
	}
	while (!NormalCargos.isempty()) //move rest of cargos in the tempq with the cargo removed
	{
		NormalCargos.dequeue(temp);
		tempq.enqueue(temp);
	}
	while (!tempq.isempty()) //move back to the cargo list
	{
		tempq.dequeue(temp);
		NormalCargos.enqueue(temp);
	}
}

void Company :: Promote(int id, int extra)  
{
	queue<Cargo*>tempq;
	Cargo*temp = nullptr;
	if (NormalCargos.isempty())
		return;
	while (!NormalCargos.isempty()) //empty queue until id is found
	{
		NormalCargos.dequeue(temp);
		if (temp->getid() == id)
			break;
		tempq.enqueue(temp);

	}
	if(temp->getid() == id)
		VIPCargos.enqueue(temp,temp->promote(extra)); //promote wa5da el extra 
	while (!NormalCargos.isempty()) //move rest of cargos in the tempq with the cargo removed
	{
		NormalCargos.dequeue(temp);
		tempq.enqueue(temp);
	}
	while (!tempq.isempty()) //move back to the cargo list
	{
		tempq.dequeue(temp);
		NormalCargos.enqueue(temp);
	}
}

bool Company::isfinished()
{
	return NormalCargos.isempty()&&SpecialCargos.isempty()&&VIPCargos.isempty()&&Events.isempty()&&(normalloadingtruck==nullptr)&&(specialloadingtruck==nullptr)&&(viploadingtruck==nullptr)&&movingtrucks.isempty()&&Checkupnormal.isempty()&& Checkupspecial.isempty()&& Checkupvip.isempty();
}

void Company::movetodelivered(Cargo* ptr, int type)
{
	if(type==1)
		NormalDelivered.enqueue(ptr);
	if (type == 2)
		SpecialDelivered.enqueue(ptr);
	if (type == 3)
		VIPDelivered.enqueue(ptr);
}





void Company::truckschanging(int day, int hour)
{
	bool noother=false;
	truck* ptr;
	if (viploadingtruck)     //should the loading truck move or not
	{
			if (VIPCargos.isempty() && Events.isempty())
				noother = true;
		if (viploadingtruck->isfull()|| (noother && viploadingtruck->finishedloading()))
		{
			viploadingtruck->departed(hour, day);
			movingtrucks.enqueue(viploadingtruck, viploadingtruck->prioritywhilemoving());
			viploadingtruck = nullptr;
		}
	}
	if (normalloadingtruck)    //should the loading truck move or not
	{
		noother = false;
			if (NormalCargos.isempty() && Events.isempty())
				noother = true;
		if (normalloadingtruck->isfull() || normalloadingtruck->hasurgentcargo()|| (noother&&normalloadingtruck->finishedloading()))
		{
			normalloadingtruck->departed(hour, day);
			movingtrucks.enqueue(normalloadingtruck, normalloadingtruck->prioritywhilemoving());
			normalloadingtruck = nullptr;
		}
	}
	if (specialloadingtruck)    //should the loading truck move or not
	{
		noother = false;
			if (SpecialCargos.isempty() && Events.isempty())
				noother = true;
		if (specialloadingtruck->isfull() || specialloadingtruck->hasurgentcargo()|| (noother && specialloadingtruck->finishedloading()))  //moves if no other cargo needs being loaded or if it loaded a maxw cargo or if full
		{
			specialloadingtruck->departed(hour, day);
			movingtrucks.enqueue(specialloadingtruck, specialloadingtruck->prioritywhilemoving());
			specialloadingtruck = nullptr;
		}
	}
	while (movingtrucks.peek(ptr))   //checks if any moving truck is back
	{
		if (ptr->finishedtrip(hour, day))   
		{
			int type = ptr->gettype();
			if (ptr->gotocheckup(hour,day))   //if yes chck if it needs check up
			{
				if (type == 1)
					Checkupnormal.enqueue(ptr);
				if (type == 2)
					Checkupspecial.enqueue(ptr);
				if (type == 3)
					Checkupvip.enqueue(ptr);
			}
			else
			{
				if (type == 1)
				{
					waitingnormaltrucks.enqueue(ptr);
				}
				if (type == 2)
				{
					waitingspecialtrucks.enqueue(ptr);
				}
				if (type == 3)
				{
					waitingviptrucks.enqueue(ptr);
				}
			}
			movingtrucks.dequeue(ptr);
		}
		else
			break;
	}


	while (Checkupnormal.peek(ptr))    //checks if any cargo finished checkup to return to waiting
	{
		if (ptr->finishedcheckup(hour, day))
		{
			waitingnormaltrucks.enqueue(ptr);
			Checkupnormal.dequeue(ptr);
		}
		else
			break;
	}
	while (Checkupspecial.peek(ptr))
	{
		if (ptr->finishedcheckup(hour, day))
		{
			waitingspecialtrucks.enqueue(ptr);
			Checkupspecial.dequeue(ptr);
		}
		else
			break;
	}
	while (Checkupvip.peek(ptr))
	{
		if (ptr->finishedcheckup(hour, day))
		{
			waitingviptrucks.enqueue(ptr);
			Checkupvip.dequeue(ptr);
		}
		else
			break;
	}

}

void Company::assign(int day, int hour)
{
	if (normalloadingtruck)     //decreasing the loadtime bending
		normalloadingtruck->decrementeloadtime();
	if (specialloadingtruck)
		specialloadingtruck->decrementeloadtime();
	if (viploadingtruck)
		viploadingtruck->decrementeloadtime();


	Cargo* temp;
	bool enqueued = false;
	truck* ptr;

	if (VIPCargos.peek(temp))
	{

		if (viploadingtruck)   //checking if loadingtruck exists
		{
			if (viploadingtruck->loadcargo(temp))   //try loading
			{
				enqueued = true;
				if (hour + temp->getloadtime() < 24)
				{
					temp->setdaywaited(day);
					temp->sethourwaited(hour);
				}
				else
				{
					temp->setdaywaited(day + 1);
					temp->sethourwaited(24 - hour);
				}
				viploadingtruck->StartofLoading(hour, day);
			}
		}
		else
		{
			if (waitingviptrucks.peek(ptr)) //checking if will move a vip truck from waiting to load
			{
				if (ptr->isenoughcargo(VIPCargos.count(), false))
				{
					waitingviptrucks.dequeue(ptr);
					viploadingtruck = ptr;
					viploadingtruck->loadcargo(temp);
					enqueued = true;
					temp->setdaywaited(day);
					temp->sethourwaited(hour);
					viploadingtruck->StartofLoading(hour, day);
				}
			}
		}
		if (viploadingtruck == nullptr)  //checks if no existing vip 
		{
			if (waitingviptrucks.isempty())                       //no waiting vip available or we already have a normal truck loading vip
				if (waitingnormaltrucks.peek(ptr))
				{
					if (ptr->isenoughcargo(VIPCargos.count(), false))
					{
						waitingnormaltrucks.dequeue(ptr);
						viploadingtruck = ptr;
						viploadingtruck->loadcargo(temp);
						enqueued = true;
						temp->setdaywaited(day);
						temp->sethourwaited(hour);
						viploadingtruck->StartofLoading(hour, day);
					}
				}

			if ((waitingviptrucks.isempty() && waitingnormaltrucks.isempty()) && !enqueued) //same but with special
				if (waitingspecialtrucks.peek(ptr))
				{
					if (ptr->isenoughcargo(VIPCargos.count(), false))
					{
						waitingspecialtrucks.dequeue(ptr);
						viploadingtruck = ptr;
						viploadingtruck->loadcargo(temp);
						enqueued = true;
						temp->setdaywaited(day);
						temp->sethourwaited(hour);
						viploadingtruck->StartofLoading(hour, day);
					}
				}
		}
		
	

	if (Events.isempty() && !enqueued && !viploadingtruck&&(waitingnormaltrucks.count() != 0 || waitingnormaltrucks.count() == ntruckcont) && (waitingspecialtrucks.count() != 0 || waitingspecialtrucks.count() == struckcont) && (waitingviptrucks.count() != 0 || waitingviptrucks.count() == vtruckcont)) //vip have no maxw rule so to check if it is the last truck
	{
		if (!waitingviptrucks.dequeue(ptr))
		if (!waitingnormaltrucks.dequeue(ptr))
		   waitingspecialtrucks.dequeue(ptr);
			
			
	    viploadingtruck = ptr;
		ptr->loadcargo(temp);
		temp->setdaywaited(day);
		temp->sethourwaited(hour);
		enqueued = true;
		ptr->StartofLoading(hour, day);
	}

	if (enqueued)
		VIPCargos.dequeue(temp);
    }

	
	if (SpecialCargos.peek(temp))    //special cargo only loads in special trucks
	{
		if (specialloadingtruck)
		{
			if (specialloadingtruck->loadcargo(temp))
			{
				SpecialCargos.dequeue(temp);
				temp->setdaywaited(day);
				temp->sethourwaited(hour);
				specialloadingtruck->StartofLoading(hour, day);
			}
		}
		else
		{
			if (waitingspecialtrucks.peek(ptr))
			{
				if (ptr->isenoughcargo(SpecialCargos.count(), temp->timewaited(hour, day) >= maxw))
				{
					waitingspecialtrucks.dequeue(ptr);
					specialloadingtruck = ptr;
					specialloadingtruck->loadcargo(temp);
					SpecialCargos.dequeue(temp);
					enqueued = true;
					temp->setdaywaited(day);
					temp->sethourwaited(hour);
					specialloadingtruck->StartofLoading(hour, day);
				}
			}

		}
	}
	enqueued = false;
	if (NormalCargos.peek(temp))   //doing the same with the vip cargos to normal cargos
	{

		if (normalloadingtruck)
		{
			if (normalloadingtruck->loadcargo(temp))
			{
				enqueued = true;
				temp->setdaywaited(day);
				temp->sethourwaited(hour);
				normalloadingtruck->StartofLoading(hour, day);
			}
		}
		else
		{
			if (waitingnormaltrucks.peek(ptr))
			{
				if (ptr->isenoughcargo(NormalCargos.count(), temp->timewaited(hour,day)>=maxw))
				{
					waitingnormaltrucks.dequeue(ptr);
					normalloadingtruck = ptr;
					normalloadingtruck->loadcargo(temp);
					enqueued = true;
					temp->setdaywaited(day);
					temp->sethourwaited(hour);
					normalloadingtruck->StartofLoading(hour, day);
				}

			}


		}
		if(normalloadingtruck == nullptr)
		{
			if (waitingnormaltrucks.isempty()&& !enqueued)
			{
					
				if (waitingviptrucks.peek(ptr))
				{
					if (ptr->isenoughcargo(NormalCargos.count(), temp->timewaited(hour, day) >= maxw))
					{
						waitingviptrucks.dequeue(ptr);
						normalloadingtruck = ptr;
						normalloadingtruck->loadcargo(temp);
						enqueued = true;
						temp->setdaywaited(day);
						temp->sethourwaited(hour);
						normalloadingtruck->StartofLoading(hour, day);
					}
				}	
			}
		}
		if (enqueued)
			NormalCargos.dequeue(temp);
	}
}

void Company::movingtruckscargo(int day, int hour)
{
	truck* truckptr;
	queue<truck*>truckqueue;
	while (movingtrucks.dequeue(truckptr))  //loops on moving trucks checking the if already delivered cargos
	{
		truckptr->cargodelievery(hour, day, this);
		truckqueue.enqueue(truckptr);
	}
	while (truckqueue.dequeue(truckptr))
	{
		movingtrucks.enqueue(truckptr, truckptr->prioritywhilemoving());
	}
}

int Company::getcountloading()
{
	int count = 0;
	if (normalloadingtruck)
		count++;
	if (specialloadingtruck)
		count++;
	if (viploadingtruck)
		count++;
	return count;
}

void Company::movingtrucksfail(int hour,int day)
{
	truck* truckptr;
	queue<truck*>truckqueue;
	while (movingtrucks.dequeue(truckptr))   //checks if any trucks failed
	{
		if (truckptr->failed(this,hour,day))
		{
			userinput->printfail();
			if (truckptr->gettype() == 1)
				Checkupnormal.enqueue(truckptr);
			if (truckptr->gettype() == 2)
				Checkupspecial.enqueue(truckptr);
			if (truckptr->gettype() == 3)
				Checkupvip.enqueue(truckptr);
			
		}
		else
		truckqueue.enqueue(truckptr);
	}
	while (truckqueue.dequeue(truckptr))
	{
		movingtrucks.enqueue(truckptr, truckptr->prioritywhilemoving());
	}

}

truck* Company::getviploadingtruck()
{
	return viploadingtruck;
}

truck* Company::getspecialloadingtruck()
{
	return specialloadingtruck;
}

truck* Company::getnormalloadingtruck()
{
	return normalloadingtruck;
}


queue<Cargo*>* Company::getwaitingnormal()
{
	return &NormalCargos;
}

queue<Cargo*>* Company::getdeliverednormal()
{
	return &NormalDelivered;
}

queue<Cargo*>* Company::getwaitingspecial()
{
	return &SpecialCargos;
}

queue<Cargo*>* Company::getdeliveredspecial()
{
	return &SpecialDelivered;
}

queue<Cargo*>* Company::getdeliveredvip()
{
	return &VIPDelivered;
}

priorityqueue<Cargo*>* Company::getwaitingvip()
{
	return &VIPCargos;
}

queue<truck*>* Company::getwaitingnormaltruck()
{
	return &waitingnormaltrucks;
}

queue<truck*>* Company::getwaitingviptruck()
{
	return &waitingviptrucks;
}

queue<truck*>* Company::getwaitingspecialtruck()
{
	return &waitingspecialtrucks;
}

queue<truck*>* Company::getCheckupnormal()
{
	return &Checkupnormal;
}

queue<truck*>* Company::getCheckupspecial()
{
	return &Checkupspecial;
}

queue<truck*>* Company::getCheckupvip()
{
	return &Checkupvip;
}




priorityqueue<truck*>* Company::getmovingtrucks()
{
	return &movingtrucks;
}


void Company::autopromote(int day,int hour)
{
	Cargo*c;
	bool p=true;
	while(p) 
	{
		if (NormalCargos.peek(c))
			if (c->timewaited(hour, day) >= autop * 24)
			{
				NormalCargos.dequeue(c);
				VIPCargos.enqueue(c, c->promote(0));
				autopromotedcont++;
			}
			else { p = false; }
		else
			p = false;

	}
}

void Company::calculateTruckUtilization(int day, int hour)
{
	truck* temp;
	while (waitingnormaltrucks.dequeue(temp))
	{
		totalutilization += temp->calculateUtilization(day, hour);
		truckstotalactivetime += temp->gettotalactivetime();
		totaltruckjournies += temp->gettotaljournies();
		delete temp;
	}

	while (waitingspecialtrucks.dequeue(temp))
	{
		totalutilization += temp->calculateUtilization(day, hour);
		truckstotalactivetime += temp->gettotalactivetime();
		totaltruckjournies += temp->gettotaljournies();
		delete temp;
	}

	while (waitingviptrucks.dequeue(temp))
	{
		totalutilization += temp->calculateUtilization(day, hour);
		truckstotalactivetime += temp->gettotalactivetime();
		totaltruckjournies += temp->gettotaljournies();
		delete temp;
	}
}

void Company::movetowaitingcargo(Cargo* ptr, int type)
{
	if (type == 1)
		NormalCargos.enqueue(ptr);
	if (type == 2)
		SpecialCargos.enqueue(ptr);
	if (type == 3)
		VIPCargos.enqueue(ptr,ptr->calcprio());
}