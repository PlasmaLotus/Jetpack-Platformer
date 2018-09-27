
#include <SFML/Graphics.hpp>
#include "Main.h"
//#include"states\statemanager.h"

void update();
int main(int argc, char *argv[])
{
	
	/*
	StateManager& sm = StateManager::getInstance();
	sm.run();
	return 0;
	*/

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock clock;
	sf::Time prevElapsed{ clock.restart() };
	sf::Time elapsed{ clock.restart() };
	sf::Time lag{ sf::milliseconds(0) };
	

	sf::Time MS_PER_FRAME{ sf::seconds(1.f / 60.f) };
	double MS_PER_UPDATE = 1000.0 / 60.0;
	int updateCounter{0};
	while (window.isOpen())
	{
		updateCounter = 0;
		elapsed = clock.restart();
		prevElapsed = elapsed;
		lag += elapsed;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//processInput();
		//gotoxy(0, 0);

		while (lag >= MS_PER_FRAME)
		{
			update();
			lag -= MS_PER_FRAME;
			++updateCounter;
		}
		if (updateCounter >= 1) {
			printf("MicroSeconds: %d, Nb of Updates: %d\n", elapsed.asMicroseconds(), updateCounter);
		
		}
		else {
			printf("MicroSeconds: %d\n", elapsed.asMicroseconds());

		}
		
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);

}

void update() {}
void render(double t);
void loop() {
	
	
	while (true)
	{
		
		
	}
}

