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
	if(angle<10)
	{
		angleadd*=-1;
	}
	if(angle>-10)
	{
		angleadd*=-1;
	}
}
/**
renders lines between the bullets to the screen
**/
void Background::drawBackground()
{
	backgroundColor->use();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
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
	glRotatef(angle,0,0,1);
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
}
