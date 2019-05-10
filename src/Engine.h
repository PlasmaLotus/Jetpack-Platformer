#ifndef __ENGINE__
#define __ENGINE__

#include <SFML/Graphics.hpp>
#include <list>
#include <algorithm>
#include "Entity.h"
#include <thread>

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

	static Engine& getInstance();
	//static Engine* getInstance();

	static float DeltaTime();
private:

	
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
