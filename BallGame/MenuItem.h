#ifndef MENUITEM_H
#define MENUITEM_H

#include "GameState.h"
#include <string>
#include "Texture.h"
#include "MenuItem.h"
using namespace std;

class MenuItem{
public:
	void drawItem();
	void setTopLeft(float,float);
	void setBottomRight(float,float);
	void setDescription(string);
	void setButtonLink(GameState* link);
	void switchState();
	Texture* texture;
	bool current;
private:
	string description;
	GameState* buttonLink;

	float topLeftX;
	float topLeftY;
	float bottomRightX;
	float bottomRightY;
};

#endif