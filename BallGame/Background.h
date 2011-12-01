#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "ArgoMatrix.h"
#include "Texture.h"

class Star
{
public:
Star(float rise1,float run1,int w, int h);
void moveStar();
void drawStar();
Texture* starTexture;
private:
	float rise;
	float run;
	float posx;
	float posy;
	int width;
	int height;
	float angle;
	float angleadd;
};

class Background
{
public:
	Star* stars[20];
	Background();
	~Background();
	Background(int w, int h);
	void drawBackground();
	void update();
	int width;
	int height;
	float angle;
	float angleadd;
	Texture* logo;
	Texture* backgroundColor;
private:


};




#endif