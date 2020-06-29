#ifndef __SLIDER__
#define __SLIDER__
#include "OptionItem.h"
class Slider :
	public OptionItem<int>
{
public:
	Slider(std::string label);
	/*
	Slider Ctor ranging from 2 values
	@param step: the amount skipped between values: ex: 1 to 10 with step 2 = {1, 3, 5, 7, 9}
	@param value: the currently selected value. If the value cannot be selected the default 1st value will be selected
	Sequence starts from min. Goes to max with step values skipped. This will not go past max, if the max is not in the suite, it is ommitted
	The value label will have the same name as the value, as a String
	*/
	Slider(std::string label, int min, int max, int step = 1, int value = -1);
	//Slider(std::string label, std::vector<tuple<std::string, int>> items);
	
	
	Slider(std::string label, std::vector<std::string> items, unsigned int selectedIndex);
	~Slider();
};
#endif