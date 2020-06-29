#ifndef __IEVENT__
#define __IEVENT__


namespace Event
{
	enum Verbosity {
		TRACE = 2,//

		DEBUG = 1,

		INFO = 0,

		WARN = -1,

		//ERROR = -2,

		FATAL = -3
	};
	enum Type
	{
		Count
	};

}//namespace Event
class IEvent
{
public:
	//IEvent( int verbose);
	IEvent(Event::Verbosity verbose );
	~IEvent ();

	Event::Verbosity& verbosity();

protected:
	Event::Verbosity mVerbosity;
	//int type;
};


#endif

