#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MainMenuState.h"
#include "LevelState.h"
#include <iostream>
#include "Background.h"
#include "ArgoMatrix.h"
#include "Globals.h"
#include <time.h>
#include <list>
using namespace std;
/**
Initializes everything needed in background
**/
Background::Background(int w, int h)
{
	/*
	//create every new bullet
	for(int x=0;x<sizeof(bullets)/sizeof(int);x++)
	{
   		bullets[x]=new Bullet((rand()/double(RAND_MAX))*1280,(rand()/double(RAND_MAX))*900,(rand()/double(RAND_MAX))*6,(rand()/double(RAND_MAX))*6);
	}
	*/
}
/**
destructor, deletes pointers used
**/
Background::~Background()
{
	/*
	for(list<ArgoVector4*>::iterator it = lineList.begin();it!=lineList.end();it++)
	{
		delete(*it);
	}
	delete(*bullets);
	*/
}
/**
updates all of the bullets positions
**/
void Background::update()
{
	/*
for(int r=0;r<sizeof(bullets)/sizeof(int);r++)
	{
		bullets[r]->position += bullets[r]->velocity;
		if(bullets[r]->position[0]<=0)
		{
			bullets[r]->position[0]=1;
			bullets[r]->velocity[0]*=-1;
		}
		if(bullets[r]->position[0]>=width)
		{
			bullets[r]->position[0]=width-1;
			bullets[r]->velocity[0]*=-1;
		}
		if(bullets[r]->position[1]<=0)
		{
			bullets[r]->position[1]=1;
			bullets[r]->velocity[1]*=-1;
		}
		if(bullets[r]->position[1]>=height)
		{
			bullets[r]->position[1]=height-1;
			bullets[r]->velocity[1]*=-1;
		}
	}
	for(int i = 0;i<sizeof(bullets)/sizeof(int);i++)
	{
		for(int j=0;j<sizeof(bullets)/sizeof(int);j++)
		{
			int xi = bullets[i]->position[0];
			int yi = bullets[i]->position[1];
			int xj = bullets[j]->position[0];
			int yj = bullets[j]->position[1];

			lineList.push_back(new ArgoVector4((float)xi,(float)yi,(float)xj,(float)yj));
			
		}
	}
	*/
}
/**
renders lines between the bullets to the screen
**/
void Background::drawBackground()
{
	/*
	glColor4f(1.0, 1.0, 1.0,0.05);

	for(list<ArgoVector4*>::iterator it = lineList.begin();it!=lineList.end();it++)
	{

			int xi = (*it)[0][0];
			int yi = (*it)[0][1];
			int xj = (*it)[0][2];
			int yj = (*it)[0][3];
			glBegin(GL_LINES);
			glVertex3f(xi,yi,-5);
			glVertex3f(xj,yj,-5);
			glEnd();
	}
	*/
}
/**
creates a bullet object
**/
Bullet::Bullet(int x,int y, int velx, int vely)
{
	/*
	position.set(x,y,0);
	velocity.set(velx,vely,0.0f);
	*/
}