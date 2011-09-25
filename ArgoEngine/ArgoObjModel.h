#ifndef ARGOOBJMODeL_H
#define ARGOOBJMODeL_H

#include "ArgoStaticModel.h"
#include <QGLWidget>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <QtCore>

class ArgoObjModel : public ArgoStaticModel
{
public:
	ArgoObjModel(){}
	~ArgoObjModel(){}
	bool load(QString filename);
};

#endif