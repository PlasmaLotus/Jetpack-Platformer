#ifndef __ENGINE__
#define __ENGINE__

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include <thread>

#include <vector>

#include "Entity.h"
#include "Input/Input.h"
#include "State/State.h"
#include <windows.h>//gotoXY
class Engine
{

private:
	//static Engine* mInstance;
	Engine();
	virtual ~Engine();
public:
	void loadContent();
	void unloadContent();
	bool Initialize();
	bool Deinitialize();
	void Clear();
	void Draw(sf::Time time);
	void Display();
	void Run();
	void render();
	void update(sf::Time time);
	void tick();

	void HandleEvents();


	//Input& Input();

	static Engine& getInstance();
	sf::RenderWindow* getWindow();
	//static Engine* getInstance();

	static float DeltaTime();
	static float RawDeltaTime();
	uint64_t getElapsedTimeAsMilliseconds();


	bool stateHasFocus(State * state);
	bool removeState(State * state);
	bool addState(State * state);
	bool removeLastState();
	bool switchToState(State * state);
	
private:
	
	sf::Time mElapsedTime;
	sf::Time mElapsedTimeTotal;
	
	sf::Time mPrevElapsedTime;

	sf::Time mTargetElapsedTime;
	sf::Time mTargetElapsedTimeRender;

	sf::Time mAccumulatedElapsedTime;
	sf::Time mAccumulatedElapsedTimeRender;
	
	static float mRawDeltaTime;
	static float mDeltaTime;
	sf::RenderWindow mWindow;
	long mFrameCounter;
	long _mFrameSubCounter;
	sf::Time _prevTimeStamp;
	sf::Clock mClock;
	bool isRunning;
	sf::Time _mFpsDeltaTime;

	float _fps;
	bool isFixedTimeStep;
	bool isFixedTimeStepRender;
	long ticks;
	long previousTicks;


	std::vector<Entity *>mEntities;

	template <class T = Entity>
	std::list<T*> GetEntities() {
		std::list<T*> litty;
		T* t = nullptr;
		for (Entity* const e : mEntities) {
			t = e;
			if (t) {
				litty.push_back(t);
			}
		}
		return t;
	}

	template <class T = Entity>
	std::list<T*> GetFirstEntity() {
		std::list<T*> litty;
		T* t = nullptr;
		for (Entity* const e : mEntities) {
			t = e;
			if (t) {
				litty.push_back(t);
			}
		}
		return t;
	}
	//void isEntityTracked();
	//void isComponentTracked();
	//void getNearestEntity();

	sf::CircleShape defaultShape;
	bool renderThisFrame = false;
	std::vector<State*> mStates;
	int currentStateID;
};


#endif // ENGINE
