/*
Created by PlasmaLotus
Updated Sept 10, 2019
*/

//GIT IN Developpement
#define _Option_Menu_Item_

#ifndef _Option_Menu_Item_
#define _Option_Menu_Item_
#include <string>
#include "MenuItem.h"

template <typename T>
class OptionItem :
	public MenuItem
{
public:
	OptionItem(std::string label):
		MenuItem(){
	}
	virtual ~OptionItem() {

	}

	virtual void Add(std::string label, T& value, bool selected);
	virtual void AddFirst(std::string label, T& value, bool selected);
	virtual void AddLast(std::string label, T& value, bool selected);
	virtual void AddAt(std::string label, T& value, int index, bool selected);


	void setSelectedValue(int index, T value);
	T& getSelectedValue();
	T& getValue(int index);

	T& getSelectedLabel();
	T& getLabel(int index);

	//Main label access

	void setOptionLabel(std::string label);
	void setOptionLabel(char* label);
	std::string getOptionLabel();

	///Callback
	virtual void onValueChanged();
private:
	std::string mLabel;
};
#endif