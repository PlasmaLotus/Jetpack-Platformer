#ifndef __RAWINPUT__
#define __RAWINPUT__

#include <Windows.h>
#pragma comment(lib,"xinput9_1_0.lib")

#include <Xinput.h>
#include <list>
#include <map>
#include <array>

#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

//constexpr int MAX_CONTROLLERS_ = 4;
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
};

#endif // RAWINPUT