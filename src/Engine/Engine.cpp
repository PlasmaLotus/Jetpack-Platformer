#include "Engine.h"
//#include "Input/RawInput.h"
//#include "Event/EventManager.h"
#include <SDL.h>

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
	//TODO: possible loss of data here
	return 1.0f/mTargetElapsedTimeRender.asSeconds();
}

unsigned int Engine::uFPS()
{
	return 1.0f/mTargetElapsedTime.asSeconds();
}

void Engine::setFPS(unsigned int fps)
{
	mTargetElapsedTimeRender = sf::seconds( 1.0f / (fps * 1.0f));
}

void Engine::setuFPS(unsigned int fps)
{
	mTargetElapsedTime = sf::seconds(1.0f / (fps * 1.0f));
}

void Engine::setFPSCap(bool cap)
{
}

void Engine::setuFPSCap(bool cap)
{
}

Engine::Engine() :
	mWindow_SFML{nullptr},
	mWindow_SDL{nullptr},
	mScreenSurface{nullptr},
	mElapsedTime{ sf::Time::Zero },
	mElapsedTimeTotal{ sf::Time::Zero },
	mPrevElapsedTime{ sf::Time::Zero },
	mTargetElapsedTime{ sf::seconds(1.0f / 144.f) },
	mTargetElapsedTimeRender{ sf::seconds(1.0f / 60.f) },
	mAccumulatedElapsedTime{ sf::Time::Zero },
	mAccumulatedElapsedTimeRender{ sf::Time::Zero },
	mTickCounter{ 0 },
	mRenderTickCounter{ 0 },
	_mTickSubCounter{ 0 },
	_prevTimeStamp{ sf::Time::Zero },
	_prevRenderTimeStamp{ sf::Time::Zero },
	mClock{ sf::Clock() },
	isRunning{ true },
	_id{ 0 },
	//_mFpsDeltaTime{ sf::Time::Zero },,
	mCalculatedRenderFPS{0.0f},
	mCalculatedUpdateFPS{0.0f},
	mIsFixedTimeStep{ false },
	mIsFixedRenderStep{ false },
	ticks{ 0 },
	previousTicks{ 0 },
	mRawDeltaTime{ 0.0f },
	mDeltaTime{ 0.0f },
	mRenderDeltaTime{0.0f}
{
	sf::ContextSettings contextSettings;
	
	mWindow_SFML = new sf::RenderWindow(sf::VideoMode(240, 160), "Jetpack Platformer");
	
	
	//mAccumulatedElapsedTime = mAccumulatedElapsedTimeRender = sf::Time::Zero;
	mPrevElapsedTime = mClock.restart();
	mElapsedTime = mClock.restart();
	//mElapsedTimeRender = mElapsedTime;
	//mLag
	//Init();
	mRawDeltaTime = mDeltaTime = mRenderDeltaTime = 1.0f / 60.0f;
}

Engine::~Engine()
{////
	if (mWindow_SDL) {
		delete mWindow_SDL;
	}
	if (mWindow_SFML) {
		delete mWindow_SFML;
	}
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
	
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		mWindow_SDL = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow_SDL == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		
	}
	
	
	mWindow_SFML->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Window");
	
	
	
	mRawInput.Init();

	//mEventManager.Init();


	//StateManager
	mStateManager.Init();

	//resourcemanager
	//audio
	//network

}

void Engine::DeInit()
{

	//mWindow.
	//Destroy window
	SDL_DestroyWindow(mWindow_SDL);

	//Quit SDL subsystems
	SDL_Quit();


	mRawInput.DeInit();
}
//Main loop
void Engine::Run()
{
	Init();
	//TODO: Before run here
	mClock.restart();
	mElapsedTimeTotal = sf::Time::Zero;

	//Begin Run
	while (mWindow_SFML->isOpen() && isRunning)
	{
		sf::Event event;
		while (mWindow_SFML->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				mWindow_SFML->close();
		}

		Tick();
	}
	//End Run
	//TODO: After run here
	DeInit();
}

void Engine::Tick()
{
	//Time
	mPrevElapsedTime = mElapsedTime;
	mElapsedTime = mClock.restart();
	mElapsedTimeTotal += mElapsedTime;
	//mElapsedTimeRender = mElapsedTine;
	//lag += elapsed;
	mRawDeltaTime = mElapsedTime.asSeconds();

	//mAccumulatedElapsedTime += mElapsedTime;
	//1: accumulate time
	int arbitraryValue = 69;
	//mTickCounter++;
	//_mTickSubCounter++;
	//Calculate Update FPS
	if (mTickCounter % arbitraryValue == 0) {
		sf::Time _lmao = mElapsedTimeTotal - _prevTimeStamp;
		mDeltaTime = _lmao.asSeconds() / (mTickCounter * 1.0f);
		mCalculatedUpdateFPS = 1.0f / mDeltaTime;
		_prevTimeStamp = mElapsedTimeTotal;
		//_mTickSubCounter = 0;
	}

	//Calculate Update FPS
	if (mRenderTickCounter % arbitraryValue == 0) {
		sf::Time _lmao = mElapsedTimeTotal - _prevRenderTimeStamp;
		mRenderDeltaTime = _lmao.asSeconds() / (mRenderTickCounter * 1.0f);
		mCalculatedRenderFPS = 1.0f / mRenderDeltaTime;
		_prevRenderTimeStamp = mElapsedTimeTotal;
		//_mTickSubCounter = 0;
	}


	//Handle ununiform time
	//update Game

	if (mIsFixedTimeStep) {
		mAccumulatedElapsedTime += mElapsedTime;

		//MS_PER_FRAME
		while (mAccumulatedElapsedTime >= mTargetElapsedTime) {
			Update(mTargetElapsedTime);
			++mTickCounter;
			mAccumulatedElapsedTime -= mTargetElapsedTime;
		}
	}
	else {
		/*
		if (this.forceElapsedTimeToZero)
		{
			this.gameTime.ElapsedGameTime = TimeSpan.Zero;
			this.forceElapsedTimeToZero = false;
		}
		else
		{
			this.gameTime.ElapsedGameTime = this.accumulatedElapsedTime;
			this.gameTime.TotalGameTime += this.gameTime.ElapsedGameTime;
		}
		this.accumulatedElapsedTime = TimeSpan.Zero;
		this.AssertNotDisposed();
		this.Update(this.gameTime);
		*/
		
		//mElapsedTime
		//mAccumulatedElapsedTime = sf::Time::Zero;
		
		//Just tick as often as the PC can
		Update(mElapsedTime);
		++mTickCounter;
	}

	// Rendering
	//bool renderThisFrame = false;

	if (mIsFixedRenderStep) {
		mAccumulatedElapsedTimeRender += mElapsedTime;
		//MS_PER_RENDER_FRAME
		if (mAccumulatedElapsedTimeRender >= mTargetElapsedTimeRender) {
			Draw(mTargetElapsedTimeRender);
			++mRenderTickCounter;
			mAccumulatedElapsedTimeRender -= mTargetElapsedTimeRender;
		}
	}
	else {
		//Render every tick
		//mAccumulatedElapsedTimeRender = sf::Time::Zero;

		Draw(mElapsedTime);
		++mRenderTickCounter;
	}

}


void Engine::Update(sf::Time time)
{
	float dt{ time.asSeconds() };
	//Update Handlers and managers
	//Handle Events

	//Handle 

	//Input
	mRawInput.update();

	//States
	mStateManager.Update(dt);
}
void Engine::Draw(sf::Time time)
{
	mWindow_SFML->clear();

	mStateManager.Render(mWindow_SFML);
	//mWindow.draw(sf::CircleShape(10.0f, 10));
	mWindow_SFML->display();
}

RawInput & Engine::Input(){
	return mRawInput;
}
EventManager& Engine::Event() {
	return mEventManager;
}
StateManager & Engine::States(){
	return mStateManager;
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

void Engine::Quit() {
	isRunning = false;
}

int Engine::GetUniqueID() {
	return _id++;
}

void Engine::onUpdateStepFixed(){
	mAccumulatedElapsedTime = mElapsedTime;
	//mTargetElapsedTime = 
}//TODO
void Engine::onUpdateStepUncapped(){
	//mAccumulatedElapsedTime = mElapsedTime;
	//mTargetElapsedTime = sf::seconds(1.0f / 300.0f);
}//TODO

void Engine::onRenderStepFixed() {
	mAccumulatedElapsedTimeRender = mElapsedTime;
}//TODO
void Engine::onRenderStepUncapped() {}//TODO