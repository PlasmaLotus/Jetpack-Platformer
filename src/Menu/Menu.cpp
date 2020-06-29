#include "Menu.h"
//#include "../States/StateManager.h"
#include "Utility/Utility.h"

Menu::Menu(const bool repeat = true) :
	mSelection(0),
	mRepetable(repeat)
{
}

Menu::Menu(std::vector<MenuItem*>& items, const bool repetable = true) :
	Menu(repetable) 
{
	/*
	std::vector<MenuItem*>::iterator it = items.begin();
	while (it != items.end()) {
		if ((*it)) {
			mItems.emplace((*it));
			++it;
		}
		else {
			//remove if the pointer is empty
			it = mItems.erase(it);
		}
	}
	mItems = std::vector<MenuItem*>();
	*/
}

Menu::~Menu(){
	//Delete all items in the menu
	for (MenuItem* item : mItems) {
		if (item) {
			delete item;
		}
	}
	mItems.clear();
}

void Menu::Update(const float dt){
	//auto it = mItems.begin();
	std::vector<MenuItem*>::iterator it = mItems.begin();
	while(it != mItems.end()) {
		if ((*it)) {
			(*it)->Update(dt);
			++it;
		}
		else {
			//remove if the pointer is empty
			it = mItems.erase(it);
		}
	}
	_isSelectionValid();
}

void Menu::Render(void * renderTarget){
	std::vector<MenuItem*>::iterator it = mItems.begin();
	while (it != mItems.end()) {
		if ((*it)) {
			(*it)->Render(renderTarget);
			++it;
		}
	}
}
#pragma region Selection_Control

void Menu::moveSelection(const int amount)
{
	if (amount > 0)
		moveSelectionUp(amount);
	else
		if (amount < 0)
			moveSelectionDown(-amount);
}

void Menu::moveSelectionUp(const unsigned int amount)
{
	for (unsigned int i = 1; i <= amount; ++i) {
		moveSelectionUpOnce();
	}
}

void Menu::moveSelectionDown(const unsigned int amount)
{
	for (unsigned int i = 1; i <= amount; ++i) {
		moveSelectionDownOnce();
	}
}


void Menu::setSelection(const int index){
	if (index >= 0 && index < mItems.size()) {
		mPreviousSelection = mSelection;
		mSelection = index;
		OnSelectionChanged();
	}
	else {
		//Cannot set the selection to this index
		//OnSelectionChangedError();
	}
}

void Menu::setSelectionFirst(const bool callback = true){
	/*
	unsigned int start = 0;
	const MenuItem* item{ mItems.at(start) };
	while (!item->selectable()) {
		++start;
		item = mItems.at(start);
	}
	mSelection = start;
	*/
	setSelection(firstSelectableIndex());
	/*
	if(callback)
		OnSelectionChanged();
	*/
}

void Menu::setSelectionLast(const bool callback = true){
	/*
	unsigned int end = mItems.size() - 1;
	const MenuItem* item{ mItems.at(end) };
	while (!item->selectable()) {
		--end;
		item = mItems.at(end);
	}
	mSelection = end;
	*/
	setSelection(lastSelectableIndex());
	/*
	if(callback)
		OnSelectionChanged();
	*/
}

void Menu::moveSelectionDownOnce(){
	//If the menu is not repeatable and the index is the 1st of the list
	if (!repetable() && mSelection >= lastSelectableIndex()) {
		setSelectionLast(false);
		OnSelectionChangedError();
	}
	else {
		//For Selection in the middle of the menu, get previous selectable MenuItem
		const MenuItem* item{ nullptr };
		bool found = false;
		int next = mSelection;
		int size = mItems.size();
		//for loop should not start if i == -1
		for (int i = mSelection + 1; i < size; ++i) {
			item = mItems.at(i);
			if (item->selectable()) {
				next = i;
				found = true;
				break;
			}
		}
		//Set the index
		if (found) {
			setSelection(next);//mSelection = previous;
		}
		else {
			setSelectionFirst();
		}
		OnSelectionUp();
	}
}

void Menu::moveSelectionUpOnce(){
	//If the menu is not repeatable and the index is the 1st of the list
	if (!repetable() && mSelection <= firstSelectableIndex()) {
		setSelectionFirst(false);
		OnSelectionChangedError();
	}
	else {
		//For Selection in the middle of the menu, get previous selectable MenuItem
		const MenuItem* item{ nullptr };
		bool found = false;
		int previous = mSelection;
		//for loop should not start if i == -1
		for (unsigned int i = mSelection - 1; i >= 0; --i) {
			item = mItems.at(i);
			if (item->selectable()) {
				previous = i;
				found = true;
				break;
			}
		}
		//Set the index
		if (found) {
			setSelection(previous);//mSelection = previous;
		}
		else {
			setSelectionLast();
		}
		OnSelectionUp();
	}
}

int Menu::firstSelectableIndex() const {
	int index { -1 };
	unsigned int size = mItems.size();
	if (size <= 0) {
		const MenuItem* item{ nullptr };
		for (unsigned int i = 0; i < size; ++i) {
			item = mItems.at(i);
			if (item->selectable()) {
				index = i;
				break;
			}
		}
	}
	return index;
}

int Menu::lastSelectableIndex() const{
	int index{ -1 };
	unsigned int size = mItems.size();
	if (size <= 0) {
		const MenuItem* item{ nullptr };
		for (int i = size -1; i >= 0; --i) {
			item = mItems.at(i);
			if (item->selectable()) {
				index = i;
				break;
			}
		}
	}
	return index;
}

unsigned int Menu::getSelectedIndex() const
{
	return mSelection;
}

MenuItem* Menu::getSelectedItem() const
{
	return mItems.at(mSelection);
	// TODO: insert return statement here
}

MenuItem* Menu::getFirstItem() const{
	return mItems.at(0);
}

MenuItem * Menu::getLastItem() const{
	return mItems.at(0);
}

MenuItem * Menu::getItem(const int index) const
{
	MenuItem* item{ nullptr };
	if (index < mItems.size())
		item = mItems.at(index);
	return item;
}

std::vector<MenuItem*> Menu::items() const{
	return std::vector<MenuItem*>(mItems);
}

unsigned int Menu::getTotalItemCount() const{
	return mItems.size();
}

unsigned int Menu::getVisibleItemCount() const{
	unsigned int count{ 0 };
	for (MenuItem* item : mItems) {
		if (item)
			if (item->visible())
				++count;
	}
	return count;
}

unsigned int Menu::getSelectableItemCount() const{
	unsigned int count{ 0 };
	for (MenuItem* item : mItems) {
		if (item)
			if (item->selectable())
				++count;
	}
	return count;
}

unsigned int Menu::getActiveItemCount() const{
	unsigned int count{ 0 };
	for (MenuItem* item : mItems) {
		if (item)
			if (!item->disabled())
				++count;
	}
	return count;
}

unsigned int Menu::getDisabledItemCount() const{
	unsigned int count{ 0 };
	for (MenuItem* item : mItems) {
		if (item)
			if (item->visible())
				++count;
	}
	return count;
}

#pragma endregion

bool Menu::repetable() const{
	return mRepetable;
}

#pragma region Callbacks

void Menu::OnMenuUdpaded() {
	//Remove empty pointers
	std::vector<MenuItem*>::iterator it = mItems.begin();
	while (it != mItems.end()) {
		if ((*it)) {
			++it;
		}
		else {
			//remove if the pointer is empty
			it = mItems.erase(it);
		}
	}

	//Ajust Selection to nearest one
	int size = mItems.size();
	bool downwards = false;
	
	if (mSelection < 0)
		mSelection = 0;
	else {
		if (mSelection >= size)
			mSelection = size - 1;
	}
	const MenuItem * wItem{ mItems.at(mSelection) };
	while (!wItem->selectable()) {
		if (mSelection <= 0)
			downwards = true;
		if (mSelection >= size - 1)
			downwards = false;
		downwards ? ++mSelection : --mSelection;
		wItem = mItems.at(mSelection);
	}
}
void Menu::OnSelectionChangedError() {}
void Menu::OnSelectionChanged() { OnMenuUdpaded(); }
void Menu::OnSelectionUp() { /*OnSelectionChanged()*/; }
void Menu::OnSelectionDown() { /*OnSelectionChanged()*/; }
void Menu::OnSelectionConfirmed() {}
void Menu::OnSelectionAltConfirmed() {}
void Menu::OnSelectionConfirmedError() {}
void Menu::OnItemsChanged() { OnMenuUdpaded(); }
void Menu::OnItemShifted() { OnMenuUdpaded(); }
void Menu::OnItemShiftedError() {}
void Menu::OnItemShiftedLeft() { OnItemShifted(); }
void Menu::OnItemShiftedRight() { OnItemShifted(); }
#pragma endregion

#pragma region Shifting


void Menu::shiftSelectionLeft(const int amount){
	if (amount >= 0) {
		for (int i = amount; i > 0; --i) {
			shiftSelectionLeftOnce();
		}
	}
}

void Menu::shiftSelectionRight(int amount)
{
	if (amount >= 0) {
		for (int i = amount; i > 0; --i) {
			shiftSelectionRightOnce();
		}
	}
}

void Menu::shiftSelection(const int amount){
	if (amount > 0)
		shiftSelectionRight(amount);
	else
		if(amount < 0)
			shiftSelectionLeft(-amount);
}

void Menu::shiftSelectionRightOnce(){
	//Do i need to check the validity
	if (_isSelectionValid()) {
		MenuItem* item = mItems.at(mSelection);
		//while (!item) {
		//	mItems.erase(mItems.begin() + mSelection);

		if (item) {
			if (item->shiftable()) {
				item->RightShift();
				OnItemShiftedRight();
			}
			else {
				OnItemShiftedError();
			}
		}
	}
}

void Menu::shiftSelectionLeftOnce(){
	//Do i need to check the validity
	if (_isSelectionValid()) {
		MenuItem* item = mItems.at(mSelection);
		//while (!item) {
		//	mItems.erase(mItems.begin() + mSelection);

		if (item) {
			if (item->shiftable()) {
				item->LeftShift();
				OnItemShiftedLeft();
			}
			else {
				OnItemShiftedError();
			}
		}
	}
}

void Menu::addItem(MenuItem * item){
	if (item) {
		_OnAddItem(item);
		mItems.push_back(item);
	}
}

void Menu::addItems(std::vector<MenuItem*> items){
	for (MenuItem* item : items) {
		if (item) {
			_OnAddItem(item);
			mItems.push_back(item);
		}
	}
}

void Menu::addItemAt(MenuItem * item, const int index){
	if (item) {
		_OnAddItem(item);
		if (abs(index) < mItems.size()) {
			if (index >= 0)
				mItems.emplace(mItems.begin() + index, item);
			else
				mItems.emplace(mItems.end() + index, item);
		}
	}
		
}

void Menu::addItemsAt(std::vector<MenuItem*> items, int index)
{
	//unsigned int wIndex{ 0 };
	auto it = mItems.begin();
	int inc = Utility::sign(index);
	if (inc < 0 ){
		it = mItems.end();
	}

	//Max out the index to be in bounds
	if (abs(index) >= mItems.size()) {
		index = mItems.size() - 1 * Utility::sign(index);
	}

	it += index;
	for (MenuItem* item : items) {
		_OnAddItem(item);
		mItems.emplace(it, item);
		it++;
	}
}

void Menu::_OnAddItem(MenuItem * item)
{
	item->Added(this);
}

void Menu::removeItem(MenuItem * item){
	for (int i = mItems.size() - 1; i >= 0; --i) {
		if (mItems.at(i) == item) {
			//Remove item
			mItems.erase(mItems.begin() + i);

			//Change selection if is higher than the removed item
			if (mSelection >= 0 && i > mSelection)
				mSelection--;
		}
	}
}

void Menu::removeAllItems()
{
	mItems.clear();
	mSelection = 0;
}

void Menu::confirmSelection()
{
	if (_isSelectionValid()) {
		MenuItem* item = mItems.at(mSelection);

		if (item) {
			if (item->hoverable()) {
				item->ConfirmAction();
				OnSelectionConfirmed();
				//OnItemsChanged();
			}
			else {
				OnSelectionConfirmedError();
			}
		}
	}
}

void Menu::altConfirmSelection()
{
	if (_isSelectionValid()) {
		MenuItem* item = mItems.at(mSelection);

		if (item) {
			if (item->hoverable()) {
				item->AltAction();
				OnSelectionAltConfirmed();
				//OnItemsChanged();
			}
			else {
				OnSelectionConfirmedError();
			}
		}
	}
}
#pragma endregion

bool Menu::_isSelectionValid(){
	return mSelection >= 0 && mSelection < mItems.size();
}
