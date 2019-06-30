#ifndef D_Loader
#define D_Loader

#include "PennerEasing\Back.h"
#include "PennerEasing\Bounce.h"
#include "PennerEasing\Linear.h"
#include <functional>
#include <cstdint>

#include "Component.h"
//class Component;
class TweenHandler: public Component{
public:
	//TweenHandler();
	TweenHandler(std::function<float(float, float, float, float)> tween, float time, bool isLooping);
	~TweenHandler();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void restart();
	virtual bool isStarted();
	virtual bool isFinished();
	virtual bool isLooping();
	virtual bool isPaused();
	virtual void setLoop(bool looping);

	virtual void setCurrentTime();//
	virtual void setEndTime();//
	virtual float timeLeft();//
	virtual float timePlayed();//
	virtual float timeTotal();//

	//Percent of the tween relative to time. Around 0 to 1
	virtual float percent();
	
	virtual void update(float delta);
	virtual void render(void* target);
	virtual void setTween(std::function<float(float, float, float, float)> tween);


	//callbacks...
	virtual void onTweenStart();
	virtual void onTweenStop();
	virtual void onTweenPause();
	virtual void onTweenEnd();
	virtual void onTweenLoop();
	int debug;

protected:
	float mTweenTimer;
	float mTweenTime;
	
	bool mLooping;
	bool mStarted;
	bool mPaused;
	bool mFinished;
	
	float mTweenPercent;
	std::function<float(float, float, float, float)> mTween;//Time, Begin, Change, Duration


};
#endif // !TweenHandler

namespace Tween{
	const int __TWEEN__NB__STATES__ = 3;
	enum TweenableState{
		None = 0,
		Idle = 1,
		Intro = 2,
		Outro = 4,

		IntroIdle = Intro | Idle,
		IntroOutro = Intro | Outro,
		IdleIntro = Idle | Outro,
		All = Idle | Intro | Outro,


		/*
		if ((mask & FLAG3) == FLAG3) -нн> tests if all bits in FLAG3 are present in mask.
		if (mask & FLAG3)						 -> tests if any are present.
		*/
		Finished = 8
	};
	const int LOOP_TIMES_INFINITE = -42069;


}
class Tweenable: public Component{
public:

	Tweenable();
	~Tweenable();
	/*
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void restart();
	virtual void finish();
	virtual bool isStarted();
	virtual bool isStarted(char flags);
	virtual bool isFinished();
	virtual bool isFinished(char flag);
	virtual bool isLooping();
	virtual void setLoop(bool looping);
	*/

	/*Toggle if these should be played*/
	/*
	void toggleIntro(bool toggle);
	void toggleOutro(bool toggle);
	void toggleIdle(bool toggle);
	*/
	void setAutoStateChangeIntro(bool autoStateChange);//Set auto change on for one or multiple states, Only for Intro and Idle 
	void setAutoStateChangeIdle(bool autoStateChange);
	//void setAutoStateChange(bool autoChangeState);

	void next();
	bool pendingStateChange();
	void setActiveStates(Tween::TweenableState state);
	void setCurrentState(Tween::TweenableState state);
	bool isStarted(Tween::TweenableState state);
	bool isFinished(Tween::TweenableState state);

	void setStateParameters(Tween::TweenableState state, bool active, float time, bool autoStateSwap, std::function<float(float, float, float, float)> tween);
	Tween::TweenableState currentState();
	void setIdleLoopTimes(int loopTimes);


	unsigned short _getStateID(Tween::TweenableState state);
	bool _autoStateChange(int stateID);
	bool _autoStateChange(Tween::TweenableState state);

	//Active state

	unsigned short mActiveStates;//Flag for if each state is active 
	Tween::TweenableState mState;//Current State Active

	TweenHandler mTweenHandler;

	float stateTime[Tween::__TWEEN__NB__STATES__];//Time each state lasts
	bool autoStateChange[Tween::__TWEEN__NB__STATES__ - 1];//Toggle to switch state automatically on completion, Intro and Idle only
	std::function<float(float, float, float, float)> _tweensF[Tween::__TWEEN__NB__STATES__];//Tweening function for each state
	unsigned short _stateID;//State ID for Array lookup
	unsigned short mStateStarted;//Flags for if each state has started
	unsigned short mStateFinished;//Flags for if each state has finished (has to have started 1st)

	float mTimer;// Timer for the current state
	float mTotalTimer;//Total time elapsed for the Tween, All states counted
	/*Addons*/
	virtual void update(float delta);
	virtual void render(void* target);
	bool mStarted;//Flag for the Full Tween to have started
	bool mFinished;//Flag for the Full Tween to have started
	int mLoopTimes;//Number of times the idle will loop
	bool _pendingStateChange;//If a state has to be changed manually, not on autoChange

	//callbacks...
	virtual void onStateChange();
		
	virtual void onStart();
	virtual void onFinish();
	virtual void onStateStart();
	virtual void onStateFinish();
	virtual void onLoop();
	/*
	virtual void onTweenPause();
	virtual void onTweenEnd();
	virtual void onTweenLoop();
	*/
	
	
};


struct Vector2{
	float x;
	float y;
};

class HoverM{
	
	Vector2 mPositionStart;
	Vector2 mPositionChange;
	Vector2 mPositionChangeMax;
	
	Vector2 mScaleStart;
	Vector2 mScaleChange;
	Vector2 mScaleChangeMax;
	
	float mRotationStart;
	float mRotationChange;
	float mRotationChangeMax;
	
	uint32_t mRGBAStart;
	uint32_t mRGBAChange;
	uint32_t mRGBAChangeMax;

	float time;
	float timer;
	float timeStep;
};