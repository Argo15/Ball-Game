#include "ParticleCube.h"
#include "btBulletDynamicsCommon.h"
#include <gl/glut.h>
#include "Particle.h"

ParticleCube::ParticleCube()
{
	start = NULL;
	end = NULL;
	//create the particle
	for(int x =0;x<10;x++)
	{
	particles[x] = new Particle(x);
	//add its texture
	particles[x]->addTexture("Data/Textures/BallGraphics/3.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/4.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/5.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/6.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/7.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/8.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/9.tga");

	particles[x]->addTexture("Data/Textures/BallGraphics/8.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/7.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/6.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/5.tga");
	particles[x]->addTexture("Data/Textures/BallGraphics/4.tga");
	}
}

ParticleCube::~ParticleCube()
{
delete start;
delete end;
}

void ParticleCube::nullify()
{
	start = NULL;
	end = NULL;
}

void ParticleCube::Update(btVector3* s, btVector3* e)
{
	start = s;
	end = e;
	for(int x=0;x<10;x++)
	{
		particles[x]->Update();
	}
}

void ParticleCube::Render()
{
	if(start == NULL || end == NULL)
	{
		return;
	}

		particles[0]->Render(end->getX(),end->getY(),end->getZ());
		particles[1]->Render(end->getX()+.5f,end->getY(),end->getZ());
		particles[2]->Render(end->getX()-.5f,end->getY(),end->getZ());
		particles[3]->Render(end->getX()+.5f,end->getY(),end->getZ()+.5f);
		particles[4]->Render(end->getX()-.5f,end->getY(),end->getZ()-.5f);
		particles[5]->Render(end->getX()+.5f,end->getY(),end->getZ()-.5f);
		particles[6]->Render(end->getX()-.5f,end->getY(),end->getZ()+.5f);
		particles[7]->Render(end->getX(),end->getY(),end->getZ()+.5f);
		particles[8]->Render(end->getX(),end->getY(),end->getZ()-.5f);
		particles[9]->Render(end->getX(),end->getY(),end->getZ());
}


