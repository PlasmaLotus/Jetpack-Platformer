#include "Input.h"
//#include <Xinput.h>
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
	updateControllersSDL();
}

InputRaw_X & InputRaw_X::getInstance()
{
	static InputRaw_X instance;
	return instance;
}

void InputRaw_X::pollInput()
{
	DWORD dwResult;
	DWORD maxCount = XUSER_MAX_COUNT;
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
				printf("Device online\n");
				//pad.timeout == 0;
			}
			else
			{
				// Controller is not connected 
				if (dwResult == ERROR_DEVICE_NOT_CONNECTED){
					printf("Device not connected\n");
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
		
		INT32 capsResult = XInputGetCapabilities(0, /*XINPUT_FLAG_GAMEPAD*/0, &gamepadCapabilities[i]);
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
	XINPUT_BATTERY_INFORMATION& info{ gamepads[pad].batteryInfo };
	XInputGetBatteryInformation(pad, BATTERY_DEVTYPE_GAMEPAD, &info);
	XINPUT_STATE& state = gamepads[pad].state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(pad, &state);
}

void InputRaw_X::onGamepadDisabled(int pad)
{
}



Input::Input()
{
	init();
}

void Input::init()
{
	//XInputEnable(true);
	//XInputGetBatteryInformation()

	// Init state
	ZeroMemory(mControllers, sizeof(CONTROLLER_STATE) * MAX_CONTROLLERS);
	update();
}

void Input::deInit()
{
	//XInputEnable(false);
}

void Input::onControllerConnect(int id)
{
	/*
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION) );
	vibration.wLeftMotorSpeed = 1000;
	XInputSetState(id, &vibration);
	*/
	printf("Controller %d Connected!/n", id);
	printf("Controller: %s\n", sf::Joystick::getIdentification(id).name.toAnsiString().c_str());
}

void Input::onControllerDisconnect(int id)
{
	//Reset Vibration to 0
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	XInputSetState(id, &vibration);
}



Input::~Input()
{
	deInit();
}

void Input::update()
{
	updateControllers();
	
}

/*
CONTROLLER_INPUTS Input::getControllerInputs(int id)
{
	return CONTROLLER_INPUTS();
}

std::array<CONTROLLER_INPUTS, MAX_CONTROLLERS> Input::getAllControllerInputs()
{
	return std::array<CONTROLLER_INPUTS, MAX_CONTROLLERS>();
}
*/

std::string Input::getControllerStateString(int id)
{
	return std::string();
}

std::string Input::getAllControllerStatesString(int id)
{
	return std::string();
}

char * Input::getControllerStateBytes(int id)
{
	return nullptr;
}

std::string Input::getAllControllerStatesBytes(int id)
{
	return std::string();
}

HRESULT Input::updateControllers() {
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &mControllers[i].state);
		printf("Controller: %s\n", sf::Joystick::getIdentification(i).name.toAnsiString().c_str());
		//mControllers[i].state.Gamepad.

		//sf::Packet p;
		
		if (dwResult == ERROR_SUCCESS)
		{
			if (!mControllers[i].bConnected) {
				onControllerConnect(i);
			}
			mControllers[i].bConnected = true;

			// Controller is connected 
			printf("Controller %d is connected \n", i);
		}

		else {
			if (mControllers[i].bConnected) {
				onControllerDisconnect(i);
			}
			mControllers[i].bConnected = false;

			// Controller is not connected 
			printf("Controller %d isn't connected \n", i);
		}
	}

	return S_OK;
}

std::string CONTROLLER_STATE::toString()
{
	return std::string();
}

char * CONTROLLER_STATE::toBytes()
{
	return nullptr;
}

sf::Packet& operator <<(sf::Packet& packet, const CONTROLLER_STATE& c)
{
	//c.state.
	return packet << c.state.Gamepad.wButtons <<
		c.state.Gamepad.sThumbLX << c.state.Gamepad.sThumbLY << c.state.Gamepad.bLeftTrigger <<
		c.state.Gamepad.sThumbRX << c.state.Gamepad.sThumbRY << c.state.Gamepad.bRightTrigger;
}

sf::Packet& operator >>(sf::Packet& packet, CONTROLLER_STATE& c)
{
	return packet >> c.state.Gamepad.wButtons >>
		c.state.Gamepad.sThumbLX >> c.state.Gamepad.sThumbLY >> c.state.Gamepad.bLeftTrigger >>
		c.state.Gamepad.sThumbRX >> c.state.Gamepad.sThumbRY >> c.state.Gamepad.bRightTrigger;
}

#include <SDL.h>
void InputRaw_X::updateControllersSDL(){
				//SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
				SDL_GameControllerAddMappingsFromFile("D:\\Documents\\Projects\\Jetpack-Platformer\\ref\\gamecontrollerdb.txt");
	SDL_GameController* controller = nullptr;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				//TODO:do stuff here
				SDL_GameControllerClose(controller);
				break;
			}
			else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}
}