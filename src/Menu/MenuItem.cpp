#include "MenuItem.h"
#include "Menu.h"

MenuItem::MenuItem(std::string label):
	MenuItem(label, true, true, false, false)
{
}

MenuItem::MenuItem(std::string label, bool visible, bool selectable, bool shiftable, bool disabled):
	mLabel(label),
	mVisible(visible),
	mSelectable(selectable),
	mShiftable(shiftable),
	mDisabled(disabled)
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

bool MenuItem::selectable() const {
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

void MenuItem::LeftShift(){
	OnShiftLeft();
}

void MenuItem::RightShift(){
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
