#include "Component.h"
#include "Entity.h"


Component::Component()
{
}


Component::~Component()
{
}

void Component::update()
{
}

void Component::removeSelf()
{
	if (mEntity) {
		mEntity->remove(this);
	}
}
