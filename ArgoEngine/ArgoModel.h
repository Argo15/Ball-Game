#ifndef ARGOMODeL_H
#define ARGOMODeL_H

#include <QGLWidget>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

class ArgoModel 
{
protected:
	int numTriangles;
	float center[3];
	float radius;
	float *physTriangles;

	bool loaded;

	QString location;
	QString *name;
public:
	ArgoModel(){}
	~ArgoModel(){}
	virtual bool load(QString filename) = 0;
	virtual void draw() = 0;
	virtual void drawSelection() = 0;
	virtual void remove() = 0;
	float *getCenter() {return center;}
	float getRadius() {
		return radius;
	}

	QString getLocation() {return location;}
	QString *getName() {return name;}
	void setName(QString newName) {*name=newName;}

	float *getPhysTriangles() {return physTriangles;}
	int getNumTriangles(){return numTriangles;}
};

#endif