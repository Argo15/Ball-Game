#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#include <windows.h>
#include <gl/glee.h>

class DepthBuffer
{
protected:
	GLuint texture;
	GLuint buffer;

public:
	DepthBuffer(int width, int height);
	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}
	GLuint getBuffer() {return buffer;}
	GLuint getTexture() {return texture;}
};
#endif