#include "Event.h"
Event::Event(int day,int hour,Company*ptr)
{
	EventDay = day;
	EventHour = hour;
	CompanyPtr = ptr;
}
bool Event::istime(int hours, int days)
{
	return (EventDay == days && EventHour == hours);
}

Event::~Event()
{
}