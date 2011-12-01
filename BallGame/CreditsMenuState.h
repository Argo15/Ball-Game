#ifndef CREDITSMENUSTATE_H
#define CREDITSMENUSTATE_H

#include "MenuState.h"
#include "Texture.h"
#include "Background.h"

class CreditsMenuState : public MenuState {
public:
	//An integer that holds the index of our menuitem
	int currentItem;
	CreditsMenuState();
	~CreditsMenuState() {}
	Background* background;
	void resize(int w, int h);
	void update(int fps);
	void render();
private:
	bool keyDown[256];
};




#endif