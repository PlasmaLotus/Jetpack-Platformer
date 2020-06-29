#ifndef __COMPONENT__
#define __COMPONENT__

#include <SFML/Graphics.hpp>


class Entity;
class Component
{
public:
	/*Ctor*/
	Component(bool activ, bool visib);

	/*Dtor*/
	virtual ~Component();

	/*Returns the entity currently posessing this component*/
	Entity* entity() { return mEntity; };

	/*Update function called every frame in the game loop*/
	virtual void Update();

	/*Render the component to the frame*/
	virtual void Render();

	/*Remove the component from the engine*/
	virtual void RemoveSelf();

	/*Defines if this component is Active and has impact in-game*/
	virtual bool Active();

	/*Defines if the component is visible on screen and should be rendered*/
	virtual bool Visible();

	/*Callback applied when an entity adds this components to it's list*/
	virtual void Added(Entity* e);
	
	/*Callback applied when an entity removes this components to it's list*/
	virtual void Removed(Entity* e);


	/*Callback applied when the entity is awake*/
	virtual void EntityAwake();

	/*Callback applied when an entity is removed from the scene*/
	virtual void EntityRemoved(void* scene);

	/*Callback applied when an entity is added to a scene*/
	virtual void EntityAdded(void* scene);

	//SceneAs
	//EntityAs

private:
	Entity* mEntity;
	//Scene mScene;
	//int* mScene;
	bool mActive;
	bool mVisible;
};



#endif // __COMPONENT__