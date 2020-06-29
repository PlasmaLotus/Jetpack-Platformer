#include "Engine.h"
#include "Input/Input.h"
//#include "ControllerTestRenderer.h"
#include "Main.h"
#include <SDL.h>
float Engine::mRawDeltaTime = 0.0f;
float Engine::mDeltaTime = 0.0f;

float Engine::DeltaTime()
{
	return 1.f / 60.f;
	//return 1.f / 144.f;
}

float Engine::RawDeltaTime()
{
	return 0.0f;
}


Engine::Engine() :
	mElapsedTime(sf::Time::Zero),
	mElapsedTimeTotal(sf::Time::Zero),
	mPrevElapsedTime(sf::Time::Zero),
	mTargetElapsedTime(sf::seconds(DeltaTime())),
	mTargetElapsedTimeRender(sf::seconds(DeltaTime())),
	mAccumulatedElapsedTime(sf::Time::Zero),
	mAccumulatedElapsedTimeRender(sf::Time::Zero),
	//mFpsCounter(0),
	mFrameCounter(0),
	_mFrameSubCounter(0),
	_prevTimeStamp(sf::Time::Zero),
	mClock(sf::Clock()),
	isRunning(true),
	_mFpsDeltaTime(sf::Time::Zero),
	isFixedTimeStep(false),
	isFixedTimeStepRender(false),
	//renderThisFrame(true),
	ticks(0),
	previousTicks(0)
{
	mAccumulatedElapsedTime = mAccumulatedElapsedTimeRender = sf::Time::Zero;
	mPrevElapsedTime = mClock.restart();
	mElapsedTime = mClock.restart();
	//mElapsedTimeRender = mElapsedTime;
	Initialize();
}

Engine::~Engine(){
	mStates.clear();
}

bool Engine::Initialize() {
	bool result = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		///SDL didnt init;
		printf("UNABLE TO INITIALISE SDL");;
		result = false;
	}

	mWindow.create(sf::VideoMode(240, 160), "OK");
	defaultShape = sf::CircleShape(50.f);
	defaultShape.setFillColor(sf::Color::Green);

	//SplashScreen State
	currentStateID = 0;

	isRunning = true;
	return result;
}

bool Engine::Deinitialize()
{
	//SDL_DestroyRenderer();
	//SDL_DestroyWindow();
	SDL_Quit();
	return true;
}

void Engine::Clear() {
	mWindow.clear();
}

void Engine::loadContent()
{
}

void Engine::unloadContent()
{
}


void Engine::Draw(sf::Time time)
{
	Clear();
	//mWindow.clear();
	mWindow.draw(defaultShape);
	Display();
}

void Engine::Display() {
	mWindow.display();
}


void Engine::Run()
{
	mPrevElapsedTime = mClock.restart();
	mElapsedTime = mClock.restart();
	mAccumulatedElapsedTime = sf::milliseconds(0);
	mAccumulatedElapsedTimeRender = sf::milliseconds(0);
	sf::Time elapsed = mClock.getElapsedTime();
	//initialize();

	//Begin Run
	while (isRunning)
	{
		
		/*Time elapsed*/
		elapsed = mClock.getElapsedTime();
		mPrevElapsedTime = mElapsedTime;
		mElapsedTime = mClock.restart();

		mAccumulatedElapsedTime += elapsed ;
		mAccumulatedElapsedTimeRender += elapsed;

		HandleEvents();
		tick();//has update
		render();
	}
	Deinitialize();
}

void Engine::HandleEvents() {

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

	if (!mWindow.isOpen()) {
		isRunning = false;
	}
}

void Engine::update(sf::Time time)
{	
	float debug = 0.0f;
	//events 1st probably

	//Update every entity
	//check and handle collisions
	//render
	/*Gamepad*/
	gotoxy(0, 0);
	InputRaw_X::getInstance().pollInput();
	printf("XInput Gamepad Data:");
	for (int i = 0; i < 4; ++i) {
		XGPad& pad = InputRaw_X::getGamepad(i);
		if (pad.enabled) {
			printf("Gamepad(%d): L: %d %d, R: %d %d, LT: %d, RT: %d , Buttons: %d--------\n", 
				i, pad.state.Gamepad.sThumbLX, pad.state.Gamepad.sThumbLY,
				pad.state.Gamepad.sThumbRX, pad.state.Gamepad.sThumbRY, pad.state.Gamepad.bLeftTrigger, 
				pad.state.Gamepad.bRightTrigger, pad.state.Gamepad.wButtons);
			//printf("Battery:")
		}
	}

	printf("SFML Joystick Data: \n");
	
	for (int i = 0; i < sf::Joystick::Count; ++i) {
		if (sf::Joystick::isConnected(i)) {
			sf::Joystick::Identification id = sf::Joystick::getIdentification(i);

			printf("Joystick(%d): Name: %s, ProdID: %d, VendorID: %d", i, id.name.toUtf8().c_str(), id.productId, id.vendorId);
			printf("\nButtons(%02d):", sf::Joystick::getButtonCount(i));
			for (int button = 0; button < sf::Joystick::getButtonCount(i); ++button) {
				//sf::Joystick::
				if (sf::Joystick::isButtonPressed(i, button)) {
					printf("|%02d", button);
				}
				else {
					printf("|  ");
				}
			}
			printf("\nAxis(): ");

			//Axis test
			if (sf::Joystick::hasAxis(i, sf::Joystick::Axis::PovX))
			{
				float pos = 0.0f;
				
				pos = sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::PovX);
				debug = -1.0f;
			}
			//sf::Joystick::
			debug = 0.0f;
			for (int axis = 0; axis < sf::Joystick::AxisCount; ++axis) {
				if(sf::Joystick::hasAxis(i, static_cast<sf::Joystick::Axis>(axis)))
					debug += 1.0f;

				printf("%d - %3.2f ", axis, sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(axis)));
			}
			sf::Joystick::Identification identification = sf::Joystick::getIdentification(i);
			printf("\n");
			//printf("Joystick(%d): %d, L: %d %d, R: %d %d, LT: %d, RT: %d \n", i, pad.state.Gamepad.wButtons, pad.state.Gamepad.sThumbLX, pad.state.Gamepad.sThumbLY,
		}
	}

	printf("\n SDL Joystick Data\n");

	SDL_Joystick* joy;
	// Check for joystick
	int index = 0;
	if (SDL_NumJoysticks() > 0) {
		// Open joystick
		joy = SDL_JoystickOpen(0);

		if (joy) {
			printf("Opened Joystick 0\n");
			printf("Name: %s\n", SDL_JoystickNameForIndex(0));
			SDL_JoystickID id = SDL_JoystickInstanceID(joy);
			printf("ID: %s\n", SDL_JoystickNameForIndex(0));
			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
		}
		else {
			printf("Couldn't open Joystick 0\n");
		}

		// Close if opened
		if (SDL_JoystickGetAttached(joy)) {
			SDL_JoystickClose(joy);
		}
	}


	gotoxy(0, 10);
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
			update(mTargetElapsedTime); // update(mElapsedTime);
			++lmao;
			mAccumulatedElapsedTime -= mElapsedTime;
		}
	}
	else {
		//Just tick as often as the PC can
		//update(mElapsedTime);
		//mElapsedTime = mAccumulatedElapsedTime;
		//mAccumulatedElapsedTime = sf::Time::Zero;
		//update(mElapsedTime);

		//update(sf::Time::Zero);
		mElapsedTime = mAccumulatedElapsedTime;
		mAccumulatedElapsedTime = sf::Time::Zero;
		update(mElapsedTime);
	}
}

void Engine::render(){
	//ct.render(&mWindow);
	//bool renderThisFrame = false;
	/*
	if (mAccumulatedElapsedTimeRender >= mTargetElapsedTimeRender) {
		if (renderThisFrame) {
			Clear();
			Draw(sf::Time::Zero);
			Display();
			mAccumulatedElapsedTimeRender -= mTargetElapsedTimeRender;

		}
		else
			renderThisFrame = true;
	}
	*/

	if (isFixedTimeStepRender) {
		mAccumulatedElapsedTimeRender += mElapsedTime;
		//MS_PER_RENDER_FRAME
		while (mAccumulatedElapsedTimeRender >= mTargetElapsedTimeRender) {
			Draw(mTargetElapsedTimeRender);
			mAccumulatedElapsedTimeRender -= mTargetElapsedTimeRender;
			//mAccumulatedElapsedTimeRender -= mElapsedTime;
		}
		//Draw(mAccumulatedElapsedTimeRender);
	}
	else {
		//Render every tick
		Draw(mElapsedTime);
		mAccumulatedElapsedTimeRender -= mElapsedTime;
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

sf::RenderWindow* Engine::getWindow()
{
	return &mWindow;
}

bool Engine::stateHasFocus(State * state)
{

	if (mStates.size() >= 1) {
		if (mStates.size() >= currentStateID) {
			for (int i = 0; i < mStates.size(); ++i) {
				if (mStates.at(i) == state) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Engine::removeState(State * state)
{
	if (mStates.size() >= 1) {
		for (int i = mStates.size() -1; i >= 0; --i) {
			if (mStates.at(i) == state) {
				mStates.erase(mStates.begin() + i);
				return true;
			}
		}
	}
	
	return false;
}

bool Engine::addState(State * state)
{
	if (mStates.size() >= 1) {
		for (int i = mStates.size() - 1; i >= 0; --i) {
			if (mStates.at(i) == state) {
				return false;
			}
		}
	}
	mStates.push_back(state);
	return true;
}
bool Engine::removeLastState()
{
	if (mStates.size() >= 1) {
		mStates.pop_back();
		return true;
	}
	return false;
	
}
bool Engine::switchToState(State * state)
{
	return false;
}
/*
*/



uint64_t Engine::getElapsedTimeAsMilliseconds()
{
	return mElapsedTime.asMicroseconds();
}
