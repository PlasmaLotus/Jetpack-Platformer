#include "Component.h"
#include "Entity.h"


Component::Component(bool active, bool visible):
	mActive{active},
	mVisible{visible}
{
}

Component::~Component()
{
}


void Component::Update()
{
}

void Component::Render()
{
}

void Component::RemoveSelf()
{
	if (mEntity) {
		mEntity->Remove(this);
	}
}

bool Component::Active()
{
	return mActive;
}

bool Component::Visible()
{
	return mVisible;
}

void Component::Added(Entity * e)
{
	mEntity = e;
	/*
	bool flag = this.Scene != null;
	if (flag)
	{
		this.Scene.Tracker.ComponentAdded(this);
	}
	*/
}

void Component::Removed(Entity * e)
{
	/*
	bool flag = this.Scene != null;
	if (flag)
	{
		this.Scene.Tracker.ComponentRemoved(this);
	}
	*/
	mEntity = nullptr;
}

void Component::EntityAwake()
{
//Not sure what to do here
}

void Component::EntityRemoved(void * scene)
{
}

void Component::EntityAdded(void * scene)
{
}
