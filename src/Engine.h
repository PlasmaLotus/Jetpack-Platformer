#ifndef __ENGINE__
#define __ENGINE__
//#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include <thread>

#include <vector>

#include "Entity.h"
#include "Input/RawInput.h"
#include "Event/EventManager.h"

class Engine
{
private:
	//static Engine* mInstance;
	Engine();
	//Engine(int width, int height, int windowWidth, int windowHeight, string windowTitle, bool fullscreen);
	virtual ~Engine();
	void Update(sf::Time time);
public:
	static Engine& getInstance();

	void DeInit();
	//Initialize
	void Init();

	void LoadContent();
	void UnloadContent();

	void draw(sf::Time time);
	void run();
	void tick();

	//Returns the engine's InputManager
	RawInput& Input();

	//Returns the engine's EventManager
	EventManager& Event();

	//static Engine* getInstance();

	//Returns the time elapsed in a update frame, as seconds
	float DeltaTime();
	//Returns the time elapsed in a rendering frame, as seconds
	float DeltaTimeRender();

	//Returns the exact time elapsed since the last tick, as seconds
	float RawDeltaTime();

	//Returns the rendering FPS
	unsigned int FPS();
private:
	//Managers
	RawInput mRawInput;
	EventManager mEventManager;


	//Data
	sf::Time mElapsedTime;
	sf::Time mElapsedTimeTotal;
	
	sf::Time mPrevElapsedTime;

	sf::Time mTargetElapsedTime;
	sf::Time mTargetElapsedTimeRender;

	sf::Time mAccumulatedElapsedTime;
	sf::Time mAccumulatedElapsedTimeRender;
	
	float mRawDeltaTime;
	float mDeltaTimeRender;
	float mDeltaTime;

	sf::RenderWindow mWindow;
	long mTickCounter;
	long _mTickSubCounter;
	sf::Time _prevTimeStamp;
	bool isRunning;

	//Global clock for calculating time elapsed
	sf::Clock mClock;
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

	//Handle update
	//Handle Rendering
	//Handle Events
};


#endif // ENGINE
