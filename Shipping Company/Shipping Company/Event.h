#pragma once
#include"Company.h"
class Company;
class Event
{
private:
	int EventDay;
	int EventHour;

protected:
	Company* CompanyPtr;

public:
	Event(int day,int hour,Company*compptr);
	virtual void Execute() = 0;
	bool istime(int hours, int day);
	virtual ~Event();
};