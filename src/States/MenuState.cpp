#include "MenuState.h"
#include "../Main.h"
#include "StateManager.h"

MenuState::MenuState():
MenuState(nullptr, nullptr){
}

MenuState::MenuState(sf::RenderWindow * w, Menu * m):
window(w),
menu(m)
{
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(2));
	p2Controller = new MenuController(p2KeyConfig, menu);
	renderer = new MenuRenderer(window, menu);
}

MenuState::MenuState(sf::RenderWindow * w):
	MenuState(w, nullptr){
}

MenuState::MenuState(Menu * m) :
	MenuState(nullptr, m){
}

void MenuState::tick(int dt, bool render){
	p1Controller->handleInput();
	p1Controller->updateConfig();
	p2Controller->handleInput();
	p2Controller->updateConfig();
	renderer->render();
	menu->tick(dt);
}

MenuState::~MenuState()
{
	if (p1Controller != nullptr) {
		delete p1Controller;
	}
	if (p2Controller != nullptr) {
		delete p2Controller;
	}
	/*
	delete p1KeyConfig;
	delete p1Controller;
	delete p2KeyConfig;
	delete p2Controller;
	*/
}
