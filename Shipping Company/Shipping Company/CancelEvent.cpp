#include "CancelEvent.h"
CancelEvent::CancelEvent(int id, int eventday, int eventhour, Company* compptr) : Event(eventday,eventhour, compptr)
{
	ID = id;
}

CancelEvent::~CancelEvent()
{

}

void CancelEvent:: Execute()
{
	CompanyPtr->cancel(ID);

}