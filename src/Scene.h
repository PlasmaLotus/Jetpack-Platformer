#ifndef __SCENE__
#define __SCENE__

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include "Entity.h"

class Scene
{
	Scene();
	virtual ~Scene();
	int width;
	int height;
public:
	
	virtual void render();
	virtual void update(sf::Time time);
	

private:
	std::list<Entity> mEntities;

};


#endif // SCENE
