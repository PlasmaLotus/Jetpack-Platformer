#include "Hover.h"

float HoverEase::easeIn (float t,float b , float c, float d) {
	return -c * cos(t/d * (PI/2)) + c + b;
}
float HoverEase::easeOut(float t,float b , float c, float d) {	
	return c * sin(t/d * (PI/2)) + b;	
}

float HoverEase::easeInOut(float t,float b , float c, float d) {
	return -c/2 * (cos(PI*t/d) - 1) + b;
}