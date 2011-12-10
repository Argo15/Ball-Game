#include "StartAndEnd.h"
#include "btBulletDynamicsCommon.h"
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

StartAndEnd::StartAndEnd()
{

}

//called in the update function of LevelState.cpp
void StartAndEnd::Update(btVector3* start, btVector3* end)
{
	if(startPoint == NULL || endPoint==NULL)
	{
	startPoint = *start;
	endPoint = *end;
	}
}

//called in the render function of LevelState.cpp
void StartAndEnd::Render()
{
	if(startPoint==NULL||endPoint==NULL)
	{
		return;
	}
	glutSolidSphere(50000,15,15);

	
}