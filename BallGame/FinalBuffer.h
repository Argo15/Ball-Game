#ifndef FINALBUFFER_H
#define FINALBUFFER_H

#include <windows.h>
#include <gl/glee.h>

class FinalBuffer 
{
private:
	GLuint finalTex;
	GLuint buffer;

	int width,height;

public:
	FinalBuffer(int width, int height);
	~FinalBuffer(){}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindFinalTex() {glBindTexture(GL_TEXTURE_2D, finalTex);}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif