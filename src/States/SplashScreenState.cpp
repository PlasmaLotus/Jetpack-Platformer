#include "SplashScreenState.h"
#include <SFML/Graphics.hpp>
SplashScreenState::SplashScreenState()
{
	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		gGameController = SDL_JoystickOpen(0);
		if (gGameController) {
			printf("SDL!");
			printf("Opened Joystick 0\n");
			printf("Name: %s\n", SDL_JoystickNameForIndex(0));
			printf("Number of Axes: %d\n", SDL_JoystickNumAxes(gGameController));
			printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(gGameController));
			printf("Number of Balls: %d\n", SDL_JoystickNumBalls(gGameController));
		
			SDL_JoystickID joystickID{ SDL_JoystickInstanceID(gGameController) };
		}
		else {
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			printf("Couldn't open Joystick 0\n");
		}
		
		if (sf::Joystick::isConnected(0)) {
			printf("SFML!");
			sf::Joystick::Identification sfmlID{ sf::Joystick::getIdentification(0) };
			printf("Name: %s\n", sfmlID.name);
			printf("Number of Buttons: %d\n", sf::Joystick::getButtonCount(0));

		}
	}
}

SplashScreenState::~SplashScreenState()
{
	if (SDL_JoystickGetAttached(gGameController	)) {
		SDL_JoystickClose(gGameController);
	}
	/*
	if (gGameController) {
		SDL_JoystickClose(gGameController);
	}
	*/
}

void SplashScreenState::Update(float dt)
{
	sf::Joystick
}

void SplashScreenState::Render(void * renderTarget)
{
	if (renderTarget) {
		sf::RenderWindow* wWindow{ static_cast<sf::RenderWindow*>(renderTarget) };
		if (wWindow) {
			sf::RectangleShape rect(sf::Vector2f(32.0f,32.0f));
			rect.setPosition(sf::Vector2f(100.0f, 100.0f));
			wWindow->draw(rect);
		}
	}
}
