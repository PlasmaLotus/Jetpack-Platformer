
/*
Created by PlasmaLotus
Updated May 17, 2017
*/ 
#ifndef __State__
#define __State__

class State {
public:
	State();
	virtual ~State();
	virtual void update(float delta, bool render);
	virtual void render(float delta);
	virtual void goBack();
private:
};

#endif
