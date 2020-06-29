#include "EventManager.h"

#include "IEvent.h"
#include "ISubject.h"
#include "IObserver.h"
using namespace Event;

EventManager::EventManager(void)
{
}

EventManager::~EventManager(void)
{
}

#define Call_Member_Fn(object, ptr) ((object).*(ptr))

void EventManager::Update(int delta)
{
	//do stuff here
}

int EventManager::_connect(ISubject * subject, IObserver * observer, void * _event)
{
	ConnectionStatus status = ConnectionStatus::ConnectionSuccesful;
	if (_event) {
		IEvent* event{ static_cast<IEvent*>(_event) };
		if (event) {
			if (observer) {
				if (subject) {
					//All 3 are there
					//ISubject* wSubject{nullptr};
					Parcel parcel(event, observer);
					bool wSubjectFound = false;
					bool wParcelFound = false;
					//Check that the subject doesnt exist already...
					for (auto it : mMap) {
						const ISubject*  const wSubject = it.first;
						if (wSubject == subject) {
							//The subject already exists
							wSubjectFound = true;
							std::list<Parcel>& parcels = it.second;
							bool dummyThicc = false;

							//Check if parcel alreay exists
							for (Parcel p : parcels) {
								if (p._event == parcel._event && 
									parcel._observer == p._observer){
									wParcelFound = true;
									dummyThicc = true;

								}
							}
							if (dummyThicc) {
								//Connection already exists
								status = Event::ConnectionAlreadyExists;
							}
							else {
								//Connection is not, establish connection
								/*Inserting connection*/
								parcels.push_back(parcel);
								status = Event::ConnectionSuccesful;
							}
						}
					}//For _map auto

					if (!wSubjectFound) {
						std::list<Parcel> _list;
						_list.push_back(parcel);
						std::pair<ISubject*, std::list<Parcel>> pair(subject, _list);
						/*Inserting connection*/
						mMap.insert(pair);
						//_map.insert(std::pair<const ISubject*, std::list<Parcel>>(subject, std::list<Parcel>(parcel))));
						status = Event::ConnectionSuccesful;
					}
				}// if subject
				else {
					//No subject implies any object
					status = ConnectionStatus::NoSubject;
				}
			}
			else {
				status = ConnectionStatus::NoObserver;
			}
		}
		else {
			//Event is null, no way to know which event
			status = ConnectionStatus::NoEvent;
		}
		return status;
	}
	else {
		//Event is null, no way to know which event
		status = ConnectionStatus::NoEvent;
	}
	return status;
}

int EventManager::_disconnect(ISubject * subject, IObserver * observer, void * _event)
{
	ConnectionStatus status = ConnectionStatus::DisconnectionSuccesful;
	if (_event) {
		IEvent* event{static_cast<IEvent*>(_event)};
		if (event) {
			if (observer) {
				if (subject) {
					//All 3 are there

					bool wSubjectFound = false;
					bool wParcelFound = false;
					//Check that the subject doesnt exist already...
					for (auto it : mMap) {
						const ISubject*  const wSubject = it.first;
						if (wSubject == subject) {
							//The subject already exists
							wSubjectFound = true;
							std::list<Parcel>& parcels = it.second;
							bool dummyThicc = false;

							//Check if parcel alreay exists
							for (auto it = parcels.begin(); it != parcels.end(); ++it) {
								//for (Parcel p : parcels) {
								Parcel& parcel{ *it };
								if (parcel._observer == observer) {

									//TODO:::: Check event also
									wParcelFound = true;
									dummyThicc = true;

								}
							}
						}
					}//For _map auto


				}// if subject
				else {
					//No subject implies any object
					status = ConnectionStatus::NoSubject;
				}
			}
			else {
				status = ConnectionStatus::NoObserver;
			}
		}
		else {
			//Event is null, no way to know which event
			status = ConnectionStatus::NoEvent;
		}
	}//_event
	else {
		//Event is null, no way to know which event
		status = ConnectionStatus::NoEvent;
	}
	
	return status;

}

void EventManager::emit(ISubject * subject, IEvent * event, bool async = false)
{
	EventStatus status = EventStatus::Ok;
	if (subject) {
		if (event) {
			if (async) {
				mAsyncList.push_back(SubParcel(event, subject));
			}
			else {
				status = _emit(subject, event);
			}
		}
		else {
			status = EventStatus::NoEventFound;
		}
	}
	else {
		status = EventStatus::NoSubjectFound;
	}
}

EventStatus EventManager::_emit(ISubject * subject, IEvent * event) {
	//both should be not null
	if (!subject || !event) {
		return EventStatus::NoSubjectFound;
	}

	//Find subject
	bool wSubjectFound = false;
	bool wEventFound = false;
	for (auto it : mMap) {
		ISubject* wSubject{ it.first };
		if (wSubject == subject) {
			wSubjectFound = true;

			std::list<Parcel>& parcels = it.second;
			for (Parcel& parcel : parcels) {
				if (parcel._event == event)
					wEventFound = true;
				//Do more once the event is found
			}

		}

	}
	if (wEventFound)
		return EventStatus::Ok;
	return EventStatus::NoEventFound;
}

int EventManager::getEvent(IObserver * observer, IEvent * oEvent)
{
	return 0;
}

IEvent * EventManager::getEvent(IObserver * observer)
{
	return nullptr;
}

