#ifndef __EVENT__SIGNAL__
#define __EVENT__SIGNAL__

/*

*/
#include <map>
#include <list>

class Signal
{
public:
		~Signal () {}
		//class Event {...};
		class Event {
		public:
			int _verbosity;
		};

		//Subject emits an event
		//Observer has a dependency with a subject.
		//Subject be like observer->update()

		template<class Subject, class Observer, class UserEvent>
		static
		void
		connect(
			Subject&, Observer&,
			void (Observer::*)(const UserEvent&, Subject*));

		template<class Subject, class Observer, class UserEvent>
		static
		void
		connect(
			Subject&, Observer&,
			void (*)(const UserEvent&, Subject*, Observer*));

		template<class Subject, class Observer, class UserEvent>
		static
		bool
		disconnect(
			Subject&, Observer&,
			void (Observer::*)(const UserEvent&, Subject*));

		template<class Subject, class Observer, class UserEvent>
		static
		bool
		disconnect(
			Subject&, Observer&,
			void (*)(const UserEvent&, Subject*, Observer*));

		template<class Subject, class UserEvent>
		static
		void
		emit(Subject&, const UserEvent&);

		private:
		Signal () {}
		struct Callee {};

		typedef void (Callee::*MemberCallback) 
			(const Event&, void*);
		typedef void (*LonelyCallback) 
			(const Event&, void*, void*);

		//class Parcel {...};
		/* Determines the Event Obj Type, Who to callback and the Callback FN */
		class Parcel
		{  
		public:
			/**/
			template<class UserEvent>
			Parcel(UserEvent* ue, Callee* c, MemberCallback* cb);
			/**/
			template<class UserEvent>
			Parcel(UserEvent* ue, Callee* c, LonelyCallback* cb);
			
			~Parcel();
			 Event*                   _event;
			 Callee*               _receiver;
			 MemberCallback _member_callback;            
			 LonelyCallback _lonely_callback;            
		};

		typedef std::list<Parcel>          List;
		typedef std::map<const void*, List> Map;

		//Map _map;
		std::map<const void*, std::list<Parcel>> map; //std::map<const void*, std::list<Parcel>>

		void       _emit (void*, const Event&);
		void    _connect (const void*, const Parcel&);
		bool _disconnect (const void*, const Parcel&);

		static Signal& _signals ();
};




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