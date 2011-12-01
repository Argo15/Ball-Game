#ifndef GRAPHICSMENUSTATE_H
#define GRAPHICSMENUSTATE_H

#include "MenuState.h"
#include "Texture.h"
#include "Background.h"

class GraphicsMenuState : public MenuState {
public:
	//An integer that holds the index of our menuitem
	int currentItem;
	GraphicsMenuState();
	~GraphicsMenuState() {}
	Background* background;
	void resize(int w, int h);
	void update(int fps);
	void render();
private:
	bool keyDown[256];
};




#endif