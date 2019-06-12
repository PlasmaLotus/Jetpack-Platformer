#include "Engine.h"


float Engine::mRawDeltaTime = 0.0f;
float Engine::mDeltaTime = 0.0f;
float Engine::DeltaTime()
{
	//TODO:fjdoasljfdnspaioh
	return 0.0f;
}

float Engine::RawDeltaTime()
{
	return 0.0f;
}

Engine::Engine():
	mElapsedTime(sf::Time::Zero),
	mElapsedTimeTotal(sf::Time::Zero),
	mPrevElapsedTime(sf::Time::Zero),
	mTargetElapsedTime(sf::Time::Zero),
	mTargetElapsedTimeRender(sf::Time::Zero),
	mAccumulatedElapsedTime(sf::Time::Zero),
	mAccumulatedElapsedTimeRender(sf::Time::Zero),
	mFrameCounter(0),
	_mFrameSubCounter(0),
	_prevTimeStamp(sf::Time::Zero),
	mClock(sf::Clock()),
	isRunning(true),
	_mFpsDeltaTime(sf::Time::Zero),
	isFixedTimeStep(false),
	isFixedTimeStepRender(false),
	ticks(0),
	previousTicks(0)
{
	mAccumulatedElapsedTime = mAccumulatedElapsedTimeRender = sf::Time::Zero;
	mPrevElapsedTime = mClock.restart();
	mElapsedTime = mClock.restart();
	//mElapsedTimeRender = mElapsedTime;
	//mLag
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
		mElapsedTimeTotal += mElapsedTime;
		//mElapsedTimeRender = mElapsedTine;
		//lag += elapsed;

		mRawDeltaTime = mElapsedTime.asSeconds();

		sf::Event event;
		while (mWindow.pollEvent(event)){
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
	mFrameCounter++;
	_mFrameSubCounter++;
	if (mFrameCounter % mFrameCounter == 42) {
		
		sf::Time _lmao = mElapsedTimeTotal - _prevTimeStamp;
		mDeltaTime = _lmao.asSeconds() / _mFrameSubCounter;
		_fps = 1.0f / mDeltaTime;
		_prevTimeStamp = mElapsedTimeTotal;
	}
	//Handle ununiform time
	//update Game

	if (isFixedTimeStep) {
		int lmao = 0;
		//mElapsedTime = mTargetElapsedTime;
		//mAccumulatedElapsedTime -= mTargetElapsedTime;
		mAccumulatedElapsedTime += mElapsedTime;

		//MS_PER_FRAME
		while (mAccumulatedElapsedTime >= mTargetElapsedTime) {
			update(mElapsedTime);
			++lmao;
			mAccumulatedElapsedTime -= mElapsedTime;
		}
	}
	else {
		//Just tick as often as the PC can
		update(mElapsedTime);
		//mElapsedTime = mAccumulatedElapsedTime;
		//mAccumulatedElapsedTime = sf::Time::Zero;
		//update(mElapsedTime);
	}

	// Rendering
	bool renderThisFrame = false;

	if (isFixedTimeStepRender) {
		mAccumulatedElapsedTimeRender += mElapsedTime;
		//MS_PER_RENDER_FRAME
		while (mAccumulatedElapsedTimeRender >= mTargetElapsedTimeRender) {
			renderThisFrame = true;
			draw(mAccumulatedElapsedTime);
			mAccumulatedElapsedTimeRender -= mElapsedTime;
		}
	}
	else {
		//Render every tick
		renderThisFrame = true;
		draw(mElapsedTime);
	}


	
}

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
	/*
	if (!mInstance) {
		mInstance = new Engine();
	}
	return *mInstance;
	*/
	
}
