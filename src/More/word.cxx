
/*
class DialogWord{
public:
	DialogWord();
	~DialogWord();
	void update(float delta);
	void render();
	void init();
	void start();
	void stop();
	void setPosition(Vector2f v, Dialog::Align);
	
	Texture texture;
	std::string mText;
	DialogState mState;
	list<DialogLetter> letters;
	Vector2f mPosition; //center
	Rect collider;
	Rect getCollider();
	///Formatting
	int fontSize;
	float mSpaceBetweenLetters;
	Vector2f mLetterSize;//letter aspect ratio
	int mAllignment;
	
	//Animation
	bool mletterSeparate;
	float mLetterTimeOffset;
	void isActive();
	void isVisible();
	bool setAnimation(AnimaitonData data);

	float mAnimationTimer;
	float mAnimationTime;

	bool mRandomTiming;
	int mInterpolationType;//Linear, Sin
	
	//Animation calculated offsets
	Vector2f mPositionOffset;
	Vector2f mScaleOffset;
	float mRotationOffset;
	RGBA mRGBAOffset;
	
	// Targeted offset
	Vector2f mPositionOffsetTarget;
	Vector2f mScaleOffsetTarget;
	RGBA mRGBAOffsetTarget;
	float mRotationTarget;
	std::function<float(float)> tween;
	//const pos offset 100px, scale offset: 2.0f, alpha offset : 0.1 + x
	
};
namespace Dialog{
	enum State{In, Idle, Out};
	enum Allign{Top, Middle, Bottom, Left, Right};
	enum IntroType{};
	enum IdleType{};
	enum OutroType{};
}

void DialogWord::init(){
	//Load Texture
}
void DialogWord::update(float delta){
	mAnimationTimer += delta;
	Vector2f wPositionOffset;
	Vector2f wScaleOffset;
	float wRotationOffset;
	RGBA wRGBAOffset;
	switch(mState){

		//float percentage = (mAnimationTime - mAnimationTimer)/mAnimationTime;
		float percentage = tween(mAnimationTimer, 0, 1, mAnimationTime);
		//check for 0 //sin = percentage* 2 * Math.pi
		if(mletterSeparate){
			//mLetterTimeOffset
			for(int l=0; l < letters.count(); ++l){
				float letterOffsetPercent = mLetterTimeOffset /mAnimationTimeCount;
				//float perOffset = percentage - l * letterOffsetPercent;
				float perOffset = tween(mAnimationTimer- l* mLetterTimeOffset, 0, 1, mAnimationTime)
				if( perOffset < 0.f){
					perOffset = 0.f;
					letter.visible = false;
				}
				else{
					letter.visible = true;
					wPositionOffset = mPositionOffsetTarget * perOffset;
					wScaleOffset = mScaleOffsetTarget * perOffset;
					wRGBAOffset = mRGBAOffsetTarget * perOffset;
					wRotationOffset = mRotationOffset * perOffset;

				}

			}
		}
		else{
			//All the letters together;
			
			wPositionOffset = mPositionOffsetTarget * percentage;
			wScaleOffset = mScaleOffsetTarget * percentage;
			wRGBAOffset = mRGBAOffsetTarget * percentage;
			wRotationOffset = mRotationOffset * percentage;
			
			
			float wRelativeRotation;
			Vector2f wAngularOffset; // Position offset given by the rotation of the whole word
			float wDistanceMultiplierRelativeToCenter; //between -1 and 1;
			for(int l=0; l < letters.count(); ++l){
				letter.visible = true;
				letter.position = wPositionOffset;
				letter.scale = wScaleOffset;
				letter.rotation = wRotationOffset;
				letter.color = wRGBAOffset;
				
			}
			
		}
	}
	/// Handle offsets;
}

class DialogLetter{	
public:
	DialogLetter();
	~DialogLetter();
	//Everything is relative to the parent
	Vector2f mPosition;
	Vector2f mSize;
	float mRotation;
	RGBA mColor;
	Texture &mTexture;
	TextureRect mRect;
	
	void render(void* target);
	void update(float delta);
};

void DialogLetter::render(void* target){
	//render target is the DialogWord texture
}

void DialogLetter::update(){
	Entity::update();
}

class InterpolationData{
public:
	Vector2f mPositionStart;
	Vector2f mPositionChange;
	
	Vector2f mScaleStart;
	Vector2f mScaleChange;
	
	float mRotationStart;
	float mRotationEnd;
	
	RGBA mRGBAStart;
	RGBA mRGBAEnd;
};


class IAnimatable{
	Vector2f mAnimationPositionStart;
	Vector2f mAnimationPositionChange;
	
	Vector2f mAnimationScaleStart;
	Vector2f mAnimationScaleChange;
	
	//Rotation: Float from 0 to 1; Out of range allowed;
	float mAnimationRotationStart;
	float mAnimationRotationEnd;
	
	RGBA mAnimationRGBAStart;
	RGBA mAnimationRGBAEnd;
	
	float mAnimationTweenPercent;
	std::function mAnimationTweenFunc;
	
	void update(float delta);
};
*/
//----------------------------------------------------------------------/




//Bungaku Shoujo
//Okami-san and Her Seven Companions //Ookami-san to Shichinin no Nakamatachi