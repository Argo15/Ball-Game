#ifndef ARGOAOBJMODEL_H
#define ARGOAOBJMODEL_H

#include "ArgoStaticModel.h"
#include <QGLWidget>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <QtCore>
#include <iostream>
#include <fstream>
using namespace std;

class ArgoAObjModel : public ArgoStaticModel
{
public:
	ArgoAObjModel(){}
	~ArgoAObjModel(){}
	bool load(QString filename);
};

#endif