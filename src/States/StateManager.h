/*
Created by PlasmaLotus
Updated May 17, 2017
*/
#ifndef __StateManager__
#define __StateManager__
#include <vector>
#include <algorithm>

#include <stdint.h>
#include <string.h>
#include <stack>
#include <list>
#include "State.h"
//#include "MenuState.h"
#include "SplashScreenState.h"
//#include "TitleScreen.h"
#include "../Main.h"
//#include "../Event/EventManager.h"
/*
#include "../Controller/ControllerConfig.h"
#include "../Event/AudioEventManager.h"
#include "../Renderer/Alert.h"
*/



/*
Class that manages all state order, transition and handling
*/
class StateManager {
public:
	StateManager();
	~StateManager();
	static StateManager& getInstance();

	void Update(float dt);
	void Render(void* renderTarget);
	//void switchToState(State* state);
	//void goBackTo(State* state);
	//void goBack();
	//void goBackToTitle();
	//void _removeFromStack();

	void Init();
	void DeInit();

	/*
	template <class T = State>
	void GoTo() {
		GoToState(0, 0.0f);
	}
	*/
	
	template <class T = State>
	void GoToState(int transitionType = 0, float transitionTime = 0.0f) {
		//State* _wState{ nullptr };
		T* state{ nullptr };
		//bool found{ false };
		for (State* state : mStates) {
			T* tState{ dynamic_cast<T*>(state) };
			if (tState) {
				//found = true;
				state = tState;
			}
		}
		if (!state) {
			state = new T();
		}

		mPreviousState = mCurrentState;
		mCurrentState = state;

		//TODO: Transition here;
	}





	int64_t getElapsedTime();
	int64_t getRenderElapsedTime();
	


	void startTransition(int transitionType, float transitionTime);
	void stopTransition();
	//EventManager eventManager;
	//AudioEventManager audioEventManager;
	/*
	std::string getCurrentGameTimer();
	void resetGameTimer();
	int getFrameRate();
	int getAbsoluteFrameRate();
	void setScreenDimensions(int x, int y);
	void setDisplayFPS(bool state);
	void setDisplayHitboxes(bool state);
	void setDisplayPlayerPositions(bool state);
	bool getDisplayFPS();
	bool getDisplayHitboxes();
	bool getDisplayPlayerPositions();
	void toggleHitboxes();
	void togglePositions();
	void toggleFPS();
	*/
protected:
	
	std::vector<State*> mStates;
	//bool _running{ true };
	void _runHandlers();
	State *mPreviousState;
	State *mCurrentState;
	//State *mNewState;
	bool currentStateDrawnOverPrevious;
	std::stack<State*> _states;
	std::list<State*> __states; //List of all already loaded states
	bool _switchState;
	bool _deletedState;
	bool _stateTransition;
	int _stateTransitionTime;
	bool _backToTitle;
	//bool _renderFrame{ true };
	bool _displayFPS;
	bool _displayHitboxes;
	bool _displayPlayerPos;
	
};

#endif 
