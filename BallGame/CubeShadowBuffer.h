#ifndef CUBESHADOWBUFFER_H
#define CUBESHADOWBUFFER_H

#include <windows.h>
#include <gl/glee.h>
#include "GLSLProgram.h"
#include "GLSLShader.h"

class CubeShadowBuffer {
private:
	GLSLProgram *cubeShadowProg;
	GLuint cubeTexture; // +X, -X, +Y, -Y, +Z, -Z, CubeMap
	GLuint buffer;
	GLuint renderbuffer;

	int width,height;

public:
	CubeShadowBuffer(int resolution);
	~CubeShadowBuffer() {}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);cubeShadowProg->use();}
	void unbind() { glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);cubeShadowProg->disable();}

	GLSLProgram *getCubeProgram() {return cubeShadowProg;}

	GLuint getCubeMap() {return cubeTexture;}
};

#endif