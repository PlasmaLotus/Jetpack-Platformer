#include "RenderWheel.h"

ConsumableWheel::ConsumableWheel():
	Component(false, true, false)
{
}
ConsumableWheel::~ConsumableWheel(){
}
void ConsumableWheel::update(float delta){
	Component::update(delta);
	_colorFlashTimer += delta;

}
void ConsumableWheel::render(void* target){
	//SDL_Renderer* wRenderer = dynamic_cast<SDL_Renderer*>(target);
	//SDL_SetRenderTarget( gRenderer, mTexture );
	//SDL_RenderTarget
}
void ConsumableWheel::render(SDL_Renderer* target){
	if(target){
		//aacircleColor(target, 100, 100, 10, 0xFF0000FF);
		//pixelColor(target, 100, 100, 0x00FFFFFF);
		
	}
}
void ConsumableWheel::debugRender(void* target){}

int RGBAtoHEX(int r, int g, int b, int a){
	int ok = 0;
	ok += (r & 0xFF) << 24;
	ok += (g & 0xFF) << 16;
	ok += (b & 0xFF) << 8;
	ok += (a & 0xFF);
	//return r << 24 & g << 16 & b << 8 & (a & 0xFF);
	return ok;
}
void ConsumableWheel::helper(){
	short nbRings = ceil(mValue / mStep );//+ 1;
	unsigned short color_r = mColor >> 24;
	unsigned short color_g = mColor >> 16 & 0xF;
	unsigned short color_b = mColor >> 8 & 0xF;
	unsigned short color_a = mColor & 0xFF;
	//unsigned int color_r_wmask = mColor & 0xFF000000;
	uint32_t _c = RGBAtoHEX(color_r, color_g, color_b, color_a);
}

void ConsumableWheel::setValue(float value = 1.0f, float step = -1.0f){
	/*
	if(value <= 0.0f){
		value = 1.0f;
	}
	if(step <= 0.0f){
		step = value;
	}
	mValue = value;
	mStep = step;
	*/
	mValue = value > 0.0f ? value : 1 ;
	mStep = step > 0.0f ? step : mValue;
}

