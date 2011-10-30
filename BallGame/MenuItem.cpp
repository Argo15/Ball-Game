#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MenuState.h"
#include "TestLevelOne.h"
#include "FunHouse.h"
#include "Globals.h"
#include "MenuItem.h"
#include <string>
using namespace std;

/**
drawItem draws the menuItem to the screen
**/
void MenuItem::drawItem()
{
    texture->use();
	glBegin(GL_QUADS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//if this is the current Item color it green, else color it black
	if(current==true)
	{
		glColor4f(0.0,0.5,0.0,0.9);
	}
	else
	{
		glColor4f(0.0,0.5,0.0,0.4);
	}
	//draw the GL_Quads
		glTexCoord2f(bottomRightX,topLeftY);glVertex3f(bottomRightX, topLeftY, -1.0);
		glTexCoord2f(bottomRightX,bottomRightY);glVertex3f(bottomRightX,  bottomRightY, -1.0);
		glTexCoord2f(topLeftX,bottomRightY);glVertex3f( topLeftX, bottomRightY, -1.0);
		glTexCoord2f(topLeftX,topLeftY);glVertex3f(topLeftX,topLeftY,-1.0);
	glEnd();
	
	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((bottomRightX+topLeftX)/2,(topLeftY+bottomRightY)/2);
	//draw the text to the screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)description.c_str());
}

/**
sets the topleft point of the Item
**/
void MenuItem::setTopLeft(float x, float y)
{
	topLeftX = x;
	topLeftY = y;
}
/**
sets the bottom right point of the Item
**/
void MenuItem::setBottomRight(float x, float y)
{
	bottomRightX = x;
	bottomRightY = y;
}
/**
sets the text to be displayed
**/
void MenuItem::setDescription(string desc)
{
	description = desc;
}
/**
sets the pointer to a gamestate
**/
void MenuItem::setButtonLink(GameState* link)
{
	buttonLink = link;
}
/**
switches the state to the linked state
**/
void MenuItem::switchState()
{
	Globals::GAMESTATE = new TestLevelOne();
}