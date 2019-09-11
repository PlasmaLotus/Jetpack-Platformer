#include "Engine.h"
//#include "Input/RawInput.h"
//#include "Event/EventManager.h"

float Engine::DeltaTime()
{
	//TODO:fjdoasljfdnspaioh
	return mTargetElapsedTime.asSeconds();
}

float Engine::DeltaTimeRender()
{
	return mTargetElapsedTimeRender.asSeconds();
}

float Engine::RawDeltaTime()
{
	return mRawDeltaTime;
	//return mElapsedTime.asSeconds();
}

unsigned int Engine::FPS()
{
	return 1/mTargetElapsedTime.asSeconds();
}

Engine::Engine():
	mElapsedTime(sf::Time::Zero),
	mElapsedTimeTotal(sf::Time::Zero),
	mPrevElapsedTime(sf::Time::Zero),
	mTargetElapsedTime(sf::seconds(1.0f/144.f)),
	mTargetElapsedTimeRender(sf::seconds(1.0f / 60.f)),
	mAccumulatedElapsedTime(sf::Time::Zero),
	mAccumulatedElapsedTimeRender(sf::Time::Zero),
	mTickCounter(0),
	_mTickSubCounter(0),
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
	Init();
}

Engine::~Engine()
{

}

void Engine::LoadContent()
{
}

void Engine::UnloadContent()
{
}

void Engine::Init()
{
	//mWindow.create(sf::VideoMode::getFullscreenModes()[0], "Neon Galaxy", sf::Style::Default);
	//mWindow.create(sf::VideoMode::getDesktopMode(), "Edge Simulator", sf::Style::Default);
	mWindow.create(sf::VideoMode(240, 160), "OK");
	mRawInput.Init();

	//mEventManager.Init();

	//StateManager

	//resourcemanager
	//audio
	//network

}

void Engine::DeInit()
{
	mRawInput.DeInit();
}
//Main loop
void Engine::run()
{
	mClock.restart();

	//Begin Run
	while (mWindow.isOpen() && isRunning)
	{
		//Time
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

void Engine::Update(sf::Time time)
{
	//Input
	mRawInput.update();
}
void Engine::draw(sf::Time time)
{
	mWindow.clear();
	//mWindow.draw(sf::CircleShape(10.0f, 10));
	mWindow.display();
}

void Engine::tick()
{
	int arbitraryValue = 69;
	mTickCounter++;
	_mTickSubCounter++;
	if (mTickCounter % arbitraryValue == 0) {
		
		sf::Time _lmao = mElapsedTimeTotal - _prevTimeStamp;
		mDeltaTime = _lmao.asSeconds() / _mTickSubCounter;
		_fps = 1.0f / mDeltaTime;
		_prevTimeStamp = mElapsedTimeTotal;
		_mTickSubCounter = 0;
	}

	//Handle ununiform time
	//update Game

	if (isFixedTimeStep) {
		int lmao = 0;
		//mElapsedTime = mTargetElapsedTime;
		//mAccumulatedElapsedTime -= mTargetElapsedTime;
		mAccumulatedElapsedTime += mElapsedTime;

		//MS_PER_FRAME
		if (mAccumulatedElapsedTime >= mTargetElapsedTime) {
			++lmao;
			Update(mTargetElapsedTimeRender);
			mAccumulatedElapsedTime -= mTargetElapsedTime;
		}
		/*
		while (mAccumulatedElapsedTime >= mTargetElapsedTime) {
			update(mElapsedTime);
			++lmao;
			mAccumulatedElapsedTime -= mElapsedTime;
		}
		*/
	}
	else {
		//Just tick as often as the PC can
		Update(mElapsedTime);
		//mElapsedTime = mAccumulatedElapsedTime;
		//mAccumulatedElapsedTime = sf::Time::Zero;
		//update(mElapsedTime);
	}

	// Rendering
	bool renderThisFrame = false;

	if (isFixedTimeStepRender) {
		mAccumulatedElapsedTimeRender += mElapsedTime;
		//MS_PER_RENDER_FRAME
		if (mAccumulatedElapsedTimeRender >= mTargetElapsedTimeRender) {
			renderThisFrame = true;
			draw(mTargetElapsedTimeRender);
			mAccumulatedElapsedTimeRender -= mTargetElapsedTimeRender;
		}
		/*
		while (mAccumulatedElapsedTimeRender >= mTargetElapsedTimeRender) {
			renderThisFrame = true;
			draw(mAccumulatedElapsedTime);
			mAccumulatedElapsedTimeRender -= mElapsedTime;
		}
		*/
	}
	else {
		//Render every tick
		renderThisFrame = true;
		draw(mElapsedTime);
	}

}

RawInput & Engine::Input(){
	return mRawInput;
}
EventManager& Engine::Event() {
	return mEventManager;
}
Engine& Engine::getInstance(){
	static Engine instance;
	return instance;
	/*
	if (!mInstance) {
		mInstance = new Engine();
	}
	return *mInstance;
	*/
}


