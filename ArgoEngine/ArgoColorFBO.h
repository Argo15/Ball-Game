#ifndef ARGOCOLORFBO_H
#define ARGOCOLORFBO_H

#include <windows.h>
#include <gl/glee.h>
#include "ArgoFramebufferObject.h"

class ArgoColorFBO : public ArgoFrameBufferObject
{
private: 
	GLuint renderbuffer;

public:
	ArgoColorFBO(int wRes, int hRes);
};
#endif