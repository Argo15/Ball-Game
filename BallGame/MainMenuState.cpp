#define PI 3.14159;

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "MainMenuState.h"
#include "LevelState.h"
#include <iostream>
#include "Background.h"
#include "ArgoMatrix.h"
#include <time.h>
#include <list>
using namespace std;



// init
int currentItem;
MainMenuState::MainMenuState() : MenuState() {
	width = 500;
	height = 500;
	srand(time(NULL));
	for(int x =0 ; x<256;x++)
	{
	keyDown[x]=false;
	cout<<x<<endl;
	}

	items = new MenuItem*[2];
	items[0] = new MenuItem();
	items[0]->setDescription("Play Level 1!!!!!!!!!!!!!!!!!");
	items[0]->texture = new Texture();
	items[0]->texture->load("Data/Textures/TGA/select.tga");
	items[0]->current=true;

	items[1] = new MenuItem();
	items[1]->setDescription("Play Level 2!!!!!!!!!!!!!!!!!");
	items[1]->texture = new Texture();
	items[1]->texture->load("Data/Textures/TGA/select.tga");
	items[1]->current=false;

	background = new Background(width,height);
	currentItem = 0;


	

}

void MainMenuState::resize(int w, int h) {
	MenuState::resize(w, h);
	background->width=w;
	background->height=h;
	cout<<w<<endl;
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
		GameState::GAMESTATE->resize(width,height);
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


	items[0]->setTopLeft(25,25);
	items[0]->setBottomRight(width-25,50);


	
	items[1]->setTopLeft(25,75);
	items[1]->setBottomRight(width-25,100);

	background->update();

}

void MainMenuState::render() {
	glLoadIdentity();
	
	background->drawBackground();

	items[0]->drawItem();
	items[1]->drawItem();

	MenuState::render();
}

Background::Background(int w, int h)
{
	width=w;
	height=h;
	for(int x=0;x<sizeof(bullets)/sizeof(int);x++)
	{
   	bullets[x]=new Bullet((rand()/double(RAND_MAX))*500,(rand()/double(RAND_MAX))*500,(rand()/double(RAND_MAX))*7,(rand()/double(RAND_MAX))*7);
	}
}

void Background::update()
{
for(int r=0;r<sizeof(bullets)/sizeof(int);r++)
	{
		bullets[r]->position += bullets[r]->velocity;
		if(bullets[r]->position[0]<=0)
		{
			bullets[r]->position[0]=1;
			bullets[r]->velocity[0]*=-1;
		}
		if(bullets[r]->position[0]>=width)
		{
			bullets[r]->position[0]=width-1;
			bullets[r]->velocity[0]*=-1;
		}
		if(bullets[r]->position[1]<=0)
		{
			bullets[r]->position[1]=1;
			bullets[r]->velocity[1]*=-1;
		}
		if(bullets[r]->position[1]>=height)
		{
			bullets[r]->position[1]=height-1;
			bullets[r]->velocity[1]*=-1;
		}
	}
	for(int i = 0;i<sizeof(bullets)/sizeof(int);i++)
	{
		for(int j=0;j<sizeof(bullets)/sizeof(int);j++)
		{
			int xi = bullets[i]->position[0];
			int yi = bullets[i]->position[1];
			int xj = bullets[j]->position[0];
			int yj = bullets[j]->position[1];

			lineList.push_back(new ArgoVector4((float)xi,(float)yi,(float)xj,(float)yj));
			
		}
	}



}

Background::Background()
{

}
void Background::drawBackground()
{
	glColor4f(1.0, 1.0, 1.0,0.2);

	for(list<ArgoVector4*>::iterator it = lineList.begin();it!=lineList.end();it++)
	{

			int xi = (*it)[0][0];
			int yi = (*it)[0][1];
			int xj = (*it)[0][2];
			int yj = (*it)[0][3];
			glBegin(GL_LINES);
			glVertex3f(xi,yi,-5);
			glVertex3f(xj,yj,-5);
			glEnd();
	}

	//draw the balls
	/*
	for(int r=0;r<sizeof(bullets)/sizeof(int);r++)
	{
	glPushMatrix();
	int x = bullets[r]->position[0];
	int y = bullets[r]->position[1];
	cout<<x<<" "<<y<<endl;
	glTranslatef(x,y,-5);
	glutSolidSphere(10,20,20);
	glPopMatrix();
	}
	*/
}

Bullet::Bullet(int x,int y, int velx, int vely)
{
	position.set(x,y,0);
	velocity.set(velx,vely,0.0f);
}

