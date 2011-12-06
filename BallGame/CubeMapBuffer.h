#ifndef CUBEMAPBUFFER_H
#define CUBEMAPBUFFER_H

#include <windows.h>
#include <gl/glee.h>
#include "GLSLProgram.h"
#include "GLSLShader.h"

class CubeMapBuffer {
private:
	GLuint cubeTexture; // +X, -X, +Y, -Y, +Z, -Z, CubeMap
	GLuint buffer;
	GLuint renderbuffer;

	int width,height;

public:
	CubeMapBuffer(int resolution);
	~CubeMapBuffer() {}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() { glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	GLuint getCubeMap() {return cubeTexture;}
};

#endif