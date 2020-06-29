#ifndef __ENTITY__
#define __ENTITY__

#include <SFML/Graphics.hpp>
#include <list>
//#include <algorithm>
#include <math.h>
#include "Component.h"


class Collider;
class Entity {
public:
	Entity();
	Entity(sf::Vector2f pos);
	virtual ~Entity();

	virtual bool Active();
	virtual bool Visible();
	virtual bool Collidable();

	virtual void Update();
	virtual void Render();
	virtual void debugRender();
	virtual void Awake(void* Scene);
	virtual void Added(void* Scene);
	virtual void Removed(void* Scene);
	virtual void RemoveSelf();
	virtual void Add(Component* c);
	virtual void Remove(Component* c);

	//virtual void HandleGraphicsReset();
	//virtual void HandleGraphicsCreate();

	//scene stuff
	virtual void SceneBegin(void* scene);
	virtual void SceneEnd(void* scene);


	sf::Vector2f position() { return mPosition; }
	sf::Vector2f & rPosition() { return mPosition; }
	void setPosition(sf::Vector2f pos) { mPosition = pos; }
protected:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
	//Scene mScene;
	std::list<Component*>mComponents;
	std::list<Component*>mGabageComponentList;

	sf::RectangleShape debugRectangle;

	//Collision
	virtual void CollisionCheck(Entity const& e);
	virtual void CollisionCheck(Entity const& e, sf::Vector2f at);

	bool mActive;
	bool mVisible;
	bool mCollidable;

};

#endif // ENTITY