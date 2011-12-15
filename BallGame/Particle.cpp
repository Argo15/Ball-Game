//particle.cpp renders a plane orthogonal to the camera at a specified location with
//animation textures
#include "Particle.h"
#include "btBulletDynamicsCommon.h"
#include "Camera.h"
#include <gl/glut.h>
#include "Texture.h"
#include <vector>
using namespace std;

Particle::Particle(int frame)
{
	frameCount =0;
	currentFrame =frame;
}

void Particle::Update()
{
	if(currentFrame>frames.size()-1)
	{
		currentFrame =0;
	}


if(frameCount >= 10)
{
	if(currentFrame<frames.size()-1)
	{
		currentFrame++;
	}
	else
	{
		currentFrame =0;
	}
	frameCount =0;
}
frameCount++;

}

void Particle::Render(float x, float y, float z, GLSLProgram *program)
{
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_MATERIAL);
	glActiveTexture(GL_TEXTURE0);

	frames[currentFrame]->use();

	if (program == 0) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1,1,1,1);
	} else {
		glDisable(GL_BLEND);
		program->sendUniform("tex",0);
	}

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	

	glPushMatrix();
	billboardSphericalBegin(x,y,z);
	glScalef(1,1,1);
	
	glBegin(GL_QUADS);
		//bottom left
		glTexCoord2f(0,0);
		glVertex3f( -.5, -.5, 0);

		//bottom right
		glTexCoord2f(1,0);
		glVertex3f(.5,-.5,0);
		
		//top right
		glTexCoord2f(1,1);
		glVertex3f(.5,.5,0);

		//top left
		glTexCoord2f(0,1);
		glVertex3f(-.5,.5,0);
	glEnd();
	glPopMatrix();
}

void Particle::billboardSphericalBegin(float x, float y, float z) {
	
	float modelview[16];
	int i,j;

	glTranslatef(x,y,z);

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

	// undo all rotations
	// beware all scaling is lost as well 
	for( i=0; i<3; i++ ) 
	    for( j=0; j<3; j++ ) {
		if ( i==j )
		    modelview[i*4+j] = 1.0;
		else
		    modelview[i*4+j] = 0.0;
	    }

	// set the modelview with no rotations
	glLoadMatrixf(modelview);
}

void Particle::addTexture(string location)
{
	frames.push_back(new Texture());
	frames.back()->load((const char*)location.c_str());
}