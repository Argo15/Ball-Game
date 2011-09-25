#ifndef ARGOSTATICMODeL_H
#define ARGOSTATICMODeL_H

#include "ArgoModel.h"

class ArgoStaticModel : public ArgoModel
{
protected:
	GLuint bufferID;
public:
	ArgoStaticModel(){}
	~ArgoStaticModel(){}
	virtual bool load(QString filename) = 0;
	void remove() { glDeleteBuffersARB(1, &bufferID); }
	void draw();
	void drawSelection();
};

#endif