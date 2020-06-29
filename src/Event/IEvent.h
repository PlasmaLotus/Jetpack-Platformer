#ifndef __IEVENT__
#define __IEVENT__

class IEvent
{
public:
	IEvent();
	~IEvent ();
	//IEvent(ISubject&);

	//ISuject* subject;
	int verbosity;
	int type;
};

namespace Event 
{
	enum EventType
	{
		Count
	};

}//namespace Event

#endif

