#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "GraphicsMenuState.h"
#include "LevelState.h"
#include <iostream>
#include "ArgoMatrix.h"
#include "Globals.h"
#include "MenuItem.h"
#include <time.h>
#include <list>
#include "SoundManager.h"
using namespace std;
/**
creates all the menuItems, and populates them with their data
**/
GraphicsMenuState::GraphicsMenuState() : MenuState() {
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
	items[1]->setDescription("Glow ");
	items[1]->texture = new Texture();
	items[1]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[1]->current=false;
	items[1]->link = "GOglow";

	items[2] = new MenuItem();
	items[2]->setDescription("Motion Blur ");
	items[2]->texture = new Texture();
	items[2]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[2]->current=false;
	items[2]->link = "GOmotionBlur";

	items[3] = new MenuItem();
	items[3]->setDescription("Ambient Occlusion ");
	items[3]->texture = new Texture();
	items[3]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[3]->current=false;
	items[3]->link = "GOambient";

	items[4] = new MenuItem();
	items[4]->setDescription("High Quality Shadows ");
	items[4]->texture = new Texture();
	items[4]->texture->load("Data/Textures/BallGraphics/BallGameSelect.tga");
	items[4]->current=false;
	items[4]->link = "GOshadows";

	//create our background object
	background = new Background(width,height);
	currentItem = 0;
}
/**
deals with resizing the application
**/
void GraphicsMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
	background->width=w;
	background->height=h;
}

/**
called each frame, allows for you to check key presses, update logic
**/
void GraphicsMenuState::update(int fps) {
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
			SoundManager::Instance()->startSound("SwitchMenu",true);
		}
	}
	//check if s is down
	if(keys['s']&& keyDown['s']==false)
	{
		keyDown['s']=true;
		if(currentItem<4)
		{
			items[currentItem]->current=false;
			currentItem++;
			items[currentItem]->current=true;
			SoundManager::Instance()->startSound("SwitchMenu",true);
		}
	}
	//check if enter key is down
		if(keys[13]&& keyDown[13]==false)
		{
			keyDown[13]=true;
			cout<<"enter down"<<endl;
			SoundManager::Instance()->startSound("MenuSelect",true);
			items[currentItem]->switchState();
//			delete(background);
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

	items[4]->setTopLeft(width/4,height/2+height/4+75);
	items[4]->setBottomRight(width/2+width/4-25,height/2+height/9+height/9+75);

	background->update();
	items[0]->updateBob();
	items[1]->updateBob();
	items[2]->updateBob();
	items[3]->updateBob();
	items[4]->updateBob();


}

void GraphicsMenuState::render() {
	glLoadIdentity();
	
	background->drawBackground();

	items[0]->drawItem();
	items[1]->drawItem();
	items[2]->drawItem();
	items[3]->drawItem();
	items[4]->drawItem();
//text if menu
	glDisable(GL_TEXTURE_2D);
	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[0]->bottomRightX+items[0]->topLeftX)/2-90,(items[0]->topLeftY+items[0]->bottomRightY)/2);
	//draw the text to the screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)items[0]->description.c_str());
	string on = "ON";
	string off = "OFF";


	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[1]->bottomRightX+items[1]->topLeftX)/2-90,(items[1]->topLeftY+items[1]->bottomRightY)/2);
	//draw the text to the screen
	if(Globals::glowEnabled == true)
	{
		string write = items[1]->description.c_str() + on;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}
	else
	{
		string write = items[1]->description.c_str() + off;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}
	

	//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[2]->bottomRightX+items[2]->topLeftX)/2-90,(items[2]->topLeftY+items[2]->bottomRightY)/2);
	//draw the text to the screen
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)items[2]->description.c_str());
	if(Globals::motionblur == true)
	{
		string write = items[2]->description.c_str() + on;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}
	else
	{
		string write = items[2]->description.c_str() + off;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}

		//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[3]->bottomRightX+items[3]->topLeftX)/2-90,(items[3]->topLeftY+items[3]->bottomRightY)/2);
	//draw the text to the screen
	if(Globals::ambientOcclusion == true)
	{
		string write = items[3]->description.c_str() + on;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}
	else
	{
		string write = items[3]->description.c_str() + off;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}

		//set the text color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	//set the texts location
	glRasterPos2f((items[4]->bottomRightX+items[4]->topLeftX)/2-90,(items[4]->topLeftY+items[4]->bottomRightY)/2);
	//draw the text to the screen
	if(Globals::highQualityShadows == true)
	{
		string write = items[4]->description.c_str() + on;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}
	else
	{
		string write = items[4]->description.c_str() + off;
		glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)write.c_str());
	}

	glEnable(GL_TEXTURE_2D);
	MenuState::render();
}




