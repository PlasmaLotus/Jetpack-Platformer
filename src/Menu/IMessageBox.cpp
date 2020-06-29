#include "IMessageBox.h"
#include "../Engine/Engine.h"
/*
#include "IEvent.h"
#include "IObserver.h"
*/
IMessageBox::IMessageBox(IObserver* menuObserver, MessageBoxType type = MessageBoxType::DEFAULT_OPTION)
: ISubject()
{
	_registerObserver(menuObserver);
}

IMessageBox::~IMessageBox()
{
	_deregisterObserver(mObserver);
	mObserver = nullptr;
}
void IMessageBox::update(float delta)
{
	//Do stuff on update
}
bool IMessageBox::_registerObserver(IObserver* observer) {
	int result = Event::Success;
	mObserver = observer;
	EventManager& eventManager{ Engine::getInstance().Event() };
	result = eventManager.Connect<MessageBoxEvent>(this, observer);
	//Engine::getInstance().Event().Connect<MessageBoxEvent>(this, o);

	//TODO
	return false;
}

bool IMessageBox::_deregisterObserver(IObserver* observer) {
	int result = Event::Success;
	//mObserver = observer;
	EventManager& eventManager{ Engine::getInstance().Event() };
	result = eventManager.Disconnect<MessageBoxEvent>(this, observer);
	//Engine::getInstance().Event().Connect<MessageBoxEvent>(this, o);
	
	//TODO
	return false;
}

MessageBoxEvent::MessageBoxEvent(MessageBoxOption mbo):
	IEvent(Event::Verbosity::TRACE),
	option(mbo){
}
MessageBoxEvent::MessageBoxEvent():
	MessageBoxEvent(MessageBoxOption::Cancel){
}

MessageBoxEvent::~MessageBoxEvent()
{
}

void MessageBoxEvent::setOption(MessageBoxOption mbo){
	option = mbo;
}

MessageBoxOption MessageBoxEvent::getOption(){
	return option;
}
