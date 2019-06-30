/*

*/


#ifndef __ENGINE__
#define __ENGINE__

#include "SDL.h"
#include <SFML/Graphics.hpp>
//#include <>
#include <list>
//#include <algorithm>
#include "Entity.h"
#include <thread>
#include <stdint.h>
#include <stack>
#include <list>
#include <vector>
#include "State/State.h"

class Engine
{
public:
	virtual ~Engine();
	void loadContent();
	void unloadContent();
	bool initialize();
	bool deinitialize();
	void clear();
	void draw(sf::Time time);
	void display();
	void handleEvents();
	void run();
	void update(sf::Time time);
	void tick();
	void render();
	static Engine& getInstance();
	sf::RenderWindow* getWindow();

	bool stateHasFocus(State* state);
	bool removeState(State* state);
	bool addState(State* state);

	bool removeLastState();
	//bool switchToState(State* state);

	//State transition8

	static float DeltaTime();
	uint64_t getElapsedTimeAsMilliseconds();
private:
	Engine();
	//static Engine& mInstance;

	sf::Time mElapsedTime;
	sf::Time mPrevElapsedTime;
	sf::Time mTargetElapsedTime;
	sf::Time mAccumulatedElapsedTime;
	sf::Time mLag;
	float mRawDeltaTime;
	float mDeltaTime;
	sf::RenderWindow mWindow;
	long mFpsCounter;
	sf::Clock mClock;
	bool isRunning;
	sf::Time MS_PER_FRAME{ sf::seconds(1.f / 60.f) };


	sf::Time mAccumulatedRenderElapsedTime;
	sf::Time mTargetRenderElapsedTime;
	bool isFixedTimeStep;
	long ticks;
	long previousTicks;
	bool renderThisFrame;


	sf::CircleShape defaultShape;
	//CTRenderer ct;

	sf::View mainView;
	sf::View otherView;

	//States
	int currentStateID;
	std::vector<State*> mStates;

};

#endif // ENGINE