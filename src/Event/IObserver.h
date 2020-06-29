#ifndef __IOBSERVER__
#define __IOBSERVER__

class ISubject;
class IEvent;

/* Interface that observes and can be notified of an IEvent*/
class IObserver
{
public:
	IObserver();
	~IObserver();

	virtual void HandleEvent(ISubject* subject, const IEvent& event);
protected:
	int __nbEventRecived;
};

#endif

