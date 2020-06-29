#include "Slider.h"

Slider::Slider(std::string label):
	OptionItem(label)
{
}

Slider::Slider(std::string label, int min, int max, int step, int value):
	OptionItem(label)
{
	for (int i = min; i <= max; i+=step) {
		add(std::to_string(i), i, i == value);
	}
}

Slider::Slider(std::string label, std::vector<std::string> items, unsigned int selectedIndex):
	OptionItem(label)
{
	int i{ 0 };
	for (std::string s: items) {
		add(s, i, i == selectedIndex);
	}
}

Slider::~Slider()
{
}


/*
public Slider(string label, Func<int, string> values, int min, int max, int value = -1) : base(label)
{
	for (int i = min; i <= max; i++)
	{
		base.Add(values(i), i, value == i);
	}
}
*/