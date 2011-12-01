#ifndef LIGHTBUFFER_H
#define LIGHTBUFFER_H

#include <windows.h>
#include <gl/glee.h>
#include "GLSLProgram.h"
#include "GLSLShader.h"

class LightBuffer 
{
private:
	GLuint lightTex;
	GLuint specTex;
	GLuint buffer;

	int width,height;

public:
	LightBuffer(int width, int height);
	~LightBuffer(){glDeleteFramebuffers(1,&buffer);}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() { glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindLightTex() {glBindTexture(GL_TEXTURE_2D, lightTex);}
	void bindSpecTex() {glBindTexture(GL_TEXTURE_2D, specTex);}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif