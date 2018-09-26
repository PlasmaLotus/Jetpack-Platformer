#include "Engine.h"


Engine::Engine():
	mFpsCounter(0),
	isRunning(true)
{
}


Engine::~Engine()
{

}

void Engine::draw(sf::Time time)
{
	//foreach entity in entity list
	//if visible
	//window.draw()
	mWindow.clear();
	mWindow.display();
}

void Engine::run()
{
	mClock.restart();

	//Begin Run
	while (mWindow.isOpen() && isRunning)
	{
		
		mPrevElapsedTime = mElapsedTime;
		mElapsedTime = mClock.restart();
		lag += elapsed;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		tick();

		

	}
	//End Run

}

void Engine::tick()
{
	//Handle ununiform time
	//update Game

	if (isFixedTimeStep) {
		int lmao = 0;
		mElapsedTime = mTargetElapsedTime;
		mAccumulatedElapsedTime -= mTargetElapsedTime;

		while (mAccumulatedElapsedTime >= mElapsedTime) {
			++lmao;
			mAccumulatedElapsedTime -= mElapsedTime;
			update(mElapsedTime);

			
		}
	}
	else {
		update(sf::Time::Zero);
		mElapsedTime = mAccumulatedElapsedTime;
		mAccumulatedElapsedTime = sf::Time::Zero;
		update(mElapsedTime);
	}

	bool renderThisFrame = true;
	if(renderThisFrame){
		draw(sf::Time::Zero);
	}
	//Render
}

Engine * Engine::getInstance()
{
	if (!mInstance) {
		mInstance = new Engine();
	}
	return mInstance;
}
