#ifndef __INPUT__
#define __INPUT__

#include <windows.h>
#include <Xinput.h>
//#include <direct.h>
//#include <SDKDDKVer.h>
//#pragma comment(lib,"xinput9_1_0.lib")

#include <list>
#include <map>
#include <array>

#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

constexpr auto MAX_CONTROLLERS = 4;

class XGPad {
public:
	bool enabled;
	long deadzone;
	INT64 timeout;
	XINPUT_BATTERY_INFORMATION batteryInfo;
	XINPUT_STATE state;
	//bool isWireless();
};

class InputRaw_X
{
public:
	~InputRaw_X();
	void update();
	static InputRaw_X& getInstance();
	void pollInput();
	static XGPad& getGamepad(int i);
	void updateControllersSDL();
private:
	InputRaw_X();
	bool initialize();
	bool deinitialize();
	XGPad gamepads[4];
	XINPUT_CAPABILITIES gamepadCapabilities[4];
	const INT64    XINPUT_ENUM_TIMEOUT_MS = 2000;  // 2 seconds
	void onGamepadEnabled(int pad);
	void onGamepadDisabled(int pad);
};



class VirtualButton {
public:
	VirtualButton();
	~VirtualButton();

	bool check; //If the button is down
	bool pressed;
	bool released;

	void consumeBuffer();
	void consumePress();
	float bufferCounter;
};
class VirtualGamepad {

public:
	VirtualGamepad();
	~VirtualGamepad();

	//lisf of virtual buttons

	void getState();
	void setState();

	/*buttons*/
};


class CONTROLLER_STATE
{
public:
	XINPUT_STATE state;
	bool bConnected;
	
	std::string toString();
	char* toBytes();
};

class Input {
public:
	Input();
	virtual ~Input();

	static enum Buttons {
	};
	
	virtual void update();
	//virtual CONTROLLER_INPUTS getControllerInputs(int id);
	//virtual std::array<CONTROLLER_INPUTS, MAX_CONTROLLERS> getAllControllerInputs();

	virtual std::string getControllerStateString(int id);
	virtual std::string getAllControllerStatesString(int id);

	virtual char* getControllerStateBytes(int id);
	virtual std::string getAllControllerStatesBytes(int id);
	//void rumble();
private:
	HRESULT updateControllers();
	CONTROLLER_STATE mControllers[MAX_CONTROLLERS];
	void init();
	void deInit();
	void onControllerConnect(int id);
	void onControllerDisconnect(int id);
};



class GenericInput {
public:
	GenericInput() {};
	~GenericInput() {};
private:
};

#endif // INPUT
