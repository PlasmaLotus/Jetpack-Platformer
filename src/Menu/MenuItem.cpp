#include "MenuItem.h"
#include "Menu.h"

MenuItem::MenuItem():
	mSelectable(true),
	mVisible(true),
	mDisabled(false),
	mShiftable(false)
{
}

MenuItem::~MenuItem(){
	mParent = nullptr;
}

void MenuItem::Update(const float dt){}

void MenuItem::Render(void * renderTarget){}

bool MenuItem::hoverable() const {
	return mSelectable && mVisible && !mDisabled;
}

bool MenuItem::selectale() const {
	return mSelectable;
}

bool MenuItem::visible() const {
	return mVisible;
}

bool MenuItem::disabled() const {
	return mDisabled;
}

bool MenuItem::shiftable() const
{
	return mShiftable;
}

void MenuItem::ConfirmAction(){
	OnConfirm();
}

void MenuItem::AltAction(){
	OnAltConfirm();
}

void MenuItem::LeftAction(){
	OnShiftLeft();
}

void MenuItem::RightAction(){
	OnShiftRight();
}

void MenuItem::Added(Menu * menu){
	if (menu) {
		mParent = menu;
	}
	else {
		///TODO: action to do if null...
		mParent = menu;
	}
}

Menu * MenuItem::getContainer() const {
	return getParent();
}

Menu * MenuItem::getParent() const {
	return mParent;
}

void MenuItem::setParent(Menu * menu){
	mParent = menu;
}

void MenuItem::setContainer(Menu * menu){
	setParent(menu);
}

void MenuItem::OnUpdate() {}
void MenuItem::OnEnter() {}
void MenuItem::OnLeave() {}
void MenuItem::OnConfirm() {}
void MenuItem::OnAltConfirm() {}
void MenuItem::OnShift(){}
void MenuItem::OnShiftLeft() { 
	OnShift(); 
}
void MenuItem::OnShiftRight() { 
	OnShift(); 
}
