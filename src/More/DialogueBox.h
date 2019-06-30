#ifndef DBOX_H
#define DBOX_H

#include "Component.h"
#include <string>


class DialogBox{
public:
	DialogBox();
	~DialogBox();
	virtual void update(float delta);
	virtual void render(void* target);
	virtual void debugRender(void* target);


	bool loadScript(std::string filepath);


};
#endif // !DBOX_H