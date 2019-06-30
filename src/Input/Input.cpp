#include "Input.h"
#include "../Engine.h"

InputRaw_X::InputRaw_X()
{
	initialize();
}


InputRaw_X::~InputRaw_X()
{
}

void InputRaw_X::update()
{
	pollInput();
}

InputRaw_X & InputRaw_X::getInstance()
{
	static InputRaw_X instance;
	return instance;
}

void InputRaw_X::pollInput()
{
	DWORD dwResult;
	//dwResult = 0;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XGPad & pad = gamepads[i];
		XINPUT_STATE& state = gamepads[i].state;
		uint64_t elapsedTime = Engine::getInstance().getElapsedTimeAsMilliseconds();


		//Check first if the controller is connected or not;
		if (!pad.enabled)
		{
			//Get the amount of time passed;
			pad.timeout += elapsedTime;
			if (pad.timeout < XINPUT_ENUM_TIMEOUT_MS)
			{
				return;
			}

			// Check for controller connection by trying to get the capabilties
			INT32 capsResult = XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &gamepadCapabilities[i]);
			if (capsResult != ERROR_SUCCESS)
			{
				return;
			}

			// Device is connected
			pad.enabled = true;
			onGamepadEnabled(i);
			pad.timeout = 0;
		}
		
		
		{
			//RtlSecureZeroMemory(&state, sizeof(XINPUT_STATE));
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState(i, &state);

			//XINPUT_BATTERY_INFORMATION& info{ gamepads[i].batteryInfo };
			//XInputGetBatteryInformation(i, BATTERY_DEVTYPE_GAMEPAD, &info);

			if (dwResult == ERROR_SUCCESS)
			{
				// Controller is connected 
				gamepads[i].enabled = true;
				onGamepadEnabled(i);
				//pad.timeout == 0;
			}
			else
			{
				// Controller is not connected 
				if (dwResult == ERROR_DEVICE_NOT_CONNECTED){
					
				}
				gamepads[i].enabled = false;
				onGamepadDisabled(i);

			}
		}



		
	}
}

XGPad& InputRaw_X::getGamepad(int i)
{
	return getInstance().gamepads[i];
	//return XGamepad();
}

bool InputRaw_X::initialize() {

	//XInputEnable(true);
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XGPad & pad = gamepads[i];
		XINPUT_STATE& state = gamepads[i].state;
		pad.timeout = 0;


		// Check for controller connection by trying to get the capabilties
		INT32 capsResult = XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &gamepadCapabilities[i]);
		if (capsResult == ERROR_SUCCESS)
		{
			// Device is connected
			pad.enabled = true;
			onGamepadEnabled(i);
				
		}
		else {
			pad.enabled = false;
			onGamepadDisabled(i);
			// Device isn't connected
		}


		XINPUT_BATTERY_INFORMATION& info{ gamepads[i].batteryInfo };
		XInputGetBatteryInformation(i, BATTERY_DEVTYPE_GAMEPAD, &info);
			
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS){
			// Controller is connected 
		}
		else{
			// Controller is not connected 
		}

	}
	return true;
}

bool InputRaw_X::deinitialize()
{
	//XInputEnable(false);
	return true;
}

void InputRaw_X::onGamepadEnabled(int pad)
{
}

void InputRaw_X::onGamepadDisabled(int pad)
{
}
