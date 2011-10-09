#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.h"
#include "Texture.h"

class MainMenuState : public MenuState {
public:
	MainMenuState();
	~MainMenuState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
private:
	Texture* background;
	void drawBackground();
	bool keyDown[256];
};




#endif