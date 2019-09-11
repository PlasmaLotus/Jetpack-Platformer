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

	//Menu();

	//Repeatable is true by default
	Menu(const bool repeatable);
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
	void setSelection(const int index);

	//Change the index of the selected MenuItem to the first item
	void setSelectionFirst();

	//Change the index of the selected MenuItem to the last item
	void setSelectionLast();


	//Get the index of the currently selected MenuItem
	unsigned int getSelectedIndex() const;

	//Get the currently selected MenuItem
	MenuItem& getSelectedItem() const;

	//Get the first MenuItem in this Menu
	MenuItem& getFirstItem() const;

	//Get the first MenuItem in this Menu
	MenuItem& getLastItem() const;

	//Get the MenuItem at the index
	//negative value means start in reverse order (from last)
	MenuItem& getItem(const int index) const;


	//Get all the MenuItems in the Menu
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

	virtual void OnUpdate();
	virtual void OnSelectionError();
	virtual void OnSelectionChange();
	virtual void OnSelectionIncrease();
	virtual void OnSelectionDecrease();
	virtual void OnSelectionConfirm();
	virtual void OnSelectionAltConfirm();
	virtual void OnItemsChange();
	//virtual void OnReturn();

#pragma endregion Callbacks

#pragma region Shifting
	//{Shifting 

	//Shift the selected MenuItem left by the amount 
	virtual void shiftSelectionLeft(int amount);

	//Shift the selected MenuItem right by the amount
	virtual void shiftSelectionRight(int amount);

	//Shift the selected MenuItem by the amount
	virtual void shiftSelection(int amount);

	//Activate the currently selected MenuItem
	virtual void confirmSelection();

	//Activate Alt the currently selected MenuItem
	virtual void altConfirmSelection();

	//}~Shifting
#pragma endregion Shifting Items left to right

#pragma region ItemsModifiers

	//Add a MenuItem to this menu
	void addItem(MenuItem* item);

	//Add MenuItems to this menu
	void addItems(std::vector<MenuItem*> items);

	//Add a MenuItem to this menu
	void addItemAt(MenuItem* item, const int index);

	//Add MenuItems to this menu
	void addItemsAt(std::vector<MenuItem*> items, const int index);

	//Remove MenuItem from this menu
	void removeItem(MenuItem* item);

	//Remove MenuItems from this menu
	void removeItems(std::vector<MenuItem*> items);

#pragma endregion Add and Remove MenuItems

protected:


	std::vector<MenuItem*> mItems;
	int mSelection;
	bool mRepetable;
	void addItem(MenuItem menuItem);
	bool _inputted;
	int _inputTime;
	static const int INPUT_INITIAL_DELAY{ 400 };
	static const int INPUT_INCRIMENTAL_DELAY{ 20 };
};

#endif
