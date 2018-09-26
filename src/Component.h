#ifndef __COMPONENT__
#define __COMPONENT__

#include <SFML/Graphics.hpp>

class Entity;
class Component
{
public:
	Component(bool activ, bool visib);
	virtual ~Component();

	Entity* entity() { return mEntity; };

	bool active;
	bool visible;

	virtual void update();
	virtual void render();
	virtual void removeSelf();

private:
	Entity* mEntity;
	int* mScene;
};

#endif // __COMPONENT__