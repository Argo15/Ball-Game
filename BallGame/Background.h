#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "ArgoMatrix.h"
class Bullet
{
	ArgoVector3 position;
	ArgoVector3 velocity;
	Bullet(int x, int y, int velx, int vely);
};

class Background
{
public:
	Background(){}
	Background(int w, int h);
	Bullet bullets[15];
	void drawBackground();
private:
	int width;
	int height;

};

#endif