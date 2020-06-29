#include "IObserver.h"
#include "IEvent.h"
#include "ISubject.h"
IObserver::IObserver():
	__nbEventRecived(0)
{
}

IObserver::~IObserver()
{
}

void IObserver::HandleEvent(ISubject * subject, const IEvent & event)
{
	++__nbEventRecived;
}
