
#include <SFML/Graphics.hpp>
#include "Main.h"
//#include "Input.h"
#include "Engine.h"
//#include"states\statemanager.h"

//Event testing
#include "Event/EventManager.h"
#include "Event/IEvent.h"
#include "Event/IObserver.h"
#include "Event/ISubject.h"

int main(int argc, char *argv[])
{
	Engine& e = Engine::getInstance();
	e.Run();
	/*
	EventManager em;
	IObserver ob;
	ISubject sb;
	int rep;
	rep = em.Connect<IEvent>(&sb, &ob);
	rep = em.Connect<IEvent>(&sb, &ob);
	em.Emit(&sb, new IEvent);
	rep = em.Disconnect<IEvent>(&sb, &ob);
	rep = em.Disconnect<IEvent>(&sb, &ob);
	*/

	/*
	InputRaw_X& input = InputRaw_X::getInstance();
	input.update();
	*/

	Menu menu(true);
	OnOff* onoff = new OnOff{ "SwitchOption" };
	Slider* slider = new Slider{ "SliderOption", 0, 10, 1, 10 };
	menu.addItem(onoff);
	menu.addItem(slider);


	onoff->Switch();
	slider->RightShift();
	slider->LeftShift();
	slider->LeftShift();
	slider->LeftShift();

	int a = 1;
	int b = Utility::sign(-3.69f);



	Engine& EN = Engine::getInstance();
	EN.Run();
	return 0;


	sf::RenderWindow window;
	window.create(sf::VideoMode(200, 200), "SFML works!");
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

		sf::Event _event;
		while (window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				window.close();
		}

		//processInput();
		//gotoxy(0, 0);

		while (lag >= MS_PER_FRAME)
		{
			//update();
			lag -= MS_PER_FRAME;
			++updateCounter;
		}
		if (updateCounter >= 1) {
			//TODO: int64
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
