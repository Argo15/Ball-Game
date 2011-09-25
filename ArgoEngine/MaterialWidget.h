#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include "ArgoAOBJModel.h"
#include "ArgoTextureManager.h"
#include "ArgoMaterialManager.h"
#include "GLSLProgram.h"
#include "GLSLShader.h"
#include "ArgoView.h"
using namespace std;

class MaterialWidget : public QGLWidget
{
    Q_OBJECT

private:
	QString *material;
	ArgoModel *sphereModel;

	ArgoView *view;

	GLSLProgram *glslProgram;

protected:
    void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

public:
	MaterialWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0);
	void setMaterial(QString *name) {material=name;}

};

#endif