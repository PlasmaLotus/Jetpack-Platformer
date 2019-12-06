#ifndef __SPLASH_STATE__
#define __SPLASH_STATE__

#include <SDL_gamecontroller.h>
#include <SFML/System.hpp>

#include "State.h"
class SplashScreenState :
	public State
{
public:
	SplashScreenState();
	~SplashScreenState();
	virtual void Update(float dt);
	virtual void Render(void* renderState);

	SDL_Joystick* gGameController = nullptr;
};

#endif
