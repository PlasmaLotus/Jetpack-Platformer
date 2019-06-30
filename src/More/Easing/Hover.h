#ifndef _HOVER_
#define _HOVER_

#include <math.h>

#ifndef PI
#define PI  3.14159265
#endif

//Time, Begin, Change, Duration
class HoverEase {
	
	public:
		
		static float easeIn(float t,float b , float c, float d);
		static float easeOut(float t,float b , float c, float d);
		static float easeInOut(float t,float b , float c, float d);
		
};

#endif