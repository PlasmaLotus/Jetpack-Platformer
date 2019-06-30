/*
#include "Signal.h"

#include <algoritm>
Signal::Signal(void)
{
}


Signal::~Signal(void)
{
}

template<class Subject, class Observer, class UserEvent>
inline void
Signal::connect(Subject& subject, Observer& observer,
   void (Observer::* cb)(const UserEvent&, Subject*))
{
   Parcel parcel(new UserEvent, (Callee*) &observer,
                 (MemberCallback) cb);
	 //Parcel p(
   _signals()._connect(&subject, parcel);
}



template<class Subject, class UserEvent>
void Signal::emit(Subject& subject, const UserEvent& userEvent){

}

template<class Subject, UserEvent>
void Signal::emit(Subject& subject, const UserEvent& uEvent){
	
	void* sub{&subject};
	void* evt{uEvent};
	for (auro a : map){
		if (sub == a->first()){
			
			for (auto parcel: a->second() ){
				Event* event = dynamic_cast<Event*>(evt);
				if(event){
					
				if (parcel.event == event){
					;
				}
				}
			}
		}
	}
	
}
void Signal::_emit(void* idk, const Event& event){

for()

}

		void    _connect (const void*, const Parcel&);

		bool _disconnect (const void*, const Parcel&);


		*/