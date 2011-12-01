#ifndef TROPHIEMENUSTATE_H
#define TROPHIEMENUSTATE_H

#include "MenuState.h"
#include "Texture.h"
#include "Background.h"

class TrophieMenuState : public MenuState {
public:
	//An integer that holds the index of our menuitem
	int currentItem;
	TrophieMenuState();
	~TrophieMenuState() {}
	Background* background;
	void resize(int w, int h);
	void update(int fps);
	void render();
private:
	bool keyDown[256];
};




#endif