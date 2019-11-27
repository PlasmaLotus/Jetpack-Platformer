#ifndef __State__
#define __State__

/*
Describes one of the states In the state manager. 
This should be where to check Input, container for menu and game as well
*/
class State {
public:
	State();
	virtual ~State();
	virtual void Update(float delta);
	virtual void Render(void* renderTarget);
	virtual void OnEnter();
	virtual void OnExit();
//private:
};

#endif
