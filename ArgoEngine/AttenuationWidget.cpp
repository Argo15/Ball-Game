#include "AttenuationWidget.h"

AttenuationWidget::AttenuationWidget(QWidget *parent,QGLWidget *shared)
 : QGLWidget(parent,shared)
{
}

void AttenuationWidget::initializeGL()
{
	glClearColor(1.0f,1.0f,1.0f,0.0f);
	view = new ArgoView();
}

void AttenuationWidget::resizeGL(int width, int height)
{
	view->viewport(0,0,width,height);
	view->set2D(0.0,1.0,0.0,1.0,-1.0,1.0);
}

void AttenuationWidget::paintGL()
{
	view->use3D(false);
	glLineWidth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	for (float i=0.0;i<=1.0;i+=0.05) {
		glVertex2f(i,1.0-pow(i,attenuation));
	}
	glEnd();
	glFlush();
}