#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

class MenuState : public GameState {
public:
	MenuState();
	~MenuState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
};

#endif