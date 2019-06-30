#ifndef R_WHEEL
#define R_WHEEL

#include <cstdint>
#include <stdlib.h>
#include <SDL.h>



#include <math.h>
#include "Component.h"
class RenderWheel{
public:
	static int progressWheel(SDL_Renderer *renderer, Sint16 x, Sint16 y, Sint16 rad, Uint32 color,
		float value, float stepVal);

private:

};

class ConsumableWheel: public Component{
public:
	ConsumableWheel();
	~ConsumableWheel();
	virtual void update(float delta);
	virtual void render(void* target);
	virtual void render(SDL_Renderer* target);
	virtual void debugRender(void* target);

	void setValue(float value, float step);
//private:
	float mValue;
	float mStep;
	void helper();

	//Depleated section Color flash controls
	bool _colorFlash;
	float _colorFlashInterval;
	float _colorFlashTimer;
	int __colorFlashFadeNegativeMultiplier;



	//Rendering
	uint32_t mColor;
	uint32_t mColorDepleated;
	uint32_t mColorDepleatedFlash;
};


#endif // !R_WHEEL

class Color{
	Color& operator= (unsigned int rgba);
};