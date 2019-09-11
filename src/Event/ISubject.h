#ifndef __ISUBJECT__
#define __ISUBJECT__

/* Interface that emits events to the event manager */
class ISubject
{
public:
	ISubject();
	~ISubject();
protected:
	int _canDoStuff;


};



#endif

