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
	angle = 0;
	angleadd = 0.3f;
	logo = new Texture();
	logo->load("Data/Textures/BallGraphics/BallGameLogo.tga");

	backgroundColor = new Texture();
	backgroundColor->load("Data/Textures/BallGraphics/BallGameBackgroundColor.tga");
	for(int x =0;x<20;x++)
	{
	stars[x]=new Star(rand()/3000,rand()/3000,1000,1000);
	}
}
/**
destructor, deletes pointers used
**/
Background::~Background()
{
	
}
/**
updates all of the bullets positions
**/
void Background::update()
{
	angle+=angleadd;
	if(angle<5)
	{
		angleadd*=-1;
	}
	if(angle>-5)
	{
		angleadd*=-1;
	}
	for(int x =0;x<20;x++)
	{
		stars[x]->moveStar();
	}
}
/**
renders lines between the bullets to the screen
**/
void Background::drawBackground()
{
	backgroundColor->use();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glBegin(GL_QUADS);
		//bottom left
		glTexCoord2f(0,0);
		glVertex3f( 0,width, -1.0);

		//bottom right
		glTexCoord2f(1,0);
		glVertex3f(width,height, -1.0);
		
		//top right
		glTexCoord2f(1,1);
		glVertex3f(width,0, -1.0);

		//top left
		glTexCoord2f(0,1);
		glVertex3f(0,0,-1.0);
glEnd();


	logo->use();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	glPushMatrix();
	glTranslatef(width/2,height/4,0);
	glRotatef(angle,0,0,1);
	glTranslatef(-width/2,-height/4,0);
	glBegin(GL_QUADS);
		//bottom left
		glTexCoord2f(0,0);
		glVertex3f( 25,height/2-25, -1.0);

		//bottom right
		glTexCoord2f(1,0);
		glVertex3f(width-25,height/2-25, -1.0);
		
		//top right
		glTexCoord2f(1,1);
		glVertex3f(width-25,25, -1.0);

		//top left
		glTexCoord2f(0,1);
		glVertex3f(25,25,-1.0);
	glEnd();
	glPopMatrix();

	for(int x =0;x<20;x++)
	{
		stars[x]->drawStar();
	}
}

Star::Star(float rise1,float run1,int w, int h)
{
angle = 0;
angleadd = 15.0f;
rise = rise1;
run = run1;
posx =0;
posy =0;
	starTexture = new Texture();
	starTexture->load("Data/Textures/BallGraphics/BallGameStar.tga");
}

void Star::moveStar()
{
	if(angle<360)
	{
		angle+=angleadd;
	}
	else
	{
		angle =0;
	}

 posx+=rise;
 posy+=run;
 if(posx>2000)
 {
	posx = 0;
 }
 if(posy>1500)
 {
	 posy = 0;
 }
}

void Star::drawStar()
{
	starTexture->use();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glPushMatrix();
	glTranslatef(posx+10,posy+10,0);
	glRotatef(angle,0,0,1);
	glTranslatef(-posx-10,-posy-10,0);
glBegin(GL_QUADS);
		//bottom left
		glTexCoord2f(0,0);
		glVertex3f( posx,posy+25, -1.0);

		//bottom right
		glTexCoord2f(1,0);
		glVertex3f(posx+25,posy+25, -1.0);
		
		//top right
		glTexCoord2f(1,1);
		glVertex3f(posx+25,posy, -1.0);

		//top left
		glTexCoord2f(0,1);
		glVertex3f(posx,posy,-1.0);
glEnd();
glPopMatrix();
}