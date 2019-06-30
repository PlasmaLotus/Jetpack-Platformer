#ifndef __INPUT_CONTROLLER__
#define __INPUT_CONTROLLER__

//include <SFML/Graphics.hpp>
#include <list>
//#include <>
//#include <algorithm>
#include <math.h>
#include "inputRecord.h"

//class InputRecord;
class InputController {
public:
	InputController();
	~InputController();


	std::string toString();

	InputRecord getCurrentInput();
	InputRecord getInput(int frame);
	InputRecord previous();
	InputRecord current();
	InputRecord next();
	void writeInputs();
	
	bool hasInputPressed();
	bool hasInputReleased();
	bool hasInput();


	std::list <InputRecord> mInputs;
	int mInputIndex;
	int currentFrame();
	int framesToNext;
};

#endif // __INPUT_CONTROLLER__