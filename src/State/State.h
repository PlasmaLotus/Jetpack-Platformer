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
	virtual void update();
	virtual void render();
	virtual void goBack();
	bool renderWhenUnfocused();
	bool updateWhenUnfocused();


	virtual void onFocus();
	virtual void onUnfocus();

protected:
	bool _renderWhenUnfocused = false;
	bool _updateWhenUnfocused = false;
private:
};

#endif
