#include "Engine.h"
#include "Input/Input.h"
//#include "ControllerTestRenderer.h"
#include "Main.h"

Engine::Engine():
	mFpsCounter(0),
	isRunning(true),
	isFixedTimeStep(true),
	renderThisFrame(true),
	mTargetElapsedTime(sf::seconds(DeltaTime())),
	mTargetRenderElapsedTime(sf::seconds(DeltaTime()))
{
	initialize();
}


Engine::~Engine(){
}

bool Engine::initialize() {
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

bool Engine::deinitialize()
{
	//SDL_DestroyRenderer();
	//SDL_DestroyWindow();
	SDL_Quit();
	return true;
}

void Engine::clear() {
	mWindow.clear();
}

void Engine::draw(sf::Time time)
{


	mWindow.draw(defaultShape);
}

void Engine::display() {
	mWindow.display();
}


void Engine::run()
{
	mPrevElapsedTime = mClock.restart();
	mElapsedTime = mClock.restart();
	mLag = sf::milliseconds(0);
	mAccumulatedElapsedTime = sf::milliseconds(0);
	mAccumulatedRenderElapsedTime = sf::milliseconds(0);
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
		mAccumulatedRenderElapsedTime += elapsed;




		handleEvents();
		tick();//has update
		render();
	}
	deinitialize();
}

void Engine::handleEvents() {

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
	

	//events 1st probably

	//Update every entity
	//check and handle collisions
	//render
}

void Engine::tick()
{
	//Handle ununiform time
	//update Game


	if (isFixedTimeStep) {
		//int updateCounter = 0;
		ticks = 0;

		while (mAccumulatedElapsedTime >= mTargetElapsedTime) {
			update(mTargetElapsedTime);
			++ticks;
			mAccumulatedElapsedTime -= mTargetElapsedTime;

		}
		if (ticks >= 1)
			printf("MicroSeconds: %d, Nb of Updates: %d\n", mElapsedTime.asMicroseconds(), ticks);
		else
			printf("MicroSeconds: %d, AccumulatedTime: %d, ---------------------\n", mElapsedTime.asMicroseconds(), mAccumulatedElapsedTime.asMicroseconds());

		if (mAccumulatedElapsedTime < sf::Time::Zero) {
			mAccumulatedElapsedTime = sf::Time::Zero;
		}
	}
	else {
		//Just tick as often as the PC can
		//update(sf::Time::Zero);
		mElapsedTime = mAccumulatedElapsedTime;
		mAccumulatedElapsedTime = sf::Time::Zero;
		update(mElapsedTime);
		
	}

	
}

void Engine::render()
{
	//mWindow.clear();
	
	
	
	
	//bool renderThisFrame = true;
	//renderThisFrame = true;
	if (mAccumulatedRenderElapsedTime >= mTargetRenderElapsedTime) {
		if (renderThisFrame) {
			clear();
			draw(sf::Time::Zero);
			display();
			mAccumulatedRenderElapsedTime -= mTargetRenderElapsedTime;

		}
		else
			renderThisFrame = true;
	}
	


	


	/*Gamepad*/
	InputRaw_X::getInstance().pollInput();
	printf("XInput Gamepad Data:");
	gotoxy(0, 20);
	for (int i = 0; i < 4; ++i) {
		XGPad& pad = InputRaw_X::getGamepad(i);
		if (pad.enabled) {
			printf("Gamepad(%d): %d, L: %d %d, R: %d %d, LT: %d, RT: %d \n", i, pad.state.Gamepad.wButtons, pad.state.Gamepad.sThumbLX, pad.state.Gamepad.sThumbLY,
				pad.state.Gamepad.sThumbRX, pad.state.Gamepad.sThumbRY, pad.state.Gamepad.bLeftTrigger, pad.state.Gamepad.bRightTrigger);
		
			//printf("Battery:")
		}
	}
	
	printf("SFML Joystick Data: \n");

	for (int i = 0; i < sf::Joystick::Count; ++i) {
		if (sf::Joystick::isConnected(i)) {
			sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
			
			
			printf("Joystick(%d): Name: %s, ProdID: %d, VendorID: %d", i, id.name.toUtf8().c_str() , id.productId, id.vendorId);
			printf("\n Buttons:");
			for (int button = 0; button < sf::Joystick::getButtonCount(i); ++button) {
				//sf::Joystick::
				if (sf::Joystick::isButtonPressed(i, button)) {
					printf("%d", button);
				}
				else {
					printf(" ");
				}
			}
			printf(" Axis: ");
			for (int axis = 0; axis < sf::Joystick::AxisCount; ++axis) {
				//if(sf::Joystick::getAxisPosition())
			
				printf("%d - %3.2f ", axis, sf::Joystick::getAxisPosition(i, sf::Joystick::Axis(axis)));
			}
			printf("\n");
			//printf("Joystick(%d): %d, L: %d %d, R: %d %d, LT: %d, RT: %d \n", i, pad.state.Gamepad.wButtons, pad.state.Gamepad.sThumbLX, pad.state.Gamepad.sThumbLY,

		}
	}

	
	gotoxy(0, 10);




	//ct.render(&mWindow);
	//Render
	//mWindow.display();
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
/*
bool Engine::switchToState(State * state)
{
	return false;
}
*/

float Engine::DeltaTime()
{
	return 1.f / 60.f;
	//return 1.f / 144.f;
}

uint64_t Engine::getElapsedTimeAsMilliseconds()
{
	return mElapsedTime.asMicroseconds();
}
