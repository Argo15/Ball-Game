#ifndef ARGODePTHFbO_H
#define ARGODePTHFbO_H

#include <windows.h>
#include <gl/glee.h>
#include "ArgoFramebufferObject.h"

class ArgoDepthFBO : public ArgoFrameBufferObject
{
public:
	ArgoDepthFBO(int wRes, int hRes);
};
#endif