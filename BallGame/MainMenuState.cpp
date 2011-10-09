#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MainMenuState.h"
#include "LevelState.h"
#include <iostream>
using namespace std;

// init
int currentItem;
MainMenuState::MainMenuState() : MenuState() {
	for(int x =0 ; x<256;x++)
	{
	keyDown[x]=false;
	cout<<x<<endl;
	}

	background = new Texture();
	background->load("Data/Textures/TGA/Background.tga");
	currentItem = 0;

	items = new MenuItem*[2];
	items[0] = new MenuItem();
	items[0]->setTopLeft(0.02f,0.96f);
	items[0]->setBottomRight(0.98f,0.90f);
	items[0]->setDescription("Play Level 1!!!!!!!!!!!!!!!!!");
	items[0]->texture = new Texture();
	items[0]->texture->load("Data/Textures/TGA/select.tga");
	items[0]->current=true;
	//items[0]->setButtonLink(new LevelState());

	items[1] = new MenuItem();
	items[1]->setTopLeft(0.02f,0.88f);
	items[1]->setBottomRight(0.98f,0.82f);
	items[1]->setDescription("Play Level 2!!!!!!!!!!!!!!!!!");
	items[1]->texture = new Texture();
	items[1]->texture->load("Data/Textures/TGA/select.tga");
	items[1]->current=false;
	//items[1]->setButtonLink(new LevelState());

}

void MainMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
}


void MainMenuState::update(int fps) {
	MenuState::update(fps);
//w down
	if(keys['w']&& keyDown['w']==false)
	{
		keyDown['w']=true;
		cout<<"w down"<<endl;
		if(currentItem>0)
		{
			items[currentItem]->current = false;
			currentItem--;
			items[currentItem]->current = true;
		}
	}
//s key
	if(keys['s']&& keyDown['s']==false)
	{
		keyDown['s']=true;
		cout<<"s down"<<endl;
		if(currentItem<sizeof(items) / sizeof(int))
		{
			items[currentItem]->current=false;
			currentItem++;
			items[currentItem]->current=true;
		}
	}
//enter key
		if(keys[13]&& keyDown[13]==false)
	{
		keyDown[13]=true;
		cout<<"enter down"<<endl;
		items[currentItem]->switchState();
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
}

void MainMenuState::render() {
	glLoadIdentity();
	
	drawBackground();

	items[0]->drawItem();
	items[1]->drawItem();

	MenuState::render();
}

void MainMenuState::drawBackground()
{
	background->use();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(1,1);	glVertex3f(1.0, 1.0, -9.0);
	glTexCoord2f(1,0);	glVertex3f(1.0,  0.0, -9.0);
	glTexCoord2f(0,0);	glVertex3f( 0.0, 0.0, -9.0);
	glTexCoord2f(0,1);	glVertex3f(0.0,1.0,-9.0);
	glEnd();
}

