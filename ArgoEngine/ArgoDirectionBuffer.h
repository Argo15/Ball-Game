#ifndef ARGODIRECTIONBUFFER_H
#define ARGODIRECTIONBUFFER_H

#include <windows.h>
#include <gl/glee.h>

#include "GLSLProgram.h"
#include "GLSLShader.h"

class ArgoDirectionBuffer {
private:
	GLSLProgram *directionProg;
	GLuint directionTex;
	GLuint buffer;

	int width,height;

public:
	ArgoDirectionBuffer(int width, int height);
	~ArgoDirectionBuffer(){}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer); directionProg->use();}
	void unbind() {directionProg->disable(); glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindDirectionTex() {glBindTexture(GL_TEXTURE_2D, directionTex);}

	GLSLProgram *getDirectionProgram() {return directionProg;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif

