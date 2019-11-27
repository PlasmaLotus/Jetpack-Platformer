#ifndef __ENGINE__
#define __ENGINE__
//#define NOMINMAX

#include <SFML/Graphics.hpp>
#include <SDL.h>
#include <list>
#include <algorithm>
#include <thread>

#include <vector>

#include "Entity/Entity.h"
#include "Input/RawInput.h"
#include "Event/EventManager.h"
#include "States/StateManager.h"
//using namespace pl;
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

	void Draw(sf::Time time);

	//Start the main running loop of the engine
	void Run();
	
	//Called every iteration of the running loop
	void Tick();

	//void Update(float dt);

	//Returns the engine's InputManager
	RawInput& Input();

	//Returns the engine's EventManager
	EventManager& Event();

	StateManager& States();

	//static Engine* getInstance();

	//Returns the time elapsed in a update frame, as seconds
	float DeltaTime();
	//Returns the time elapsed in a rendering frame, as seconds
	float DeltaTimeRender();

	//Returns the exact time elapsed since the last tick, as seconds
	float RawDeltaTime();

	//Returns the rendering FPS
	unsigned int FPS();

	//Returns the update tics per seconds
	unsigned int uFPS();

	//Set the Frame per Second rate of the current Engine
	void setFPS(unsigned int fps);

	//Set the Tick per Second rate of the Updating functionnality
	void setuFPS(unsigned int fps);

	//Set if the Rendering rate is capped to FPS
	void setFPSCap(bool cap);
	
	//Set if the Update rate is capped to the uFPS
	void setuFPSCap(bool cap);
	
	/*
	//Set the frame cap of window rendering, Min: 60, Max: 300
	//Fixed shows if the 
	void setRenderStepCap(bool fixed, int fps);
	void setRenderStepCap(bool fixed, float tickTime);

	void setUpdateStepCap(bool fixed, int fps);
	void setUpdateStepCap(bool fixed, float tickTime);
	*/



	void Quit();
	int GetUniqueID();
	//sf::RenderTarget& getWindow();
private:
	sf::RenderWindow* mWindow_SFML;
	SDL_Window* mWindow_SDL;

	SDL_Surface* mScreenSurface;
	/////sdl

	void _handleRawEvents();
	//Managers
	RawInput mRawInput;
	EventManager mEventManager;
	StateManager mStateManager;


	//Elapsed Time Data
	sf::Time mElapsedTime;
	sf::Time mElapsedTimeTotal;
	
	sf::Time mPrevElapsedTime;

	sf::Time mTargetElapsedTime;
	sf::Time mTargetElapsedTimeRender;

	sf::Time mAccumulatedElapsedTime;
	sf::Time mAccumulatedElapsedTimeRender;
	
	//FPS tracking?
	sf::Time mPrevTimeStamp;
	sf::Time mNewTimeStamp;

	sf::Time mPrevRenderTimeStamp;
	sf::Time mNewRenderTimeStamp;

	float mRawDeltaTime;
	float mDeltaTime;
	float mRenderDeltaTime;

	//The max time that can be elapsed between ticks
	const float MaxElapsedTime{ 0.50f };

	long mTickCounter;
	long _mTickSubCounter;
	sf::Time _prevTimeStamp;

	long mRenderTickCounter;
	long _mRenderTickSubCounter;
	sf::Time _prevRenderTimeStamp;
	bool isRunning;

	//Global clock for calculating time elapsed / GameTimer
	sf::Clock mClock;
	//sf::Time _mFpsDeltaTime;

	//Calculated rendered frames per second
	float mCalculatedRenderFPS;

	//Calculated update tics per seconds
	float mCalculatedUpdateFPS;


	bool mIsFixedTimeStep;
	bool mIsFixedRenderStep;
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
	int SCREEN_WIDTH{ 640 };
	int SCREEN_HEIGHT{ 480 };

	static int getWindowWidth();
	static int getWindowHeight();
	int getUniqueID();
	int _id;
	//	static const int FPS = 144;//144
	//  static const int renderFPS = 60;
	void onUpdateStepFixed();
	void onUpdateStepUncapped();

	void onRenderStepFixed();
	void onRenderStepUncapped();
};


#endif // ENGINE
