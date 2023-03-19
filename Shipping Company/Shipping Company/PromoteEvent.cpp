#include "PromoteEvent.h"
PromoteEvent::PromoteEvent(int id, int extra, int eventday, int eventhour, Company* compptr) : Event(eventday,eventhour, compptr)
{
	ID = id;
	extramoney = extra;
}


void PromoteEvent::Execute()
{
	CompanyPtr->Promote(ID, extramoney);

}



PromoteEvent::~PromoteEvent()
{

}