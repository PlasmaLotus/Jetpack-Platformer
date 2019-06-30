#ifndef __INPUT__
#define __INPUT__

#include <windows.h>
#include <Xinput.h>
//#include <direct.h>
//#include <SDKDDKVer.h>

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


class Input {
public:

	~Input();
	void update();
	void initialize();
	void deinitialize();
	int gamepads[4];
	void rumble();
	int getGamepad(int id);
	
private:
	Input();

};


#endif

