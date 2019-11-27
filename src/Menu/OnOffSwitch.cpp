#include "OnOffSwitch.h"
//#include "pch.h"

const float OnOff::SWITCH_TIME{ 1.0f };

OnOff::OnOff(std::string label):
	OnOff(label, "On", "Off", true)
{
}

OnOff::OnOff(std::string label, bool isOn) :
	OnOff(label, "On", "Off", isOn)
{
}

OnOff::OnOff(std::string label, std::string onText, std::string offText, bool isOn):
	MenuItem(label),
	mTrue(onText),
	mFalse(offText),
	mValue(isOn),
	mIsSwitching(false)
{
	mShiftable = true;
	mEaseStep = isOn ? 0.0f: 1.0f;
}

OnOff::~OnOff()
{
}

void OnOff::Update(float dt)
{
	MenuItem::Update(dt);
}

void OnOff::Render(void * renderTarget)
{
	MenuItem::Render(renderTarget);
}

void OnOff::ConfirmAction()
{
	MenuItem::ConfirmAction();
	Switch();
	OnConfirm();
}

void OnOff::AltAction()
{
	MenuItem::AltAction();
	Switch();
	OnAltConfirm();
}

void OnOff::LeftShift()
{
	MenuItem::LeftShift();
	if (!mValue) {
		SwitchOn();
		OnShiftLeft();
	}
	//Else the value does not change, it is already On
}

void OnOff::RightShift()
{
	MenuItem::RightShift();
	if (mValue) {
		SwitchOff();
		OnShiftRight();
	}
	//Else the value does not change, it is already Off
}

void OnOff::Switch()
{
	if (mValue)
		SwitchOff();
	else
		SwitchOn();
}

void OnOff::SwitchOn()
{
	mValue = true;
}

void OnOff::SwitchOff()
{
	mValue = false;
}

bool OnOff::getSwitchState()
{
	return mValue;
}

std::string OnOff::getTrueLabel()
{
	return mTrue;
}

std::string OnOff::getFalseLabel()
{
	return mFalse;
}

void OnOff::OnSwitch()
{
}

