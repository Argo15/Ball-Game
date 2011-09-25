#ifndef ARGOGBUFFER_H
#define ARGOGBUFFER_H

#include <windows.h>
#include <gl/glee.h>

#include "GLSLProgram.h"
#include "GLSLShader.h"

class ArgoGBuffer 
{
private:
	GLSLProgram *gBufferProg;
	GLuint depthTex;
	GLuint normalTex;
	GLuint colorTex;
	GLuint glowTex;
	GLuint buffer;

	int width,height;

public:
	ArgoGBuffer(int width, int height);
	~ArgoGBuffer(){}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer); gBufferProg->use();}
	void unbind() {gBufferProg->disable(); glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindDepthTex() {glBindTexture(GL_TEXTURE_2D, depthTex);}
	void bindNormalTex() {glBindTexture(GL_TEXTURE_2D, normalTex);}
	void bindColorTex() {glBindTexture(GL_TEXTURE_2D, colorTex);}
	void bindGlowTex() {glBindTexture(GL_TEXTURE_2D, glowTex);}

	GLuint getGlowTex() {return glowTex;}

	GLSLProgram *getProgram() {return gBufferProg;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif