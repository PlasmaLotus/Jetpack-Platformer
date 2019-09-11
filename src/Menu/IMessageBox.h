#ifndef __IMESSAGEBOX__
#define __IMESSAGEBOX__

#include <string>
#include "../Event/IObserver.h"
#include "../Event/ISubject.h"

#include "../Event/IEvent.h"

enum MessageBoxOption {
	Confirm = 0,
	Decline = 1,
	Cancel = 2,
	Closed = 3
};

enum MessageBoxType {
	YES_NO_OPTION,
	YES_NO_CANCEL_OPTION,
	OK_CANCEL_OPTION,
	DEFAULT_OPTION,
};

class IMessageBox: public ISubject
{
public:
	IMessageBox(IObserver* menuObserver, MessageBoxType type);
	IMessageBox(IObserver* parent, std::string title, std::string message);
	
	virtual ~IMessageBox();

	virtual void update(float delta);
protected:
	bool _registerObserver(IObserver* o);
	bool _deregisterObserver(IObserver* o);
	int _canDoStuff;
	IObserver* mObserver;
};

class MessageBoxEvent: IEvent {
public:
	MessageBoxEvent();
	MessageBoxEvent(MessageBoxOption option);
	~MessageBoxEvent();

	void setOption(MessageBoxOption mbo);
	MessageBoxOption getOption();
	MessageBoxOption option = MessageBoxOption::Cancel;
};


/*
namespace MessageBox {
	enum MessageBoxOption {
		Confirm = 0,
		Deny = 1,
		Cancel = 2,
		Close = 3
	};

	enum MessageBoxType {
		YES_NO_OPTION,
		YES_NO_CANCEL_OPTION,
		OK_CANCEL_OPTION,
		DEFAULT_OPTION,
	};
}
*/

class MessageBox {
	static void/*IMessageBox&*/showMessageBox() {}
};

#endif

