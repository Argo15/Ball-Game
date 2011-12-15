#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MainMenuState.h"
#include "LevelState.h"
#include <iostream>
#include "ArgoMatrix.h"
#include "Globals.h"
#include "MenuItem.h"
#include <time.h>
#include <list>
#include "SoundManager.h"
#include <al.h>
#include <alc.h>
#include <AL/alut.h>
using namespace std;
/**
creates all the menuItems, and populates them with their data
**/
MainMenuState::MainMenuState() : MenuState() {
	//seed our random function
	srand((unsigned int)time(NULL));

	items = new MenuItem*[4];
	items[0] = new MenuItem();
	items[0]->setDescription("Select A Level");
	items[0]->texture = new Texture();
	items[0]->texture->load("Data/Textures/BallGraphics/BallGameLevels.tga");
	items[0]->current=true;
	items[0]->link="LevelMenuState";

	items[1] = new MenuItem();
	items[1]->setDescription("Change Graphics Options");
	items[1]->texture = new Texture();
	items[1]->texture->load("Data/Textures/BallGraphics/BallGameGraphics.tga");
	items[1]->current=false;
	items[1]->link = "GraphicsMenuState";

	items[2] = new MenuItem();
	items[2]->setDescription("View Achievements");
	items[2]->texture = new Texture();
	items[2]->texture->load("Data/Textures/BallGraphics/BallGameTrophies.tga");
	items[2]->current=false;
	items[2]->link = "TrophieMenuState";

	items[3] = new MenuItem();
	items[3]->setDescription("Game Credits");
	items[3]->texture = new Texture();
	items[3]->texture->load("Data/Textures/BallGraphics/BallGameCredits.tga");
	items[3]->current=false;
	items[3]->link = "CreditsMenuState";
	//create our background object
	background = new Background(width,height);
	currentItem = 0;
	
//add sounds
	ALfloat fl[3];
	fl[0]=0;
	fl[1]=0;
	fl[2]=0;
SoundManager::Instance()->updateListenerPosition(fl);
SoundManager::Instance()->addSoundSource("Data/Sound/menuMusic.wav","MenuMusic",NULL);
SoundManager::Instance()->addSoundSource("Data/Sound/menuSelect.wav","MenuSelect",NULL);
SoundManager::Instance()->addSoundSource("Data/Sound/switchMenu.wav","SwitchMenu",NULL);

SoundManager::Instance()->addSoundSource("Data/Sound/BeatLevel.wav","BeatLevel",NULL);
//start menu sound
SoundManager::Instance()->startSound("MenuMusic",false);
SoundManager::Instance()->makeLoop("MenuMusic");
SoundManager::Instance()->updateSourcePosition("MenuMusic",fl);
}
/**
deals with resizing the application
**/
void MainMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
	background->width=w;
	background->height=h;
}

/**
called each frame, allows for you to check key presses, update logic
**/
void MainMenuState::update(int fps) {
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
		if(currentItem<=(sizeof(items)/sizeof(int))+1)
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
			SoundManager::Instance()->startSound("MenuSelect",true);
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
	items[0]->setTopLeft(25.0f,height/2.0f);
	items[0]->setBottomRight(width/2.0f-25,height/2.0f + height/4.0f-25);
	
	items[1]->setTopLeft(25.0f,height/2.0f+height/4.0f);
	items[1]->setBottomRight(width/2.0f-25,height-25.0f);
	
	//second column
	items[2]->setTopLeft(width/2.0f+25,height/2.0f);
	items[2]->setBottomRight(width-25.0f,height/2.0f+height/4.0f-25);

	items[3]->setTopLeft(width/2.0f+25,height/2.0f+height/4.0f);
	items[3]->setBottomRight(width-25.0f,height-25.0f);



	background->update();
	items[0]->updateBob();
	items[1]->updateBob();
	items[2]->updateBob();
	items[3]->updateBob();

}

void MainMenuState::render() {
	glLoadIdentity();
	
	background->drawBackground();

	items[0]->drawItem();
	items[1]->drawItem();
	items[2]->drawItem();
	items[3]->drawItem();

	MenuState::render();
}




