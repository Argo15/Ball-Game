#ifndef ARGOLINEARDEPTHBUFFER_H
#define ARGOLINEARDEPTHBUFFER_H


#include <windows.h>
#include <gl/glee.h>

#include "GLSLProgram.h"
#include "GLSLShader.h"

class ArgoLinearDepthBuffer 
{
private:
	GLSLProgram *depthProg;
	GLuint linearDepthTex;
	GLuint buffer;

	int width,height;

public:
	ArgoLinearDepthBuffer(int width, int height);
	~ArgoLinearDepthBuffer(){}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer); depthProg->use();}
	void unbind() {depthProg->disable(); glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindLinearDepthTex() {glBindTexture(GL_TEXTURE_2D, linearDepthTex);}

	GLSLProgram *getDepthProgram() {return depthProg;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif