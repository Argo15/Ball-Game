#ifndef MENUITEM_H
#define MENUITEM_H

#include "GameState.h"
#include <string>
#include "Texture.h"
#include "MenuItem.h"
using namespace std;

class MenuItem{
public:
	MenuItem();
	void drawItem();
	void setTopLeft(float,float);
	void setBottomRight(float,float);
	void setDescription(string);
	void setButtonLink(GameState* link);
	void switchState();
	void updateBob();
	Texture* texture;
	bool current;
	int bobamount;
	int bobadd;
	string link;
	float topLeftX;
	float topLeftY;
	float bottomRightX;
	float bottomRightY;
	string description;
private:
	GameState* buttonLink;


};

#endif