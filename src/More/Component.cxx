#include "Component.h"

Component::Component(bool active = false, bool visible = false, bool collidable = false):
	mActive(active),
	mVisible(visible),
	mCollidable(collidable){
}
Component::~Component(){}
void Component::update(float delta){}
void Component::render(void* target){}
void Component::debugRender(void* target){}

bool Component::active() const{
	return mActive;
}
bool Component::visible() const{
	return mVisible;
}
bool Component::collidable() const{
	return mCollidable;
}

bool& Component::rActive(){
	return mActive;
}
bool& Component::rVisible(){
	return mVisible;
}
bool& Component::rCollidable(){
	return mCollidable;
}



void Component::add(Component* c){
}
void Component::remove(Component* c){
}