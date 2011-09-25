#ifndef ARGOFINALBUFFER_H
#define ARGOFINALBUFFER_H

#include <windows.h>
#include <gl/glee.h>

#include "GLSLProgram.h"
#include "GLSLShader.h"

class ArgoFinalBuffer 
{
private:
	GLSLProgram *finalProg;
	GLuint finalTex;
	GLuint buffer;

	int width,height;

public:
	ArgoFinalBuffer(int width, int height);
	~ArgoFinalBuffer(){}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer); finalProg->use();}
	void unbind() {finalProg->disable(); glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindFinalTex() {glBindTexture(GL_TEXTURE_2D, finalTex);}

	GLSLProgram *getFinalProgram() {return finalProg;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif