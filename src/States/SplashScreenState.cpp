#include "SplashScreenState.h"
#include <SFML/Graphics.hpp>
SplashScreenState::SplashScreenState()
{
}

SplashScreenState::~SplashScreenState()
{
}

void SplashScreenState::Update(float dt)
{
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
