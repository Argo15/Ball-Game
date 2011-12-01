#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "CreditsMenuState.h"
#include "LevelState.h"
#include <iostream>
#include "ArgoMatrix.h"
#include "Globals.h"
#include "MenuItem.h"
#include <time.h>
#include <list>
using namespace std;
/**
creates all the menuItems, and populates them with their data
**/
CreditsMenuState::CreditsMenuState() : MenuState() {
	//seed our random function
	srand(time(NULL));

	items = new MenuItem*[4];
	items[0] = new MenuItem();
	items[0]->setDescription("Press Enter To Return To Main Menu");
	items[0]->texture = new Texture();
	items[0]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[0]->current=true;
	items[0]->link="MainMenuState";

	items[1] = new MenuItem();
	items[1]->setDescription("Created By");
	items[1]->texture = new Texture();
	items[1]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[1]->current=false;
	items[1]->link = "MainMenuState";

	items[2] = new MenuItem();
	items[2]->setDescription("Bill Crane");
	items[2]->texture = new Texture();
	items[2]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[2]->current=false;
	items[2]->link = "MainMenuState";

	items[3] = new MenuItem();
	items[3]->setDescription("Michael DeRoy");
	items[3]->texture = new Texture();
	items[3]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[3]->current=false;
	items[3]->link = "MainMenuState";

	//create our background object
	background = new Background(width,height);
	currentItem = 0;
}
/**
deals with resizing the application
**/
void CreditsMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
	background->width=w;
	background->height=h;
}

/**
called each frame, allows for you to check key presses, update logic
**/
void CreditsMenuState::update(int fps) {
	//super
	MenuState::update(fps);
	//check if w is down
	if(keys['w']&& keyDown['w']==false)
	{
		keyDown['w']=true;
		if(currentItem>0)
		{
			items[currentItem]->current = false;
			currentItem--;
			items[currentItem]->current = true;
		}
	}
	//check if s is down
	if(keys['s']&& keyDown['s']==false)
	{
		keyDown['s']=true;
		if(currentItem<=(sizeof(items)/sizeof(int))+1)
		{
			items[currentItem]->current=false;
			currentItem++;
			items[currentItem]->current=true;
		}
	}
	//check if enter key is down
		if(keys[13]&& keyDown[13]==false)
		{
			keyDown[13]=true;
			cout<<"enter down"<<endl;
			items[currentItem]->switchState();
			delete(background);
			Globals::GAMESTATE->resize(width,height);
			return;
		}
	//return keys to be unpressed if they are not pressed
	if(!keys['w'])
	{
	keyDown['w']=false;
	}
	if(!keys['s'])
	{
	keyDown['s']=false;
	}
	if(!keys[13])
	{
	keyDown[13]=false;
	}
	//Set the location of the menu items

	//first column
	items[0]->setTopLeft(width/4,height/2);
	items[0]->setBottomRight(width/2+width/4-25,height/2+height/9);
	
	items[1]->setTopLeft(width/4,height/2+height/4);
	items[1]->setBottomRight(width/2+width/4-25,height/2+height/9+height/9);

	items[2]->setTopLeft(width/4,height/2+height/4+25);
	items[2]->setBottomRight(width/2+width/4-25,height/2+height/9+height/9+25);

	items[3]->setTopLeft(width/4,height/2+height/4+50);
	items[3]->setBottomRight(width/2+width/4-25,height/2+height/9+height/9+50);



	background->update();
	items[0]->updateBob();
	items[1]->updateBob();
	items[2]->updateBob();
	items[3]->updateBob();


}

void CreditsMenuState::render() {
	glLoadIdentity();
	
	background->drawBackground();

	items[0]->drawItem();
	items[1]->drawItem();
	items[2]->drawItem();
	items[3]->drawItem();
//text if menu

	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[0]->bottomRightX+items[0]->topLeftX)/2-150,(items[0]->topLeftY+items[0]->bottomRightY)/2);
	//draw the text to the screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)items[0]->description.c_str());
for(int x =1;x<4;x++)
{
	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[x]->bottomRightX+items[x]->topLeftX)/2-60,(items[x]->topLeftY+items[x]->bottomRightY)/2);
	//draw the text to the screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)items[x]->description.c_str());
}

	MenuState::render();
}




