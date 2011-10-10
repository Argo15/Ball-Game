#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "ArgoMatrix.h"
#include <list>
#include "ArgoMatrix.h"
class Bullet
{
public:
	ArgoVector3 position;
	ArgoVector3 velocity;
	Bullet(int x, int y, int velx, int vely);
	Bullet(){}
};

class Background
{
public:
	Background();
	Background(int w, int h);
	Bullet* bullets[3];
	void drawBackground();
	void update();
	int width;
	int height;
	list<ArgoVector4*> lineList;
private:


};

#endif