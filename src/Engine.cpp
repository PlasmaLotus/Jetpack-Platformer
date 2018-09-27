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
		

		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mWindow.close();
		}

		tick();

		

	}
	//End Run

}

void Engine::update(sf::Time time)
{
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
			update(mElapsedTime);
			++lmao;
			mAccumulatedElapsedTime -= mElapsedTime;

			
		}
	}
	else {
		//Just tick as often as the PC can
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

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
	/*
	if (!mInstance) {
		mInstance = new Engine();
	}
	return mInstance;
	 */
}
