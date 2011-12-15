#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "LevelMenuState.h"
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
LevelMenuState::LevelMenuState() : MenuState() {
	//seed our random function
	srand(time(NULL));

	items = new MenuItem*[5];
	items[0] = new MenuItem();
	items[0]->setDescription("Return To Main Menu");
	items[0]->texture = new Texture();
	items[0]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[0]->current=true;
	items[0]->link="MainMenuState";

	items[1] = new MenuItem();
	items[1]->setDescription("Level One");
	items[1]->texture = new Texture();
	items[1]->texture->load("Data/Textures/BallGraphics/BallGameSelectLevelOne.tga");
	items[1]->current=false;
	items[1]->link = "LevelOneState";

	items[2] = new MenuItem();
	items[2]->setDescription("Level Two");
	items[2]->texture = new Texture();
	items[2]->texture->load("Data/Textures/BallGraphics/BallGameSelectLevelTwo.tga");
	items[2]->current=false;
	items[2]->link = "LevelTwoState";

	items[3] = new MenuItem();
	items[3]->setDescription("Level Three");
	items[3]->texture = new Texture();
	items[3]->texture->load("Data/Textures/BallGraphics/BallGameSelectLevelThree.tga");
	items[3]->current=false;
	items[3]->link = "LevelThreeState";

	items[4] = new MenuItem();
	items[4]->setDescription("Level Four");
	items[4]->texture = new Texture();
	items[4]->texture->load("Data/Textures/BallGraphics/BallGameSelectLevelFour.tga");
	items[4]->current=false;
	items[4]->link = "LevelFourState";

	//create our background object
	background = new Background(width,height);
	currentItem = 0;
}
/**
deals with resizing the application
**/
void LevelMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
	background->width=w;
	background->height=h;
}

/**
called each frame, allows for you to check key presses, update logic
**/
void LevelMenuState::update(int fps) {
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
		if(currentItem<=3)
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

	background->update();

	for (int i = 0; i<5; i++) {
		items[i]->setTopLeft(width/2.5,height/2+height/8);
		items[i]->setBottomRight(width/2+width/6-25,height/2+height/3-25);
		items[i]->updateBob();
	}


}

void LevelMenuState::render() {
	glLoadIdentity();
	
	background->drawBackground();
	items[currentItem]->drawItem();
//text if menu
	glDisable(GL_TEXTURE_2D);
	if(currentItem==0)
	{
	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[currentItem]->bottomRightX+items[currentItem]->topLeftX)/2-90,(items[currentItem]->topLeftY+items[currentItem]->bottomRightY)/2);
	//draw the text to the screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)items[currentItem]->description.c_str());
	}
	glEnable(GL_TEXTURE_2D);
	MenuState::render();
}




