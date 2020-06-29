#ifndef __Utility__
#define __Utility__

#include <windows.gaming.input.h>
#include <algorithm>
#include <ppl.h>
#include <exception>

/*
using namespace ABI;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Gaming::Input;
using namespace concurrency;
*/

class Utility
{
public:
	//Returns the sign of a T value as -1 , 0 , 1 
	template <typename T> 
	static int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

	// Usable AlmostEqual function    
	bool AlmostEqual2sComplement(float A, float B, int maxUlps = 4)
	{
		// Make sure maxUlps is non-negative and small enough that the    
		// default NAN won't compare as equal to anything.    
		{
		//assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
			if (maxUlps <= 0)
				maxUlps = 1;
			else 
				if (maxUlps >= 4 * 1024 * 1024)
					maxUlps = (4 * 1024 * 1024 - 1)
		}
		int aInt = *(int*)&A;
		// Make aInt lexicographically ordered as a twos-complement int    
		if (aInt < 0)
			aInt = 0x80000000 - aInt;
		// Make bInt lexicographically ordered as a twos-complement int    
		int bInt = *(int*)&B;
		if (bInt < 0)
			bInt = 0x80000000 - bInt;
		int intDiff = abs(aInt - bInt);
		if (intDiff <= maxUlps)
			return true;
		return false;
	}
	
	bool cmpf(float A, float B, float epsilon = 0.005f)
	{
		return (fabs(A - B) < epsilon);
	}

	static void inputTest() {
		//ABI::Windows::Gaming::Input::
		//Gamepad::GamepadAdded
		//Windows::Gaming::Input::ArcadeStick^ stick;
		//ABI::Windows::Gaming::Input::IGameController gc;
		
	}
};

#endif // Util!

