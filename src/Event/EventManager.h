#ifndef __EVENT__MANAGER__
#define __EVENT__MANAGER__


#include <map>
#include <list>
#include <functional>

namespace Event {
	enum EventStatus {
		NoEventFound = 0, 
		NoSubjectFound = 0,
		NoObserverFound = 0,
		Ok = 1,

	};
	enum ConnectionStatus {
		ConnectionSuccesful = 1,
		DisconnectionSuccesful = 1,
		Success = 1,
		NoEvent = 0,
		NoObserver = -1,
		NoSubject = -2,
		ConnectionError = -3,
		ConnectionAlreadyExists = -4
	};
}//namespace Event

//class Manager;
class ISubject;
class IObserver;
class IEvent;

class Parcel;
class SubParcel;

/*
Event manager is owner of events stored, but not of observers and subjects.
*/
class EventManager
{
public:
	~EventManager();
	EventManager();
	void update(int delta);
		
	template <class EventClass = IEvent>
	int Connect(ISubject* subject, IObserver* observer) {
		//auto *clapped = new EventClass;
		//return _connect(subject, observer, new EventClass);
		Event::ConnectionStatus status = Event::ConnectionStatus::ConnectionSuccesful;

		EventClass* event = new EventClass;
		if (event) {
			if (observer) {
				if (subject) {
					//All 3 are there
					//ISubject* wSubject{nullptr};
					Parcel parcel(event, observer);
					bool wSubjectFound = false;
					bool wObserverFound = false;
					bool wEventFound = false;
					//Check that the subject doesnt exist already...
					for (auto it : mMap) {
						ISubject* const wSubject = it.first;
						if (wSubject == subject) {
							//The subject already exists
							wSubjectFound = true;
							std::list<Parcel>& parcels = it.second;
								
							//Check if parcel alreay exists
							for (Parcel p : parcels) {
								if (p._observer == parcel._observer) {
									wObserverFound = true;
									if (p._event) {
										EventClass* wEvent{ static_cast<EventClass*>(p._event) };
										//EventClass* wEvent{ dynamic_cast<EventClass*>(p._event) };
										if (wEvent) {
											//parcel event is the same type
											wEventFound = true;
										}
									}
								}
							}//for parcels
							if (wSubjectFound) {
								if (wEventFound) {
									//Connection already exists
									status = Event::ConnectionStatus::ConnectionAlreadyExists;
								}
								else {
									// Subject is here but Connection is not, establish connection
									/* Inserting connection */
									parcels.push_back(parcel);
									status = Event::ConnectionStatus::ConnectionSuccesful;
								}
							}//if wSubjectFound
						}//if wSubject == subject
					}//For _map auto

					if (!wSubjectFound) {
						std::list<Parcel> _list;
						_list.push_back(parcel);
						std::pair<ISubject*, std::list<Parcel>> pair(subject, _list);
						/* Subject is not here, Add subject and establish connection*/
						/* Inserting connection */
						//_map.insert(std::pair<const ISubject*, std::list<Parcel>>(subject, std::list<Parcel>(parcel))));
						std::pair<std::map<ISubject*, std::list<Parcel>>::iterator,bool> ret;
						ret = mMap.insert(pair);
						if (ret.second == false) {
							//Insert failed failed
							//LOG insert failed
							status = Event::ConnectionStatus::ConnectionError;
						}
						else {
							status = Event::ConnectionStatus::ConnectionSuccesful;
						}
					}//if !wSubjectFound
				}// if subject
				else {
					//No subject implies any object
					status = Event::ConnectionStatus::NoSubject;
				}
			}
			else {
				status = Event::ConnectionStatus::NoObserver;
			}
		}
		else {
			//Event is null, no way to know which event
			status = Event::ConnectionStatus::NoEvent;
		}
		return status;
	}

	template <class EventClass = IEvent>
	int Disconnect(ISubject* subject, IObserver* observer) {
		//auto *clapped = new EventClass;
		//return _disconnect(subject, observer, new EventClass);
		Event::ConnectionStatus status = Event::ConnectionStatus::DisconnectionSuccesful;
			
		EventClass* event = new EventClass;
		if (event) {
			if (observer) {
				if (subject) {
					//All 3 are there
					bool wSubjectFound = false;
					bool wObserverFound = false;
					bool wEventFound = false;
					//Check that the subject doesnt exist already...
					for (auto it : mMap) {
						const ISubject*  const wSubject = it.first;
						if (wSubject == subject) {
							//The subject already exists
							wSubjectFound = true;
							std::list<Parcel>& parcels = it.second;
								
							//Check if parcel alreay exists
							for (auto it = parcels.begin(); it != parcels.end(); ++it) {
								//for (Parcel p : parcels) {
								Parcel& parcel{ *it };
								if (parcel._observer == observer) {
									wObserverFound = true;
									if (parcel._event){
										EventClass* wEvent{static_cast<EventClass*>(parcel._event)};
										//EventClass* wEvent{dynamic_cast<EventClass*>(parcel._event)};
										if (wEvent) {
											//Event of same class
											wEventFound = true;

											//Removing Parcel
											/// it = parcels.erase(it);
											parcels.erase(it++);
											//status = Event::DisconnectionSuccesful;
										}
									}
								}//if parcel.observer
							}//for parcels
						}//if subject
					}//For _map auto

					if (wSubjectFound) {
						if (wObserverFound) {
							if (wEventFound) {
								status = Event::DisconnectionSuccesful;
							}
							else {
								status = Event::ConnectionStatus::NoEvent;
							}
						}
						else {
							status = Event::ConnectionStatus::NoObserver;
						}
					}
					else {
						status = Event::ConnectionStatus::NoSubject;
					}

				}// if subject
				else {
					//No subject implies any object
					status = Event::ConnectionStatus::NoSubject;
				}
			}
			else {
				status = Event::ConnectionStatus::NoObserver;
			}
		}
		else {
			//Event is null, no way to know which event
			status = Event::ConnectionStatus::NoEvent;
		}
		return status;
	}

	template <class EventClass = IEvent>
	void Emit(ISubject* subject, EventClass* event) {
		Event::EventStatus status = Event::EventStatus::Ok;
		int notifications{ 0 };
		if (subject) {
			if (event) {
				bool wSubjectFound = false;
				//Search through all subjects
				for (auto it : mMap) {
					ISubject* wSubject{ it.first };
					if (wSubject == subject) {
						wSubjectFound = true;
						std::list<Parcel>& parcels = it.second;
						//Search trough all parcels
						for (Parcel& parcel : parcels) {
							EventClass* pEvent{ static_cast<EventClass*>(parcel._event) };
							if (pEvent) {
								//Parcel event is of same type
								/* Notify observer */
								parcel._observer->HandleEvent(subject, *event);
								//remove previous event
								if (parcel._event) {
									delete parcel._event;
									parcel._event = event;
								}
								++notifications;
							}
						}//for parcels
					}//if wSubject == subject
				}//for mMap	
			}//if event
			else {
				status = Event::EventStatus::NoEventFound;
			}
		}
		else {
			status = Event::EventStatus::NoSubjectFound;
		}
	}

	void emit(ISubject* subject, IEvent* event, bool async);
	
	int getEvent(IObserver* observer, IEvent* oEvent);
	IEvent* getEvent(IObserver* observer);
private:

	Event::EventStatus _emit(ISubject * subject, IEvent * event);
	typedef std::list<IEvent*>			EvList;
	typedef std::map<ISubject*, EvList> EvMap;

	std::map<ISubject*, std::list<Parcel>> mMap; //std::map<const void*, std::list<Parcel>>

	std::map<const IObserver*, std::list<IEvent>> mVoidMap;//Observers for events of any subjects
	//Void* is the Subject

	std::list<SubParcel> mAsyncList;

	//int connect(ISubject* subject, IObserver* observer, IEvent* event);
	int _connect(ISubject* subject, IObserver* observer, void* _event);

	//int disconnect(ISubject* subject, IObserver* observer, IEvent* event);
	int _disconnect(ISubject* subject, IObserver* observer, void* _event);

};

/* Determines the Event Obj Type, Who to callback and the Callback FN */
class Parcel
{
public:
	Parcel(void* evt = nullptr, IObserver* obv = nullptr) :
		_event(evt),
		_observer(obv),
		_processed(false) {
	}
	~Parcel() {}
	/*
	bool operator==(Parcel& p) {
		return (_event == p._event && _observer == p._observer);
	}
	*/

	//IEvent*	_event;//owner
	void*		_event;//owner
	IObserver*	_observer;//not owner  
	bool		_processed;//If the event has been handled by an observer
};

/* Determines the Event Obj Type, And the subject to call on update */
class SubParcel
{
public:
	SubParcel(IEvent* evt = nullptr, ISubject* sub = nullptr) :
		_event(evt),
		_subject(sub),
		_processed(false) {
	}
	~SubParcel() {}
	IEvent*		_event;//owner
	ISubject*	_subject;//not owner  
	bool		_processed;//If the event has been handled by an observer
};

#endif