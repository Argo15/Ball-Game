#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "ArgoMatrix.h"
#include "Texture.h"

class Background
{
public:
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