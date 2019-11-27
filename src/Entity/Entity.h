#ifndef __ENTITY__
#define __ENTITY__

//#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include <math.h>
#include "Component.h"

#include "Utility/Vector2.h"
//#include <SFML/Graphics.hpp>
//using namespace pl;
//namespace pl {

class Entity {
public:
	Entity();
	Entity(Vector2 pos);
	Entity(Vector2 pos, bool active, bool visible, bool collidable);
	virtual ~Entity();

	virtual void Update(float dt);
	virtual void Render(void* renderTarget);
	virtual void debugRender();
	virtual void added(char Scene);
	virtual void removed(char Scene);
	virtual void removeSelf();
	virtual void add(Component* c);
	virtual void remove(Component* c);
	
	virtual bool active();
	virtual bool visible();
	virtual bool collidable();
	
	Vector2 position() { return mPosition; };
	Vector2 & rPosition() { return mPosition; };
protected:
	Vector2 mPosition;
	//Scene mScene;
	std::list<Component*> mComponents;
	std::list<Component*>mGabageComponentList;

	//Collision
	virtual void CollisionCheck(Entity const& e);
	virtual void CollisionCheck(Entity const& e, Vector2 at);

	bool mActive;
	bool mVisible;
	bool mCollidable;
};

//}//Namespace pl

#endif // ENTITY