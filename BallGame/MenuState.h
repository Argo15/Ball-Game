#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include <string>
using namespace std;
class MenuItem;

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

class MenuItem{
public:
	void drawItem();
	void setTopLeft(float,float);
	void setBottomRight(float,float);
	void setDescription(string);
private:
	string description;
	GameState* buttonLink;

	float topLeftX;
	float topLeftY;
	float bottomRightX;
	float bottomRightY;
};

#endif