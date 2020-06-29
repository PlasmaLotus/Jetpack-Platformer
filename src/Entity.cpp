#include "Entity.h"
#include "Engine.h"
#include <algorithm>
Entity::Entity() : Entity(sf::Vector2f(0.f, 0.f)) {	 
}
	
Entity::Entity(sf::Vector2f pos) :
	mPosition(pos),
	mActive(true),
	mVisible(true),
	mCollidable(true)
{
	debugRectangle = sf::RectangleShape(sf::Vector2f(8, 8));
}

Entity::~Entity()
{
	for (Component* c : mComponents) {
		if (c) {
			delete c;
		}
	}
	mComponents.clear();
	mGabageComponentList.clear();
}

void Entity::Update()
{

	//Update Components
	for (Component* c : mComponents) {
		if (c) {
			c->Update();
		}
		else { 
			mGabageComponentList.push_back(c); 
		}
	}

	//Clear garbage list
	for (int i = mGabageComponentList.size() - 1; i >= 0; --i) {
		Component * c = mGabageComponentList.back();
		if (c) {
			delete c;
		}
		mGabageComponentList.remove(c);
		mComponents.remove(c);
	}
}

void Entity::Render()
{
	//Render all components
	for (Component* c : mComponents) {
		if (c) {
			c->Render();
		}
	}
}

void Entity::debugRender()
{
	debugRectangle.setPosition(mPosition);
	Engine::getInstance().getWindow()->draw(debugRectangle);

	/*
	bool flag = this.Collider != null;
	if (flag)
	{
		this.Collider.Render(camera, this.Collidable ? Color.Red : Color.DarkRed);
	}
	this.Components.DebugRender(camera);
	*/
}

void Entity::Awake(void * scene)
{
	for(Component* c : mComponents)
	{
		c->EntityAwake();
	}
}

void Entity::Added(void* scene)
{
	for (Component* c : mComponents)
	{
		c->EntityAdded(scene);
	}
	//mScene = scene;
}

void Entity::Removed(void* scene)
{
	for (Component* c : mComponents)
	{
		c->EntityRemoved(scene);
	}
	//mScene = nullptr;
}

void Entity::RemoveSelf()
{
	/*
	if (flag)
	{
		this.Scene.Entities.Remove(this);
	}
	*/
}

void Entity::Add(Component * c)
{
	mComponents.push_back(c);

	c->Added(this);
}

void Entity::Remove(Component * c)
{
	//put in garbage pile
	mGabageComponentList.push_back(c);

	c->Removed(this);
}

bool Entity::Active()
{
	return mActive;
}

bool Entity::Visible()
{
	return mVisible;
}

bool Entity::Collidable()
{
	return mCollidable;
}

void Entity::CollisionCheck(Entity const & e)
{
}

void Entity::CollisionCheck(Entity const & e, sf::Vector2f at)
{
}

void Entity::SceneBegin(void* scene) {
//Do stuff to the entity when the scene begins
}
void Entity::SceneEnd(void* scene) {
//Do stuff when the scene ends
}