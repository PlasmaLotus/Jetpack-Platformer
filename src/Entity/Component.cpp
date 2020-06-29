#include "Component.h"
#include "Entity.h"
//using namespace pl;

//namespace pl {

Component::Component(bool active, bool visible):
	mActive{active},
	mVisible{visible}
{
}

Component::~Component()
{
}

bool Component::active(){
	return mActive;
}

bool Component::visible(){
	return mVisible;
}

void Component::Update(float dt)
{
}

void Component::Render(void* renderTarget)
{
}

void Component::added(Entity * entity)
{
	mEntity = entity;
}

void Component::removed()
{
	mEntity = nullptr;
}

/*
void Component::removeSelf()
{
	if (mEntity) {
		mEntity->remove(this);
	}
}
*/
//}//Namespace pl
