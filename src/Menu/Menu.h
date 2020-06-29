/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

//MenuState will handle input
/*Under Construction*/
//#define _Menu_

#ifndef _Menu_
#define _Menu_
#include <vector>
//#include "SFML\Graphics.hpp"
#include "MenuItem.h"

class Menu {
public:
	//Repeatable is true by default
	Menu(const bool repeat);
	Menu(std::vector<MenuItem*>& items, const bool repetable);
	virtual ~Menu();
#pragma region Loop

	//Update the Item based on a certain elapsed time frame
	virtual void Update(const float dt);

	//Display the Item on a rendering target
	virtual void Render(void* renderTarget);

#pragma endregion

#pragma region Selection_Control
	///Menu Control 

	//Change the index of the selected MenuItem by the amount (Up or Down)
	void moveSelection(const int amount);

	//Change the index of the selected MenuItem upwards by the amount
	void moveSelectionUp(const unsigned int amount);

	//Change the index of the selected MenuItem downwards by the amount
	void moveSelectionDown(const unsigned int amount);

	//Change the index of the selected MenuItem to the selected value
	//Any negative value will not change the selections
	void setSelection(const int index);

	//Change the index of the selected MenuItem to the first selectable item
	void setSelectionFirst(const bool callback);

	//Change the index of the selected MenuItem to the last selectable item
	void setSelectionLast(const bool callback);

protected:
	//Move the selection up 1 time
	void moveSelectionDownOnce();
	
	//Move the selection up 1 time
	void moveSelectionUpOnce();

	//Return the index of the last selectable MenuItem
	//This will return -1 if no such item can be found
	int firstSelectableIndex() const;
	
	//Return the index of the first selectable MenuItem
	//This will return -1 if no such item can be found
	int lastSelectableIndex() const;
public:
	//Get the index of the currently selected MenuItem
	unsigned int getSelectedIndex() const;

	//Get the currently selected MenuItem
	MenuItem* getSelectedItem() const;

	//Get the first MenuItem in this Menu
	MenuItem* getFirstItem() const;

	//Get the first MenuItem in this Menu
	//Todo: first item or selectable item?
	MenuItem* getLastItem() const;

	//Get the MenuItem at the index
	//negative value means start in reverse order (from last)
	MenuItem* getItem(const int index) const;


	//Get all the MenuItems in the Menu as a copy
	std::vector<MenuItem*> items() const;

	//Count

	//Get the number of MenuItems in this Menu
	unsigned int getTotalItemCount() const;

	//Get the number of Visible MenuItems in this Menu
	unsigned int getVisibleItemCount() const;

	//Get the number of Selectable MenuItems in this Menu
	unsigned int getSelectableItemCount() const;

	//Get the number of Active MenuItems in this Menu
	unsigned int getActiveItemCount() const;
	  
	//Get the number of Disabled MenuItems in this Menu
	unsigned int getDisabledItemCount() const;

	//getItems

	//If the menu loops back on index is out of range
	virtual bool repetable() const;
#pragma endregion Selection_Control

#pragma region Callbacks
	//Callback when the content of the menu has changed
	//Called by default when Menu selection has updated or MenuItems have been updated or shifted
	virtual void OnMenuUdpaded();
	
	//Callback when the selection change des nothing or oor expression
	virtual void OnSelectionChangedError();

	//Callback when the selection has been changed
	virtual void OnSelectionChanged();

	//Callback when the selection has changed upwards
	virtual void OnSelectionUp();

	//Callback when the selection has been changed downwards
	virtual void OnSelectionDown();

	//Callback when the selection has been selected/confirmed
	virtual void OnSelectionConfirmed();
	
	//Callback when the selection has been selected/confirmed alternatively
	virtual void OnSelectionAltConfirmed();

	//Callback when the selectied MenuItem cannot be confirmed
	virtual void OnSelectionConfirmedError();
	
	//Callback when the MenuItems have been changed
	virtual void OnItemsChanged();

	//virtual void OnReturn();
	
	//Callback when the MenuItem has been shifted or toggled
	//This is called by default by OnItemShiftLeft and OnItemShiftRight
	virtual void OnItemShifted();

	//Callback when shift failed or the item is unshiftable
	virtual void OnItemShiftedError();

	//Callback when the MenuItem has been shifted left
	virtual void OnItemShiftedLeft();

	//Callback when the MenuItem has been shifted right
	virtual void OnItemShiftedRight();

#pragma endregion Callbacks

#pragma region Shifting
	//{Shifting 

	//Shift the selected MenuItem left by the amount 
	void shiftSelectionLeft(const int amount);

	//Shift the selected MenuItem right by the amount
	void shiftSelectionRight(const int amount);

	//Shift the selected MenuItem by the amount
	//Positive means shift right and negative is shift left
	void shiftSelection(const int amount);

	//Activate the currently selected MenuItem
	void confirmSelection();

	//Activate Alt the currently selected MenuItem
	void altConfirmSelection();

private:
	void shiftSelectionRightOnce();
	void shiftSelectionLeftOnce();

public:
	//}~Shifting
#pragma endregion Shifting Items left to right

#pragma region ItemsModifiers

	//Add a MenuItem to this menu
	void addItem(MenuItem* item);

	//Add MenusItems to this menu
	void addItems(std::vector<MenuItem*> items);

	//Add a MenuItem to this menu
	//if the index is out of range, the item will be added to the last possible index
	//Negative means index start from the end
	void addItemAt(MenuItem* item, const int index);

	//Add MenuItems to this menu
	void addItemsAt(std::vector<MenuItem*> items, const int index);

	void _OnAddItem(MenuItem* item);
	//Remove MenuItem from this menu
	void removeItem(MenuItem* item);

	//Remove MenuItems from this menu
	//void removeItems(std::list<MenuItem*> items);

	void removeAllItems();
#pragma endregion Add and Remove MenuItems

protected:

	bool _isSelectionValid();
	std::vector<MenuItem*> mItems;
	unsigned int mSelection;
	unsigned int mPreviousSelection;
	bool mRepetable;
	//void addItem(MenuItem menuItem);
	bool _inputted;
	int _inputTime;
	static const int INPUT_INITIAL_DELAY{ 400 };
	static const int INPUT_INCRIMENTAL_DELAY{ 20 };
};

#endif
