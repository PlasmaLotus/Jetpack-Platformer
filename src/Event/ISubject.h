#ifndef __EVENT__MANAGER__
#define __EVENT__MANAGER__

/*

*/
#include <map>
#include <list>
#include <functional>

//class Manager;
class ISubject;
class IObserver;
class IEvent;
class EventManager
{
public:
		~EventManager();
		EventManager();

		void connect(ISubject& subject, IObserver& observer, IEvent& event);

		int disconnect(ISubject& subject, IObserver& observer, IEvent& event);

		void emit(ISubject& subject, const IEvent& event);

		private:


		//class Parcel {...};
		/* Determines the Event Obj Type, Who to callback and the Callback FN */
		class Parcel
		{  
		public:
			/**/
			Parcel(){
				_event = nullptr;
				_observer = nullptr;
			}


			Parcel(IEvent* ue, IObserver* c){
				
				_event = ue;
				_observer = c;
			}
			
			~Parcel(){
				if(_event){
					delete _event;
				}
			}
			 IEvent*                   _event;//owner
			 IObserver*               _observer;//not owner   
		};

		typedef std::list<IEvent>        List;
		typedef std::map<ISubject*, List> Map;

		
		std::map<const ISubject*, std::list<IObserver>> subjectMap; //std::map<const void*, std::list<Parcel>>

		std::map<const IObserver*, std::list<IEvent>> voidmap;
		//Void* is the Subject

		void       _emit (void*, const IEvent&);
		void    _connect (const void*, const Parcel&);
		bool _disconnect (const void*, const Parcel&);


};
/*
class EventDr: public IEvent{
public:
	int __r;
};

class _Subject{
public:
	_Subject(){}
	~_Subject(){}
	void doStuff(EventManager& signal){
		signal.emit(*this, new EventDr());
	}
};

class _Observer{
public:
	_Observer(){};
	~_Observer(){};
	void doStuff(const EventDr& event, _Subject* subject){
		/**/
		printf("Observer event caught\n");
	}
};
*/

#endif

/*
 1  // A global event.
 2  class DestroyEvent : public Signal::Event {};
 3  
 4  class Employee
 5  { ...
 6     // Employee-specific events.
 7  
 8     class EnterEvent : public Signal::Event {...};
 9     class LeaveEvent : public Signal::Event {...};
10  
11     void enter()
12     {  ...
13        // Report an employee-entering-facility event.
14        Signal::emit(*this, EnterEvent());
15     }
16  
17     void leave()
18     {  ...
19        // Report an employee-leaving-facility event.
20        Signal::emit(*this, LeaveEvent());
21     }
22  
23     ~Employee()
24     {  ...
25        // Report an event of employee being fired.
26        Signal::emit(*this, DestroyEvent());
27     }
28  };
29  
30  class PayrollOffice
31  {  ...
32     // Callbacks.
33     void employee_enters(
34        const Employee::EnterEvent&, Employee&);
35     void employee_leaves(
36        const Employee::LeaveEvent&, Employee&);
37  };
38  
39  PayrollOffice::employee_enters(
40     const Employee::EnterEvent& ev, Employee* employee)
41  {
42     if (ev.is_late()) // Employee is late in.
43     {
44        remember_the_guy(employee);
45     }
46     else { ... }
47  }
48  
49  PayrollOffice::employee_leaves(
50     const Employee::LeaveEvent& ev, Employee* employee)
51  {
52     if (ev.is_early()) // Employee is early out.
53     {
54        remember_the_guy(employee);
55     }
56     else { ... }
57  }
58  
59  int main()
60  {
61     PayrollOffice po;
62     Employee    john;
63  
64     typedef PayrollOffice PO;
65
66     Signal::connect(john, po, &PO::employee_enters);
67     Signal::connect(john, po, &PO::employee_leaves);
68
69     // Registered for Employee::EnterEvent callbacks will be
70     // invoked in response to the employee entering facility.
71
72     john.enter();
73
74     Signal::disconnect(john, po, &PO::employee_enters);
75     Signal::disconnect(john, po, &PO::employee_leaves);
76  }
— End of Listing —
*/