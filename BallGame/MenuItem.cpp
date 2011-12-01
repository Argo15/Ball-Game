#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MenuState.h"
#include "TestLevelOne.h"
#include "TestLevelTwo.h"
#include "LevelMenuState.h"
#include "MainMenuState.h"
#include "FunHouse.h"
#include "Globals.h"
#include "MenuItem.h"
#include <string>
using namespace std;

/**
drawItem draws the menuItem to the screen
**/

MenuItem::MenuItem()
{
bobamount =0;
bobadd = 1;
}
void MenuItem::drawItem()
{
    texture->use();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	//draw the GL_Quads
	int bob =0;
	if(current)
	{
	//updateBob();
	bob = bobamount;
	}
	else
	{
	bob = 0;
	}
	//cout<<bob<<endl;
		
	
		glBegin(GL_QUADS);

		//bottom left
		glTexCoord2f(0,0);
		glVertex3f( topLeftX, bottomRightY+bob, -1.0);

		//bottom right
		glTexCoord2f(1,0);
		glVertex3f(bottomRightX,  bottomRightY+bob, -1.0);
		
		//top right
		glTexCoord2f(1,1);
		glVertex3f(bottomRightX, topLeftY+bob, -1.0);

		//top left
		glTexCoord2f(0,1);
		glVertex3f(topLeftX,topLeftY+bob,-1.0);


		glEnd();

	
	//set the text color to white
	//glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	//glRasterPos2f((bottomRightX+topLeftX)/2,(topLeftY+bottomRightY)/2);
	//draw the text to the screen
	//glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)description.c_str());
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
	if(link=="LevelMenuState")
	{
		Globals::GAMESTATE = new LevelMenuState();
	}
	else if(link=="GraphicsMenuState")
	{
		
	}
	else if(link =="TrophieMenuState")
	{

	}
	else if(link == "CreditsMenuState")
	{

	}
	else if(link == "MainMenuState")
	{
		Globals::GAMESTATE = new MainMenuState();
	}
	else if(link == "LevelOneState")
	{
		Globals::GAMESTATE = new TestLevelOne();
	}
	else if(link == "LevelTwoState")
	{
		Globals::GAMESTATE = new TestLevelTwo();
	}
	else if(link == "LevelThreeState")
	{
		Globals::GAMESTATE = new FunHouse();
	}
	else if(link == "LevelFourState")
	{

	}
}

void MenuItem::updateBob()
{
	bobamount += bobadd;
if(bobamount>=-10)
{
bobadd*=-1;
}
if(bobamount<=10)
{
bobadd*=-1;
}

}