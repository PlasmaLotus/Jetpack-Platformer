#include "pch.h"
//#include "../../src/Menu/OnOffSwitch.h"
//#include "Menu/OnOffSwitch.h"
//#include "Menu/OnOffSwitch.h"


/*
//Create a new Switch and set it at on
TEST(OnOffSwitch, ConstructorOn) {
	OnOff sw("Switch", true);
	EXPECT_TRUE(sw.getSwitchState());
}

//Create a new Switch and set it at off
TEST(OnOffSwitch, ConstructorOff) {
	OnOff sw("Switch", false);
	EXPECT_FALSE(sw.getSwitchState());
}

//Switch to on
TEST(OnOffSwitch, SwitchOn) {
	OnOff sw("Switch");
	sw.SwitchOn();
	EXPECT_TRUE(sw.getSwitchState());

	sw = OnOff("SwitchOn", true);
	sw.SwitchOn();
	EXPECT_TRUE(sw.getSwitchState());

	sw = OnOff("SwitchOff", false);
	sw.SwitchOn();
	EXPECT_TRUE(sw.getSwitchState());
}

//Switch to off
TEST(OnOffSwitch, SwitchOff) {
	OnOff sw("Switch");
	sw.SwitchOff();
	EXPECT_FALSE(sw.getSwitchState());

	sw = OnOff("SwitchOn", true);
	sw.SwitchOff();
	EXPECT_FALSE(sw.getSwitchState());

	sw = OnOff("SwitchOff", false);
	sw.SwitchOff();
	EXPECT_FALSE(sw.getSwitchState());
}

//Switch
TEST(OnOffSwitch, Switch) {
	OnOff sw("Switch");

	bool a = sw.getSwitchState();
	EXPECT_EQ(a, sw.getSwitchState());

	sw.Switch();
	EXPECT_EQ(!a, sw.getSwitchState());

	sw.Switch();
	EXPECT_EQ(a, sw.getSwitchState());


	//Start from on
	sw = OnOff("Switch", true);
	EXPECT_TRUE(sw.getSwitchState());

	sw.Switch();
	EXPECT_FALSE(sw.getSwitchState());

	sw.Switch();
	EXPECT_TRUE(sw.getSwitchState());

	//Start from off
	sw = OnOff("Switch", false);
	EXPECT_FALSE(sw.getSwitchState());

	sw.Switch();
	EXPECT_TRUE(sw.getSwitchState());

	sw.Switch();
	EXPECT_FALSE(sw.getSwitchState());
}


//Trigger a switch from on to off with Confirm
*/