#include "Input.h"
#include <Xinput.h>

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
}

void Input::deInit()
{
	//XInputEnable(false);
}

void Input::onControllerConnect(int id)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION) );
	vibration.wLeftMotorSpeed = 1000;
	XInputSetState(id, &vibration);
}

void Input::onControllerDisconnect(int id)
{
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

CONTROLLER_INPUTS Input::getControllerInputs(int id)
{
	return CONTROLLER_INPUTS();
}

std::array<CONTROLLER_INPUTS, MAX_CONTROLLERS> Input::getAllControllerInputs()
{
	return std::array<CONTROLLER_INPUTS, MAX_CONTROLLERS>();
}

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