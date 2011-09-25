#ifndef ARGOLIGHTBUFFER_H
#define ARGOLIGHTBUFFER_H

#include <windows.h>
#include <gl/glee.h>
#include "GLSLProgram.h"
#include "GLSLShader.h"

class ArgoLightBuffer 
{
private:
	GLSLProgram *dLightProg;
	GLSLProgram *pLightProg;
	GLuint lightTex;
	GLuint specTex;
	GLuint buffer;

	int width,height;

public:
	ArgoLightBuffer(int width, int height);
	~ArgoLightBuffer(){}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() { glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindLightTex() {glBindTexture(GL_TEXTURE_2D, lightTex);}
	void bindSpecTex() {glBindTexture(GL_TEXTURE_2D, specTex);}

	GLSLProgram *getDLightProgram() {return dLightProg;}
	GLSLProgram *getPLightProgram() {return pLightProg;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif