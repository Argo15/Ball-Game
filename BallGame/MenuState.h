#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <string>
#include "Texture.h"
#include "MenuItem.h"
using namespace std;

class MenuState : public GameState {
public:
	MenuState();
	~MenuState() {}

	void resize(int w, int h);
	void update(int fps);
	void render();
	MenuItem** items;

	static int screenWidth;
	static int screenHeight;
};



#endif