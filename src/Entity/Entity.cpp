#include "Entity.h"
//using namespace pl;

//namespace pl {

	Entity::Entity() : Entity(Vector2(0.f, 0.f)) {
	}

	Entity::Entity(Vector2 pos) :
		Entity(pos, true, true, true)
	{
	}

	Entity::Entity(Vector2 pos, bool active, bool visible, bool collidable) :
		mPosition(pos),
		mActive(active),
		mVisible(visible),
		mCollidable(collidable)
	{
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

	void Entity::Update(float dt)
	{
		for (Component* c : mComponents) {
			if (c) {
				c->Update(dt);
			}
			else {
				mGabageComponentList.push_back(c);
			}
		}

		//TODO: from int to size_t
		for (int i = mGabageComponentList.size() - 1; i >= 0; --i) {
			Component * c = mGabageComponentList.back();
			if (c) {
				delete c;
			}
			mGabageComponentList.remove(c);
		}
	}

	void Entity::Render(void* renderTarget)
	{
		for (Component* c : mComponents) {
			if (c) {
				c->Render(renderTarget);
			}
		}
	}

	void Entity::debugRender()
	{
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

	bool Entity::active()
	{
		return mActive;
	}

	bool Entity::visible()
	{
		return mVisible;
	}

	bool Entity::collidable()
	{
		return mCollidable;
	}

	void Entity::CollisionCheck(Entity const & e)
	{
	}

	void Entity::CollisionCheck(Entity const & e, Vector2 at)
	{
	}

//}//Namespace PL