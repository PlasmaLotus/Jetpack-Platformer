#include "State.h"

State::State()
{
}

State::~State()
{
}

void State::update()
{
}

void State::render()
{
}

void State::goBack() {

}

bool State::renderWhenUnfocused()
{
	return _renderWhenUnfocused;
}

bool State::updateWhenUnfocused()
{
	return _updateWhenUnfocused;
}

void State::onFocus()
{
}

void State::onUnfocus()
{
}
