#ifndef __ENGINE__
#define __ENGINE__

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include "Entity.h"
#include <thread>

class Engine
{
public:
	virtual ~Engine();
	void loadContent();
	void unloadContent();
	void initialize();
	void draw(sf::Time time);
	void run();
	void update(sf::Time time);
	void tick();
	Engine& getInstance();

	static float DeltaTime();
private:
	Engine();
	//static Engine& mInstance;

	sf::Time mElapsedTime;
	sf::Time mPrevElapsedTime;
	sf::Time mTargetElapsedTime;
	sf::Time mAccumulatedElapsedTime;
	float mRawDeltaTime;
	float mDeltaTime;
	sf::RenderWindow mWindow;
	long mFpsCounter;
	sf::Clock mClock;
	bool isRunning;



	bool isFixedTimeStep;
	long ticks;
	long previousTicks;

};

#endif // ENGINE