#ifndef __Utility__
#define __Utility__

#include <windows.gaming.input.h>
#include <algorithm>
#include <ppl.h>

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


	static void inputTest() {
		//ABI::Windows::Gaming::Input::
		//Gamepad::GamepadAdded
		//Windows::Gaming::Input::ArcadeStick^ stick;
		//ABI::Windows::Gaming::Input::IGameController gc;
		
	}
};

#endif // Util!

