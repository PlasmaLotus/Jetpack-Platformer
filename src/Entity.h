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
};

#endif // ENTITY