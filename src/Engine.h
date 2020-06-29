#ifndef __ENGINE__
#define __ENGINE__

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include <thread>

#include <vector>

#include "Entity.h"
#include "Input.h"

class Engine
{

private:
	//static Engine* mInstance;
	Engine();
	virtual ~Engine();
public:
	void loadContent();
	void unloadContent();
	void initialize();
	void draw(sf::Time time);
	void run();
	void update(sf::Time time);
	void tick();


	//Input& Input();

	static Engine& getInstance();
	//static Engine* getInstance();

	static float DeltaTime();
	static float RawDeltaTime();
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


	//
};


#endif // ENGINE
