#include "Entity.h"

Entity::Entity() : Entity(sf::Vector2f(0.f, 0.f)) {	 
}
	
Entity::Entity(sf::Vector2f pos) :
	mPosition(pos)
{
	active = true;
	collidable = true;
	visible = true;
}

Entity::~Entity()
{
	for (Component* c : mComponents) {
		if (c) {
			delete c;
		}
	}
	mComponents.clear();
}

void Entity::update()
{
	for (Component* c : mComponents) {
		if (c) {
			c->update();
		}
		else { 
			mGabageComponentList.push_back(c); 
		}
	}

	for (int i = mGabageComponentList.size() - 1; i >= 0; --i) {
		Component * c = mGabageComponentList.back();
		if (c) {
			delete c;
		}
		mGabageComponentList.remove(c);
	}
}

void Entity::render()
{
	for (Component* c : mComponents) {
		if (c) {
			c->render();
		}
	}
}

void Entity::added(char Scene)
{
}

void Entity::removed(char Scene)
{
}

void Entity::removeSelf()
{
}

void Entity::add(Component * c)
{
	mComponents.push_back(c);
}

void Entity::remove(Component * c)
{
	mGabageComponentList.push_back(c);
}
