#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdio.h>
#include <SDL.h>
#include "SDL_syswm.h"
#include <string>

class Settings{
public:
	void parseArgs(int args, char** argv);
	void parseConfig();
	std::string ReadFile(std::string filename);
	std::string ReadFile(const char* filename);
	void logSystenInformation(SDL_Window* window);
	static Settings& getInstance();
	~Settings();
	/*
	Settings(Settings const&)= delete;
	void operator=(Settings const&) = delete;
	*/
private :
	//static Settings* instance;
	Settings();

};
#endif // !Component_H

namespace Utility{
	enum Typeface
	{
		Minuscule = 0,
		FirstLetterCap = 1,
		AllCap = 2,

		Default = -1
	};
	const char* boolToChar(const bool b, Utility::Typeface flag);

}// namespace Utility