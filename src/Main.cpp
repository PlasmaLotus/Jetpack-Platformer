
#include <SFML/Graphics.hpp>
#include "Main.h"
#include "Engine.h"

//#include"states\statemanager.h"

int main(int argc, char *argv[])
{
	
	Engine& e = Engine::getInstance();
	e.run();

	/*
	StateManager& sm = StateManager::getInstance();
	sm.run();
	return 0;
	*/

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


