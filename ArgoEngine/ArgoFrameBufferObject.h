#ifndef ARGOFRAMEBUFFEROBJECT_H
#define ARGOFRAMEBUFFEROBJECT_H

#include <windows.h>
#include <gl/glee.h>

class ArgoFrameBufferObject
{
protected:
	GLuint texture;
	GLuint buffer;

public:
	ArgoFrameBufferObject(){}
	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}
	GLuint getBuffer() {return buffer;}
	GLuint getTexture() {return texture;}
};
#endif