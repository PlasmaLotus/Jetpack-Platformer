#include "StateManager.h"

StateManager::StateManager() :
	mPreviousState(nullptr),
	mCurrentState(nullptr),
	_switchState(false),
	_deletedState(false),
	_stateTransition(false),
	_backToTitle(false),
	_stateTransitionTime(0)
	//m_alertManager("Assets/Fonts/Minecraft.ttf", 18, window.getView().getSize())
	//m_alertManager("Assets/Fonts/arial.ttf", 18, window.getView().getSize())
{
	//window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Neon Galaxy");
	//window.create(sf::VideoMode::getFullscreenModes()[0], "Neon Galaxy", sf::Style::Fullscreen);

	//_currentState = new TitleScreen(&window);
	//_states.push(_currentState);
	//eventManager.setAudioEventManager(&audioEventManager);
	//m_alertManager = Alerts("Assets\fonts\Minecraft.ttf", 18, window.getSize());
	
	
	//FreeConsole();
}

StateManager::~StateManager(){
	if (!mStates.empty()) {
		for (State* state : mStates) {
			if (state) {
				delete state;
			}
		}
	}
	if (mCurrentState) {
		delete mCurrentState;
	}
	if (mPreviousState) {
		delete mPreviousState;
	}
}

StateManager& StateManager::getInstance() {
	static StateManager instance;
	return instance;
}

void StateManager::Update(float dt)
{
	if (mCurrentState) {
		mCurrentState->Update(dt);
	}
	//TODO
}

void StateManager::Render(void * renderTarget)
{
	if (mCurrentState) {
		mCurrentState->Render(renderTarget);
	}
	//TODO
}

void StateManager::Init()
{
	GoToState<SplashScreenState>();
}

void StateManager::DeInit()
{
}
