#ifndef __COMPONENT__
#define __COMPONENT__

//namespace pl {

class Entity;
class Scene;
class Component
{
public:
	Component(bool active, bool visible);
	virtual ~Component();

	Entity* entity() { return mEntity; };
	virtual bool active();
	virtual bool visible();

	virtual void Update(float dt);
	virtual void Render(void* renderTarget);

	//Called when this component is added to an entity
	virtual void added(Entity* entity);

	//Called when this component is removed from an entity
	virtual void removed();
	//virtual void removeSelf();

private:
	bool mActive;
	bool mVisible;
	Entity* mEntity;
	//Scene* mScene;
};


//}//Namespace pl

#endif // __COMPONENT__