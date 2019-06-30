class DialogueTree{
	map<std::string, DialogText> _tree;//dialogTag, dialogueText
};
struct DialogText{
	std::string id;
	std::string charName;
	std::string text;
	
	void getId();
	void getCharName();
	void getText();
	void getTextAsPlain();
};


//Dialogue box containing DialogueText;

class DialogBox: public Component{
public:
	DialogBox();
	~DialogBox();
	
	bool loadScript(std::string &path);
	bool loadScript(std::File &file);
	bool loaded(); const
	bool init();
	
	virtual void update(float delta);
	virtual void render(void* target);
	virtual void decodeText(std::string dialog);
	//Dialogue commands
	
	//void play();
	void Added();
	void Removed();
	
	void restartScript();
	void restartAll();
	
	void start(char flags);
	void pause();
	void stop();
	void restart();
	bool isFinished(char flags);
	bool isStarted(char flags);
	
	
	//Skip to the end of the section. This does not start the next section
	void skip();
	
	//Pass to next section of the Script part. Does not work if the section isnt finished.
	void next();
	
	void skipAndNext();
	
	//void end();
	
	

	
private:
	bool mLoaded;
	std::string mFullScript;
	//std::map<int, TweenHandler> mTweens;
	/*
	bool mScriptSectionStarted;
	bool mScriptSectionEnded;
	bool mScriptStarted;
	bool mScriptEnded;
	bool mDialogBoxStarted;
	bool mDialogBoxEnded;
	*/
	int mScriptNbSections;
	int mScriptSectionIndex;
	
	int mCurrentState;
	
	// Timer loaded on script load
	float mIntroTime;
	float mOutroTime;
	float mIdleTime;
	float mTimer;
	
	bool mStarted;
	bool mSectionFinished;
	bool mFinished;
	bool mPaused;//Not yet
	
	//void sectionEntities;
	std::vector<std::vector<Component>> dialogEntities;
};

/*
Order of operation:
1 create
2 load part of script
3 fade in
4 play script
5 fade out
*/

void DialogBox::update(float delta){
	Component::update(delta);
	mTimer += delta;
	
	if(mStarted){
		switch(mCurrentState){
			case TweenableState::Intro:{
				break;
			}
			case TweenableState::Outro:{
				break;
			}
			case TweenableState::Idle:{
				for (int i=0; i> dialogEntities[mScriptSectionIndex].length(), ++i){
					//Tweenable object
					//Tweenable str::string, func1, func2, func3, time1, time2, time3
					//Active false, visible false, collidable false;
					Tweenable &obj = dialogEntities[mScriptSectionIndex].at(i);
					if(!obj.active()){
						//Check previous obj
						if (i <=0){
							//Set object active.
							obj.active(true);
							obj.visible(true);
							obj.start();
						}
						else{
							Tweenable &prev = dialogEntities[mScriptSectionIndex].at(i-1);
							if(prev.active() && prev.isStarted(TweenableState::Intro)&& prev.isFinished(TweenableState::Intro){
								//If prev has finished his intro, and has started idle
								//Set object active.
								obj.active(true);
								obj.visible(true);
								obj.start();
							}
							else{
								//Previous object did not start or finish intro yet.
								//do nothing
							}
						}
					}
					else{
						//obj already started
						obj.update();
					}
				}
				break;
			}
			case TweenableState::None:
			default: {
				break;
			}
			
		}
	}
	
	
	
	if(mDialogBoxStarted){
		
		if(mScriptStarted){
			
			if (mScriptSectionStarted){
				//for(auto a: 
			}
			
		}
	}

	
}
void DialogBox::next(){
	
	
	// On idle state
	if(mSectionFinished){
		mScriptSectionIndex++;
		if (mScriptSectionIndex < mScriptNbSections){
			mScriptSectionIndex= mScriptNbSections - 1;
			//mCurrentState = TweenableState::Outro;
			//mTime
			switchToState(TweenableState::Outro);
			mSectionFinished = false;
		}
	}
	
}
void DialogBox::switchToState(char flag){
	mCurrentState = flag;
	mTimer = 0.f;
	mStarted = true;
	mFinished = false;
}

void DialogBox::decodeText(std::string dialog){
	int len = dialog.length()
	int _index = 0;
	char c = '/0';
	bool _special=false;
	std::string __special;
	std::string __plain;
	while(_index < len){
		c = dialog.at(_index);
		if(c == '[' || c == ']'){
			if(c == '['){
				_special=true;
				__special="";
			}
			else{
				_special=false;
			}
		}
		else if(c == '<' || c == '>'){
			if(c == '['){
				_special=true;
				__special="";
			}
			else{
				_special=false;
			}
		}
		
		
		if(_special){
			__special+= c;
		}
		else{
			__plain +=c;
		}
		
		if(!_special && __special != ""){
			switch(){
				//
			}
		}
		
	}
}