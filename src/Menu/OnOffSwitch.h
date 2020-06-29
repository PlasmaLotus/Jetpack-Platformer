#ifndef __ONOFF__
#define __ONOFF__
#include "MenuItem.h"
class OnOff :
	public MenuItem
{
public:
	//Is on by default
	OnOff(std::string label);
	OnOff(std::string label, bool isOn);
	OnOff(std::string label, std::string trueText, std::string falseText, bool isOn);
	
	~OnOff();

	virtual void Update(float dt);

	virtual void Render(void* renderTarget);

	virtual void ConfirmAction();
	virtual void AltAction();
	virtual void LeftShift();
	virtual void RightShift();

	//Change the on/off value of this OnOffSwitch
	void Switch();
	//Change the on/off value of this OnOffSwitch to the selected value
	//void Switch(bool on);
	//Change the on/off value of this OnOffSwitch to On
	void SwitchOn();
	//Change the on/off value of this OnOffSwitch to On
	void SwitchOff();

	//Get the on/off value of this OnOffSwitch
	bool getSwitchState();

	//Get the string showed when the OnOff Switch is ON
	std::string getTrueLabel();
	
	//Get the string showed when the OnOff Switch is OFF
	std::string getFalseLabel();

	///Callbacks

	//Called when the state of this OnOffSwitch changes
	void OnSwitch();
protected:
	//The on/off value of this MenuItem
	//True is On and is on the Left
	//False is Off and is on the Right
	bool mValue;
	std::string mTrue;//Text to display if the switch is on
	std::string mFalse;//Text to display if the switch is off


	//Render values: ignore for now

	static const float SWITCH_TIME;//Total time the slide animation of the OnOff labels slide when switching
	float switchTimer;//timer on the slide animation of the OnOff labels with switching
	bool mIsSwitching;

	//Relative position of the OnOff slider between the On and Off labels
	//Changes when switching from on and off
	//0 is On and 1 is Off
	float mEaseStep;
};
#endif