#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MenuState.h"
#include "TestLevelOne.h"
#include "TestLevelTwo.h"
#include "LevelMenuState.h"
#include "CreditsMenuState.h"
#include "GraphicsMenuState.h"
#include "TrophieMenuState.h"
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
		Globals::GAMESTATE = new GraphicsMenuState();
	}
	else if(link =="TrophieMenuState")
	{
		Globals::GAMESTATE = new TrophieMenuState();
	}
	else if(link == "CreditsMenuState")
	{
		Globals::GAMESTATE = new CreditsMenuState();
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
	else if(link == "GOglow")
	{
		if(Globals::glowEnabled==true)
		{
			Globals::glowEnabled = false;
		}
		else
		{
			Globals::glowEnabled = true;
		}
	}
	else if(link == "GOmotionBlur")
	{
		if(Globals::motionblur==true)
		{
			Globals::motionblur = false;
		}
		else
		{
			Globals::motionblur = true;
		}

	}
	else if(link == "GOambient")
	{
		if(Globals::ambientOcclusion==true)
		{
			Globals::ambientOcclusion = false;
		}
		else
		{
			Globals::ambientOcclusion = true;
		}
	}
	else if(link == "GOshadows")
	{
		if(Globals::highQualityShadows==true)
		{
			Globals::highQualityShadows = false;
		}
		else
		{
			Globals::highQualityShadows = true;
		}
	}
	else if(link == "TONE")
	{
		if(Globals::LevelOnePassed==true)
		{
			Globals::LevelOnePassed = false;
		}
		else
		{
			Globals::LevelOnePassed = true;
		}
	}
	else if(link == "TTWO")
	{
		if(Globals::LevelTwoPassed==true)
		{
			Globals::LevelTwoPassed = false;
		}
		else
		{
			Globals::LevelTwoPassed = true;
		}
	}
		else if(link == "TTHREE")
	{
		if(Globals::LevelThreePassed==true)
		{
			Globals::LevelThreePassed = false;
		}
		else
		{
			Globals::LevelThreePassed = true;
		}
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