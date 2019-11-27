#ifndef __SPLASH_STATE__
#define __SPLASH_STATE__

#include "State.h"
class SplashScreenState :
	public State
{
public:
	SplashScreenState();
	~SplashScreenState();
	virtual void Update(float dt);
	virtual void Render(void* renderState);
};

#endif
