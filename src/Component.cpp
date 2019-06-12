#include "Component.h"
#include "Entity.h"


Component::Component(bool activ, bool visib):
	active{activ},
	visible{visib}
{
}

Component::~Component()
{
}

void Component::update()
{
}

void Component::render()
{
}

void Component::removeSelf()
{
	if (mEntity) {
		mEntity->remove(this);
	}
}
