#ifndef __ENGINE__
#define __ENGINE__

#include <cstdint>
#include <stdlib.h>

namespace PL{

class Engine{
public:
	Engine();
	~Engine();

	int ProcessArgs(int args, char** argv);
	int Run();

	int GameLoop();

	int InitSettingsConfig();

	void ProcessInput(/**/);
	void InitRenderer();
	void Cleanup();
	void Quit(int exitCode);
};
}

#endif // !__ENGINE__

