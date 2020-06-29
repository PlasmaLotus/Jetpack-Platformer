#ifndef __D_STATE__
#define __D_STATE__

#include "State.h"
class DebugState :
	public State
{
public:
	DebugState();
	~DebugState();
	void Update(float dt){}
	void Render(void* renderTarget){}
};

#endif
