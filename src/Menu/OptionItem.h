/*
Created by PlasmaLotus
Updated Sept 10, 2019
*/

#ifndef _Option_Menu_Item_
#define _Option_Menu_Item_

#include "MenuItem.h"
#include <list>
#include <vector>
#include <map>
#include <tuple>
#include <string>

//This list is non repeatable
/*
This OptionItem is an item that has a list of selectable values.
Each value has a Label:string and a value T. 
The label is the menu item text that will be viewed on the menu and the value is the actual value.
*/
template <typename T>
class OptionItem :
	public MenuItem
{
public:
	OptionItem(std::string label):
		MenuItem(label)/*,
		mIndex( 0 ),
		mPrevIndex{ 0 },
		sine{ 0.0f }*/{
		mIndex = 0;
		mPrevIndex = 0;
		sine = 0.0f;
		mValues = std::vector<std::tuple<std::string, T>>();
	}

	//Ctor with vector of tuples
	OptionItem(std::string label, std::vector<std::tuple<std::string, T>>& items, unsigned int selectedIndex = 0) :
		OptionItem(label) {
		//Copy each item
		for (std::tuple<std::string, T> tuple : items) {
			std::string l{ std::get<0>(tuple) };
			T t{ std::get<1>(tuple) };
			add(l, t);
		}
	}

	//Ctor with map
	OptionItem(std::string label, std::map<std::string, T> items) :
		OptionItem(label) {
		//Copy each item
		for (std::tuple<std::string, T> tuple : items) {
			std::string l{ std::get<0>(tuple) };
			T t{ std::get<1>(tuple) };
			add(l, t);
		}
		//TODO setIndex method
		mIndex = 0;
	}
	
	virtual ~OptionItem() {
		mValues.clear();
	}

	virtual void Update(float dt) {
		sine += dt;
	}
	virtual void Render(void* renderTarget) {
		//Any rendering to do yet?
	}

	///ADD and remove tuples

	//Add a Value and corresponding label to the OptionItem list
	void add(std::string label, T value, bool selected = false) {
		mValues.push_back(std::make_tuple(label, value));
		if (selected) {
			mIndex = mValues.size() - 1;
		}
	}
	//Add a Value and corresponding label to the OptionItem list
	void add(std::tuple<std::string, T> tuple, bool selected = false) {
		add(std::get<0>(tuple), std::get<1>(tuple), selected);
	}


	void addFirst(std::string label, T value, bool selected = false) {
		mValues.emplace(mValues.begin(),(std::make_tuple(label, value)));
		if (selected) {
			mIndex = 0;
		}
	}
	//void addLast(std::string label, T value, bool selected = false);
	void addAt(std::string label, T value, int index, bool selected = false) {
		if (index >= 0) {
			if (index < mValues.size()) {
				mValues.emplace(mValues.begin()+index, (std::make_tuple(label, value)));
				if (selected) {
					mIndex = index;
				}
			}
			else {
				mValues.push_back(std::make_tuple(label, value));
				if (selected) {
					mIndex = mValues.size() - 1;
				}
			}
		}
	}

	//Overwrite the value at a selected index
	//If this index is not found nothing happens
	void setValue(int index, T value) {
		//TODO
	}
	//Get the currently selected value of the OptionItem
	T getSelectedValue() {
		return std::get<1>(_getSelectedTuple(mIndex));
	}
	T getValueAt(int index) {
		return std::get<1>(_getSelectedTuple(index));
	}

	std::string getSelectedLabel() {
		return std::get<0>(_getSelectedTuple(mIndex));
	}
	std::string getLabelAt(int index) {
		return std::get<0>(_getSelectedTuple(index));
	}

	std::tuple<std::string, T>& _getSelectedTuple(unsigned int index) {
		//auto it{ mValues.begin() };
		//std::vector<std::tuple<std::string, T>>::iterator it{ mValues.begin() };
		std::tuple<std::string, T> & value{ mValues.at(index) };
		return value;
	}
	
	//Change the index of the selected value to the left (-)
	virtual void LeftShift() {
		if (mIndex > 0) {
			mPrevIndex = mIndex;
			mIndex--;
			OnShiftLeft();
		}
	}
	//Change the index of the selected value to the right (+)
	virtual void RightShift() {
		if (mIndex < mValues.size()) {
			mPrevIndex = mIndex;
			mIndex++;
			OnShiftRight();
		}
	}

	//Callback
	//OnShift
	//virtual void OnValueChanged();
private:
	unsigned int mIndex;
	float sine;
	int lastDir;
	unsigned int mPrevIndex;
	std::vector<std::tuple<std::string, T>> mValues;
};

#endif