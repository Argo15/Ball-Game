#ifndef LINEARDEPTHBUFFER_H
#define LINEARDEPTHBUFFER_H


#include <windows.h>
#include <gl/glee.h>
#include "GLSLProgram.h"
#include "GLSLShader.h"

class LinearDepthBuffer 
{
private:
	GLuint linearDepthTex;
	GLuint buffer;

	int width,height;

public:
	LinearDepthBuffer(int width, int height);
	~LinearDepthBuffer(){glDeleteFramebuffers(1,&buffer);}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindLinearDepthTex() {glBindTexture(GL_TEXTURE_2D, linearDepthTex);}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif