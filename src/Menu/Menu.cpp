#include "Menu.h"
//#include "../States/StateManager.h"


Menu::Menu(const bool repeatable = true) :
	mSelection(0),
	mRepetable(repetable)
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

bool Menu::repetable() const{
	return mRepetable;
}
