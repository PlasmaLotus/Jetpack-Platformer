#ifndef __IEVENT__
#define __IEVENT__



class IEvent
{
public:
	IEvent();
	//IEvent(ISubject&);
	~IEvent ();

	int verbosity;
	int type;
	
	//ISuject* subject;


};

namespace Event 
{
	enum EventType
	{
		Count
	};

}//namespace Event



#endif

