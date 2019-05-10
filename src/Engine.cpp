#include "Engine.h"

Engine* Engine::mInstance = 0;

Engine * Engine::getInstance()
{
	if (mInstance == 0) {
		mInstance = new Engine();
	}
	return mInstance;
}

Engine::Engine():
	mFpsCounter(0),
	isRunning(true)
{
}

Engine::~Engine()
{

}

void Engine::loadContent()
{
}

void Engine::unloadContent()
{
}

void Engine::initialize()
{
}

void Engine::draw(sf::Time time)
{

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
		//lag += elapsed;

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


float Engine::DeltaTime()
{
	return 0.0f;
}
