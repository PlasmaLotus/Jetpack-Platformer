#include "IEvent.h"


IEvent::IEvent(Event::Verbosity verbose = Event::Verbosity::INFO):
	mVerbosity(verbose)
{
}

IEvent::~IEvent()
{
}

Event::Verbosity & IEvent::verbosity()
{
	return mVerbosity;
	// TODO: insert return statement here
}
