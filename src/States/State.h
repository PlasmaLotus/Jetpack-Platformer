
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
	virtual void tick(float delta, bool render = true);
	virtual void goBack();
private:
};

#endif
