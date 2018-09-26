#ifndef __ENTITY__
#define __ENTITY__

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include <math>
#include "Component.h"

class Entity {
public:
	Entity();
	Entity(sf::Vector2f pos);
	virtual ~Entity();

	virtual void update();
	virtual void render();
	virtual void debugRender();
	virtual void added(char Scene);
	virtual void removed(char Scene);
	virtual void removeSelf();
	virtual void add(Component* c);
	virtual void remove(Component* c);
	bool active;
	bool visible;
	bool collidable;
	

	sf::Vector2f position() { return mPosition; };
	sf::Vector2f & rPosition() { return mPosition; };
protected:
	sf::Vector2f mPosition;
	//Scene mScene;
	std::list<Component*> mComponents;
	std::list<Component*>mGabageComponentList;


};

#endif // ENTITY