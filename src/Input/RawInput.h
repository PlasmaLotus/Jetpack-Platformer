#ifndef __RAWINPUT__
#define __RAWINPUT__

#include <Windows.h>
#pragma comment(lib,"xinput9_1_0.lib")

#include <Xinput.h>
#include <list>
#include <map>
#include <array>
#include <vector>

//#include <SFML/Window.hpp>
//#include <SFML/Network.hpp>

//#include <windows.gaming.input.h>

//constexpr int MAX_CONTROLLERS_ = 4;
#include <windows.gaming.input.h>
#include <algorithm>
#include <ppl.h>
#include <concrt.h>

const int MAX_CONTROLLERS_ = 4;

class CONTROLLER_STATE
{
public:
	XINPUT_STATE previousState;
	XINPUT_STATE state;
	bool bConnected;

	std::string toString();
	char* toBytes();
};

struct CONTROLLER_INPUTS {
};

class RawInput {
public:
	//static const int MAX_CONTROLLERS_ = 4;
	RawInput();
	virtual ~RawInput();

	virtual void update();
	virtual CONTROLLER_INPUTS getControllerInputs(int id);
	virtual std::array<CONTROLLER_INPUTS, MAX_CONTROLLERS_> getAllControllerInputs();

	virtual std::string getControllerStateString(int id);
	virtual std::string getAllControllerStatesString(int id);

	virtual char* getControllerStateBytes(int id);
	virtual std::string getAllControllerStatesBytes(int id);

	void Init();
	void DeInit();
private:

	bool active;
	bool disabled;
	HRESULT updateControllers();
	CONTROLLER_STATE mControllers[MAX_CONTROLLERS_];
	void onControllerConnect(int id);
	void onControllerDisconnect(int id);

	//auto myGamepads = ref new std::vector<ABI::Windows::Gaming::Input::Gamepad^>();
	//concurrency::critical_section myLock{};

	/*
	for (auto gamepad : Gamepad::Gamepads)
	{
		// Check if the gamepad is already in myGamepads; if it isn't, add it.
		critical_section::scoped_lock lock{ myLock };
		auto it = std::find(begin(myGamepads), end(myGamepads), gamepad);

		if (it == end(myGamepads))
		{
			// This code assumes that you're interested in all gamepads.
			myGamepads->Append(gamepad);
		}
	}
	*/
};

#endif // RAWINPUT