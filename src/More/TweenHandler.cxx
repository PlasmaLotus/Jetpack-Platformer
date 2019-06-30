#include "TweenHandler.h"
//#include "Component.h"

TweenHandler::TweenHandler(std::function<float(float, float, float, float)> tween = nullptr, float time = 1.f, bool isLooping = false):
	Component(false, false, false),
	debug(0),// TODO: remove
	mTween(tween),
	mTweenTimer(0.f),
	mTweenTime(time),
	mLooping(isLooping),
	mStarted(false),
	mFinished(false),
	mPaused(false),
	mTweenPercent(0.f){
}
/*
TweenHandler::TweenHandler():
	Component(false, false, false),
	mTween(nullptr),
	mTweenTimer(0.f),
	mTweenTime(0.f),
	mLooping(false),
	mStarted(false),
	mFinished(false),
	mTweenPercent(0.f){
}
*/
TweenHandler::~TweenHandler(){}

void TweenHandler::start(){
	mStarted = true;
	onTweenStart();
}
void TweenHandler::stop(){
	mStarted = false;
	mFinished = true;
	mTweenPercent = 0.f;
	mTweenTimer = 0.f;
	onTweenStop();
}
void TweenHandler::restart(){
	stop();
	start();
}
void TweenHandler::pause(){
	//Toggle
	mPaused = !mPaused;
	onTweenPause();
}

bool TweenHandler::isStarted(){return mStarted;}
bool TweenHandler::isFinished(){return mFinished;}
bool TweenHandler::isLooping(){return mLooping;}
bool TweenHandler::isPaused(){return mPaused;}
void TweenHandler::setLoop(bool looping){mLooping = looping;}

void TweenHandler::onTweenStart(){++debug;}
void TweenHandler::onTweenStop(){++debug;}
void TweenHandler::onTweenPause(){++debug;}
void TweenHandler::onTweenEnd(){++debug;}
void TweenHandler::onTweenLoop(){++debug;}


void TweenHandler::setCurrentTime(){/**/}
void TweenHandler::setEndTime(){/**/}

float TweenHandler::timeLeft(){return mTweenTime - mTweenTimer;}
float TweenHandler::timeTotal(){return mTweenTime;}
float TweenHandler::timePlayed(){return mTweenTimer;}


float TweenHandler::percent(){
	return mTweenPercent;
}

void TweenHandler::setTween(std::function<float(float, float, float, float)> tween){
	mTween = tween;
}

void TweenHandler::update(float delta){
	Component::update(delta);
	if(mStarted ){
		if(!mFinished || (mFinished && mLooping)){
			if(!mPaused){
				mTweenTimer += delta;
				if(mTweenTimer >= mTweenTime){
					mFinished = true;
					if(mLooping){
						mTweenTimer -= mTweenTime;
						onTweenLoop();
					}
					else{
						onTweenEnd();
					}
				}
				mTweenPercent = mTween(mTweenTimer, 0, 1, mTweenTime);
			}
		}
	}
	return;
}

void TweenHandler::render(void* target){
	Component::render(target);
}





/*************/
/**Tweenable**/
/*************/

Tweenable::Tweenable():
	Component(false, false, false){
}

Tweenable::~Tweenable(){
}
void Tweenable::render(void* target){
}
void Tweenable::update(float delta){
	Component::update(delta);// TweenHandler::update();
	
	if(mStarted){
		mTimer += delta;
		mTotalTimer += delta;
		//if Tween is finished
		if(mTweenHandler.isFinished()){
			//If handler has finished tween
			//Swap state
			if(_autoStateChange(mState)){
				next();
				
			}
			else{
				//State is finished but will not pass to the next one
				_pendingStateChange = true;
			}
			//Else no autoSwap, Don't swap yet
			
		}
		//Else not finished, keep going
		mTweenHandler.update(delta);
	}
	//Else not started
}

// Transition to the next State
void Tweenable::next(){
	//if(_autoStateChange(mState)){
		switch(mState){
		case Tween::Intro:{
			mStateFinished |= Tween::Intro;
			if((mActiveStates & Tween::Idle) == Tween::Idle){
				//Goto Idle, Reset vars
				mState = Tween::Idle;
				mStateStarted |= Tween::Idle;
				_pendingStateChange = false;
				_stateID = 1;
				mTimer = 0.0f;
			}
			else{
				//Skip Idle: Go to Outro
				if((mActiveStates & Tween::Outro) == Tween::Outro){
					mState = Tween::Outro;
					mStateStarted |= Tween::Outro;
					_pendingStateChange = false;
					_stateID = 2;
					mTimer = 0.0f;
				}
				else{
					//Skip outro also
					mFinished = true;
				}
			}
			break;
		}
		case Tween::Idle:{
			mStateFinished |= Tween::Idle;
			if((mActiveStates & Tween::Outro) == Tween::Outro){
					mState = Tween::Outro;
					mStateStarted |= Tween::Outro;
					_stateID = 3;
					_pendingStateChange = false;
					//Setup tween
					mTweenHandler.setTween(_tweensF[_stateID]);
					mTimer = 0.0f;
				}
				else{
					//Skip outro also
					mFinished = true;
				}
			break;
		}
		case Tween::Outro:{
			mStateFinished |= Tween::Outro;
			_pendingStateChange = false;
			mFinished = true;
			break;
		}
		default: break;
		}


		
	/**/
}

unsigned short Tweenable::_getStateID(Tween::TweenableState state){
	switch(state){
		case Tween::Intro:{
			return 0;
			break;
		}
		case Tween::Idle:{
			return 1;
			break;
		}
		case Tween::Outro:{
			return 2;
			break;
		}
		default: return -1; break;
		}
}

bool Tweenable::_autoStateChange(Tween::TweenableState state){return false;}
/*Callbacks*/

void Tweenable::onStateChange(){}
void Tweenable::onStart(){}
void Tweenable::onFinish(){}
void Tweenable::onStateStart(){}
void Tweenable::onStateFinish(){}
void Tweenable::onLoop(){}
