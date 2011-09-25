#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include "ArgoOBJModel.h"
#include "ArgoTextureManager.h"
#include "ArgoMaterialManager.h"
#include "ArgoModelManager.h"
#include "GLSLProgram.h"
#include "GLSLShader.h"
#include "ArgoCamera.h"
#include "ArgoView.h"
using namespace std;

class ModelWidget : public QGLWidget
{
    Q_OBJECT

private:
	QString *material;
	QString *model;

	ArgoCamera *camera;
	ArgoView *view;
	float cameraDist;

	GLSLProgram *glslProgram;

	void shaderPaint();
	void shaderlessPaint();

protected:
    void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

public:
	ModelWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0);
	void setMaterial(QString *name) {material=name;}
	void setModel(QString *name);
};

#endif